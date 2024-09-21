/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include "Board.h"
#include <iostream>
#include <thread>

#pragma warning(disable: 4996)

using std::cout;
using std::endl;
using std::string;


void main()
{
	srand(time_t(NULL));

	// Initializing board structure
	Board* chessBoard = new Board();

	// Getting the attributes of the chess board
	Piece*** boardArray = chessBoard->getBoard();
	bool currentPlayer = chessBoard->getCurrentPlayer();

	// X and Y coordinates for the source and destination
	int sourceX, sourceY, destX, destY;

	// Variable to hold the code
	int code;

	// C string to hold the response code
	char responseCode[2] = { '\0' };

	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	// Copying the board into the string to send
	strcpy_s(msgToGraphics, BOARD);
	
	// Send the board string
	p.sendMessageToGraphics(msgToGraphics);  

	// Get initial message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// Updating the current player variable
		currentPlayer = chessBoard->getCurrentPlayer();

		// Decode the message into x and y coordinates
		sourceX = msgFromGraphics[0] - A; 
		sourceY = SIZE - (msgFromGraphics[1] - ZERO);
		destX = msgFromGraphics[2] - A;
		destY = SIZE - (msgFromGraphics[3] - ZERO);

		// Attempting to move the piece
		code = boardArray[sourceY][sourceX]->checkMove(sourceX, sourceY, destX, destY, boardArray, currentPlayer);

		// If the piece was moved
		if (code == 0 || code == 1)
		{
			// Printing the board in the terminal
			chessBoard->printBoard();

			// Change the current player
			chessBoard->changeCurrentPlayer();
		}

		// Turning the integer into its char value
		code += ZERO;

		// Placing it as the response code
		responseCode[0] = code;

		// Placing a null terminating character
		responseCode[1] = '\0';

		// YOUR CODE
		strcpy_s(msgToGraphics, 2, responseCode); // msgToGraphics should contain the result of the operation

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}
#pragma once

#include <string>
#include "Constants.h"
#include <iostream>

class Piece
{
protected:
	// Protected attributes
	// Piece's colour (false/0 = white, true/1 = black)
	int _colour;

	// Piece's type (King, Bishop, Knight, etc...)
	char _type;

public:
	// Public methods
	// Constructor
	Piece(bool colour, char type);

	// Getters
	bool getColour() const; // Colour Getter
	char getType() const; // Type Getter

	// Setters
	void setColour(bool colour); // Colour Setter
	void setType(char type); // Type Setter

	// Methods
	virtual int checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const = 0; // Method checks if the movement passes all necessary tests
	virtual int checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const = 0; // Method checks if there is a piece in the path to the new location
	virtual int checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const = 0; // Method checks if the movement is legal

	static bool checkSourceAndDest(int& sourceX, int& sourceY, int& destX, int& destY); // Method makes sure the source and destination are within the board
	static bool checkIfMoves(int& sourceX, int& sourceY, int& destX, int& destY); // Method checks if source and destination are the same
	static int handlePositionErrors(int& sourceX, int& sourceY, int& destX, int& destY); // Method uses the previous 2 methods and returns the error code
	static int canMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer); // Method checks if the piece can move into the old position
	static int move(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer); // Method moves the piece
	static bool isChecked(Piece*** board, bool& currentPlayer); // Method checks if the current player is checked
	static int findKing(Piece*** board, int* xCoordinate, int* yCoordinate, bool& colour); // Method finds the king of the given colour
};
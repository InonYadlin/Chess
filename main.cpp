#include "Board.h"

int main(void)
{

    Board* chessBoard = new Board();
    std::string movement = "";
    int sourceX = 0;
    int sourceY = 0;
    int destX = 0;
    int destY = 0;
    int code = 0;
    Piece*** boardArray = chessBoard->getBoard();
    bool currentPlayer;

    while (true)
    {
        currentPlayer = chessBoard->getCurrentPlayer();
        chessBoard->printBoard();
        if (currentPlayer)
        {
            std::cout << "Current player: BLACK\n";
        }
        else
        {
            std::cout << "Current player: WHITE\n";
        }
        std::cout << "Choose your move: ";
        getline(std::cin, movement);
        // Decode the message into x and y coordinates
        sourceX = movement[0] - A;
        sourceY = SIZE - (movement[1] - ZERO);
        destX = movement[2] - A;
        destY = SIZE - (movement[3] - ZERO);

        // Attempting to move the piece
        code = boardArray[sourceY][sourceX]->checkMove(sourceX, sourceY, destX, destY, boardArray, currentPlayer);

        // If the piece was moved
        if (code == 0 || abs(code) == 1)
        {
            std::cout << "\nMove was successful\nSuccsess code: " << code << std::endl;
            // Change the current player
            chessBoard->changeCurrentPlayer();
        }
        else
        {
            std::cout << "\nMove was unsuccessful\nError code: " << code << std::endl;
        }

    }


    return 0;
}
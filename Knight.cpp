#include "Knight.h"

/** Constructor */
Knight::Knight(bool colour) : Piece(colour, KNIGHT) {}

/** Method to check of the piece can move to the designated location */
int Knight::checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const
{
    // Checking for position errors 
    int temp = Piece::handlePositionErrors(sourceX, sourceY, destX, destY);

    // If the value returned is not -1 (signifies a legal move)
    if (temp != -1)
    {
        // Return the error code
        return temp;
    }

    // Checking if the player can move to the designated position
    temp = Piece::canMove(sourceX, sourceY, destX, destY, board, currentPlayer);

    // If the value returned is not -1 (signifies a legal move)
    if (temp != -1)
    {
        // Return the error code
        return temp;
    }

    // Checking if the move is legal
    temp = this->checkIllegalMove(sourceX, sourceY, destX, destY);

    // If the value returned is not -1 (signifies a legal move)
    if (temp != -1)
    {
        // Return the error code
        return temp;
    }
    temp = this->checkPath(sourceX, sourceY, destX, destY, board);
    if (!temp)
    {
        // Return the error code
        return 6;
    }

    // If all checks were passed move the piece
    temp = Piece::move(sourceX, sourceY, destX, destY, board, currentPlayer);

    // If the error code isn't 4
    if (temp != 4)
    {
        // Place an EmptyBoard object inside the source position
        board[sourceY][sourceX] = new EmptyPiece(WHITE);
    }

    // Return the code from the move method
    return temp;
}

/** Method which checks the path */
int Knight::checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const
{
    // Inon's magical Knight formula 
    int t1 = abs(sourceY - destY);
    int t2 = abs(sourceX - destX);
    return ((t1 != t2) && (((t1 == 2) && (t2 == 1)) || ((t1 == 1) && (t2 == 2))));
}

/** Checking if the move is legal */
int Knight::checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const
{
	// Checking if the movement is legal
	if ((sourceX == destX) || (sourceY == destY))
	{
		return 6;
	}

	// Otherwise, proceeding as intended
	return -1;
}

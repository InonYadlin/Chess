#include "Bishop.h"

/** Bishop constructor */
Bishop::Bishop(bool colour) : Piece(colour, BISHOP) {}

/** Method to check if we can move the piece*/
int Bishop::checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const
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

	// Checking the path of the piece
	temp = this->checkPath(sourceX, sourceY, destX, destY, board);

	// If the value returned is not -1 (signifies a legal move)
	if (temp != -1)
	{
		// Return the error code
		return temp;
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

/** Method checks if there is a piece in the path to the new location*/
int Bishop::checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const
{
	// Getting the movement directions
	int directionX = this->getDirection(sourceX, destX);
	int directionY = this->getDirection(sourceY, destY);

	// Creating loop variables
	int i = sourceY - directionY;
	int j = sourceX - directionX;

	// Going over the diagonal pieces
	while (i != destY && i < SIZE && i >= 0 && j != destX && j < SIZE && j >= 0)
	{
		// If the piece isn't Empty, the path is blocked
		if (board[i][j]->getType() != EMPTY)
		{
			std::cout << board[i][j]->getType() << std::endl;
			// Return the error code
			return 6;
		}

		// Changing the variable according to the x direction
		j -= directionX;

		// Changing the variable according to the y direction
		i -= directionY;
	}

    // Otherwise, return -1
    return -1;
}

/** Method checks if the movement is legal */
int Bishop::checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const
{
    // If the move isn't diagonal, return the error
    if (!(abs(sourceX - destX) == (abs(sourceY - destY))))
    {
        return 6;
    }

    // Otherwise, return -1
    return -1;
}

/** Method gets the direction of the x movement (positive or negative) */
int Bishop::getDirection(int source, int dest) const
{
	// Returning the direction
	return (source - dest) / abs(source - dest);
}
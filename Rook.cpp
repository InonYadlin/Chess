#include "Rook.h"

/** Rook constructor */
Rook::Rook(bool colour) : Piece(colour, ROOK) {}

/** Method to check if we can move the piece */
int Rook::checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const
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

/** Method to check if there is a piece in the path to the new location */
int Rook::checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const
{
	// Checking the movement axis
	bool axis = this->checkMovementAxis(sourceX, sourceY, destX, destY);

	if (axis)
	{
		int direction = this->checkMovementDirection(sourceX, destX);

		for (int i = sourceX + direction; i != destX; i += direction)
		{
			if (board[sourceY][i]->getType() != EMPTY)
			{
				return 6;
			}
		}
	}

	else
	{
		int direction = this->checkMovementDirection(sourceY, destY);

		for (int i = sourceY + direction; i != destY; i += direction)
		{
			if (board[i][sourceX]->getType() != EMPTY)
			{
				return 6;
			}
		}
	}

	return -1;
}

/** Checking if the move is legal */
int Rook::checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const
{
	// Checking if the movement is legal
	if ((sourceX == destX) == (sourceY == destY))
	{
		return 6;
	}

	// Otherwise, proceeding as intended
	return -1;
}

/** Method Checks the direction of the movement (on which axis)
* (0/false for y axis)
* (1/true for x axis)*/
bool Rook::checkMovementAxis(int& sourceX, int& sourceY, int& destX, int& destY) const
{
	return !(sourceX == destX);
}

/** Method checks the direction of the movement (positive or negative)
* (0/false for negative)
* (1/true for positive) */
int Rook::checkMovementDirection(int& source, int& dest) const
{
	return (dest - source) / abs(dest - source);
}

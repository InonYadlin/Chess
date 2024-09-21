#include "King.h"

/** King constructor */
King::King(bool colour) : Piece(colour, KING) {}

/** Method performs all tests on the king */
int King::checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const
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

/** Serves as override to allow for upcasting */
int King::checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const {return 0;}

/** Method checks if the move is legal */
int King::checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const
{
	// Getting the absolute value of the movements on each axis
	int xMovement = abs(sourceX - destX);
	int yMovement = abs(sourceY - destY);

	// If the move on each axis isn't 1 or 0, return the error 
	if (!((xMovement == 1 || xMovement == 0) && (yMovement == 1 || yMovement == 0)))
	{
		return 6;
	}

	// Otherwise, proceeding as intended
	return -1;
}

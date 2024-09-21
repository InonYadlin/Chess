#include "Pawn.h"

/** Pawn constructor */
Pawn::Pawn(bool colour) : Piece(colour, PAWN) 
{
	// Setting the first move to true
	setIsFirstMove(true);
}

/** isFirstMove Getter */
bool Pawn::getIsFirstMove() const
{
	// Returning the attribute
	return this->_isFirstMove;
}

/** isFirstMove setter */
void Pawn::setIsFirstMove(bool isFirstMove)
{
	// Settin the attribute
	this->_isFirstMove = isFirstMove;
}

int Pawn::checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const
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

/** Serves to override to allow for upcasting */
int Pawn::checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const
{
	// Absolute values of the movement
	int movementX = abs(sourceX - destX);
	int movementY = abs(sourceY - destY);

	// if the pawn is at its first move the loop will check both slots 
	if (dynamic_cast<Pawn*>(board[sourceY][sourceX])->getIsFirstMove())
	{

		// If the source and destination x are equal
		if (destX == sourceX)
		{
			// And the destination isn't empty
			if (board[destY][destX]->getType() != EMPTY)
			{
				// Return the error
				return 6;
			}

		}

		// If the movementY is more than 2
		if (movementY > 2)
		{
			// Return the error
			return 6;
		}


		// Setting the firstMove to false
		dynamic_cast<Pawn*>(board[sourceY][sourceX])->setIsFirstMove(false);

	}
	//if the pawn can only move once only the dest will be checked
	else if (sourceX == destX && board[destY][destX]->getType() != EMPTY)
	{
		return 6;
	}

	// If the x is changed by 1, and the destination is empty
	if (movementX == 1 && board[destY][destX]->getType() == EMPTY)
	{
		// Return the error
		return 6;
	}

	// If the x is by 1 and the y isn't changed by 1
	if (movementX == 1 && movementY != 1)
	{
		// Return the error
		return 6;
	}

	// Otherwise, return success
	return -1;
}

int Pawn::checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const
{
	// Absolute values of the movement
	int yMovement = abs(sourceY - destY);
	int xMovement = abs(sourceX - destX);

	// If the movement x isn't by 1 or zero, return the error
	if (xMovement != 0 && xMovement != 1)
	{
		return 6;
	}
	
	// checking if the movement is in the correct direction relative to the colour
	if (!this->getColour())
	{ 
		if (destY > sourceY)
		{
			return 6;
		}
		

	}
	else
	{
		if (destY < sourceY)
		{
			return 6;
		}

	}

	// If the movement size is supported by the first move status, return the success code
	if (this->getIsFirstMove() && yMovement <= 2)
	{
		return -1;
	}
	if (!this->getIsFirstMove() && yMovement <= 1)
	{
		return -1;
	}

	// Otherwise, return the error
	return 6;
}


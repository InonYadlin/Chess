#include "Piece.h"

/** Piece constructor */
Piece::Piece(bool colour, char type)
{
	// Setting the values
	setColour(colour);
	setType(type);
}

/** Colour getter */
bool Piece::getColour() const
{
	// Returning the colour 
	return this->_colour;
}

/** Type getter*/
char Piece::getType() const
{
	// Returning the type
	return this->_type;
}

/** Colour setter */
void Piece::setColour(bool colour)
{
	// Setting the colour 
	this->_colour = colour;
}

/** Type setter */
void Piece::setType(char type)
{
	// Setting the type
	this->_type = type;
}

/** Method checks if the x and y coordinates of both points are between 8 and 0*/
bool Piece::checkSourceAndDest(int& sourceX, int& sourceY, int& destX, int& destY)
{
	return (sourceX < SIZE && sourceX >= 0 && sourceY < SIZE && sourceY >= 0 && destX <= SIZE && destX >= 0 && destY <= SIZE && destY >= 0);
}

/** Method checks if the source and destination are identical*/
bool Piece::checkIfMoves(int& sourceX, int& sourceY, int& destX, int& destY)
{
	return ((sourceX == destX) && (sourceY == destY));
}

/** Method checks if x and y are inside the board and if the source and destination are different */
int Piece::handlePositionErrors(int& sourceX, int& sourceY, int& destX, int& destY)
{
	// Checking if the source and destination are inside the board
	if (!Piece::checkSourceAndDest(sourceX, sourceY, destX, destY))
	{
		return 5;
	}

	// Checking if the source and destination are identical
	else if (Piece::checkIfMoves(sourceX, sourceY, destX, destY))
	{
		return 7;
	}

	// If no errors popped up, continue
	return -1;
}

/** Method to check of the piece can move to the designated location */
int Piece::canMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer)
{
	// If the colour of both pieces in the given positions is equal, return the appropriate error
	if (board[sourceY][sourceX]->getColour() == board[destY][destX]->getColour() && board[destY][destX]->getType() != EMPTY)
	{
		return 3;
	}

	// Making sure the source isn't a piece, return the error
	if (board[sourceY][sourceX]->getType() == EMPTY)
	{
		return 2;
	}

	// Checking if the piece in the source position doesn't belong to the current player
	if (!(board[sourceY][sourceX]->getColour() == currentPlayer && board[sourceY][sourceX]->getType() != EMPTY))
	{
		return 2;
	}

	// Otherwise, return -1 (signifies that the move is legal and the checking can proceed)
	return -1;
}

/** Method moves the piece */
int Piece::move(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer)
{
	// Getting the source and destination
	Piece* dest = board[destY][destX];
	Piece* src = board[sourceY][sourceX];

	// Saving the original values of the destination
	bool originalColour = dest->getColour();
	char originalType = dest->getType();

	// Turning the destination into an EmptyPiece
	dest->setColour(WHITE);
	dest->setType(EMPTY);

	bool oppositePlayer = !currentPlayer;

	// Place the source piece in the destination slot
	board[destY][destX] = src;

	// Place a null pointer in the old slot
	board[sourceY][sourceX] = dest;

	// If a self check has happened
	if (isChecked(board, currentPlayer))
	{
		// Switch the positions back
		board[destY][destX] = dest;
		board[sourceY][sourceX] = src;

		// Setting the values of the destination to the original ones
		dest->setColour(originalColour);
		dest->setType(originalType);

		// Returning the error code
		return 4;
	}

	// If a check on the opposite player has occured
	else if (isChecked(board, oppositePlayer))
	{
		// Delete the destination
		delete dest;

		// Set the array in the source position to nullptr
		board[sourceY][sourceX] = nullptr;

		// Return the success message
		return 1;
	}

	// Delete the destination
	delete dest;

	// Set the array in the source position to nullptr
	board[sourceY][sourceX] = nullptr;

	// Return the success message
	return 0;
}

/** Method checks if the current player is checked */
bool Piece::isChecked(Piece*** board, bool& currentPlayer)
{
	int kingX;
	int kingY;

	// Getting the king coordinates
	Piece::findKing(board, &kingX, &kingY, currentPlayer);

	// Going over all the pieces of the opposite colour
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j]->getColour() != currentPlayer && board[i][j]->getType() != KING && board[i][j]->getType() != EMPTY)
			{
				// Checking if the move is legal
				int temp = board[i][j]->checkIllegalMove(j, i, kingX, kingY);

				// If the value returned is -1 (signifies a legal move)
				if (temp == -1)
				{
					// Checking the path of the piece
					temp = board[i][j]->checkPath(j, i, kingX, kingY, board);

					// If the value returned is -1 (signifies a legal move)
					if (temp == -1)
					{
						// Return true (is checked)
						return true;
					}
				}
			}
		}
	}

	// Otherwise, the king isn't checked, return false
	return false;
}

/** Method finds the king of the given colour */
int Piece::findKing(Piece*** board, int* xCoordinate, int* yCoordinate, bool& colour)
{
	// Loop to go over the board and find the king
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j]->getColour() == colour && board[i][j]->getType() == KING)
			{
				*xCoordinate = j;
				*yCoordinate = i;
				return -1;
			}
		}
	}

	return -1;
}

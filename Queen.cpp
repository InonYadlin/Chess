#include "Queen.h"

Queen::Queen(bool colour) : Piece(colour, QUEEN) {}

int Queen::checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const
{
	// Creating a new rook and bishop with the same colour as the queen
	Queen* currQueen = dynamic_cast<Queen*>(board[sourceY][sourceX]); // Downcasting the Piece* into a Queen*
	Rook* tempRook = new Rook(board[sourceY][sourceX]->getColour());
	Bishop* tempBishop = new Bishop(board[sourceY][sourceX]->getColour());


	// Performing the check on the rook
	board[sourceY][sourceX] = dynamic_cast<Piece*>(tempRook); // Upcasting the Rook* into a Piece*
	int temp = tempRook->checkMove(sourceX, sourceY, destX, destY, board, currentPlayer);

	// If the rook wasn't moved
	if (temp != 1 && temp != 0)
	{
		// Place the bishop in place of him
		board[sourceY][sourceX] = dynamic_cast<Piece*>(tempBishop); // Upcasting the Bishop* into a Piece*
	}

	// Otherwise
	else
	{
		// Place the queen in the destination
		board[destY][destX] = dynamic_cast<Piece*>(currQueen);

		// Free the allocated memory
		delete tempBishop;
		delete tempRook;

		// Return -1 (Move was successful)
		return temp;
	}

	// Performing the check on the bishop
	temp = tempBishop->checkMove(sourceX, sourceY, destX, destY, board, currentPlayer);

	// If the bishop wasn't moved
	if (temp != 1 && temp != 0)
	{
		// Place the queen in place of him
		board[sourceY][sourceX] = currQueen;

		// Free the allocated memory
		delete tempBishop;
		delete tempRook;

		// Return the error code (Move was unsuccessful)
		return temp;
	}

	// Placing the queen in the destination
	board[destY][destX] = currQueen;

	// Free the allocated memory
	delete tempBishop;
	delete tempRook;

	// Return -1 (Move was successful)
	return temp;
}

/** Serves to override to allow for upcasting */
int Queen::checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const {return 0;}

/** Serves to override to allow for upcasting */
int Queen::checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const {return 0;}
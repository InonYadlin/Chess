#pragma once

#include "Piece.h"
#include "EmptyPiece.h"

class Bishop : public Piece
{
public:
	// Constructor
	Bishop(bool colour);

	// Virtual methods
	virtual int checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const override; // Method checks if the movement passes all necessary tests
	virtual int checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const override; // Method checks if there is a piece in the path to the new location
	virtual int checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const override; // Method checks if the movement is legal

	// Methods
	int getDirection(int source, int dest) const; // Method gets the direction of the given axis movement (positive or negative)
};
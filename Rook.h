#pragma once

#include "Piece.h"
#include "EmptyPiece.h"

class Rook : public Piece
{
public:
	// Constructor
	Rook(bool colour);

	// Virtual methods
	virtual int checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const override; // Method checks if the movement passes all necessary tests
	virtual int checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const override; // Method checks if there is a piece in the path to the new location
	virtual int checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const override; // Method checks if the movement is legal

	// Methods
	bool checkMovementAxis(int& sourceX, int& sourceY, int& destX, int& destY) const; // Checking the direction of the movement (on which axis)
	int checkMovementDirection(int& source, int& dest) const; 
};

#pragma once
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"

class Queen : public Piece
{
public:
	// Constructor
	Queen(bool colour);

	// Method to move the queen, since she moves like the rook and bishop we will use those methods to move her
	virtual int checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const override; // Method checks if the movement passes all necessary tests
	virtual int checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const override; // Method checks if there is a piece in the path to the new location
	virtual int checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const override; // Method checks if the movement is legal
};
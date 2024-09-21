#pragma once
#include "Piece.h"
#include "EmptyPiece.h"

class Pawn : public Piece
{
private:
	// Attribute defines whether this is the first move of the pawn
	bool _isFirstMove;

public:
	// Constructor
	Pawn(bool colour);

	// Getter 
	bool getIsFirstMove() const; // isFirstMove Getter

	// Setter
	void setIsFirstMove(bool isFirstMove); //isFirstMove setter

	// Virtual methods
	virtual int checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** boardPtr, bool& currentPlayer) const override; // Method checks if the movement passes all necessary tests
	virtual int checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const override; // Method checks if there is a piece in the path to the new location
	virtual int checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const override; // Method checks if the movement is legal
};
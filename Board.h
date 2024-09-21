#pragma once

#include <iostream>
#include <string.h>
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"
#include "EmptyPiece.h"

class Board
{
private:
	// Private attributes
	// 2d Array to hold all pieces
	Piece*** _board;

	// Current player, (false/0 - white, true/1 - black)
	bool _currentPlayer;

public:
	// Public methods
	// Constructor
	Board();

	// Destructor
	~Board();

	// Getters
	Piece*** getBoard() const;
	bool getCurrentPlayer() const;

	// Methods
	void arrangePieces(); // Method places all the pieces in the board
	void changeCurrentPlayer(); // Method changes the current player
	void printBoard() const; // Method prints the board
};
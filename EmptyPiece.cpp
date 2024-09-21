#include "EmptyPiece.h"

/** Constructor */
EmptyPiece::EmptyPiece(bool colour) : Piece(colour, EMPTY) {}

/** Serves to override to allow for upcasting */
int EmptyPiece::checkMove(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board, bool& currentPlayer) const {return 2;}

/** Serves to override to allow for upcasting */
int EmptyPiece::checkPath(int& sourceX, int& sourceY, int& destX, int& destY, Piece*** board) const {return 2;}

/** Serves to override to allow for upcasting */
int EmptyPiece::checkIllegalMove(int& sourceX, int& sourceY, int& destX, int& destY) const {return 2;}

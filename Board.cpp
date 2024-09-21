#include "Board.h"

Board::Board()
{
    // Set the first player to white
    this->_currentPlayer = WHITE;

    // Allocating memory to a 2d array 8x8
    this->_board = new Piece * *[SIZE];
    for (int i = 0; i < SIZE; ++i)
    {
        this->_board[i] = new Piece * [SIZE];
    }

    this->arrangePieces();
}

Board::~Board()
{
    // Deleting each piece individually
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (this->_board[i][j] != nullptr)
            {
                delete this->_board[i][j];
            }
        }
    }

    // Deleting the 2d array
    delete this->_board;
}

/** Method gets the board */
Piece*** Board::getBoard() const
{
    // Return the board
    return this->_board;
}

/** Method gets the current player */
bool Board::getCurrentPlayer() const
{
    // Return the current player 
    return this->_currentPlayer;
}

/** Method places the pieces in the board */
void Board::arrangePieces()
{
    // Placing the rooks
    this->_board[0][0] = new Rook(BLACK);
    this->_board[0][7] = new Rook(BLACK);
    this->_board[7][0] = new Rook(WHITE);;
    this->_board[7][7] = new Rook(WHITE);

    // Placing the bishops
    this->_board[0][2] = new Bishop(BLACK);
    this->_board[0][5] = new Bishop(BLACK);
    this->_board[7][2] = new Bishop(WHITE);
    this->_board[7][5] = new Bishop(WHITE);

    // Placing the kings
    this->_board[0][3] = new King(BLACK);
    this->_board[7][3] = new King(WHITE);

    // Placing the knights
    this->_board[0][1] = new Knight(BLACK);
    this->_board[0][6] = new Knight(BLACK);
    this->_board[7][1] = new Knight(WHITE);
    this->_board[7][6] = new Knight(WHITE); 

    // Placing the queens
    this->_board[0][4] = new Queen(BLACK);
    this->_board[7][4] = new Queen(WHITE);

    // Loop to place all black pawns
    for (int i = 0; i < SIZE; i++)
    {
        this->_board[1][i] = new Pawn(BLACK);
    }

    // Loop to place all white pawns
    for (int i = 0; i < SIZE; i++)
    {
        this->_board[6][i] = new Pawn(WHITE);
    }

    // Loop to fill the rest with empty pieces
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            this->_board[i][j] = new EmptyPiece(WHITE);
        }
    }
}

/** Method changes the current player */
void Board::changeCurrentPlayer()
{
    // Change the current player 
    this->_currentPlayer = !(this->getCurrentPlayer());
}

/** Method prints the board */
void Board::printBoard() const
{
    Piece*** board = this->getBoard();
    std::cout << "   abcdefgh" << std::endl;
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << (SIZE - i) << "  ";
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j]->getType() != EMPTY && board[i][j]->getColour() == WHITE)
            {
                std::cout << char(board[i][j]->getType() - DIFFERENCE);
            }
            else
            {
                std::cout << board[i][j]->getType();
            }
        }
        std::cout << std::endl;
    }
}

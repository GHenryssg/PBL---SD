#ifndef BOARD_H
#define BORAD_H

#include "pieces.h"

#define ROWS 24
#define VISIBLE_ROWS 20
#define COLS 10

void initBoard(int board[ROWS][COLS]);

void displayBoard(int board[ROWS][COLS]);

void clearLines(int board[ROWS][COLS]);

int canPlacePiece(int board[ROWS][COLS], Piece *piece, int x, int y);

void placePiece(int board[ROWS][COLS], Piece *piece, int x, int y);

void renderWithPiece(int board[ROWS][COLS], Piece *piece, int x, int y);

int moveLeft(int board[ROWS][COLS], Piece *piece, int x, int *y);

int moveRight(int board[ROWS][COLS], Piece *piece, int x, int *y);

#endif
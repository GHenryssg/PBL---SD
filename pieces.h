#ifndef PICES_H
#define PICES_H

#define PIECES_SIZE 4

typedef struct {
    int shape[PIECES_SIZE][PIECES_SIZE];
} Piece;

Piece getPiece (char type);

#endif
#include <stdio.h>
#include "borad.c"
#include "pieces.c"

int main() {
    int board[ROWS][COLS];

    initBoard(board);
    Piece piece = getPiece('T');

    printf("Tabuleiro inicial:\n");
    displayBoard(board);

    int x = 0, y = 4;
    if (canPlacePiece(board, &piece, x, y)) {
        placePiece(board, &piece, x, y);
        printf("oi");
        printf("\nTabuleiro após adicionar a peça 'T':\n");
        displayBoard(board);
    } else {
        printf("\nNão é possível adicionar a peça 'T' na posição (%d, %d)\n", x, y);
    }

    return 0;
} 
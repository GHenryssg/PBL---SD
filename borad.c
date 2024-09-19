#include <stdio.h>
#include "borad.h"

void initBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }
}

void displayBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                printf(". ");
            }
            else {
                printf("# ");
            }
        }
        printf("\n");
    }
}

void clearLines(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        int fullLine = 1;
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                fullLine = 0;
                break;
            }
        }

        if (fullLine) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < COLS; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }

            for (int j = 0; j < COLS; j++) {
                board[0][j] = 0;
            }
        }
    }
}

int canPlacePiece (int board[ROWS][COLS], Piece *piece, int x, int y) {
    for (int i = 0; i < PIECES_SIZE; i++) {
        for (int j = 0; j < PIECES_SIZE; j++) {
            if (piece->shape[i][j] == 1) {
                int boardX = x + i;
                int boardY = y + j;
                if (boardX < 0 || boardX >= ROWS || boardY < 0 || boardY >= COLS || board[boardX][boardY] != 0) {
                    return 0; // não consegue colocar a peça
                }
            }
        }
    }

    return 1; // poe colocar a peça
}

void placePiece(int board[ROWS][COLS], Piece *piece, int x, int y) {
    for (int i = 0; i < PIECES_SIZE; i++) {
        for (int j = 0; j < PIECES_SIZE; j++){
            if (piece->shape[i][j] == 1) {
                board[x + i][y + j] = 1; // insere na matriz
            }
        }
    }
}

//função para renderizar o tabuleiro com a peça e visualizar 
void renderWithPiece(int board[ROWS][COLS], Piece *piece, int x, int y) {
    int tempBoard[ROWS][COLS];

    // Copia o tabuleiro original para um temporário
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    // Adiciona a peça temporária no tabuleiro temporário
    for (int i = 0; i < PIECES_SIZE; i++) {
        for (int j = 0; j < PIECES_SIZE; j++) {
            if (piece->shape[i][j] == 1) {
                tempBoard[x + i][y + j] = 1;
            }
        }
    }

    // Exibe o tabuleiro com a peça temporária
    displayBoard(tempBoard);
}
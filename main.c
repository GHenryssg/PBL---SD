#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "borad.c"
#include "pieces.c"

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

int main() {
    int board[ROWS][COLS];

    // Inicializa o tabuleiro e a peça
    initBoard(board);
    Piece piece = getPiece('T');

    int x = 0, y = 4; // Posição inicial da peça no tabuleiro

    // Loop principal do jogo
    while (1) {
        system("cls"); // Limpa a tela (no Windows)

        // Renderiza o tabuleiro com a peça em sua posição atual
        renderWithPiece(board, &piece, x, y);

        // Verifica se a peça pode descer
        if (canPlacePiece(board, &piece, x + 1, y)) {
            x++; // A peça desce se houver espaço
        } else {
            // Fixar a peça no tabuleiro quando ela não puder descer mais
            placePiece(board, &piece, x, y);
            

            // Reinicia com uma nova peça (substitua por peça aleatória se preferir)
            piece = getPiece('O'); // Exemplo com nova peça
            x = 0;
            y = 4;
        }

        Sleep(500); // Controla o intervalo de tempo entre as quedas (500 ms)
    }

    return 0;
}
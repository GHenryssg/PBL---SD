#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "borad.c"
#include "pieces.c"

int main() {
    int board[ROWS][COLS];

    // Inicializa o tabuleiro e a peça
    initBoard(board);
    Piece piece = getRandomPiece();

    int x = 0, y = 3; // Posição inicial da peça no tabuleiro

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
            piece = getRandomPiece(); // Exemplo com nova peça
            x = 0;
            y = 3;
        }

        Sleep(500); // Controla o intervalo de tempo entre as quedas (500 ms)
    }

    return 0;
}
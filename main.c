#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "board.c"
#include "pieces.c"


int main() {
    int board[ROWS][COLS];

    // inicializa a semente do gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializa o tabuleiro e a peça
    initBoard(board);
    Piece piece = getRandomPiece();

    int x = 0, y = 3; // Posição inicial da peça no tabuleiro

    int end = 0;
    // Loop principal do jogo
    while (end !=1 ) {

        system("cls"); // Limpa a tela (no Windows)


        // Renderiza o tabuleiro com a peça em sua posição atual
        renderWithPiece(board, &piece, x, y);
        
        end = gameOver(board, &piece);
        
        if (_kbhit()) { // verifica se uma tecla foi pressionada
            char key = _getch(); // captura a tecla pressionada 

            switch (key) {
                case 'a':
                    moveLeft(board, &piece, x, &y);
                    break;
                
                case 'd':
                    moveRight(board, &piece, x, &y);
                    break;
            }
        }

        // Verifica se a peça pode descer
        if (canPlacePiece(board, &piece, x + 1, y)) {
            x++; // A peça desce se houver espaço
        } else {
            // Fixar a peça no tabuleiro quando ela não puder descer mais
            placePiece(board, &piece, x, y);

            clearLines(board);
            

            // Reinicia com uma nova peça (substitua por peça aleatória se preferir)
            piece = getRandomPiece(); // Exemplo com nova peça
            x = 0;
            y = 3;
        }
    
        

        Sleep(500); // Controla o intervalo de tempo entre as quedas (500 ms)
        
    }
    
    printf("GAME OVER!");

    return 0;
}
#include <stdio.h>
#include "board.h"

 

void initBoard(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = 0;
        }
    }
}

void displayBoard(int board[ROWS][COLS]) {
    int cellSize = 8;
    int borderSize = 1; // Tamanho da borda

    int boardWidth = COLS * cellSize;
    int boardHeight = ROWS * cellSize;

    int marginX = (319 - boardWidth) / 2;
    int marginY = (239 - boardHeight) / 2;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            short cellColor = (board[i][j] == 0) ? 0X00 : video_BLUE;

            int x1 = j * cellSize + marginX + borderSize;
            int y1 = i * cellSize + marginY + borderSize;
            int x2 = x1 + (cellSize - 2 * borderSize);
            int y2 = y1 + (cellSize - 2 * borderSize);

            // Desenha as bordas brancas primeiro
            video_box(j * cellSize + marginX, i * cellSize + marginY, (j + 1) * cellSize + marginX, (i + 1) * cellSize + marginY, video_WHITE);

            // Desenha a célula dentro das bordas
            video_box(x1, y1, x2, y2, cellColor);
        }
    }
    video_show();
}


void clearLines(int board[ROWS][COLS], int* pontuacao) { 
    for (int i = 0; i < ROWS; i++) {
        int fullLine = 1;
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                fullLine = 0;
                break;
            }
        }

        if (fullLine) {
            *pontuacao +=  10;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < COLS; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }

            for (int j = 0; j < COLS; j++) {
                board[0][j] = 0;
            }
            
            i--;
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

void renderWithPiece(int board[ROWS][COLS], Piece *piece, int x, int y) {
    //  Cria um tabuleiro temporário
    int tempBoard[ROWS][COLS];
    
    // Copia o tabuleiro original para o temporário
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }
    
    // Adiciona a peça temporária no tabuleiro temporário
    for (int i = 0; i < PIECES_SIZE; i++) {
        for (int j = 0; j < PIECES_SIZE; j++) {
            if (piece->shape[i][j] == 1) {
                int drawX = y + j; // Coluna
                int drawY = x + i; // Linha
                
                // Verifica se a posição está dentro dos limites do tabuleiro
                if (drawX >= 0 && drawX < COLS && drawY >= 0 && drawY < ROWS) {
                    tempBoard[drawY][drawX] = 2; // Para identificar que é a peça
                }
                
            }
        }
    }
    // Exibe o tabuleiro com a peça temporária
    displayBoard(tempBoard);
}


// função para mover a peça para a esquerda 
int moveLeft(int board[ROWS][COLS], Piece *piece, int x, int *y) {
    if (canPlacePiece(board, piece, x, *y - 1)) {
        *y -= 1;
        return 1; // movimento bem-sucedido
    }

    return 0; // não pode mover para a direita 
}

// função para mover para a direita
int moveRight(int board[ROWS][COLS], Piece *piece, int x, int *y) {
    if (canPlacePiece(board, piece, x, *y + 1)) {
        *y += 1;
        return 1; // movimento bem-sucedido 
    }

    return 0; // não pode mover para a direita 
}

int gameOver(int board[ROWS][COLS], Piece *Piece){
    return !canPlacePiece(board, Piece, 0, 4);
}







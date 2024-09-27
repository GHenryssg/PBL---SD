#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> // Para srand e usleep
#include <intelfpgaup/KEY.h>
#include <pthread.h>
#include "i2c.c"
#include "board.c"
#include "pieces.c"

int ACCEL = 1;
int BUTTON = 1;
int pausegame = 0;
int endgame = 1;
int iniciarjogo = 1;
int fd;
I2C_Registers regs;
static int16_t X[1];
void inicializacao_accel();
void* accel_working(void *args);
void* button_threads(void *args);


int main() {

    int board[ROWS][COLS];
    pthread_t thread_accel, thread_button;  
    int pontuacao = 0;
    char pontos[20];
    sprintf(pontos,"Score %d",pontuacao);
    inicializacao_accel();
    pthread_create(&thread_accel, NULL, accel_working , NULL);
    pthread_create(&thread_button, NULL, button_threads , NULL);

    // Inicia o VGA
    if (!video_open()) {
        printf("Erro ao abrir o dispositivo VGA\n");
        return -1;
    }
    video_clear(); // Limpa a tela
    video_erase();

    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    // Inicializa o tabuleiro e a peça
    initBoard(board);
    Piece piece = getRandomPiece();

    int x = 0, y = 3; // Posição inicial da peça no tabuleiro
   
    while(iniciarjogo){
        video_text(34, 1, "CLIQUE NO BOTAO PARA INICIAR O JOGO!!");
    }

    
    while (endgame) {
        // Converte inteiro em string
        sprintf(pontos,"Score:%d",pontuacao);
        
        // Renderiza a peça na posição atual
        renderWithPiece(board, &piece, x, y);
        
        video_text(1, 30,pontos); 
        
        
        if (gameOver(board, &piece)) {
            endgame = 0; // Se o jogo acabou, sai do loop
        }
        
        while(pausegame) {
            video_text(34, 1, "JOGO PAUSADO!"); 
            usleep(100000);
            video_clear();
            video_erase();
            video_text(1, 30,pontos); 
        }

        // Verificação se o valor de X é maior, menor ou igual a 0
        if (X[0] > 20 && pausegame == 0) {
            moveRight(board, &piece, x, &y);
        } else if (X[0] < -20 && pausegame == 0) {
            moveLeft(board, &piece, x, &y);
        } 

        // Verifica se a peça pode descer
        if (canPlacePiece(board, &piece, x + 1, y)) {
            x++; // A peça desce se houver espaço
        }else if (pausegame == 0) {
            // Fixar a peça no tabuleiro quando ela não puder descer mais
            placePiece(board, &piece, x, y);
            clearLines(board, &pontuacao);

            // Reinicia com uma nova peça
            piece = getRandomPiece();
            x = 0;
            y = 3;
        }

        usleep(200000); // Controla o intervalo de tempo entre as quedas (50 ms)
    }

    // Exibe a tela de Game Over
    video_clear();
    video_erase();
    video_text(34, 30, "GAME OVER!");
    video_show();
    BUTTON = 0; // Mata o 
    ACCEL = 0;
    //Encerrando as threads
    pthread_join(thread_accel, NULL);
    pthread_join(thread_button, NULL);

    return 0;
}

void inicializacao_accel(){
    fd = open_fd();
    regs = map_i2c(fd);
    I2C0_Init(&regs); // Estabelece a comunicação com o acelerômetro
    accelerometer_init(regs); // Configura o acelerômetro
}

void* accel_working(void *args){
    while (ACCEL){    
        if(accelereometer_isDataReady(regs)) {
            accelerometer_x_read(X, regs); // lê os dados do eixo x
        }
        usleep(200000);
    }
    return NULL;
}

void* button_threads(void *args){
    KEY_open();
    while(BUTTON){
        int teste;
        KEY_read(&teste);
        switch (teste) {
            case 1: // Pausa o jogo B0
                pausegame = 1;
                break;
            case 2: // Retoma o jogo B1
                pausegame = 0;
                break;
            case 4: // Acabar o jogo B2
            	endgame = 0;
                break;
            case 8: // Iniciar o jogo B3
                iniciarjogo = 0;
                break;
            default:
                break;
        }
    }
    KEY_close();
    return NULL;
}

#include <termios.h>

void setRawMode() {
    struct termios raw;

    // Obtem as configurações atuais do terminal
    tcgetattr(STDIN_FILENO, &raw);

    // Muda as configurações do terminal para o modo raw
    raw.c_lflag &= ~(ICANON | ECHO); // Desativa o modo canônico e o echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // Aplica as configurações
}

void resetTerminal() {
    struct termios original;

    // Restaura as configurações originais do terminal
    tcgetattr(STDIN_FILENO, &original);
    original.c_lflag |= (ICANON | ECHO); // Ativa o modo canônico e o echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

int kbhit() {
    struct termios oldt, newt;
    int oldf;

    // Configura o terminal para modo não bloqueante
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    // Restaura as configurações do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1; // Tem uma tecla pressionada
    }

    return 0; // Nenhuma tecla pressionada
}

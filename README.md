<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=00FFFF&height=120&section=header"/>

<div align="center">  

# Projeto de Jogo Tetris em Linguagem C com acelerômetro

## Problema I - TEC499 - MI Sistemas Digitais - 2024.2
<div align="justify"> 

<div align="center">
 <a href="#-SOBRE-O-PROJETO"> SOBRE</a> •
 <a href="#-CARACTERÍSTICAS-DO-PROJETO"> CARACTERÍSTICAS</a> •
 <a href="#-REQUISITOS"> REQUISITOS</a> •
 <a href="#-HARDWARE-UTILIZADO"> HARDWARE</a> • 
 <a href="#-SOFTWARE-UTILIZADO"> SOFTWARE</a> • 
 <a href="#-DESENVOLVIMENTO-E-EXECUÇÃO-DO-PROJETO"> DESENVOLVIMENTO</a> • 
 <a href="#-FUNCIONAMENTO-DO-JOGO"> FUNCIONAMENTO</a> •
 <a href="#-SOLUÇÃO-DO-JOGO"> SOLUÇÃO</a> •
 <a href="#-BIBLIOTECAS-UTILIZADAS"> BIBLIOTECAS</a> •
 <a href="#-TESTES"> TESTES</a> •
 <a href="#-CONCLUSÃO"> CONCLUSÃO</a> •
 <a href="#-EXECUÇÃO-DO-PROJETO"> EXECUÇÃO</a> •
 <a href="#-DESENVOLVEDORES"> DESENVOLVEDORES</a>
</div>

# SOBRE O PROJETO
<div align="justify"> 
 
Este projeto implementa o jogo Tetris utilizando a linguagem C e o acelerômetro ADXL-345 do kit de desenvolvimento DE1-SoC. O jogo é reproduzido em um monitor conectado via VGA, e a mecânica de controle é baseada na inclinação da placa, que determina o lado para o qual as peças se movem.

# CARACTERÍSTICAS DO PROJETO
<div align="justify"> 
 
Linguagem: C Plataforma: DE1-SoC (com FPGA Cyclone V) Controle de Jogo: Acelerômetro ADXL-345 Saída de Vídeo: Conexão VGA

# REQUISITOS
<div align="justify"> 

1. O código deve ser escrito em linguagem C;
2. O sistema só poderá utilizar os componentes disponíveis na placa;
3. Não é permitido o uso de bibliotecas para o acelerômetro;
4. O usuário não muda a orientação das peças;
5. O jogo deve pontuar e eliminar agrupamentos.


# HARDWARE UTILIZADO
<div align="justify"> 

**kit de desenvolvimento DE1-SoC**

A placa DE1-SoC é um kit de desenvolvimento que combina um processador ARM Cortex-A9 dual-core com um FPGA Cyclone V da Intel. Sendo ideal para o desenvolvimento de projetos de prototipagem e desenvolvimento de sistemas embarcados. A execução do jogo é acessada por meio de uma conexão SSH (via Ethernet) através do terminal de um computador.

**Acelerômetro ADXL345**

O ADXL345 é um acelerômetro digital de baixa potência e alta resolução, projetado para medir aceleração em três eixos (X, Y e Z). Ele pode detectar acelerações de até ±16g com uma precisão de 13 bits e é amplamente usado em dispositivos portáteis, sistemas de navegação, sensores de inclinação, e várias aplicações em robótica e sistemas embarcados.



# SOFTWARE UTILIZADO
<div align="justify"> 

**Linguagem C**

A linguagem C foi escolhida por sua eficiência, portabilidade e grande popularidade em sistemas embarcados. Sua sintaxe clara oferece controle direto sobre o hardware, ao mesmo tempo em que suas bibliotecas padrão e ferramentas possibilitam o desenvolvimento de código compacto e otimizado para dispositivos com restrições de recursos.

**Compilador GNU**

O Compilador GNU (GCC - GNU Compiler Collection) é uma coleção de compiladores de código aberto que faz parte do projeto GNU, sendo amplamente utilizado para compilar programas em várias linguagens de programação, como C, C++, Fortran, Ada e outras. Ele é um dos compiladores mais populares e é essencial no desenvolvimento de software livre e projetos baseados em Linux.


**VSCODE**

O Visual Studio Code (VSCode) é um editor de código-fonte leve, desenvolvido pela Microsoft, que oferece uma ampla gama de funcionalidades para programadores. Ele é gratuito, de código aberto e disponível para várias plataformas, incluindo Windows, macOS e Linux.

# DESENVOLVIMENTO E EXECUÇÃO DO PROJETO
<div align="justify"> 

**Acelerômetro, Mapeamento de Memória e I2C**

O acelerômetro utilizado no jogo é um dispositivo ADXL345, que se comunica via o barramento I2C (Inter-Integrated Circuit). Para acessá-lo, o código implementa o mapeamento de memória e manipulação direta de registradores.
Mapeamento de Memória: O sistema Linux oferece um dispositivo especial chamado /dev/mem, que permite que processos de usuário acessem endereços físicos de hardware. O código usa o mapeamento de memória através da função mmap(), transformando os registradores do controlador I2C em ponteiros acessíveis pelo programa. Isso permite a leitura e escrita direta nos registradores de controle do barramento I2C.
Comunicação I2C: Após o mapeamento, as funções implementadas permitem a leitura e escrita nos registradores do acelerômetro. Para isso, a inicialização do controlador I2C é feita com a função I2C0_Init(), que configura o dispositivo para o modo mestre e define o endereço do acelerômetro. Funções como accelerometer_x_read() são usadas para capturar os valores do eixo X do acelerômetro, enquanto accelerometer_isDataReady() verifica se os dados estão prontos para leitura.
Função no Jogo: O acelerômetro detecta a inclinação do dispositivo, e com base nesses valores, o jogo move as peças para a esquerda ou direita no tabuleiro, conforme os movimentos do jogador. Isso adiciona uma camada de interatividade física ao jogo.

**Threads**

O jogo faz uso de threads para permitir a execução de tarefas concorrentes. Duas threads são criadas para gerenciar a leitura contínua do acelerômetro e o monitoramento dos botões do dispositivo.
Thread do Acelerômetro: A função accel_working() é executada em uma thread separada. Essa thread continuamente verifica se há novos dados no acelerômetro e, se houver, lê os valores do eixo X para determinar se a peça deve se mover para a esquerda ou direita no tabuleiro. O uso de usleep() controla a frequência de leitura para evitar sobrecarga de processamento.
Thread dos Botões: A função button_threads() também é executada em uma thread separada, que monitora o estado dos botões do hardware. Os botões têm diferentes funcionalidades: um deles pausa e retoma o jogo, e outro termina o jogo. Isso é feito através de uma leitura contínua dos botões usando a biblioteca KEY_read(), onde os eventos de pressionamento dos botões disparam as ações correspondentes no jogo.
Sincronização com o Jogo: As threads permitem que o jogo continue a rodar independentemente, enquanto as entradas de controle (acelerômetro e botões) são monitoradas em segundo plano. Isso garante que a interação seja fluida e sem interrupções na lógica principal do jogo.

**Tabuleiro e Peças no VGA**

O jogo exibe o tabuleiro e as peças na tela usando um controlador VGA (Video Graphics Array).
Tabuleiro: O tabuleiro é uma matriz bidimensional (int board[ROWS][COLS]) que representa as células onde as peças caem. A função initBoard() inicializa essa matriz, e cada célula pode estar vazia ou ocupada por parte de uma peça. O tabuleiro é renderizado na tela a cada iteração do loop principal do jogo, sendo atualizado conforme as peças se movem ou são fixadas.
Peças: As peças do jogo são representadas por structs que contêm suas formas e posições. A função getRandomPiece() seleciona aleatoriamente uma nova peça para cair. A peça atual é renderizada na posição adequada no tabuleiro com a função renderWithPiece(), que combina o estado do tabuleiro com a peça ativa.
Exibição VGA: A comunicação com a tela VGA é feita através de um dispositivo de vídeo. As funções video_open(), video_clear(), e video_text() são responsáveis por gerenciar a exibição gráfica. A tela é constantemente limpa e redesenhada a cada ciclo do jogo para refletir o estado atual do tabuleiro, a peça em queda e outras informações, como a pontuação.
Pontuação e Fim de Jogo: A pontuação é exibida na tela junto com o tabuleiro. A cada vez que uma linha do tabuleiro é completada, ela é removida e a pontuação é atualizada usando a função clearLines(). Quando o jogo termina (se a peça alcançar o topo do tabuleiro), a mensagem "GAME OVER" é exibida e o jogo é finalizado.


# FUNCIONAMENTO DO JOGO
<div align="justify"> 

As peças são formadas por quatro blocos quadrados. Existem sete formas básicas de peças, cada uma com uma letra correspondente.

**Início:**

O jogo é iniciado em um tabuleiro que consiste em uma grade retangular (10 colunas x 20 linhas), o jogo começa com um espaço vazio e, gradualmente, os tetriminos começam a cair do topo da tela.

**Mecânica de Jogo:**

As peças caem de uma posição inicial no topo do tabuleiro e continuam descendo até tocarem a linha mais baixa ou outra peça já posicionada. O diferencial na jogabilidade é o uso de um acelerômetro: ao inclinar a placa, o jogador pode mover as peças para a esquerda ou direita. O acelerômetro detecta o grau de inclinação, e, conforme os dados de inclinação são lidos, o movimento da peça no tabuleiro é ajustado.

Esse controle intuitivo permite que, inclinando a placa para a direita, a peça se mova para a direita no tabuleiro, enquanto inclinações para a esquerda fazem a peça se deslocar para a esquerda. A precisão do acelerômetro faz com que o jogador tenha controle direto sobre o posicionamento das peças em tempo real, influenciando a estratégia de encaixe nas lacunas.

Quando uma linha é completamente preenchida com blocos, ela desaparece, e as linhas acima descem uma posição, gerando pontos. O jogador ganha pontos ao remover linhas, e a habilidade de controlar a movimentação das peças com a inclinação da placa cria uma experiência de jogo mais dinâmica e interativa.

**Objetivo:**

O jogo tem como objetivo fazer a maior pontuação possível sem que as peças atinjam o topo do tabuleiro.

**Pausa e retomada**

Botão de Pausa: Quando o jogador pressiona o botão correspondente, o jogo é pausado. Durante a pausa, o jogador não pode mover as peças, e uma mensagem indicando o estado de pausa aparece na tela. Pressionar o botão novamente retoma o jogo.
Botão de Retomar: Esse botão é usado para retornar ao jogo após ele ter sido pausado. Ele faz com que o jogo volte à sua dinâmica normal, permitindo o controle das peças e a continuidade da partida.
Botão de Encerramento: Pressionar este botão encerra o jogo imediatamente, interrompendo qualquer ação em andamento e levando ao fim da partida.


# SOLUÇÃO DO JOGO
<div align="justify"> 
 
A implementação apresentada demonstra a capacidade de atender integralmente aos requisitos propostos. Preliminarmente ao laço principal de execução, é realizada uma verificação para confirmar o desejo do usuário em iniciar o jogo. Em seguida, são inicializados os periféricos necessários para o funcionamento do sistema, a saber: interface gráfica (VGA), acelerômetro e botões de controle.
Na sequência, são instanciados os elementos essenciais para o jogo, o mecanismo de geração aleatória de peças e as threads responsáveis pela execução concorrente das diferentes funcionalidades do sistema.
Dentro do laço principal, o sistema realiza a leitura contínua dos dados provenientes do acelerômetro e verifica a ocorrência de eventos de clique nos botões. Na ausência de eventos de clique, a execução do jogo prossegue normalmente. Os dados obtidos do acelerômetro são utilizados para determinar a movimentação da peça em jogo, que é atualizada de acordo com os valores capturados.
Após a atualização da posição da peça, é verificada a ocorrência de colisões com outras peças ou com as bordas do tabuleiro. Caso ocorra uma colisão, a peça é fixada na posição atual, sendo incorporada à matriz principal. Em seguida, é realizada uma verificação para determinar se o jogo chegou ao fim, condição que ocorre quando a pilha de peças atinge o topo do tabuleiro. Caso o jogo não tenha terminado, é verificada a ocorrência de eventos de clique nos botões, sendo executada a ação correspondente a cada botão pressionado. Ao final do jogo, é exibida a mensagem "GAME OVER!" na tela.



# BIBLIOTECAS UTILIZADAS
<div align="justify"> 

Nesta seção, serão abordadas as principais bibliotecas essenciais para o funcionamento completo do Tetris.

**intelfpgaup/video.h**

A biblioteca VGA (Video Graphics Array) desempenha um papel fundamental na implementação do tetris, fornecendo acesso direto ao framebuffer da VGA para controle granular de cada pixel. Funções como video_pixel, video_box, e video_line permitem a manipulação precisa das coordenadas e cores, essenciais para renderizar as peças do tetris e o tabuleiro em tempo real. O uso de buffers duplos (video_show) permite alternar entre o buffer de desenho e o buffer de exibição, eliminando o tearing (descontinuidade na imagem) e garantindo atualizações suaves da tela. Essa abordagem reduz a latência entre os cálculos lógicos do jogo e a atualização visual, otimizando a jogabilidade.

**sys/mman**

O uso de mmap é fundamental para acessar o acelerômetro na DE1-SoC, pois permite mapear o endereço físico do hardware (como o controlador I2C do acelerômetro) diretamente no espaço de memória do processo. Isso facilita a leitura e escrita de registradores do acelerômetro sem a necessidade de chamadas de sistema frequentes, reduzindo a latência e permitindo acesso direto e eficiente ao dispositivo.

**pthread**

A biblioteca pthread é crucial para integrar a leitura dos dados do acelerômetro ao loop principal do tetris, permitindo que ambos funcionem de maneira paralela. Ao criar duas threads principais — uma para a leitura contínua dos dados do acelerômetro e outra para o loop principal do jogo — é possível evitar que a leitura dos sensores bloqueie ou atrase a execução do jogo. A thread dedicada ao acelerômetro interpreta os valores de inclinação para mover as peças do Tetris (esquerda, direita) sem interferir na renderização ou na lógica do jogo. Simultaneamente, a thread do loop principal mantém o fluxo do jogo, verificando colisões, atualizando o estado da tela VGA e respondendo rapidamente às ações do jogador. A sincronização entre as threads, usando mutexes ou variáveis de condição, garante que a comunicação seja correta e sem inconsistências. 

**intelfpgaup/KEY.h**

A biblioteca de botões é essencial para a implementação de controles interativos permitindo ao jogador pausar e finalizar o jogo de forma. Através da integração dessa biblioteca, é possível mapear ações específicas a eventos de pressionamento de botões, oferecendo uma experiência de usuário mais rica e responsiva.
Quando um botão de pausa é acionado, a biblioteca permite interromper temporariamente o loop principal do jogo, mantendo o estado atual da partida e congelando a lógica de movimento das peças.
Além disso, a biblioteca de botões também pode implementar a funcionalidade de finalização do jogo.


# TESTES
<div align="justify"> 

**Tela do jogo**

<p align="center">
  <img src="Downloads/tela-do-jogo.jpg" width = "400" />
</p>


**Tela de Game over**

<p align="center">
  <img src="C:\Users\Henry\Documents\PBL - SISTEMAS DIGITAIS 2024.2\Images.jpg" width = "400" />
</p>


**Tela do jogo pausado**

O teste foi realizado com sucesso e o jogo foi pausado após o botão responsável por pausar ser pressionado

<p align="center">
  <img src="Downloads/tela-pausada.jpg" width = "400" />
</p>


**Teste de despausar o jogo**

O teste foi realizado com sucesso e o jogo retornou de onde parou logo após o botão de despausar ser pressionado
Teste de eliminar linhas e pontuar

<p align="center">
  <img src="Downloads/jogo-despausado.jpg" width = "400" />
</p>


**Teste de Pontuação - Linha Completa**

<p align="center">
  <img src="Downloads/linha-completa.jpg" width = "400" />
</p>


**Teste de Pontuação - Pontuação efetivada**

O teste foi realizado com sucesso e a linha foi deletada e acrescentado a pontuação na variável de Score
Teste perder o jogo

<p align="center">
  <img src="Downloads/pontuação.jpg" width = "400" />
</p>


**Teste de finalização da partida ao perder**

O teste foi realizado com sucesso e o jogo parou quando as peças chegaram ao topo do tabuleiro

<p align="center">
  <img src="Downloads/tela-de-game-over.jpg" width = "400" />
</p>


# CONCLUSÃO
<div align="justify">
 
A presente implementação do clássico jogo Tetris, desenvolvida em linguagem C para a plataforma DE1-SoC, demonstra a viabilidade e eficácia da utilização de sistemas embarcados em aplicações de entretenimento. A arquitetura da placa DE1-SoC, aliada a drivers disponíveis, proporcionou o ambiente ideal para o desenvolvimento e execução do jogo, atendendo integralmente aos requisitos propostos.
A integração entre o software e o hardware da plataforma permitiu a utilização coordenada de diversos periféricos, como a interface VGA para a renderização gráfica, o acelerômetro para a interação por movimento e os botões para o controle tradicional do jogo.
Os testes realizados demonstraram a estabilidade e o desempenho satisfatório do sistema, garantindo a execução confiável do jogo em diferentes cenários. A arquitetura ARM da plataforma DE1-SoC, em conjunto com a linguagem C, proporcionou um ambiente de desenvolvimento eficiente, permitindo a implementação de algoritmos para a execução.
Além de cumprir os objetivos específicos do projeto, a implementação do Tetris em plataforma DE1-SoC contribuiu significativamente para o desenvolvimento das competências dos envolvidos, aprofundando os conhecimentos em sistemas embarcados, arquitetura ARM e programação em linguagem C. A experiência adquirida neste projeto abre novas perspectivas para o desenvolvimento de sistemas digitais mais complexos e a criação de soluções inovadoras em diversos setores.

# EXECUÇÃO DO PROJETO
<div align="justify">

Siga os passos abaixo para baixar, compilar e executar o código do projeto em um dispositivo FPGA DE1-SoC.

**Passo 1: Clonar o Repositório**
Abra o terminal e execute o comando a seguir para clonar o repositório com o código-fonte:

    git clone https://github.com/GHenryssg/PBL---SD.git

**Passo 2: Navegar até o Diretório e Compilar**
Após clonar o repositório, entre no diretório do projeto com o comando:


    cd PBL---SD

**Passo 3: Em seguida, compile e execute o código utilizando o comando:**

    make


# 💻 DESENVOLVEDORES

<div align="center">  

<table>
  <tr>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/142272107?v=4" width="100px;" alt=""/><br /><sub><b> Gabriel Henry </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/143047526?v=4" width="100px;" alt=""/><br /><sub><b> Ilson Neto </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/157659009?v=4" width="100px;" alt=""/><br /><sub><b> Carlos Arthur </b></sub></a><br />👨‍💻</a></td>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/129235302?v=4" width="100px;" alt=""/><br /><sub><b> Luis Guilherme </b></sub></a><br />👨‍💻</a></td>
  </tr>
</table>

#### [Voltar ao topo](#Projeto-de-Jogo-Tetris-em-Linguagem-C-com-acelerômetro)

<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=00FFFF&height=120&section=footer"/>

<div align="center">  



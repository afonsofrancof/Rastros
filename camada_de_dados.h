#ifndef CAMADA_DADOS_H
#define CAMADA_DADOS_H
#include "listas.h"
typedef enum
{
    VAZIO = '.',
    BRANCA = '*',
    PRETA = '#'
} CASA;

typedef struct
{
    int coluna;
    int linha;
} COORDENADA;

typedef struct
{
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

typedef JOGADA JOGADAS[32];

typedef struct
{
    CASA tab[8][8];
    COORDENADA ultima_jogada;
    JOGADAS jogadas;
    int jogador_atual;
    int jogada;
} ESTADO;
/**
@file camada_de_dados.h 
Estado e funções que o manipulam
*/

/**
 Função que inicializa o estado do jogo
*/

ESTADO *inicializar_estado();

/**
 Função que esvazia o tabuleiro
 */

void empty_tabuleiro(ESTADO *e);
/**
Função 
*/
/**
Função que devolve o jogador atual
*/
int obter_jogador_atual(ESTADO *estado);
/**Função que obtem a casa de uma certa posição */
CASA obter_estado_casa(ESTADO *e, int c, int l);

/**
Função booleana que verifica se a peça dada no input está numa posição de jogada válida
*/

int is_near_branca(ESTADO *estado, int colatual, int linatual);

/**
Função que coloca a peça branca nas coordenadas do input
*/

void put_branca(ESTADO *estado, int col, int lin);

/**
Função que coloca uma peça preta na posição que lhe é dada
*/

void put_preta(ESTADO *estado);

/**
Função que coloca uma peça preta nas coordenadas da jogada anterior 
*/

void atualiza_ultima_jogada(ESTADO *estado, int col, int lin);

/**
Função que atualiza a ultima jogada para a jogada que acabou de ser feita
*/

int verifica_preta(ESTADO *estado, int col, int lin);

/**
Função que determina se o jogador se pode mover tendo em conta todos os possíveis obstáculos como os cantos do tabuleiro e a existencia de peças pretas no caminho
*/

int pode_mover(ESTADO *estado, int col, int lin);

/**
Função que modifica o jogador atual 
*/

void modifica_jogador_atual(ESTADO *estado, int contador);

/**
Função que obtem a coluna anterior através do estado
*/

int get_coluna_anterior(ESTADO *estado);

/**
Função que obtem a linha anterior através do estado
*/

int get_linha_anterior(ESTADO *estado);

/**
Função que obtem a coluna da coordenada dada 
*/

int get_coluna(COORDENADA coord);

/**
Função que obtem a linha da coordenada dada
*/

int get_linha(COORDENADA coord);

/**
Função que obtem a jogada 
*/

int get_jogada(ESTADO *estado);

/**
Função que atualiza o número de jogadas através dependendo do jogador atual
*/

int atualiza_jogadas(ESTADO *estado);

/**
Função que analiza o tabuleiro imprimido e adiciona a informação que recebe sobre as peças 
*/

void set_casa(ESTADO *e, int c, int l, CASA casa);

/**
Função que armazena no array jogadas[32] as jogadas à medida em que são feitas
*/

void armazena_jogada(ESTADO *e, COORDENADA c);

/**
Função que armazena no array jogadas[32] as jogadas à medida em que são feitas
*/

void fdisplay_jogadas(FILE *fp, ESTADO *e);

/**
Função que recebe uma coluna e uma linha e atualiza o array jogadas
*/

void le_e_escreve_jogadas(ESTADO *e, int col, int lin, int n_jogada, int jog);

/**
Função que vai ao estado e introduz o número de jogadas passado no input
*/

void put_jogada(ESTADO *e, int jogada);

/**
Função muda o jogador atual
*/

void put_jogador_atual(ESTADO *e, int jog);

/**
Função que efetua todas as jogadas existentes no array backup
*/

int jogar_pos(ESTADO *e, JOGADAS backup, int pos);

/**
Função que copia as jogadas do array JOGADAS[32] para o array backup
*/
void array_backup(ESTADO *e, JOGADAS backup, int pos);

/**
Função que imprime somente as jogadas no file pointer passado no input
*/

void imprime_play(ESTADO *e, int n_jogada, int jogador, FILE *fp);

/**
Função que copia os elemntos da lista ligada para um array, para que possa ser percorrido e determinado a coordenada da jogada que o bot irá efetuar
*/

COORDENADA *selectcasas(ESTADO *e, llig lista, int *tamanho);

/**
Função que vai à lista passada no input e devolve o elemento com o respetivo índice
*/

COORDENADA *devolveindice(llig lista, int indice);

/**
Função que calcula a distância da posição atual do jogador até ao objetivo
*/

float distanciacasas(COORDENADA *coord, int jog);

/**
Função que faz com o que bot efetue uma jogada segundo a sua estratégia
*/

void jogEuclidiano(ESTADO *e, int *jog1, int *jog2);

/**
Função que aramzena na lista todas as jogadas possíveis que o bot pode fazer no momento
*/

llig armazena_posicoes(ESTADO *e, llig lista, int *tamanho);

/**
Le o estado a partir de um ficheiro
*/
void ler(ESTADO *e, char *filename);
/**
Grava o estado do jogo num ficheiro
*/
void gravar(ESTADO *e, char *filename);

/**
Aloca espaço na memória para uma coordenada e devolve o apontador da nova coordenada
*/
COORDENADA *aloca_coord(COORDENADA c);

/**
Implementação da segunda heurística
*/
void jogRandom(ESTADO *e, int *jog1, int *jog2);

#endif
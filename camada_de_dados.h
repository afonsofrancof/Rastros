#ifndef CAMADA_DADOS_H
#define CAMADA_DADOS_H

typedef enum {VAZIO, BRANCA, PRETA} CASA;

typedef struct {
    int coluna;
    int linha;
} COORDENADA;

typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

typedef JOGADA JOGADAS[32];

typedef struct {
    CASA tab[8][8];
    COORDENADA ultima_jogada;
    JOGADAS jogadas;
    int num_jogadas;
    int jogador_atual;
    int jogada;
} ESTADO;



ESTADO *inicializar_estado();

int obter_jogador_atual(ESTADO *estado);

int obter_numero_de_jogadas(ESTADO *estado);

CASA obter_estado_casa(ESTADO *e,int c,int l);

int is_near_branca(ESTADO *estado,int colatual,int linatual);

void put_branca(ESTADO *estado,int col,int lin);

void put_preta(ESTADO *estado);

void atualiza_ultima_jogada(ESTADO *estado, int col , int lin);

int verifica_preta(ESTADO *estado,int col, int lin);

int pode_mover(ESTADO *estado, int col, int lin);

void aumenta_jogadas(ESTADO *estado);

void modifica_jogador_atual(ESTADO *estado);

int get_coluna_anterior(ESTADO *estado);

int get_linha_anterior(ESTADO *estado);

int get_coluna(COORDENADA coord);

int get_linha(COORDENADA coord);

int get_jogada(ESTADO *estado);

int atualiza_jogadas(ESTADO *estado);

#endif
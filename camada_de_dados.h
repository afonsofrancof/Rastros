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
} ESTADO;



ESTADO *inicializar_estado();

int obter_jogador_atual(ESTADO *estado);

int obter_numero_de_jogadas(ESTADO *estado);

CASA obter_estado_casa(ESTADO *e,int c,int l);

int is_near_branca(ESTADO *estado,int colatual,int linatual);

void put_branca(ESTADO *estado,int col,int lin);

void put_preta(ESTADO *estado);

void atualiza_ultima_jogada(ESTADO *estado, int col , int lin);

#endif
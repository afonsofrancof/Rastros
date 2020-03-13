#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camada_de_dados.h"

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->num_jogadas = 0;
    for(int l=0;l<=7;l++)
        for(int c=0;c<=7;c++){
            e->tab[l][c]=VAZIO;
        }
    e->tab[3][4]=BRANCA;
    return e;
}

int obter_jogador_atual(ESTADO *estado){
    int j;
    j=estado->jogador_atual;
    return j;
}

int obter_numero_de_jogadas(ESTADO *estado){
    int n;
    n=estado->num_jogadas;
    return n;
}

CASA obter_estado_casa(ESTADO *e, COORDENADA c){
    int line,column,casa;
    column=c.coluna;
    line=c.linha;
    casa=e->tab[line][column];
    return casa;    
}
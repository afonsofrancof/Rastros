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
    e->ultima_jogada.linha = 4;
    e->ultima_jogada.coluna = 3;
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

CASA obter_estado_casa(ESTADO *estado,int c,int l){
    int casa;
    casa=estado->tab[c][l];
    return casa;   
}

int is_near_branca(ESTADO *estado,int colatual,int linatual){
    int col,lin,ans;
    col = estado->ultima_jogada.coluna;
    lin = estado->ultima_jogada.linha;
    if ((abs(colatual-col)<=1)&&(abs(linatual-lin)<=1)) ans = 1;
    else ans = 0;
    return ans;
}

void put_branca(ESTADO *estado,int col,int lin){
    estado->tab[col] [lin]=BRANCA;
} 

void put_preta(ESTADO *estado){
    int col,lin;
    col = estado->ultima_jogada.coluna;
    lin = estado->ultima_jogada.linha;
    estado->tab[col] [lin]=PRETA;
}

void atualiza_ultima_jogada(ESTADO *estado, int col , int lin){
    estado->ultima_jogada.coluna = col;
    estado->ultima_jogada.linha = lin;
}

int verifica_preta(ESTADO *estado,int col, int lin){
    int ans=0;
    if(estado->tab[col] [lin]==PRETA)
        ans =1;
    return ans;
}

int pode_mover(ESTADO *estado, int col, int lin){
    int ans=1;
    if(col==0&&lin==0){
        if(verifica_preta(estado,col+1,lin)) ans=0;
        if(verifica_preta(estado,col+1,lin+1)) ans=0;
        if(verifica_preta(estado,col,lin+1)) ans=0;
}
}
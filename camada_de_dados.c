#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camada_de_dados.h"

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->num_jogadas = 1;
    e->jogada = 0;
    for(int l=7;l<=0;l--)
        for(int c=0;c<=7;c++){
            e->tab[c][l]=VAZIO;
        }
    e->tab[4][4]=BRANCA;
    e->ultima_jogada.linha = 4;
    e->ultima_jogada.coluna = 4;
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
    if(col==0&&lin==7) // canto superior esquerdo
        if((verifica_preta(estado,col-1,lin))&&(verifica_preta(estado,col+1,lin-1))&&(verifica_preta(estado,col,lin-1))) ans=0;
    if (col==7&&lin==0) // canto inferior direito
        if((verifica_preta(estado,col+1,lin))&&(verifica_preta(estado,col,lin+1))&&(verifica_preta(estado,col-1,lin-1))) ans=0;
    if (lin==7&&col!=7&&col!=0) // linha de cima sem os 2 cantos
        if((verifica_preta(estado,col,lin-1))&&(verifica_preta(estado,col+1,lin-1))&&(verifica_preta(estado,col-1,lin-1))&&(verifica_preta(estado,col-1,lin))&&(verifica_preta(estado,col+1,lin))) ans=0;
    if (col==0&&lin!=0&&lin!=7) // coluna da esquerda sem os 2 cantos
        if((verifica_preta(estado,col,lin-1))&&(verifica_preta(estado,col,lin+1))&&(verifica_preta(estado,col+1,lin))&&(verifica_preta(estado,col+1,lin-1))&&(verifica_preta(estado,col+1,lin+1))) ans=0;
    if (lin==0&&col!=0&&col!=7) // linha de baixo sem os 2 cantos
        if((verifica_preta(estado,col,lin+1))&&(verifica_preta(estado,col-1,lin))&&(verifica_preta(estado,col+1,lin))&&(verifica_preta(estado,col-1,lin+1))&&(verifica_preta(estado,col+1,lin+1))) ans=0;
    if (lin!=7&&lin!=0&&col==7) // coluna da direita sem os 2 cantos
        if((verifica_preta(estado,col,lin+1))&&(verifica_preta(estado,col,lin-1))&&(verifica_preta(estado,col-1,lin))&&(verifica_preta(estado,col-1,lin-1))&&(verifica_preta(estado,col-1,lin+1))) ans=0;
    if (ans) 
        if((verifica_preta(estado,col,lin+1))&&(verifica_preta(estado,col,lin-1))&&(verifica_preta(estado,col+1,lin))&&(verifica_preta(estado,col-1,lin))&&(verifica_preta(estado,col-1,lin+1))&&(verifica_preta(estado,col+1,lin+1))&&(verifica_preta(estado,col+1,lin-1))&&(verifica_preta(estado,col-1,lin-1))) ans=0;
    return ans;
}



void modifica_jogador_atual(ESTADO *estado,int *contador){
    int a;
    a = *contador;
    if(a==1) estado->jogador_atual=2;
    else{
    if(a%2==1) estado->jogador_atual=1;
    else estado->jogador_atual=2;
}
}



int get_coluna_anterior(ESTADO *estado){
    int a;
    a = estado->ultima_jogada.coluna;
    return a;
}

int get_linha_anterior(ESTADO *estado){
    int a;
    a = estado->ultima_jogada.linha;
    return a;
}

int get_coluna(COORDENADA coord){
    int a;
    a=coord.coluna;
    return a;
}

int get_linha(COORDENADA coord){
    int a;
    a=coord.linha;
    return a;
}

int get_jogada(ESTADO *estado){
    int a;
    a=estado->jogada;
    return a;
}

int atualiza_jogadas(ESTADO *estado){
    int j=estado->jogador_atual;
    if(j==2) estado->jogada++;
    return get_jogada(estado);
}

void set_casa(ESTADO *e, int c, int l, CASA casa){
    switch(casa){
        case '*' : e->tab[c][l] = BRANCA; break;
        case '#' : e->tab[c][l] = PRETA ; break;
        case '.' : e->tab[c][l] = VAZIO ; break;
    }
}

void teste(CASA casa){
    switch(casa){
        case '*' : printf("BRANCA"); break;
        case '.' : printf("VAZIO"); break;
        case '#' : printf("PRETA"); break;
    }
}

void armazena_jogada(ESTADO *e,COORDENADA c){
    if (obter_jogador_atual(e)==1)
        e->jogadas[get_jogada(e)].jogador1=c;
    else 
        e->jogadas[get_jogada(e)].jogador2=c;
}



/*void get_jogada_index(ESTADO *e,int a){
    int col = e->jogadas[a].jogador1.coluna;
    int lin = e->jogadas[a].jogador1.linha;
    printf("%d %d \n",col , lin);
}*/
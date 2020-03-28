#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camada_de_dados.h"
#include "interface.h"
#include "logica.h"
#define BUF_SIZE 1024


void mostrar_tabuleiro(ESTADO *e){
    int c,l,contagem=8;
    for(l=7;l>=0;l--){
       printf("%d|",contagem--);
        for(c=0;c<=7;c++){
            if(obter_estado_casa(e,c,l)==BRANCA){
                putchar(' ');
                putchar('*');
                }
                else if(obter_estado_casa(e,c,l)==PRETA){
                        putchar(' ');
                        putchar('#');}
                        else if(l==7&&c==7){
                                putchar(' ');
                                putchar('2');
                                }
                                else if(l==0&&c==0){
                                        putchar(' ');
                                        putchar('1');}
                                        else {putchar(' '); putchar('.');}
        }
    putchar('\n');
    }
    printf("   a b c d e f g h");
    putchar('\n');
}




int interpretador(ESTADO *e) {
    int jog1=0,jog2=0,contador=1;
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int ctrl_j;
    char exit[2],save[BUF_SIZE];
    FILE *file;
    while (!jog1&&!jog2){ 
    printf("#%d  PL %d (%d) -> ",contador,obter_jogador_atual(e),atualiza_jogadas(e)); ///home/diogo/rastros/interface.c
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;   
    //if(sscanf(linha,"%[gr] %s",save)>4) file=fopen("save_estado/save[4].txt","w");
    if(sscanf(linha, "%[Q||q]", exit)==1) return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a',*lin - '1'}; 
        ctrl_j =jogar(e, coord,&jog1,&jog2);
        if(ctrl_j) aumenta_jogadas(e);
        mostrar_tabuleiro(e);
        if(ctrl_j) {modifica_jogador_atual(e);//# <número de comandos> PL<1 ou 2 conforme o jogador> (<número da jogada atual>)>
        contador++;
        }
    }
    else printf ("Jogada Inválida\n");
        if (!pode_mover(e,get_coluna_anterior(e),get_linha_anterior(e))&&obter_jogador_atual(e)==1) jog2=1; 
        if (!pode_mover(e,get_coluna_anterior(e),get_linha_anterior(e))&&obter_jogador_atual(e)==2) jog1=1;
    }

    if (jog1) printf("Parabéns, o vendedor foi o Jogador 1\n");
    if (jog2) printf("Parabéns , o vendedor foi o Jogador 2\n");
return 1;
}


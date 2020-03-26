#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camada_de_dados.h"
#include "interface.h"
#include "logica.h"
#define BUF_SIZE 1024



//[0][7],[7][0],[3][5];

void mostrar_tabuleiro(ESTADO *e){
    int c,l,contagem=8;
    for(c=7;c>=0;c--){
       printf("%d|",contagem--);
        for(l=0;l<8;l++){
            if(obter_estado_casa(e,c,l)==BRANCA){
                putchar(' ');
                putchar('*');
                }
                else if(obter_estado_casa(e,c,l)==PRETA){
                        putchar(' ');
                        putchar('#');}
                        else if(l==0&&c==0){
                                putchar(' ');
                                putchar('1');
                                }
                                else if(l==7&&c==7){
                                        putchar(' ');
                                        putchar('2');}
                                        else {putchar(' '); putchar('.');}
        }
    putchar('\n');
    }
    printf("   a b c d e f g h");
    putchar('\n');
}




int interpretador(ESTADO *e) {
    int jog1=0,jog2=0,n_comandos=1;
    char linha[BUF_SIZE];
    char col[2], lin[2];
    char exit[2],save[BUF_SIZE];
    FILE *file;
    while (!jog1&&!jog2){
    printf("#%d -> PL %d ",n_comandos++,obter_jogador_atual(e));
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;   
    if(sscanf(linha, "%[Q||q]", exit)==1) return 0;
    //if(sscanf(linha,"%[gr] %s",save)) 
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2){
        COORDENADA coord = {*lin - '1',*col - 'a'}; 
        jogar(e, coord,&jog1,&jog2);
        aumenta_jogadas(e);
        mostrar_tabuleiro(e);
        modifica_jogador_atual(e);//# <número de comandos> PL<1 ou 2 conforme o jogador> (<número da jogada atual>)>
    }
    else printf ("Jogada Inválida\n");
        if (!pode_mover(e,get_coluna_anterior(e),get_linha_anterior(e))&&obter_jogador_atual(e)==1) jog2=1; 
        if (!pode_mover(e,get_coluna_anterior(e),get_linha_anterior(e))&&obter_jogador_atual(e)==2) jog1=1;
    }
    if (!jog1) printf("Parabéns, o vendedor foi o Jogador 1\n");
    if (!jog2) printf("Parabéns , o vendedor foi o Jogador 2\n");
return 1;
}



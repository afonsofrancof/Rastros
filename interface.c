#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camada_de_dados.h"
#include "interface.h"
#include "logica.h"
#define BUF_SIZE 1024

//[0][7],[7][0],[3][5];

void mostrar_tabuleiro(ESTADO *e){
    int c,l;
    for(c=0;c<8;c++){
        for(l=0;l<8;l++){
            if(obter_estado_casa(e,c,l)==BRANCA){
                putchar('*');
                }
                else if(obter_estado_casa(e,c,l)==PRETA)
                        putchar('#');
                        else if(l==0&&c==7){
                                putchar('1');
                                }
                                else if(l==7&&c==0)
                                        putchar('2');
                                        else putchar('.');
        }
    putchar('\n');
    }
    putchar('\n');
}




int interpretador(ESTADO *e) {
    int jog1=0,jog2=0;
    char linha[BUF_SIZE];
    char col[2], lin[2];
    while (!jog1&&!jog2){
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;    
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*lin - '1',*col - 'a'};
        jogar(e, coord,&jog1,&jog2);
        mostrar_tabuleiro(e);
    }
    }
    if (!jog1) printf("Parabéns, o vendedor foi o Jogador 1\n");
    if (!jog2) printf("Parabéns , o vendedor foi o Jogador 2\n");
return 1;
}
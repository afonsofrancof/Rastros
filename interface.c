#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camada_de_dados.h"
#include "interface.h"
#define BUF_SIZE 1024

//[0][7],[7][0],[3][5];

void mostrar_tabuleiro(ESTADO *e){
    int c,l;
    for(c=0;c<8;c++){
        for(l=0;l<8;l++){
            if((*e).tab[l][c]==BRANCA)
                putchar('*');
            if((*e).tab[l][c]==PRETA)
                putchar('#');
            else{
            if(l==0&&c==7) 
                putchar('2');
            if(l==7&&c==0)
                putchar('1');
            else putchar('.');}
        }
    }
    putchar('\n');
}




int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*lin - '1',*col - 'a'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
return 1;
}
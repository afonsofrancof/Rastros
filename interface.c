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

void mostrar_tabuleiro_gr(FILE *fp,ESTADO *e){
    int c,l;
    for(l=7;l>=0;l--){
        for(c=0;c<=7;c++){
            if(obter_estado_casa(e,c,l)==BRANCA){
                fputc('*',fp);
                }
                else if(obter_estado_casa(e,c,l)==PRETA){
                        fputc('#',fp);
                        }
                        else if(l==7&&c==7){
                                fputc('2',fp);
                                }
                                else if(l==0&&c==0){
                                        fputc('1',fp);}
                                        else  fputc('.',fp);
        }
    fputc('\n',fp);
    }
    fputc('\n',fp);
}
/*
void mostrar_tabuleiro_gr(FILE *fp,ESTADO *e){
    int c,l;
    for(l=7;l>=0;l--){
        for(c=0;c<=7;c++){
            fprintf(fp,"%c",e->tab[c][l]);
        }
    }
}
*/

void gravar(ESTADO *e,char *filename){
        FILE *fp;
        fp = fopen(filename,"w");
        mostrar_tabuleiro_gr(fp,e);
        fclose(fp);
}

void ler(ESTADO *e,char *filename){
    FILE *fp;
    fp = fopen(filename,"r");
    char buffer[BUF_SIZE];
    int l=7;
    while(fgets(buffer,BUF_SIZE,fp)!=NULL){
        for(int c = 0;c<=7;c++){
            set_casa(e,c,l,buffer[c]);
        }
        l--;
    }
    fclose(fp);
    mostrar_tabuleiro(e);
}



int interpretador(ESTADO *e) {
    int jog1=0,jog2=0,contador=1,jogada_valida;
    char linha[BUF_SIZE],col[2], lin[2],exit[2],aux[2],aux1[2],filename[BUF_SIZE];
    while (!jog1&&!jog2){ 
    printf("#%d  PL %d (%d) -> ",contador,obter_jogador_atual(e),get_jogada(e)); ///home/diogo/rastros/interface.c
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(sscanf(linha, "%[Q||q]", exit)==1) return 0;
    if(sscanf(linha,"%[g]%[r] %s",aux,aux1,filename)==3) gravar(e,filename);
    if(sscanf(linha,"%[r]%[d] %s",aux,aux1,filename)==3) ler(e,filename);
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a',*lin - '1'}; 
        jogada_valida =jogar(e, coord,&jog1,&jog2);
        mostrar_tabuleiro(e);
        if(jogada_valida) atualiza_jogadas(e);
        if(jogada_valida) {contador++;modifica_jogador_atual(e,&contador);//# <número de comandos> PL<1 ou 2 conforme o jogador> (<número da jogada atual>)>
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


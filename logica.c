#include <stdio.h>
#include <stdlib.h>
#include "camada_de_dados.h"
#include "logica.h"

int jogar(ESTADO *e, COORDENADA c,int *jog1,int *jog2){
  int col = c.coluna,lin = c.linha;
  printf("jogar %d %d\n", col, lin);
  if ((obter_estado_casa(e,col,lin)!=PRETA)&&(is_near_branca(e,col,lin))) { //((lin<8)&&(col<8)&&(lin>0)&&(col>0)) se for preciso verificar se está no tabuleiro
  put_branca(e,col,lin);
  put_preta(e);
  atualiza_ultima_jogada(e,col,lin);
  }
  else 
  printf("Jogada inválida\n");
  if (col==7&&lin==0)  *jog2 = 1;
  if (col==0&&lin==7)  *jog1 = 1; 
  return 1;
}
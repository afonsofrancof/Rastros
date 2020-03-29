#include <stdio.h>
#include <stdlib.h>
#include "camada_de_dados.h"
#include "logica.h"

int jogar(ESTADO *e, COORDENADA c,int *jog1,int *jog2){
  int col = get_coluna(c),lin=get_linha(c);
  if ((obter_estado_casa(e,col,lin)!=PRETA)&&(is_near_branca(e,col,lin))&&((lin!=get_linha_anterior(e))||(col!=get_coluna_anterior(e) ))){ // &&((lin<8)&&(col<8)&&(lin>=0)&&(col>=0))
  put_branca(e,col,lin);
  put_preta(e);
  atualiza_ultima_jogada(e,col,lin);
  armazena_jogada(e,c);
  if (col==7&&lin==7)  *jog2 = 1;
  if (col==0&&lin==0)  *jog1 = 1; 
  }
  else{
  printf("Jogada inválida\n");
  return 0;
  }
  return 1;
}
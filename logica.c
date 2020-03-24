#include <stdio.h>
#include <stdlib.h>
#include "camada_de_dados.h"
#include "logica.h"

int jogar(ESTADO *e, COORDENADA c){
  printf("jogar %d %d\n", c.linha, c.coluna);
  if ((c.linha<8)&&(c.coluna<8)&&(c.linha>0)&&(c.coluna>0))
  if (e->tab[c.linha] [c.coluna]!=PRETA) 
  e->tab[c.linha] [c.coluna]=BRANCA;
  else 
  printf("Jogada inválida");
  return 1;
}
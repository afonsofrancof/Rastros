#include <stdio.h>
#include <stdlib.h>
#include "camada_de_dados.h"
#include "logica.h"

int jogar(ESTADO *e, COORDENADA c){
  printf("jogar %d %d\n", c.linha, c.coluna);
  e->tab[c.linha] [c.coluna]=BRANCA;
  return 1;
}
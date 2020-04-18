#ifndef INTERFACE_H
#define INTERFACE_H

void mostrar_tabuleiro(ESTADO *e);
void mostrar_tabuleiro_gr(FILE *fp, ESTADO *e);
int interpretador(ESTADO *e);
void mostra_pos(ESTADO *e, int pos, int *contador);
int ler(ESTADO *e, char *filename);
void gravar(ESTADO *e, char *filename);

#endif
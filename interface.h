#ifndef INTERFACE_H
#define INTERFACE_H
/**
@file interface.h
Modulo da interface , para interação máquina-jogador
*/

/**
Mostra o tabuleiro atual 
*/
void mostrar_tabuleiro(ESTADO *e);
/**
Mostra o tabuleiro atual no file pointer passado no input 
*/
void mostrar_tabuleiro_gr(FILE *fp, ESTADO *e);
/**
Recebe e efetua as jogadas efetuadas e os várias comandos implementados
*/
int interpretador(ESTADO *e);
/**
Mostra o tabuleiro na jogada indicada no inputm fazendo as devidas alterações no estado para que o jogo possa continuar
*/
void mostra_pos(ESTADO *e, int pos, int *contador);

#endif
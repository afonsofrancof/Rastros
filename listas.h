#ifndef LISTAS_H
#define LISTAS_H

typedef struct nodo
{
    void *head;
    struct nodo *tail;
} * llig, listamalloc;
/**
@file listas.h
Modulo de listas ligadas
*/

/**
Cria uma lista vazia
*/
llig criar_lista();
/**
Insere um valor na cabeça da lista
*/
llig insere_cabeca(llig L, void *valor);
/** 
Devolve a cabeça da lista
*/
void *devolve_cabeca(llig L);
/** 
Devolve a cauda da lista
*/
llig proximo(llig L);
/**
Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda
*/
llig remove_cabeca(llig L);
/**
Devolve verdareiro se a lista é vazia
*/
int lista_esta_vazia(llig L);
/**
Determina o índice do menor elemento do array
*/
int menorelem(float *save, int *tamanho);

#endif
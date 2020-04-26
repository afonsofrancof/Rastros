#ifndef LISTAS_H
#define LISTAS_H

typedef struct nodo
{
    void *head;
    struct nodo *tail;
} * llig, listamalloc;

// Cria uma lista vazia
llig criar_lista();
// Insere um valor na cabeça da lista
llig insere_cabeca(llig L, void *valor);
// Devolve a cabeça da lista
void *devolve_cabeca(llig L);
// Devolve a cauda da lista
llig proximo(llig L);
// Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda
llig remove_cabeca(llig L);
// Devolve verdareiro se a lista é vazia
int lista_esta_vazia(llig L);
void imprimellig(llig l);
llig armazena_posicoes(ESTADO *e, llig lista, int *tamanho);

COORDENADA *selectcasas(ESTADO *e, llig lista, int *tamanho);

COORDENADA *devolveindice(llig lista, int indice);

float distanciacasas(COORDENADA *coord, int jog);

int menorelem(float *save, int *tamanho);

void jog(ESTADO *e);

#endif
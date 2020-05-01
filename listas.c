#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "camada_de_dados.h"
#include "logica.h"
#include "listas.h"

llig criar_lista()
{
    llig lista = malloc(sizeof(listamalloc));
    lista->head = NULL;
    lista->tail = NULL;
}

llig insere_cabeca(llig L, void *valor)
{
    llig temp;
    temp = malloc(sizeof(listamalloc));
    temp->tail = L;
    temp->head = valor;
    if (L->head == NULL)
        temp->tail = NULL;
    return temp;
}

void *devolve_cabeca(llig L) { return (L->head); }

llig proximo(llig L)
{
    return (L->tail);
}

llig remove_cabeca(llig L)
{
    L = L->tail;
    return L;
}

int lista_esta_vazia(llig L)
{
    int ans = 1;
    if (L->head)
        ans = 0;
    return ans;
}

COORDENADA *aloca_coord(COORDENADA c)
{
    COORDENADA *coord2 = (COORDENADA *)malloc(sizeof(COORDENADA) * 2);
    *coord2 = c;
    return coord2;
}

void imprimellig(llig l)
{
    while (l)
    {
        COORDENADA *coord = malloc(sizeof(COORDENADA) * 2);
        coord = l->head;
        printf("%d", coord->coluna);
        printf("%d", coord->linha);
        l = l->tail;
        putchar(' ');
    }
    putchar('\n');
}

int menorelem(float *save, int *tamanho)
{
    int menor = 0;
    for (int i = 0; i < (*tamanho); i++)
    {
        if (save[i] < save[menor])
            menor = i;
    }
    return menor;
}

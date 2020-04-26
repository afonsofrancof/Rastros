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

llig armazena_posicoes(ESTADO *e, llig lista, int *tamanho)
{
    int col, lin;
    *tamanho = 0;
    COORDENADA coord;
    col = obter_coluna_ult_jogada(e);
    lin = obter_linha_ult_jogada(e);
    if ((col - 1 >= 0 && lin + 1 <= 7) && !verifica_preta(e, col - 1, lin + 1))
    {
        COORDENADA coord = {col - 1, lin + 1};
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    if ((lin + 1 <= 7) && !verifica_preta(e, col, lin + 1))
    {
        coord.coluna = col;
        coord.linha = lin + 1;
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    if ((col + 1 <= 7 && lin + 1 <= 7) && !verifica_preta(e, col + 1, lin + 1))
    {
        coord.coluna = col + 1;
        coord.linha = lin + 1;
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    if ((col - 1 >= 0 && lin - 1 >= 0) && !verifica_preta(e, col - 1, lin - 1))
    {
        coord.coluna = col - 1;
        coord.linha = lin - 1;
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    if ((lin - 1 >= 0) && !verifica_preta(e, col, lin - 1))
    {
        coord.coluna = col;
        coord.linha = lin - 1;
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    if ((col + 1 <= 7 && lin - 1 >= 0) && !verifica_preta(e, col + 1, lin - 1))
    {
        coord.coluna = col + 1;
        coord.linha = lin - 1;
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    if ((col - 1 >= 0) && !verifica_preta(e, col - 1, lin))
    {
        coord.coluna = col - 1;
        coord.linha = lin;
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    if ((col + 1 <= 7) && !verifica_preta(e, col + 1, lin))
    {
        coord.coluna = col + 1;
        coord.linha = lin;
        lista = insere_cabeca(lista, aloca_coord(coord));
        (*tamanho)++;
    }
    return lista;
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

float distanciacasas(COORDENADA *coord, int jog)
{
    int catetox, catetoy;

    if (jog == 1)
    {
        catetox = coord->coluna;
        catetoy = coord->linha;
    }
    else
    {
        catetox = 7 - coord->coluna;
        catetoy = 7 - coord->linha;
    }
    float dist = sqrt((catetox ^ 2) + (catetoy ^ 2));
    return dist;
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

COORDENADA *devolveindice(llig lista, int indice) //[2,3,1,4,2,4,6] 2
{
    llig temp;
    temp = malloc(sizeof(listamalloc));
    temp = lista;
    for (int i = 0; i < indice; i++)
    {
        temp = temp->tail;
    }
    COORDENADA *coord = malloc(sizeof(listamalloc));
    coord = (temp->head);
    return coord;
}

COORDENADA *selectcasas(ESTADO *e, llig lista, int *tamanho)
{
    int jog = obter_jogador_atual(e);
    float save[8];
    COORDENADA *coord = malloc(sizeof(listamalloc));
    llig temp;
    temp = malloc(sizeof(listamalloc));
    temp = lista;
    for (int i = 0; i < (*tamanho); i++)
    {
        coord = temp->head;
        save[i] = distanciacasas(coord, jog);
        temp = temp->tail;
    }
    int menorindice = menorelem(save, tamanho);
    COORDENADA *coordfinal = malloc(sizeof(listamalloc));
    coordfinal = devolveindice(lista, menorindice);
    return coordfinal;
}

void jog(ESTADO *e)
{
    int tamanho = 0;
    llig lista;
    lista = criar_lista();
    lista = armazena_posicoes(e, lista, &tamanho);
    COORDENADA *posicao = malloc(sizeof(listamalloc));
    posicao = selectcasas(e, lista, &tamanho);
    COORDENADA coord = {posicao->coluna, posicao->linha};
    jogar(e, coord, 0, 0);
}
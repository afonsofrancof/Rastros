#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "listas.h"
#include "camada_de_dados.h"
#include "logica.h"
#include "interface.h"

#define BUF_SIZE 1024

ESTADO *inicializar_estado()
{
    ESTADO *e = (ESTADO *)malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->jogada = 1;
    for (int l = 7; l >= 0; l--)
        for (int c = 0; c <= 7; c++)
        {
            e->tab[c][l] = VAZIO;
        }
    e->tab[4][4] = BRANCA;
    e->ultima_jogada.linha = 4;
    e->ultima_jogada.coluna = 4;
    return e;
}

//Função que esvazia o tabuleiro

void empty_tabuleiro(ESTADO *e)
{
    for (int l = 7; l >= 0; l--)
    {
        for (int c = 0; c <= 7; c++)
        {
            e->tab[c][l] = VAZIO;
        }
    }
}

//Função que obtem o jogador atual

int obter_jogador_atual(ESTADO *estado)
{
    int j;
    j = estado->jogador_atual;
    return j;
}

//Função que obtem a casa de uma certa posição

CASA obter_estado_casa(ESTADO *estado, int c, int l)
{
    int casa;
    casa = estado->tab[c][l];
    return casa;
}

//Função que verifica se as coordenadas introduzidas estão a uma certa distância da peça branca

int is_near_branca(ESTADO *estado, int colatual, int linatual)
{
    int col, lin, ans;
    col = estado->ultima_jogada.coluna;
    lin = estado->ultima_jogada.linha;
    if ((abs(colatual - col) <= 1) && (abs(linatual - lin) <= 1))
        ans = 1;
    else
        ans = 0;
    return ans;
}

//Função que coloca a peça branca nas coordenadas do input

void put_branca(ESTADO *estado, int col, int lin)
{
    estado->tab[col][lin] = BRANCA;
}

//Função que coloca uma peça preta nas coordenadas da jogada anterior

void put_preta(ESTADO *estado)
{
    int col, lin;
    col = estado->ultima_jogada.coluna;
    lin = estado->ultima_jogada.linha;
    estado->tab[col][lin] = PRETA;
}

//Função que atualiza a ultima jogada para a jogada que acabou de ser feita

void atualiza_ultima_jogada(ESTADO *estado, int col, int lin)
{
    estado->ultima_jogada.coluna = col;
    estado->ultima_jogada.linha = lin;
}

//Função que verifica se a peça nas coordenadas passadas no input é preta

int verifica_preta(ESTADO *estado, int col, int lin)
{
    int ans = 0;
    if (estado->tab[col][lin] == PRETA)
        ans = 1;
    return ans;
}

//Função que determina se o jogador se pode mover tendo em conta todos os possíveis obstáculos como os cantos do tabuleiro e a existencia de peças pretas no caminho.

int pode_mover(ESTADO *estado, int col, int lin)
{
    int ans = 1;
    if (col == 0 && lin == 7) // canto superior esquerdo
        if ((verifica_preta(estado, col + 1, lin)) && (verifica_preta(estado, col + 1, lin - 1)) && (verifica_preta(estado, col, lin - 1)))
            ans = 0;
    if (col == 7 && lin == 0) // canto inferior direito
        if ((verifica_preta(estado, col - 1, lin)) && (verifica_preta(estado, col, lin + 1)) && (verifica_preta(estado, col - 1, lin + 1)))
            ans = 0;
    if (lin == 7 && col != 7 && col != 0) // linha de cima sem os 2 cantos
        if ((verifica_preta(estado, col, lin - 1)) && (verifica_preta(estado, col + 1, lin - 1)) && (verifica_preta(estado, col - 1, lin - 1)) && (verifica_preta(estado, col - 1, lin)) && (verifica_preta(estado, col + 1, lin)))
            ans = 0;
    if (col == 0 && lin != 0 && lin != 7) // coluna da esquerda sem os 2 cantos
        if ((verifica_preta(estado, col, lin - 1)) && (verifica_preta(estado, col, lin + 1)) && (verifica_preta(estado, col + 1, lin)) && (verifica_preta(estado, col + 1, lin - 1)) && (verifica_preta(estado, col + 1, lin + 1)))
            ans = 0;
    if (lin == 0 && col != 0 && col != 7) // linha de baixo sem os 2 cantos
        if ((verifica_preta(estado, col, lin + 1)) && (verifica_preta(estado, col - 1, lin)) && (verifica_preta(estado, col + 1, lin)) && (verifica_preta(estado, col - 1, lin + 1)) && (verifica_preta(estado, col + 1, lin + 1)))
            ans = 0;
    if (lin != 7 && lin != 0 && col == 7) // coluna da direita sem os 2 cantos
        if ((verifica_preta(estado, col, lin + 1)) && (verifica_preta(estado, col, lin - 1)) && (verifica_preta(estado, col - 1, lin)) && (verifica_preta(estado, col - 1, lin - 1)) && (verifica_preta(estado, col - 1, lin + 1)))
            ans = 0;
    if (ans)
        if ((verifica_preta(estado, col, lin + 1)) && (verifica_preta(estado, col, lin - 1)) && (verifica_preta(estado, col + 1, lin)) && (verifica_preta(estado, col - 1, lin)) && (verifica_preta(estado, col - 1, lin + 1)) && (verifica_preta(estado, col + 1, lin + 1)) && (verifica_preta(estado, col + 1, lin - 1)) && (verifica_preta(estado, col - 1, lin - 1)))
            ans = 0;
    return ans;
}

//Função que modifica o jogador atual

void modifica_jogador_atual(ESTADO *estado, int contador)
{
    if (contador == 1)
        estado->jogador_atual = 2;
    else
    {
        if (contador % 2 == 1)
            estado->jogador_atual = 1;
        else
            estado->jogador_atual = 2;
    }
}

//Função que obtem a coluna anterior através do estado

int get_coluna_anterior(ESTADO *estado)
{
    int a;
    a = estado->ultima_jogada.coluna;
    return a;
}

//Função que obtem a linha anterior através do estado

int get_linha_anterior(ESTADO *estado)
{
    int a;
    a = estado->ultima_jogada.linha;
    return a;
}

//Função que obtem a coluna

int get_coluna(COORDENADA coord)
{
    int a;
    a = coord.coluna;
    return a;
}

//Função que obtem a linha

int get_linha(COORDENADA coord)
{
    int a;
    a = coord.linha;
    return a;
}

//Função que obtem a jogada

int get_jogada(ESTADO *estado)
{
    int a;
    a = estado->jogada;
    return a;
}

//Função que atualiza o número de jogadas através dependendo do jogador atual

int atualiza_jogadas(ESTADO *estado)
{
    int j = estado->jogador_atual;
    if (j == 2)
        estado->jogada++;
    return get_jogada(estado);
}

//Função que analiza o tabuleiro imprimido e adiciona a informação que recebe sobre as peças

void set_casa(ESTADO *e, int c, int l, CASA casa)
{
    switch (casa)
    {
    case '*':
        e->tab[c][l] = BRANCA;
        e->ultima_jogada.coluna = c;
        e->ultima_jogada.linha = l;
        break;
    case '#':
        e->tab[c][l] = PRETA;
        break;
    case '.':
        e->tab[c][l] = VAZIO;
        break;
    }
}
/*
//teste

void teste(CASA casa)
{
    switch (casa)
    {
    case '*':
        printf("BRANCA");
        break;
    case '#':
        printf("PRETA");
        break;
    case '.':
        printf("VAZIO");
        break;
    }
}

*/

//Função que armazena no array jogadas[32] as jogadas à medida em que são feitas

void armazena_jogada(ESTADO *e, COORDENADA c)
{
    if (obter_jogador_atual(e) == 1)
        e->jogadas[get_jogada(e)].jogador1 = c;
    else
        e->jogadas[get_jogada(e)].jogador2 = c;
}

/**

*/
void print_string(char *string)
{
    for (int i = 0; string[i]; i++)
    {
        putchar(string[i]);
    }
}
/**
Função que imprime as jogadas efetuadas até aquela etapa do jogo, com os repetivos números das jogadas
*/

void fdisplay_jogadas(FILE *fp, ESTADO *e)
{
    int i, num_jogadas;
    if (obter_jogador_atual(e) == 1)
        num_jogadas = get_jogada(e) - 1;
    else
        num_jogadas = get_jogada(e);

    for (i = 2; i <= num_jogadas + 1; i++)
    {
        fprintf(fp, "%02d: ", i - 1);
        imprime_play(e, i, 1, fp);
        fputc(' ', fp);
        if (!(i == num_jogadas + 1 && obter_jogador_atual(e) == 2))
        {
            imprime_play(e, i, 2, fp);
        }
        fputc('\n', fp);
    }
}

void le_e_escreve_jogadas(ESTADO *e, int col, int lin, int n_jogada, int jog)
{
    if (jog == 1)
    {
        e->jogadas[n_jogada].jogador1.coluna = col;
        e->jogadas[n_jogada].jogador1.linha = lin;
    }
    else
    {
        e->jogadas[n_jogada].jogador2.coluna = col;
        e->jogadas[n_jogada].jogador2.linha = lin;
    }
}

//Função que vai ao estado e introduz o número de jogadas passado no input

void put_jogada(ESTADO *e, int jogada)
{
    e->jogada = jogada;
}

//Função que vai ao estado e introduz o jogador atual passado no input

void put_jogador_atual(ESTADO *e, int jog)
{
    e->jogador_atual = jog;
}

//Função que efetua todas as jogadas existentes no array backup

int jogar_pos(ESTADO *e, JOGADAS backup, int pos)
{
    int contador = 1;
    for (int u = 1; u <= pos; u++)
    {
        jogar(e, backup[u].jogador1, 0, 0);
        atualiza_jogadas(e);
        contador++;
        modifica_jogador_atual(e, contador);
        jogar(e, backup[u].jogador2, 0, 0);
        atualiza_jogadas(e);
        contador++;
        modifica_jogador_atual(e, contador);
    }
    return contador;
}

void array_backup(ESTADO *e, JOGADAS backup, int pos)
{
    for (int i = 0; i <= pos; i++)
    {
        backup[i].jogador1 = e->jogadas[i].jogador1;
        backup[i].jogador2 = e->jogadas[i].jogador2;
    }
}

void imprime_play(ESTADO *e, int n_jogada, int jogador, FILE *fp)
{
    n_jogada--;
    int col, lin;
    if (jogador == 1)
    {
        col = e->jogadas[n_jogada].jogador1.coluna;
        lin = e->jogadas[n_jogada].jogador1.linha;
        fprintf(fp, "%c", col + 'a');
        fprintf(fp, "%d", lin + 1);
    }
    else
    {
        col = e->jogadas[n_jogada].jogador2.coluna;
        lin = e->jogadas[n_jogada].jogador2.linha;
        fprintf(fp, "%c", col + 'a');
        fprintf(fp, "%d", lin + 1);
    }
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
        printf("%f \n", save[i]);
        temp = temp->tail;
    }
    int menorindice = menorelem(save, tamanho);
    COORDENADA *coordfinal = malloc(sizeof(listamalloc));
    coordfinal = devolveindice(lista, menorindice);
    return coordfinal;
}

void jogEuclidiano(ESTADO *e, int *jog1, int *jog2)
{
    int tamanho = 0;
    llig lista;
    lista = criar_lista();
    lista = armazena_posicoes(e, lista, &tamanho);
    COORDENADA *posicao = malloc(sizeof(listamalloc));
    posicao = selectcasas(e, lista, &tamanho);
    COORDENADA coord = {posicao->coluna, posicao->linha};
    jogar(e, coord, jog1, jog2);
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

float distanciacasas(COORDENADA *coord, int jog)
{
    int catetox, catetoy;
    float dist;
    if (jog == 1)
    {
        catetox = coord->coluna;
        catetoy = coord->linha;
        dist = sqrt((catetox * catetox) + (catetoy * catetoy));
        printf("Jog1 : ");
        return dist;
    }
    else
    {
        catetox = coord->coluna;
        catetoy = coord->linha;
        dist = sqrt((7 - catetox) * (7 - catetox) + (7 - catetoy) * (7 - catetoy));
        printf("Jog2 : ");
        return dist;
    }
}

llig armazena_posicoes(ESTADO *e, llig lista, int *tamanho)
{
    int col, lin;
    *tamanho = 0;
    COORDENADA coord;
    col = get_coluna_anterior(e);
    lin = get_linha_anterior(e);
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

void ler(ESTADO *e, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    char buffer[BUF_SIZE];
    int l = 7, contador = 0, n_jogada = 0, col, lin, i = 0;
    while (fgets(buffer, BUF_SIZE, fp) != NULL)
    {
        for (int c = 0; c <= 7 && l >= 0; c++)
        {
            set_casa(e, c, l, buffer[c]);
        }
        l--;
        contador++;
        if (contador >= 10 && buffer[i++])
        {
            n_jogada = contador - 10;
            col = buffer[4] - 'a';
            lin = buffer[5] - '1';
            le_e_escreve_jogadas(e, col, lin, n_jogada + 1, 1);
            col = buffer[7] - 'a';
            lin = buffer[8] - '1';
            le_e_escreve_jogadas(e, col, lin, n_jogada + 1, 2);
        }
    }
    if (!buffer[7])
        e->jogador_atual = 2;
    else
        e->jogador_atual = 1;
    e->jogada = n_jogada + 2;

    fclose(fp);
    mostrar_tabuleiro(e);
}

void gravar(ESTADO *e, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    mostrar_tabuleiro_gr(fp, e);
    fputc('\n', fp);
    fdisplay_jogadas(fp, e);
    fclose(fp);
}

void jogRandom(ESTADO *e, int *jog1, int *jog2)
{
    int tamanho = 0, indice;
    llig lista;
    lista = criar_lista();
    lista = armazena_posicoes(e, lista, &tamanho);
    indice = rand() % tamanho;
    COORDENADA *posicao = malloc(sizeof(listamalloc));
    posicao = devolveindice(lista, indice);
    COORDENADA coord = {posicao->coluna, posicao->linha};
    jogar(e, coord, jog1, jog2);
}

COORDENADA *aloca_coord(COORDENADA c)
{
    COORDENADA *coord2 = (COORDENADA *)malloc(sizeof(COORDENADA) * 2);
    *coord2 = c;
    return coord2;
}
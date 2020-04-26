#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "camada_de_dados.h"
#include "logica.h"

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

int obter_jogador_atual(ESTADO *estado)
{
    int j;
    j = estado->jogador_atual;
    return j;
}

CASA obter_estado_casa(ESTADO *estado, int c, int l)
{
    int casa;
    casa = estado->tab[c][l];
    return casa;
}

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

void put_branca(ESTADO *estado, int col, int lin)
{
    estado->tab[col][lin] = BRANCA;
}

void put_preta(ESTADO *estado)
{
    int col, lin;
    col = estado->ultima_jogada.coluna;
    lin = estado->ultima_jogada.linha;
    estado->tab[col][lin] = PRETA;
}

void atualiza_ultima_jogada(ESTADO *estado, int col, int lin)
{
    estado->ultima_jogada.coluna = col;
    estado->ultima_jogada.linha = lin;
}

int verifica_preta(ESTADO *estado, int col, int lin)
{
    int ans = 0;
    if (estado->tab[col][lin] == PRETA)
        ans = 1;
    return ans;
}

int pode_mover(ESTADO *estado, int col, int lin)
{
    int ans = 1;
    if (col == 0 && lin == 7) // canto superior esquerdo
        if ((verifica_preta(estado, col - 1, lin)) && (verifica_preta(estado, col + 1, lin - 1)) && (verifica_preta(estado, col, lin - 1)))
            ans = 0;
    if (col == 7 && lin == 0) // canto inferior direito
        if ((verifica_preta(estado, col + 1, lin)) && (verifica_preta(estado, col, lin + 1)) && (verifica_preta(estado, col - 1, lin - 1)))
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

int get_coluna_anterior(ESTADO *estado)
{
    int a;
    a = estado->ultima_jogada.coluna;
    return a;
}

int get_linha_anterior(ESTADO *estado)
{
    int a;
    a = estado->ultima_jogada.linha;
    return a;
}

int get_coluna(COORDENADA coord)
{
    int a;
    a = coord.coluna;
    return a;
}

int get_linha(COORDENADA coord)
{
    int a;
    a = coord.linha;
    return a;
}

int get_jogada(ESTADO *estado)
{
    int a;
    a = estado->jogada;
    return a;
}

int atualiza_jogadas(ESTADO *estado)
{
    int j = estado->jogador_atual;
    if (j == 2)
        estado->jogada++;
    return get_jogada(estado);
}

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

void armazena_jogada(ESTADO *e, COORDENADA c)
{
    if (obter_jogador_atual(e) == 1)
        e->jogadas[get_jogada(e)].jogador1 = c;
    else
        e->jogadas[get_jogada(e)].jogador2 = c;
}

void get_and_transforma_jogadas(ESTADO *e, int jog, int numero_da_jogada, char *coordenada)
{
    int col, lin;
    if (jog == 1)
    {
        col = e->jogadas[numero_da_jogada].jogador1.coluna;
        lin = e->jogadas[numero_da_jogada].jogador1.linha + 1;
    }
    else
    {
        col = e->jogadas[numero_da_jogada].jogador2.coluna;
        lin = e->jogadas[numero_da_jogada].jogador2.linha + 1;
    }

    coordenada[0] = col + 'a';
    coordenada[1] = lin + '0';
}

void print_string(char *string)
{
    for (int i = 0; string[i]; i++)
    {
        putchar(string[i]);
    }
}

void fprint_string(FILE *fp, char *string)
{
    for (int i = 0; string[i]; i++)
    {
        fputc(string[i], fp);
    }
}
/*
void display_jogadas(ESTADO *e){
    int i,num_jogadas;
    if (obter_jogador_atual(e)==1) num_jogadas = get_jogada(e)-1;
    else num_jogadas = get_jogada(e);
    char coordenada_final[]="a";
    for(i=0;i<=num_jogadas;i++){
        printf("%02d : ",i);
        get_and_transforma_jogadas(e,1,i,coordenada_final);
        print_string(coordenada_final);
        get_and_transforma_jogadas(e,2,i,coordenada_final);
        putchar(' ');
        print_string(coordenada_final);
        putchar('\');
    }
}
*/

void fdisplay_jogadas(FILE *fp, ESTADO *e)
{
    int i, num_jogadas;
    if (obter_jogador_atual(e) == 1)
        num_jogadas = get_jogada(e) - 1;
    else
        num_jogadas = get_jogada(e);
    char coordenada_final[] = "a";

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

void put_jogada(ESTADO *e, int jogada)
{
    e->jogada = jogada;
}

void put_jogador_atual(ESTADO *e, int jog)
{
    e->jogador_atual = jog;
}

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

void ImprimeJogadas(ESTADO *e, int num_jogadas)
{
    int col, lin;
    for (int i = 0; i <= num_jogadas; i++)
    {
        col = e->jogadas[i].jogador1.coluna;
        lin = e->jogadas[i].jogador1.linha;
        printf("Jog1 ");
        printf("%c", col + 'a');
        printf("%d", lin + 1);
        putchar(' ');
        putchar('|');
        putchar(' ');
        col = e->jogadas[i].jogador2.coluna;
        lin = e->jogadas[i].jogador2.linha;
        printf("Jog2 ");
        printf("%c", col + 'a');
        printf("%d", lin + 1);
        putchar('\n');
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

int obter_coluna_ult_jogada(ESTADO *e)
{
    return (e->ultima_jogada.coluna);
}
int obter_linha_ult_jogada(ESTADO *e)
{
    return (e->ultima_jogada.linha);
}
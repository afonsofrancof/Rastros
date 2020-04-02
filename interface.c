#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camada_de_dados.h"
#include "interface.h"
#include "logica.h"
#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e)
{
    int c, l, contagem = 8;
    for (l = 7; l >= 0; l--)
    {
        printf("%d|", contagem--);
        for (c = 0; c <= 7; c++)
        {
            if (obter_estado_casa(e, c, l) == BRANCA)
            {
                putchar(' ');
                putchar('*');
            }
            else if (obter_estado_casa(e, c, l) == PRETA)
            {
                putchar(' ');
                putchar('#');
            }
            else if (l == 7 && c == 7)
            {
                putchar(' ');
                putchar('2');
            }
            else if (l == 0 && c == 0)
            {
                putchar(' ');
                putchar('1');
            }
            else
            {
                putchar(' ');
                putchar('.');
            }
        }
        putchar('\n');
    }
    printf("   a b c d e f g h");
    putchar('\n');
}

void mostrar_tabuleiro_gr(FILE *fp, ESTADO *e)
{
    int c, l;
    for (l = 7; l >= 0; l--)
    {
        for (c = 0; c <= 7; c++)
        {
            if (obter_estado_casa(e, c, l) == BRANCA)
            {
                fputc('*', fp);
            }
            else if (obter_estado_casa(e, c, l) == PRETA)
            {
                fputc('#', fp);
            }
            else if (l == 7 && c == 7)
            {
                fputc('2', fp);
            }
            else if (l == 0 && c == 0)
            {
                fputc('1', fp);
            }
            else
                fputc('.', fp);
        }
        fputc('\n', fp);
    }
}
/*
void mostrar_tabuleiro_gr(FILE *fp,ESTADO *e){
    int c,l;
    for(l=7;l>=0;l--){
        for(c=0;c<=7;c++){
            fprintf(fp,"%c",e->tab[c][l]);
        }
    }
}
*/

void gravar(ESTADO *e, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    mostrar_tabuleiro_gr(fp, e);
    fputc('\n', fp);
    fdisplay_jogadas(fp, e);
    fclose(fp);
}

void ler(ESTADO *e, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    char buffer[BUF_SIZE];
    int l = 7, contador = 0, n_jogada, col, lin, i;
    while (fgets(buffer, BUF_SIZE, fp) != NULL)
    {
        for (int c = 0; c <= 7 && l >= 0; c++)
        {
            set_casa(e, c, l, buffer[c]);
        }
        l--;
        contador++;
        for (contador = 8; contador >= 8 && buffer[i] != '\n'; contador++, i++)
        {
            n_jogada = contador - 7;
            col = buffer[4] - 'a';
            lin = buffer[5] - '0';
            le_e_escreve_jogadas(e, col, lin, n_jogada, 1);
            col = buffer[7] - 'a';
            lin = buffer[8] - '0';
            le_e_escreve_jogadas(e, col, lin, n_jogada, 2);
        }
    }
    fclose(fp);
    mostrar_tabuleiro(e);
}

/* ESTADO *inicializar_estado()
{
    ESTADO *e = (ESTADO *)malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->num_jogadas = 1;
    e->jogada = 0;
    for (int l = 7; l <= 0; l--)
        for (int c = 0; c <= 7; c++)
        {
            e->tab[c][l] = VAZIO;
        }
    e->tab[4][4] = BRANCA;
    e->ultima_jogada.linha = 4;
    e->ultima_jogada.coluna = 4;
    return e;
} */

void mostra_pos(ESTADO *e, int pos, int *jog1, int *jog2)
{
    int contador = 0;
    JOGADAS backup;
    for (int i = 0; i <= pos; i++)
    {
        backup[i].jogador1 = e->jogadas[i].jogador1;
        backup[i].jogador2 = e->jogadas[i].jogador2;
    }
    e->jogador_atual = 1;
    e->num_jogadas = 1;
    e->jogada = 0;
    for (int l = 7; l <= 0; l--)
        for (int c = 0; c <= 7; c++)
        {
            e->tab[c][l] = VAZIO;
        }
    e->tab[4][4] = BRANCA;
    e->ultima_jogada.linha = 4;
    e->ultima_jogada.coluna = 4;
    for (int u = 0; u <= pos; u++)
    {
        jogar(e, backup[u].jogador1, jog1, jog2);
        atualiza_jogadas(e);
        jogar(e, backup[u].jogador2, jog1, jog2);
        atualiza_jogadas(e);
        contador++;
        modifica_jogador_atual(e, &contador);
    }
    mostrar_tabuleiro(e);
}

int interpretador(ESTADO *e)
{
    int jog1 = 0, jog2 = 0, contador = 1, jogada_valida, movs_int[2];
    char linha[BUF_SIZE], col[2], lin[2], exit[2], aux[2], aux1[2], filename[BUF_SIZE];
    while (!jog1 && !jog2)
    {
        printf("#%d  PL %d (%d) -> ", contador, obter_jogador_atual(e), get_jogada(e)); ///home/diogo/rastros/interface.c
        if (fgets(linha, BUF_SIZE, stdin) == NULL)
            return 0;
        if (sscanf(linha, "%[Q||q]", exit) == 1)
            return 0;
        if (sscanf(linha, "%[p]%[o]%[s] %d", aux, aux, aux, movs_int) == 4)
            mostra_pos(e, movs_int[0], &jog1, &jog2);
        if (sscanf(linha, "%[m]%[o]%[v]%[s]", aux, aux, aux, aux) == 4)
            fdisplay_jogadas(stdout, e);
        if (sscanf(linha, "%[g]%[r] %s", aux, aux1, filename) == 3)
            gravar(e, filename);
        if (sscanf(linha, "%[r]%[d] %s", aux, aux1, filename) == 3)
            ler(e, filename);
        if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2)
        {
            COORDENADA coord = {*col - 'a', *lin - '1'};
            jogada_valida = jogar(e, coord, &jog1, &jog2);
            mostrar_tabuleiro(e);
            if (jogada_valida)
                atualiza_jogadas(e);
            if (jogada_valida)
            {
                contador++;
                modifica_jogador_atual(e, &contador); //# <número de comandos> PL<1 ou 2 conforme o jogador> (<número da jogada atual>)>
            }
        }
        else
            printf("Jogada Inválida\n");
        if (!pode_mover(e, get_coluna_anterior(e), get_linha_anterior(e)) && obter_jogador_atual(e) == 1)
            jog2 = 1;
        if (!pode_mover(e, get_coluna_anterior(e), get_linha_anterior(e)) && obter_jogador_atual(e) == 2)
            jog1 = 1;
    }

    if (jog1)
        printf("Parabéns, o vendedor foi o Jogador 1\n");
    if (jog2)
        printf("Parabéns , o vendedor foi o Jogador 2\n");
    return 1;
}

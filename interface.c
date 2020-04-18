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

void gravar(ESTADO *e, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w");
    mostrar_tabuleiro_gr(fp, e);
    fputc('\n', fp);
    fdisplay_jogadas(fp, e);
    fclose(fp);
}

/* void ler(ESTADO *e, char *filename)
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
} */
int ler(ESTADO *e, char *filename)
{
    FILE *fp;
    putchar('2');
    fp = fopen(filename, "r");
    char buffer[BUF_SIZE];
    int col, lin, control = 0, i;
    int contador = 1;
    put_jogador_atual(e, 1);
    put_jogada(e, 1);
    empty_tabuleiro(e);
    put_branca(e, 4, 4);
    atualiza_ultima_jogada(e, 4, 4);
    while (fgets(buffer, BUF_SIZE, fp) != NULL)
    {
        control++;
        for (control = 8, i = 0; control >= 8 && buffer[i]; control++, i++)
        {
            col = buffer[4] - 'a';
            lin = buffer[5] - '0';
            COORDENADA cjog1 = {col, lin};
            jogar(e, cjog1, 0, 0);
            contador++;
            atualiza_jogadas(e);
            modifica_jogador_atual(e, contador);
            col = buffer[7] - 'a';
            lin = buffer[8] - '0';
            COORDENADA cjog2 = {col, lin};
            jogar(e, cjog2, 0, 0);
            contador++;
            atualiza_jogadas(e);
            modifica_jogador_atual(e, contador);
        }
    }
    fclose(fp);
    mostrar_tabuleiro(e);
    return contador;
}

void mostra_pos(ESTADO *e, int pos, int *contador)
{

    JOGADAS backup;
    array_backup(e, backup, pos);
    put_jogador_atual(e, 1);
    put_jogada(e, 1);
    empty_tabuleiro(e);
    put_branca(e, 4, 4);
    atualiza_ultima_jogada(e, 4, 4);
    *contador = jogar_pos(e, backup, pos);
    mostrar_tabuleiro(e);
}

int interpretador(ESTADO *e)
{
    int jog1 = 0, jog2 = 0, contador = 1, num_comandos = 1, jogada_valida, movs_int[BUF_SIZE];
    char linha[BUF_SIZE], col[2], lin[2], exit[2], aux[2], aux1[2], filename[BUF_SIZE];
    while (!jog1 && !jog2)
    {
        printf("#%d  PL %d (%d) -> ", num_comandos, obter_jogador_atual(e), get_jogada(e)); ///home/diogo/rastros/interface.c
        if (fgets(linha, BUF_SIZE, stdin) == NULL)
            return 0;
        else if (sscanf(linha, "%[Q||q]", exit) == 1)
            return 0;
        else if (sscanf(linha, "%[p]%[o]%[s] %d", aux, aux, aux, movs_int) == 4)
        {
            mostra_pos(e, movs_int[0], &contador);
            num_comandos++;
        }
        else if (sscanf(linha, "%[m]%[o]%[v]%[s]", aux, aux, aux, aux) == 4)
        {
            fdisplay_jogadas(stdout, e);
            num_comandos++;
        }
        else if (sscanf(linha, "%[g]%[r] %s", aux, aux1, filename) == 3)
        {
            gravar(e, filename);
            num_comandos++;
        }
        else if (sscanf(linha, "%[r]%[d] %s", aux, aux1, filename) == 3)
        {
            contador = ler(e, filename);
            num_comandos++;
        }
        else if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2)
        {
            num_comandos++;
            COORDENADA coord = {*col - 'a', *lin - '1'};
            jogada_valida = jogar(e, coord, &jog1, &jog2);
            mostrar_tabuleiro(e);
            if (jogada_valida)
            {
                atualiza_jogadas(e); //alterado
                contador++;
                modifica_jogador_atual(e, contador); //# <número de comandos> PL<1 ou 2 conforme o jogador> (<número da jogada atual>)>
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

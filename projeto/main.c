#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "camada_de_dados.h"
#include "logica.h"
#include "interface.h"

int main()
{
    ESTADO *e = inicializar_estado();
    mostrar_tabuleiro(e);
    interpretador(e);
    return 0;
}
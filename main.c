#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./backtracking.h"
#include "./heuristica.h"
#include "./leitura.h"
#include "./saida.h"
#include "./cronometro.h"
#include "./estrutura-de-dados/lista.h"
#include "filaSu.h"

int main(){
    Fila* sudokus = leitura("./su-do-ku.txt");
    imprimirFilaSu(sudokus);


    //struct timeval inicio = iniciaCronometro();
    //finalizaCronometro(inicio," ", 0);
    
    //resolveSudokuHeuristica(sudokus);

    printf("------\n");

    //resolveSudokuForcaBruta(sudokus);

    destroiFilaSu(sudokus);
    return 0;
}
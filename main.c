#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./backtracking.h"
#include "./heuristica.h"
#include "./leitura.h"
#include "./saida.h"
#include "./cronometro.h"  //no linux é show
#include "./estrutura-de-dados/lista.h"
#include "./estrutura-de-dados/filaSu.h"

double tempoDecorrido = 0.0;

int main(int arg, char *argv[]){
    Fila* sudokus = leitura("./su-do-ku.txt");
    //imprimirFilaSu(sudokus);
    
    //resolveSudokuHeuristica(sudokus);

    printf("------\n");

    resolveSudokuForcaBruta(sudokus, argv[1]);

    destroiFilaSu(sudokus);
    return 0;
}
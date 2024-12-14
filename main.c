#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./backtracking.h"
#include "./heuristica.h"
#include "./leitura.h"
#include "./saida.h"
#include "./cronometro.h"
#include "./estrutura-de-dados/lista.h"

int main(){
    int **sudoku = leitura("./su-do-ku.txt");
    imprimeSudoku(sudoku);

    //struct timeval inicio = iniciaCronometro();
    //finalizaCronometro(inicio," ", 0);
    
    resolveSudokuHeuristica(sudoku);

    printf("------\n");

    resolveSudokuForcaBruta(sudoku);
    
    destroiSudokuInt(sudoku);
    return 0;
}
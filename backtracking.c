#include <stdio.h>
#include <stdlib.h>
#include "./saida.h"
#include "./sudoku.h"

int backtracking(int **sudoku) {
    for (int linha = 0; linha < 9; linha++) {
        for (int coluna = 0; coluna < 9; coluna++) {
            if (sudoku[linha][coluna] == 0) {
                int *list = (int*) malloc (sizeof(int) * 9);
                for(int i = 0; i < 9; i++) list[i] = i+1;

                for (int k = 0; k < 9; k++) {
                    if (posicaoSegura(sudoku, list[k], linha, coluna)) {
                        sudoku[linha][coluna] = list[k];
                        if (backtracking(sudoku)) {
                            return 1;
                        }
                        sudoku[linha][coluna] = 0; 
                    }
                }
                free(list);
                return 0; 
            }
        }
    }
    return 1;
}


void resolveSudokuForcaBruta(int **sudoku){
    backtracking(sudoku);
    imprimeSudoku(sudoku);
}
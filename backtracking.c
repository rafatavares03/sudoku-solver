#include <stdio.h>
#include <stdlib.h>
#include "./saida.h"
#include "./sudoku.h"

void listaRamdom(int *list){
    // 5 trocas
    for(int i = 0; i < 5; i++){
        int x = rand() % 9;
        int y = rand() % 9;
        int aux = list[x];
        list[x] = list[y];
        list[y] = aux;
    }
}

int backtracking(int **sudoku) {
    for (int linha = 0; linha < 9; linha++) {
        for (int coluna = 0; coluna < 9; coluna++) {
            if (sudoku[linha][coluna] == 0) {
                int *list = (int*) malloc (sizeof(int) * 9);
                for(int i = 0; i < 9; i++) list[i] = i+1;
                listaRamdom(list);

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
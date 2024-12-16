#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "./sudoku.h"

// ----------------------------------------------------- //

char** alocaSudoku(){
    char **sudoku = (char**) malloc (DimensaoSudoku * sizeof(char*));
    for(int i = 0; i < DimensaoSudoku; i++){
        sudoku[i] = (char*) malloc (DimensaoSudoku * sizeof(char));        
    } 
    return sudoku;
}

int** alocaSudokuInt(){
    int **sudoku = (int**) malloc (DimensaoSudoku * sizeof(int*));
    for(int i = 0; i < DimensaoSudoku; i++){
        sudoku[i] = (int*) malloc (DimensaoSudoku * sizeof(int));        
    } 
    return sudoku;
}

void destroiSudoku(char** sudoku){
    for(int i = 0; i < DimensaoSudoku; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}

void destroiSudokuInt(int** sudoku){
    for(int i = 0; i < DimensaoSudoku; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}

int **copiaSudoku(int **original){
    int  **copia = alocaSudokuInt();
    for(int i = 0; i < DimensaoSudoku; i++){
        for(int j = 0; j < DimensaoSudoku ; j++){
            copia[i][j] = original[i][j];
        }
    }
    return copia;
}

int posicaoSegura(int **sudoku, int num, int linha, int coluna) {
    for (int i = 0; i < DimensaoSudoku; i++) {
        if (sudoku[linha][i] == num || sudoku[i][coluna] == num) {
            return 0;
        }
    }

    int blocoLinha = (linha / 3);
    blocoLinha *= 3;
    int blocoColuna = (coluna / 3);
    blocoColuna *= 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[blocoLinha + i][blocoColuna + j] == num) {
                return 0;
            }
        }

    }

    return 1;
}

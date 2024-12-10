#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "./sudoku.h"

//int **0alocaSudokuInt();
//char **alocaSudoku();
//void destroiSudoku(char **sudoku);


// ----------------------------------------------------- //

char** alocaSudoku(){
    char **sudoku = (char**) malloc (9 * sizeof(char*));
    for(int i = 0; i < 9; i++){
        sudoku[i] = (char*) malloc (9 * sizeof(char));        
    } 
    return sudoku;
}

int** alocaSudokuInt(){
    int **sudoku = (int**) malloc (9 * sizeof(int*));
    for(int i = 0; i < 9; i++){
        sudoku[i] = (int*) malloc (9 * sizeof(int));        
    } 
    return sudoku;
}

void destroiSudoku(char** sudoku){
    for(int i = 0; i < 9; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}

void destroiSudokuInt(int** sudoku){
    for(int i = 0; i < 9; i++){
        free(sudoku[i]);
    }
    free(sudoku);
}

int **copiaSudoku(int **original){
    int  **copia = alocaSudokuInt();
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9 ; j++){
            copia[i][j] = original[i][j];
        }
    }
    return copia;
}

// ------------------------ backtracking acima ---------------------------- //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "./sudoku.h"

//funções de manipulação de sudoku int
//==================================================================================//
int** alocaSudokuInt(){
    int **sudoku = (int**) malloc (DimensaoSudoku * sizeof(int*));
    for(int i = 0; i < DimensaoSudoku; i++){
        sudoku[i] = (int*) malloc (DimensaoSudoku * sizeof(int));        
    } 
    return sudoku;
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

//verifica se é seguro num sudoku int 
int posicaoSegura(int **sudoku, int num, int linha, int coluna) {
    for (int i = 0; i < DimensaoSudoku; i++) {
        if (sudoku[linha][i] == num || sudoku[i][coluna] == num) {
            return 0;
        }
    }

    int blocoLinha = DimensaoGrid * (linha / DimensaoGrid);
    int blocoColuna = DimensaoGrid * (coluna / DimensaoGrid);
    for (int i = blocoLinha; i < blocoLinha + DimensaoGrid; i++) {
        for (int j = blocoColuna; j < blocoColuna + DimensaoGrid; j++) {
            if (sudoku[i][j] == num) {
                return 0;
            }
        }
    }
    return 1;
}

//funções de manipulação de sudoku struct
//==================================================================================//

//inicializa elementos da struct pra cada posição
void InicializaPosicao(Posicao *posicao){
    if(posicao != NULL) {
        posicao->possibilidade = (int*) malloc(sizeof(int) * DimensaoSudoku);
        for(int i = 0; i < DimensaoSudoku; i++) posicao->possibilidade[i] = 0;
        posicao->valor = 0;
        posicao->ehFixo = 0;
    }
}

Sudoku *criaSudoku() {
    Sudoku *sudoku = (Sudoku*)malloc(sizeof(Sudoku));

    if(sudoku != NULL) {
        sudoku->matriz = (Posicao**)malloc(DimensaoSudoku * sizeof(Posicao*));
        for(int i = 0; i < DimensaoSudoku; i++) {
            sudoku->matriz[i] = (Posicao*)malloc(DimensaoSudoku * sizeof(Posicao));
            for(int j = 0; j < DimensaoSudoku; j++) {
                InicializaPosicao(&sudoku->matriz[i][j]); 
            }
        }
    }
    return sudoku;
}

void destroiSudokuStruct(Sudoku *sudoku) {
    if(sudoku == NULL) return;
    for(int i = 0; i < DimensaoSudoku; i++) {
        for(int j = 0; j < DimensaoSudoku; j++) {
            free(sudoku->matriz[i][j].possibilidade);
        }
        free(sudoku->matriz[i]);
    }
    free(sudoku->matriz);
    free(sudoku);
}

//verifica se é seguro colocar numa posicao num sudoku strcut
int seguro(Posicao **matriz, int linha, int coluna, int numero) {
    for(int i = 0; i < DimensaoSudoku; i++) {
        if(matriz[linha][i].valor == numero || matriz[i][coluna].valor == numero) return 0;
    }

    int quadranteLinha = DimensaoGrid * (linha / DimensaoGrid);
    int quadranteColuna =  DimensaoGrid * (coluna / DimensaoGrid);
    for(int i = quadranteLinha; i < (quadranteLinha+DimensaoGrid); i++) {
        for(int j = quadranteColuna; j < (quadranteColuna+DimensaoGrid); j++) {

            if(matriz[i][j].valor == numero) return 0;
        }
    }
    return 1;
}

int **structPraMatriz(Sudoku *sudoku){
    int **sudokuDefinitivo = alocaSudokuInt(); //aloca aqui e depos passa pro no
    
    if(sudoku == NULL) return NULL;

    for(int i = 0; i < DimensaoSudoku; i++) {
        for(int j = 0; j < DimensaoSudoku; j++) {
            sudokuDefinitivo[i][j] = sudoku->matriz[i][j].valor;
        }
    }
    return sudokuDefinitivo;
}

void preencheSudoku(Sudoku *sudoku, int **sudokuInicial){
    for(int i = 0; i < DimensaoSudoku; i++) {
        for(int j = 0; j < DimensaoSudoku; j++) {
            if(sudokuInicial[i][j] != 0) {
                sudoku->matriz[i][j].ehFixo = 1;
                sudoku->matriz[i][j].valor = sudokuInicial[i][j];
            }
        }
    }
    
    for(int i = 0; i < DimensaoSudoku; i++){       
        for(int j = 0; j < DimensaoSudoku; j++) {
            if(sudokuInicial[i][j] == 0) {
                for(int k = 1; k <= DimensaoSudoku; k++){
                   if(seguro(sudoku->matriz,i,j,k)){
                       sudoku->matriz[i][j].possibilidade[k-1] = 1;
                   }
                }
            }
        }
    }
}
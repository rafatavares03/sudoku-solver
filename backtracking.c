#include <stdio.h>
#include <stdlib.h>
#include "./cronometro.h"
#include "./saida.h"
#include "./sudoku.h"
#include "./estrutura-de-dados/fila.h"
#include "saida.h"



int backtracking(int **sudoku, int *tentativasContador) {
    (*tentativasContador)++;
    for(int linha = 0; linha < DimensaoSudoku; linha++) {
        for(int coluna = 0; coluna < DimensaoSudoku; coluna++) {
            if(sudoku[linha][coluna] == 0) {

                for(int k = 1; k <= DimensaoSudoku; k++) {
                    if(posicaoSegura(sudoku, k, linha, coluna)) {
                        sudoku[linha][coluna] = k;
                        if(backtracking(sudoku, tentativasContador)) {
                            return 1;
                        }
                        sudoku[linha][coluna] = 0; 
                    }
                }
                return 0; 
            }
        }
    }
    
    return 1;
}


Fila* resolveSudokuForcaBruta(Fila *sudokus){
    struct timeval inicio = iniciaCronometro();
    Fila* sudokusResolvidos = criaFila();

    NO *susu = sudokus->inicio;
    while(susu != NULL){
        int **sudokuBack = copiaSudoku(susu->sudoku);// o sudoku é alocado ao fazer a copia  
        int cont = 0;
        backtracking(sudokuBack, &cont);
        printf( "tentativas backtracking  = %d\n", cont);
        enfileirar(sudokusResolvidos, sudokuBack); 
        susu = susu->prox;
    }

    finalizaCronometro(inicio, "Forca Bruta");
    
    return sudokusResolvidos;
    
}
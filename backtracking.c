#include <stdio.h>
#include <stdlib.h>
#include "./cronometro.h"
#include "./saida.h"
#include "./sudoku.h"
#include "./estrutura-de-dados/filaSu.h"
#include "saida.h"



int backtracking(int **sudoku) {
    for(int linha = 0; linha < 9; linha++) {
        for(int coluna = 0; coluna < 9; coluna++) {
            if(sudoku[linha][coluna] == 0) {
                int *list = (int*) malloc(sizeof(int) * 9); if(list == NULL) return 0; 

                for(int i = 0; i < 9; i++) list[i] = i + 1;

                for(int k = 0; k < 9; k++) {
                    if(posicaoSegura(sudoku, list[k], linha, coluna)) {
                        sudoku[linha][coluna] = list[k];
                        if(backtracking(sudoku)) {
                            free(list); 
                            return 0;
                        }
                        sudoku[linha][coluna] = 0; 
                    }
                }
                
                free(list); 
                return 0; 
            }
        }
    }
    return 0;
}


Fila* resolveSudokuForcaBruta(Fila *sudokus){
    struct timeval inicio = iniciaCronometro();
    Fila* sudokusResolvidos = criaFilaSu();

    NO *susu = sudokus->inicio;
    while(susu != NULL){
        int **sudokuBack = copiaSudoku(susu->sudoku);
        backtracking(sudokuBack);
        enfileirarSu(sudokusResolvidos, sudokuBack); //nao aloca mais no enfileira //tirar comentario depois   
        susu = susu->prox;
    }

    double aux = finalizaCronometro(inicio, "Forca Bruta", tempoDecorrido);
    tempoDecorrido = aux;
    
    return sudokusResolvidos;
    
}
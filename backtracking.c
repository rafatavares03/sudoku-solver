#include <stdio.h>
#include <stdlib.h>
#include "./cronometro.h"
#include "./saida.h"
#include "./sudoku.h"
#include "./estrutura-de-dados/fila.h"
#include "saida.h"

int backtracking(int **sudoku, int *tentativasContador) {
    (*tentativasContador)++; // conta quantas tentativas foram feitas
    for(int linha = 0; linha < DimensaoSudoku; linha++) {
        for(int coluna = 0; coluna < DimensaoSudoku; coluna++) {
            if(sudoku[linha][coluna] == 0) { // percorre o sudoku e busca uma posição vazia
                for(int k = 1; k <= DimensaoSudoku; k++) {
                    if(posicaoSegura(sudoku, k, linha, coluna)) { // tenta inserir um valor válido nessa posição
                        sudoku[linha][coluna] = k;
                        if(backtracking(sudoku, tentativasContador)) { // se retornar 1, o sudoku foi solucionado
                            return 1;
                        }
                        sudoku[linha][coluna] = 0; // reseta o valor da posição, e testa inserir outro valor válido
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
    Fila* sudokusResolvidos = criaFila(); // cria fila para armazenar as soluções do backtracking

    NO *resolvendo = sudokus->inicio; // sudoku que esta sendo resolvido atualmente
    printf( "Tentativas Backtracking: "); int caso = 1;
    while(resolvendo != NULL){ 
        int **solucaoAtual = copiaSudoku(resolvendo->sudoku);// o sudoku é alocado ao fazer a copia  
        int cont = 0;
        backtracking(solucaoAtual, &cont);
        printf( "[caso%d: %d] ", caso, cont);
        enfileirar(sudokusResolvidos, solucaoAtual); 
        resolvendo = resolvendo->prox; caso++;
    }
    printf( "\n");

    finalizaCronometro(inicio, "Forca Bruta");
    
    return sudokusResolvidos;
    
}
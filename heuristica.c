#include <stdio.h>
#include <stdlib.h>
#include "./heuristica.h"
#include "./cronometro.h"
#include "./sudoku.h"
#include "./estrutura-de-dados/fila.h"
#include "saida.h"

// remove uma possibilidade na linha, coluna e subgrid referente a uma posição do sudoku
void removePossibilidade(Posicao **matriz, int linha, int coluna, int valor) {
    if(matriz == NULL) return;
    for(int i = 0; i < DimensaoSudoku; i++) {
        if(matriz[linha][i].ehFixo != 1){
            if(matriz[linha][i].possibilidade[valor-1] == 1) matriz[linha][i].possibilidade[valor-1] = 0;
        }
        if(matriz[i][coluna].ehFixo != 1) {
            if(matriz[i][coluna].possibilidade[valor-1] == 1) matriz[i][coluna].possibilidade[valor-1] = 0;
        }
    }

    int quadranteLinha = DimensaoGrid * (linha / DimensaoGrid);
    int quadranteColuna =  DimensaoGrid * (coluna / DimensaoGrid);
    for(int i = quadranteLinha; i < (quadranteLinha + DimensaoGrid); i++) {
        for(int j = quadranteColuna; j < (quadranteColuna + DimensaoGrid); j++) {

            if (matriz[i][j].possibilidade[valor-1] == 1)
                matriz[i][j].possibilidade[valor-1] = 0;

            
        }
    }
}

// adiciona uma possibilidade na linha, coluna e subgrid referente a uma posição do sudoku
void adicionaPossibilidade(Posicao **matriz, int linha, int coluna,int valor) {
    if(matriz == NULL) return;
    for(int i = 0; i < DimensaoSudoku; i++) {
        if(matriz[linha][i].ehFixo != 1){
            if(seguro(matriz, linha, i, valor)) matriz[linha][i].possibilidade[valor-1] = 1;
        }
        if(matriz[i][coluna].ehFixo != 1) {
            if(seguro(matriz, i, coluna, valor)) matriz[i][coluna].possibilidade[valor-1] = 1;
        }
    }

    int quadranteLinha = DimensaoGrid * (linha / DimensaoGrid);
    int quadranteColuna =  DimensaoGrid * (coluna / DimensaoGrid);
    for(int i = quadranteLinha; i < (quadranteLinha + DimensaoGrid); i++) {
        for(int j = quadranteColuna; j < (quadranteColuna + DimensaoGrid); j++) {
            if(matriz[i][j].ehFixo != 1) {
                if(seguro(matriz, i, j, valor)) 
                    matriz[i][j].possibilidade[valor-1] = 1;
            }
        }
    }
}

void encontraMenorPossibilidade(Posicao **matriz, int *linha, int *coluna) {
    int menor = 1000;
    for(int i = 0; i < DimensaoSudoku; i++) {
        for(int j = 0; j < DimensaoSudoku; j++) {
            if(matriz[i][j].valor == 0) {

                int quantidade = 0;
                for(int k = 0; k < DimensaoSudoku; k++)
                    quantidade += matriz[i][j].possibilidade[k];
                
                if(menor > quantidade) {
                    menor = quantidade;
                    *(linha) = i;
                    *(coluna) = j;
                }
            }
        }
    }
}

int backtrackingHeuristica(Posicao **sudoku, int *tentativasContador) {
    (*tentativasContador)++;
    int linha = -1, coluna = -1;
    //procura a posição com a menor fila de possibilidades
    encontraMenorPossibilidade(sudoku, &linha, &coluna); 

    // Não há mais posições vazias, ou seja, o sudoku foi resolvido
    if (linha == -1 && coluna == -1) return 1;

    for (int valor = 1; valor <= DimensaoSudoku; valor++) {
        if (seguro(sudoku, linha, coluna, valor)) {
            sudoku[linha][coluna].valor = valor;
            removePossibilidade(sudoku, linha, coluna, valor); // remove o valor inserido como possibilidade nas posições de mesmo quadrante, linha e coluna
            if (backtrackingHeuristica(sudoku, tentativasContador)) { // o sudoku conseguiu ser resolvido
                return 1;
            } else { // o número inserido não trouxe solução para o sudoku
                sudoku[linha][coluna].valor = 0; // reseta essa posição
                adicionaPossibilidade(sudoku,linha,coluna, valor); // repôe o valor que havia sido inserido como possibilidade para as posições de mesma linha, coluna e quadrante que puderem ser preenchidas com esse valor
                //tenta outro valor
            }
        }
    }
    return 0; //todos os valores foram testados para uma posição e nenhum conseguiu resolver o sudoku
}

Fila* resolveSudokuHeuristica(Fila *sudokus) {
    struct timeval inicio = iniciaCronometro();
    Fila *solucaoSudokus = criaFila(); //fila de soluções a ser retornada

    NO *sudokuOriginal = sudokus->inicio;
    while(sudokuOriginal != NULL){
        Sudoku *sudoku = criaSudoku();
        preencheSudoku(sudoku, sudokuOriginal->sudoku); // faz uma copia do sudoku original para o sudoku de struct

        int tentativas = 0; // quantidade de tentativas em preencher posições
        backtrackingHeuristica(sudoku->matriz, &tentativas);
        printf("Tentativas heuristica: %d\n", tentativas);

        enfileirar(solucaoSudokus, structPraMatriz(sudoku));
        // a converão de struct pra int retorna um sudoku alocado
        // que é passado por parametro pra enfileirar 

        destroiSudokuStruct(sudoku);
        sudokuOriginal = sudokuOriginal->prox;
    }

    finalizaCronometro(inicio, "Heuristica");
    
    return solucaoSudokus;

}
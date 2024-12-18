#include <stdio.h>
#include <stdlib.h>
#include "./heuristica.h"
#include "./cronometro.h"
#include "./sudoku.h"
#include "./estrutura-de-dados/lista.h"
#include "./estrutura-de-dados/filaSu.h"
#include "saida.h"


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

void imprimeSudokuStruct(Sudoku *sudoku) {
    if(sudoku == NULL) return;
    for(int i = 0; i < DimensaoSudoku; i++) {
        for(int j = 0; j < DimensaoSudoku; j++) {
            printf("%d ", sudoku->matriz[i][j].valor);
        }
        printf("\n");
    }
}

int seguro(Posicao **matriz, int linha, int coluna, int numero) {
    for(int i = 0; i < DimensaoSudoku; i++) {
        if(matriz[linha][i].valor == numero || matriz[i][coluna].valor == numero) return 0;
    }

    int quadranteLinha = 3 * (linha / 3);
    int quadranteColuna =  3 * (coluna / 3);
    for(int i = quadranteLinha; i < (quadranteLinha+3); i++) {
        for(int j = quadranteColuna; j < (quadranteColuna+3); j++) {

            if(matriz[i][j].valor == numero) return 0;
        }
    }
    return 1;
}


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

    int quadranteLinha = 3 * (linha / 3);
    int quadranteColuna =  3 * (coluna / 3);
    for(int i = quadranteLinha; i < (quadranteLinha + 3); i++) {
        for(int j = quadranteColuna; j < (quadranteColuna + 3); j++) {

            if (matriz[i][j].possibilidade[valor-1] == 1)
                matriz[i][j].possibilidade[valor-1] = 0;

            
        }
    }
}

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

    int quadranteLinha = 3 * (linha / 3);
    int quadranteColuna =  3 * (coluna / 3);
    for(int i = quadranteLinha; i < (quadranteLinha + 3); i++) {
        for(int j = quadranteColuna; j < (quadranteColuna + 3); j++) {
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
    //printf("%d=%d=%d     ", menor, (*linha), (*coluna));
}

int backtrackingHeuristica(Posicao **sudoku, int *te) {
    (*te)++;
    int linha = -1, coluna = -1;
    encontraMenorPossibilidade(sudoku, &linha, &coluna);
    // Não há mais posições vazias, ou seja, o sudoku foi resolvido
    if (linha == -1 && coluna == -1) return 1;

    for (int valor = 1; valor <= DimensaoSudoku; valor++) {
        if (seguro(sudoku, linha, coluna, valor)) {
            sudoku[linha][coluna].valor = valor;
            removePossibilidade(sudoku, linha, coluna, valor); // remove o valor inserido como possibilidade nas posições de mesmo quadrante, linha e coluna
            if (backtrackingHeuristica(sudoku, te)) { // o sudoku conseguiu ser resolvido
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

int** intermediarioBack(int **sudokuInicial){
    Sudoku *sudoku = criaSudoku();

    int **sudokuDefinitivo; //aloca na conversao

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
    

    int te = 0;
    backtrackingHeuristica(sudoku->matriz, &te);
    printf("tenta heu : %d\n\n", te );
    sudokuDefinitivo = structPraMatriz(sudoku);

    //imprimeSudoku(sudokuDefinitivo);
   
    destroiSudokuStruct(sudoku);

    return sudokuDefinitivo;
}

Fila* resolveSudokuHeuristica(Fila *sudokus) {
    struct timeval inicio = iniciaCronometro();
    Fila *sudSolucao = criaFilaSu();
    int **sudInter;

    NO *resolvendo = sudokus->inicio;
    while(resolvendo != NULL){
        sudInter = intermediarioBack(resolvendo->sudoku);
        enfileirarSu(sudSolucao, sudInter);
        resolvendo = resolvendo->prox;
    }


    double aux = finalizaCronometro(inicio, "Heuristica", tempoDecorrido);
    tempoDecorrido = aux;
    
    return sudSolucao;

}
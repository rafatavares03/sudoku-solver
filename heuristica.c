#include <stdio.h>
#include <stdlib.h>
#include "./heuristica.h"
#include "./cronometro.h"
#include "./sudoku.h"
#include "./estrutura-de-dados/lista.h"
#include "./estrutura-de-dados/filaSu.h"



void InicializaPosicao(Posicao *posicao){
    if(posicao != NULL) {
        posicao->possibilidade = criaLista();
        for(int i = 0; i < 9; i++) insereElemento(posicao->possibilidade, i+1);
        posicao->valor = 0;
        posicao->ehFixo = 0;
    }
}

Sudoku *criaSudoku() {
    Sudoku *sudoku = (Sudoku*)malloc(sizeof(Sudoku));
    if(sudoku != NULL) {
        sudoku->matriz = (Posicao**)malloc(9 * sizeof(Posicao*));
        for(int i = 0; i < 9; i++) {
            sudoku->matriz[i] = (Posicao*)malloc(9 * sizeof(Posicao));
            for(int j = 0; j < 9; j++) {
                InicializaPosicao(&sudoku->matriz[i][j]); 
            }
        }
    }
    return sudoku;
}

void destroiSudokuStruct(Sudoku *sudoku) {
    if(sudoku == NULL) return;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            destroiLista(sudoku->matriz[i][j].possibilidade);
        }
        free(sudoku->matriz[i]);
    }
    free(sudoku->matriz);
    free(sudoku);
}

void imprimeSudokuStruct(Sudoku *sudoku) {
    if(sudoku == NULL) return;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%d ", sudoku->matriz[i][j].valor);
        }
        printf("\n");
    }
}

int seguro(Posicao **matriz, int linha, int coluna, int numero) {
    for(int i = 0; i < 9; i++) {
        if(matriz[linha][i].valor == numero || matriz[i][coluna].valor == numero) return 0;
    }

    int quadranteLinha = linha - linha % 3;
    int quadranteColuna = coluna - coluna % 3;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(matriz[quadranteLinha + i][quadranteColuna + j].valor == numero) return 0;
        }
    }
    return 1;
}


void removePossibilidade(Posicao **matriz, int linha, int coluna, int valor) {
    if(matriz == NULL) return;
    for(int i = 0; i < 9; i++) {
        if(matriz[linha][i].ehFixo != 1){
            if(buscaElemento(matriz[linha][i].possibilidade, valor) != -1) removeElemento(matriz[linha][i].possibilidade, valor);
        }
        if(matriz[i][coluna].ehFixo != 1) {
            if(buscaElemento(matriz[i][coluna].possibilidade, valor) != -1) removeElemento(matriz[i][coluna].possibilidade, valor);
        }

        int quadranteLinha = linha - linha % 3;
        int quadranteColuna = coluna - coluna % 3;
        for(int i = 0; i < 3; i++) {
            if(i == linha) continue;
            for(int j = 0; j < 3; j++) {
                if(j == coluna) continue;
                if(buscaElemento(matriz[i + quadranteLinha][j + quadranteColuna].possibilidade, valor) != -1){
                    removeElemento(matriz[i + quadranteLinha][j + quadranteColuna].possibilidade, valor);
                }
            }
        }
    }
}

void adicionaPossibilidade(Posicao **matriz, int linha, int coluna,int valor) {
    if(matriz == NULL) return;
    for(int i = 0; i < 9; i++) {
        if(matriz[linha][i].ehFixo != 1){
            if(seguro(matriz, linha, i, valor)) insereElemento(matriz[linha][i].possibilidade, valor);
        }
        if(matriz[i][coluna].ehFixo != 1) {
            if(seguro(matriz, i, coluna, valor)) insereElemento(matriz[i][coluna].possibilidade, valor);
        }

        int quadranteLinha = linha - linha % 3;
        int quadranteColuna = coluna - coluna % 3;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(matriz[i+quadranteLinha][j+quadranteColuna].ehFixo != 1) {
                    if(seguro(matriz, i+quadranteLinha, j+quadranteLinha, valor)) insereElemento(matriz[i+quadranteLinha][j+quadranteColuna].possibilidade, valor);
                }
            }
        }
    }
}

void encontraMenorPossibilidade(Posicao **matriz, int *linha, int *coluna) {
    int menor = 1000;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(matriz[i][j].valor == 0) {
                if(menor > matriz[i][j].possibilidade->quantidade) {
                    menor = matriz[i][j].possibilidade->quantidade;
                    *(linha) = i;
                    *(coluna) = j;
                }
            }
        }
    }
}

int backtrackingHeuristica(Posicao **sudoku) {
    int linha = -1, coluna = -1;
    encontraMenorPossibilidade(sudoku, &linha, &coluna);
    // Não há mais posições vazias, ou seja, o sudoku foi resolvido
    if (linha == -1 && coluna == -1) return 1;

    for (int valor = 1; valor <= 9; valor++) {
        if (seguro(sudoku, linha, coluna, valor)) {
            if(buscaElemento(sudoku[linha][coluna].possibilidade, valor) == -1) printf("uai %d, l=%d, c=%d\n", valor, linha, coluna);
            sudoku[linha][coluna].valor = valor;
            removePossibilidade(sudoku, linha, coluna, valor); // remove o valor inserido como possibilidade nas posições de mesmo quadrante, linha e coluna
            if (backtrackingHeuristica(sudoku)) { // o sudoku conseguiu ser resolvido
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
    int **sudokuDefinitivo = alocaSudokuInt();
    if(sudoku == NULL) return NULL;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            sudokuDefinitivo[i][j] = sudoku->matriz[i][j].valor;
        }
    }
    return sudokuDefinitivo;
}

int** intermediarioBack(int **sudokuInicial){
    Sudoku *sudoku = criaSudoku();
    int **sudokuDefinitivo = alocaSudokuInt();

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudokuInicial[i][j] != 0) {
                sudoku->matriz[i][j].ehFixo = 1;
                sudoku->matriz[i][j].valor = sudokuInicial[i][j];
                removePossibilidade(sudoku->matriz, i, j, sudokuInicial[i][j]);
            }
        }
    }
    backtrackingHeuristica(sudoku->matriz);
    sudokuDefinitivo = structPraMatriz(sudoku);
    destroiSudokuStruct(sudoku);

    return sudokuDefinitivo;

}

Fila* resolveSudokuHeuristica(Fila *sudokus) {
    struct timeval inicio = iniciaCronometro();
    Fila *sudSolucao = criaFila();

    NO *resolvendo = sudokus->inicio;
    while(resolvendo != NULL){
        int **sudInter = intermediarioBack(resolvendo->sudoku);
        enfileirarSu(sudSolucao, sudInter);
        resolvendo = resolvendo->prox;
    }


    double aux = finalizaCronometro(inicio, "Forca Bruta", tempoDecorrido);
    tempoDecorrido = aux;
    
    return sudSolucao;

}
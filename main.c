#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./leitura.h"
#include "./saida.h"
#include "./estrutura-de-dados/lista.h"

typedef struct Elemento{
    Lista *possibilidade;
    int valor;
    int ehFixo;
} Elemento;

typedef struct Sud {
    Elemento **oku;
} Sud;

void InicializaElemento(Elemento *elem){
    if(elem != NULL) {
        elem->possibilidade = criaLista();
        for(int i = 0; i < 9; i++) insereElemento(elem->possibilidade, i+1);
        elem->valor = 0;
        elem->ehFixo = 0;
    }
}

Sud *criaSud() {
    Sud *sud = (Sud*)malloc(sizeof(Sud));
    if(sud != NULL) {
        sud->oku = (Elemento**)malloc(9 * sizeof(Elemento*));
        for(int i = 0; i < 9; i++) {
            sud->oku[i] = (Elemento*)malloc(9 * sizeof(Elemento));
            for(int j = 0; j < 9; j++) {
                InicializaElemento(&sud->oku[i][j]);
            }
        }
    }
    return sud;
}

void destroiSud(Sud *sud) {
    if(sud == NULL) return;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            destroiLista(sud->oku[i][j].possibilidade);
        }
        free(sud->oku[i]);
    }
    free(sud->oku);
    free(sud);
}

void imprimeSud(Sud *sud) {
    if(sud == NULL) return;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%d ", sud->oku[i][j].valor);
        }
        printf("\n");
    }
}

int seguro(Elemento **matriz, int linha, int coluna, int numero) {
    for(int i = 0; i < 9; i++) {
        if(matriz[linha][i].valor == numero || matriz[i][coluna].valor == numero) return 0;
    }

    int quadranteLinha = linha - linha % 3;
    int quadranteColuna = coluna - coluna % 3;
    for(int i = 0; i < 3; i++) {
        if(i == linha) continue;
        for(int j = 0; j < 3; j++) {
            if(j == coluna) continue;
            if(matriz[quadranteLinha + i][quadranteColuna + j].valor == numero) return 0;
        }
    }
    return 1;
}


void removePossibilidade(Elemento **matriz, int linha, int coluna, int valor) {
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

void adicionaPossibilidade(Elemento **matriz, int linha, int coluna,int valor) {
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
            if(i == linha) continue;
            for(int j = 0; j < 3; j++) {
                if(j == coluna) continue;
                if(matriz[i+quadranteLinha][j+quadranteColuna].ehFixo != 1) {
                    if(seguro(matriz, i+quadranteLinha, j+quadranteLinha, valor)) insereElemento(matriz[i+quadranteLinha][j+quadranteColuna].possibilidade, valor);
                }
            }
        }
    }
}

void encontraMenorPossibilidade(Elemento **matriz, int *linha, int *coluna) {
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

int resolveSudokuHeuristica(Elemento **sudoku) {
    int linha = -1, coluna = -1;
    // Encontra a célula com o menor número de opções possíveis
    encontraMenorPossibilidade(sudoku, &linha, &coluna);

    // Se não houver mais células vazias, o Sudoku está resolvido
    if (linha == -1 && coluna == -1) {
        return 1;
    }

    // Tenta colocar números de 1 a 9 na célula (row, col)
    for (int valor = 1; valor <= 9; valor++) {
        if (seguro(sudoku, linha, coluna, valor)) {
            sudoku[linha][coluna].valor = valor;
            removePossibilidade(sudoku, linha, coluna, valor);
            // Recursivamente tenta preencher o próximo valor
            if (resolveSudokuHeuristica(sudoku)) {
                return 1;
            } else {
                sudoku[linha][coluna].valor = 0;
                adicionaPossibilidade(sudoku,linha,coluna, valor);
            }
        }
    }
    return 0;
}


int main(){
    int **sudoku = leitura("./su-do-ku.txt");
    imprimeSudoku(sudoku);
    Sud *sud = criaSud();
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j] != 0) {
                sud->oku[i][j].ehFixo = 1;
                sud->oku[i][j].valor = sudoku[i][j];
                removePossibilidade(sud->oku, i, j, sudoku[i][j]);
            }
        }
    }

    imprimeSud(sud);
    resolveSudokuHeuristica(sud->oku);
    printf("-------------\n");
    imprimeSud(sud);
    destroiSud(sud);
    destroiSudokuInt(sudoku);
    return 0;
}
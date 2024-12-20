#include <stdio.h>
#include <string.h>
#include "./estrutura-de-dados/fila.h"
#include "./cronometro.h"
#include "./sudoku.h"

void imprimeSudoku(int** sudoku){
        for(int i = 0; i < DimensaoSudoku; i++){
            printf("|");
            for(int j = 0; j < DimensaoSudoku; j++){
                printf(" %d |", sudoku[i][j]);
            }
        printf("\n");
    }
    printf("\n");
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

void initArquivo(char *path){
    FILE *arquivo = fopen(path, "w");
    fprintf(arquivo, "%s" ,"");
    fclose(arquivo);
}

void escreveSudoku(int **sudoku, char *path, char *operacao, int i){
    FILE *arquivo = fopen(path, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "%s: %d\n", operacao, i);
    for (int i = 0; i < DimensaoSudoku; i++) {
        for (int j = 0; j < DimensaoSudoku; j++) {
            if(j == DimensaoSudoku-1){
                fprintf(arquivo, "%2d", sudoku[i][j]); // Escreve cada número
                //fprintf(arquivo, " ");
                
            } else {
                fprintf(arquivo, "%2d", sudoku[i][j]); // Escreve cada número

            }
            if ((j + 1) % DimensaoGrid == 0 && j != DimensaoSudoku-1) fprintf(arquivo, " "); // Adiciona divisores
        }
        fprintf(arquivo, "\n");
        if ((i + 1) % DimensaoGrid == 0 && i != DimensaoSudoku-1) fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "\n");

    fclose(arquivo);
}


void escreveArquivo(Fila *sudoku, char *path, char *operacao){
    struct timeval inicio = iniciaCronometro();

    NO *solucao = sudoku->inicio;
    int i = 1; //contagem
    while(solucao != NULL){
        escreveSudoku(solucao->sudoku, path, operacao, i);
        solucao = solucao->prox; i++;
    }
    
    //tem que ter tamanho fixo pra n dar falha de segmentação
    char concatenado[51] = "escrita da ";
    strcat(concatenado, operacao);

    finalizaCronometro(inicio, concatenado);

}
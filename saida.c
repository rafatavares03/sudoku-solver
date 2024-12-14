#include <stdio.h>
#include "./estrutura-de-dados/filaSu.h"

void imprimeSudoku(int** sudoku){
        for(int i = 0; i < 9; i++){
            printf("|");
            for(int j = 0; j < 9; j++){
                printf(" %d |", sudoku[i][j]);
            }
        printf("\n");
    }
    printf("\n");
}

void escreveSudoku(int **sudoku, char *path){
    FILE *arquivo = fopen(path, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "+---------------------+\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(j == 0) fprintf(arquivo, "|");
            
            if(j == 8){
                fprintf(arquivo, "%d", sudoku[i][j]); // Escreve cada número
                fprintf(arquivo, "|");
                
            } else {
                fprintf(arquivo, "%d ", sudoku[i][j]); // Escreve cada número

            }
            if ((j + 1) % 3 == 0 && j != 8) fprintf(arquivo, "| "); // Adiciona divisores
        }
        fprintf(arquivo, "\n");
        if ((i + 1) % 3 == 0 && i != 8) fprintf(arquivo, "|---------------------|\n");
    }
    fprintf(arquivo, "+---------------------+\n");
    fprintf(arquivo, "\n\n\n");

    fclose(arquivo);
}

void escreveArquivo(Fila *sudoku, char *path){
    //ter certeza que ta em branco
    FILE *arquivo = fopen(path, "w");
    fprintf(arquivo, "%s" ,"");
    fclose(arquivo);

    NO *aux = sudoku->inicio;
    while(aux != NULL){
        escreveSudoku(aux->sudoku, path);
        aux = aux->prox;
    }


}
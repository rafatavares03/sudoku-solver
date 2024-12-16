#include <stdio.h>
#include <string.h>
#include "./estrutura-de-dados/filaSu.h"
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

void escreveSudoku(int **sudoku, char *path, char *operacion, int i){
    FILE *arquivo = fopen(path, "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "%s: %d\n", operacion, i);
    fprintf(arquivo, "+---------------------+\n");
    for (int i = 0; i < DimensaoSudoku; i++) {
        for (int j = 0; j < DimensaoSudoku; j++) {
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
    fprintf(arquivo, "\n");

    fclose(arquivo);
}

void initArquivo(char *path){
    FILE *arquivo = fopen(path, "w");
    fprintf(arquivo, "%s" ,"");
    fclose(arquivo);
 }

void escreveArquivo(Fila *sudoku, char *path, char *operacion){
    struct timeval inicio = iniciaCronometro();

    NO *susu = sudoku->inicio;
    int i = 1; //contagem
    while(susu != NULL){
        escreveSudoku(susu->sudoku, path, operacion, i);
        susu = susu->prox; i++;
    }
    
    //tem que ter tamanho fixp pra n dar seg falha
    char concatenado[51] = "escrita da ";
    strcat(concatenado, operacion);

    double aux = finalizaCronometro(inicio, concatenado, tempoDecorrido);
    tempoDecorrido = aux;

}
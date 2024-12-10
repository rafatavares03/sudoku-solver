#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sudoku.h"

int **converteSudoku(char **original){
   int **copia = alocaSudokuInt();
   for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(original[i][j] == 'v'){
                copia[i][j] = 0;
            } else {
                copia[i][j] = (original[i][j] - '0');

            }
        }
    }
    destroiSudoku(original);
    return copia;
}

int **leitura(char *path) {
    char **sudoku = alocaSudoku();
    FILE *arquivo = fopen(path, "r");
    if (arquivo != NULL) {
        char *linha = (char*) malloc(20 * sizeof(char));
        for (int i = 0; i < 9; i++) {
            if (fgets(linha, 20, arquivo)) {
                sudoku[i][0] = linha[0];
                sudoku[i][1] = linha[2];
                sudoku[i][2] = linha[4];
                sudoku[i][3] = linha[6];
                sudoku[i][4] = linha[8];
                sudoku[i][5] = linha[10];
                sudoku[i][6] = linha[12];
                sudoku[i][7] = linha[14];
                sudoku[i][8] = linha[16];
            }
        }
        free(linha);
        fclose(arquivo);
        return converteSudoku(sudoku);
    } else {
        printf("Erro ao abrir o arquivo!\n");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sudoku.h"
#include "filaSu.h"
#include "saida.h"

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

Fila *leitura(char *path) {
    Fila *sudokus = criaFila();
    FILE *arquivo = fopen(path, "r");
    int con =1;

    if (arquivo != NULL) {
        char *linha = (char*) malloc(22 * sizeof(char));
        while( ! feof(arquivo) ){
            

            char **sudoku = alocaSudoku();

            for (int i = 0; i < 9; i++) {
                if (fgets(linha, 22, arquivo)) {

                    if(strlen(linha) < 5){ //quebra de linha do subgrid
                        fgets(linha, 22, arquivo);
                    } 


                    sudoku[i][0] = linha[0];
                    sudoku[i][1] = linha[2];
                    sudoku[i][2] = linha[4];
                    sudoku[i][3] = linha[7];
                    sudoku[i][4] = linha[9];
                    sudoku[i][5] = linha[11];
                    sudoku[i][6] = linha[14];
                    sudoku[i][7] = linha[16];
                    sudoku[i][8] = linha[18];
                }
            }
            fgets(linha, 22, arquivo); // comer a segunda linha na troca de sudoku

            enfileirarSu(sudokus, converteSudoku(sudoku));
            //printf("%d \n", con);
            con++;
        }

        fclose(arquivo);
        free(linha);
        return sudokus;

    } else {
        printf("Erro ao abrir o arquivo!\n");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sudoku.h"
#include "./estrutura-de-dados/filaSu.h"
#include "saida.h"
#include "./cronometro.h"


int **converteSudoku(char **original){
   int **copia = alocaSudokuInt();
   for(int i = 0; i < DimensaoSudoku; i++){
        for(int j = 0; j < DimensaoSudoku; j++){
            if(original[i][j] == 'v'){
                copia[i][j] = 0;
            } else {
                copia[i][j] = (original[i][j] - '0');

            }
        }
    }

    return copia;
}

Fila *leitura(char *path) {
    struct timeval inicio = iniciaCronometro();
    
    Fila *sudokus = criaFilaSu();
    FILE *arquivo = fopen(path, "r");

    if (arquivo != NULL) {
        char *linha = (char*) malloc(22 * sizeof(char));
        
        while( ! feof(arquivo) ){
            char **sudoku = alocaSudoku();

            for (int i = 0; i < DimensaoSudoku; i++) {
                if (fgets(linha, 22, arquivo)) {
                    if(strlen(linha) < 5){ //quebra de linha do subgrid
                        fgets(linha, 22, arquivo);
                    } 
                    sudoku[i][0] = linha[0];
                    sudoku[i][1] = linha[2];
                    sudoku[i][2] = linha[4];
                    sudoku[i][3] = linha[7];
                    sudoku[i][4] = linha[DimensaoSudoku];
                    sudoku[i][5] = linha[11];
                    sudoku[i][6] = linha[14];
                    sudoku[i][7] = linha[16];
                    sudoku[i][8] = linha[18];
                }
            }
            fgets(linha, 22, arquivo); // comer a segunda linha na troca de sudoku

            enfileirarSu(sudokus, converteSudoku(sudoku)); 
            destroiSudoku(sudoku);

        }

        fclose(arquivo);
        free(linha);

    } else {
        printf("Erro ao abrir o arquivo!\n");
    }

    
    double aux = finalizaCronometro(inicio, "Leitura", tempoDecorrido);
    tempoDecorrido = aux;
    return sudokus;
}
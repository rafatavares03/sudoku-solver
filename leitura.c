#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sudoku.h"
#include "./estrutura-de-dados/fila.h"
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
    
    Fila *sudokus = criaFila();
    FILE *arquivo = fopen(path, "r");

    if (arquivo != NULL) {
        int tama = (DimensaoSudoku * DimensaoSudoku); 
        // calculo exato :( dimensao * 2) + sqrt(dimensao)
        //gasto mais memoria pra evitar calculo de raiz

        char *linha = (char*) malloc(tama * sizeof(char));
        
        while( ! feof(arquivo) ){
            int **sudoku = alocaSudokuInt();

            for (int i = 0; i < DimensaoSudoku; i++) {
                if (fgets(linha, tama, arquivo)) {
                    if(strlen(linha) < 5){ //quebra de linha do subgrid
                        fgets(linha, tama, arquivo);
                    } 
                    
                }

                char *token = strtok(linha, " ");
                for (int j = 0; token != NULL; j++) {
                    sudoku[i][j] = atoi(token);
                    token = strtok(NULL, " ");
                }

            }
            fgets(linha, tama, arquivo); // comer a segunda linha na troca de sudoku
<<<<<<< HEAD
            enfileirarSu(sudokus, sudoku); 
=======

            enfileirar(sudokus, converteSudoku(sudoku)); 
            destroiSudoku(sudoku);

>>>>>>> 4b11aeaa08c501c68e047c9c5c939474f80475f8
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
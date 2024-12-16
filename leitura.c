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
        int tama = (DimensaoSudoku * 3); 
        // calculo exato :( dimensao * 2) + sqrt(dimensao)
        //gasto mais memoria pra evitar calculo de raiz

        char *linha = (char*) malloc(tama * sizeof(char));
        
        while( ! feof(arquivo) ){
            char **sudoku = alocaSudoku();


            for (int i = 0; i < DimensaoSudoku; i++) {
                if (fgets(linha, tama, arquivo)) {
                    if(strlen(linha) < 5){ //quebra de linha do subgrid
                        fgets(linha, tama, arquivo);
                    } 
                    
                }

                for(int j = 0, k = 0; linha[k] != '\0' && linha[k] != '\n'; k++){
                    if(linha[k] != ' '){  // Ignora espaços em branco
                        sudoku[i][j] = linha[k];
                        j++;
                    }
                }


            }
            fgets(linha, tama, arquivo); // comer a segunda linha na troca de sudoku

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
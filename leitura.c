#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sudoku.h"
#include "./estrutura-de-dados/fila.h"
#include "saida.h"
#include "./cronometro.h"

Fila *leitura(char *path) {
    struct timeval inicio = iniciaCronometro();

    Fila *sudokus = criaFila();
    FILE *arquivo = fopen(path, "r");

    if (arquivo != NULL) {
        int tamanho = (DimensaoSudoku * DimensaoSudoku); 
        // calculo exato :( dimensao * 2) + sqrt(dimensao)
        //gasto mais memoria pra evitar calculo de raiz e ter mais segurança

        char *linha = (char*) malloc(tamanho * sizeof(char));
        
        while( ! feof(arquivo) ){
            int **sudoku = alocaSudokuInt();

            for (int i = 0; i < DimensaoSudoku; i++) {
                if (fgets(linha, tamanho, arquivo)) {
                    if(strlen(linha) < 5){ //quebra de linha do subgrid //5 pra margem de erro
                        fgets(linha, tamanho, arquivo);
                    } 
                }
                char *token = strtok(linha, " ");
                for (int j = 0; token != NULL; j++) {
                    if(i < DimensaoSudoku && j < DimensaoSudoku)
                        sudoku[i][j] = atoi(token);
                    token = strtok(NULL, " ");
                }

            }
            fgets(linha, tamanho, arquivo); // comer a segunda linha na troca de sudoku
            enfileirar(sudokus, sudoku); 
        }
        fclose(arquivo);
        free(linha);

    } else {
        printf("Erro ao abrir o arquivo!\n");
    }
    
    finalizaCronometro(inicio, "Leitura");
    return sudokus;
}
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

void fogoNoRabo(char *path){
    FILE *arquivo = fopen(path, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int x = DimensaoSudoku;
    int cont = 1;
    
    // Inicializa o gerador de números aleatórios com a hora atual
    srand(time(NULL));
    
    for(int i = 0; i < x; i++){
        for(int j = 0; j < x; j++){
            int y = rand() % 100; // Gera um número aleatório entre 0 e 99
            if(y < 10 && cont <= x && i > DimensaoSudoku/2 ){
                fprintf(arquivo, "%d ", cont);  // Imprime o número cont
                cont++;
            } else {
                fprintf(arquivo, "0 ");  // Imprime 0
            }
        }
        if(i!=x-1)
        fprintf(arquivo, "\n");  // Quebra de linha após cada linha do grid
    }
    
    fclose(arquivo);  // Não se esqueça de fechar o arquivo
}

Fila *leitura(char *path) {
    struct timeval inicio = iniciaCronometro();

    fogoNoRabo(path);

    
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
                    if(i < DimensaoSudoku && j < DimensaoSudoku)
                        sudoku[i][j] = atoi(token);
                    token = strtok(NULL, " ");
                }

            }
            fgets(linha, tama, arquivo); // comer a segunda linha na troca de sudoku
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
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

void gerarSudokuParcial(char *path) {
    FILE *arquivo = fopen(path, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int **sudoku = alocaSudokuInt(); // Inicializa o grid com zeros
    int numPreenchido = DimensaoSudoku * DimensaoSudoku / 4; // Define a quantidade de células preenchidas

    // Inicializa o gerador de números aleatórios com a hora atual
    srand(time(NULL));

    // Preenche o tabuleiro com alguns números aleatórios seguindo as regras do Sudoku
    while (numPreenchido > 0) {
        int linha = rand() % DimensaoSudoku;
        int coluna = rand() % DimensaoSudoku;
        int num = (rand() % DimensaoSudoku) + 1;

        if (sudoku[linha][coluna] == 0 && posicaoSegura(sudoku, linha, coluna, num)) {
            sudoku[linha][coluna] = num;
            numPreenchido--;
        }
    }

    // Grava o Sudoku gerado no arquivo
    for (int i = 0; i < DimensaoSudoku; i++) {
        for (int j = 0; j < DimensaoSudoku; j++) {
            fprintf(arquivo, "%d ", sudoku[i][j]);
        }
        if(i!=DimensaoSudoku-1)
        fprintf(arquivo, "\n");
    }
    destroiSudokuInt(sudoku);

    fclose(arquivo); // Fecha o arquivo
}

void gerarSudokuVazio(char *path) {
    FILE *arquivo = fopen(path, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < DimensaoSudoku; i++) {
        for (int j = 0; j < DimensaoSudoku; j++) {
            if(i==j)
            fprintf(arquivo, "%d ", i+1);
            else  // Escreve "0" seguido de um espaço
            fprintf(arquivo, "0 "); // Escreve "0" seguido de um espaço
        }
        if(i!=DimensaoSudoku-1)
        fprintf(arquivo, "\n"); // Quebra de linha ao final de cada linha
    }

    fclose(arquivo); // Fecha o arquivo
}



Fila *leitura(char *path) {
    struct timeval inicio = iniciaCronometro();

    //gerarSudokuParcial(path);
    gerarSudokuVazio(path);

    
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sudoku.h"
#include "./estrutura-de-dados/fila.h"
#include "saida.h"
#include "./cronometro.h"

// pra teste de complexidade
//gera um sudoku vazio com a diagila preenchida de 1 a n
void gerarSudouDiagonal(char *path) {
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

    // para fins de teste
    // cria um sudoku com  a diagonal principal preenchida
    //gerarSudouDiagonal(path);

    
    Fila *sudokus = criaFila();
    FILE *arquivo = fopen(path, "r");



    if (arquivo != NULL) {
        int tama = (DimensaoSudoku * DimensaoSudoku); 
        // calculo exato :( dimensao * 2) + sqrt(dimensao)
        //gasto mais memoria pra evitar calculo de raiz e ter mais segurança

        char *linha = (char*) malloc(tama * sizeof(char));
        
        while( ! feof(arquivo) ){
            int **sudoku = alocaSudokuInt();

            for (int i = 0; i < DimensaoSudoku; i++) {
                if (fgets(linha, tama, arquivo)) {
                    if(strlen(linha) < 5){ //quebra de linha do subgrid //5 pra margem de erro
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
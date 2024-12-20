/* 
======================================
    Autores:                      
    Hugo Alves Azevedo de Souza 
    Rafael Moisés de Sá Tavares 
======================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./backtracking.h"
#include "./heuristica.h"
#include "./leitura.h"
#include "./saida.h"
#include "./cronometro.h"  
#include "./estrutura-de-dados/fila.h"
#include <math.h>

double tempoDecorridoCPU = 0.0;

int DimensaoSudoku = 9;
int DimensaoGrid = 3;

int main(int arg, char *argv[]){

    printf("-------------------------------------------------------------------------------\n");

    Fila* sudokus = leitura(argv[1]); // lê e armazena todos os sudokus da entrada
    
    //cria ou zera o arquivo;    
    initArquivo(argv[2]);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *resolucoesDaHeuristica = resolveSudokuHeuristica(sudokus); // recebe como retorno todas as soluções resolvidas pela heurística
    escreveArquivo(resolucoesDaHeuristica, argv[2], "heuristica");  // escreve todas as soluções da heurística no arquivo
    destroiFila(resolucoesDaHeuristica);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *ResolucoesDaForcaBruta = resolveSudokuForcaBruta(sudokus); // recebe como retorno todas as soluções resolvida pelo backtracking
    escreveArquivo(ResolucoesDaForcaBruta, argv[2], "forca bruta"); // escreve todas as soluções do backtracking no arquivo
    destroiFila(ResolucoesDaForcaBruta);

    printf("-------------------------------------------------------------------------------\n");

    destroiFila(sudokus);

    return 0;
}
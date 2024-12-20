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

    Fila* sudokus = leitura(argv[1]);
    
    //cria ou zera o arquivo;    
    initArquivo(argv[2]);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *resolucoesDaHeuristica = resolveSudokuHeuristica(sudokus);
    escreveArquivo(resolucoesDaHeuristica, argv[2], "heuristica"); 
    destroiFila(resolucoesDaHeuristica);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *ResolucoesDaForcaBruta = resolveSudokuForcaBruta(sudokus);
    escreveArquivo(ResolucoesDaForcaBruta, argv[2], "forca bruta");
    destroiFila(ResolucoesDaForcaBruta);

    printf("-------------------------------------------------------------------------------\n");

    destroiFila(sudokus);

    return 0;
}
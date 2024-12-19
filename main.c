#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./backtracking.h"
#include "./heuristica.h"
#include "./leitura.h"
#include "./saida.h"
#include "./cronometro.h"  //no linux é show
#include "./estrutura-de-dados/fila.h"

double tempoDecorrido = 0.0;
int DimensaoSudoku = 9;
int DimensaoGrid = 3;

int main(int arg, char *argv[]){
    printf("-------------------------------------------------------------------------------\n");

    Fila* sudokus = leitura(argv[1]);
    //imprimirFilaSu(sudokus);
    
    //cria ou zera o arquivo;

    
    initArquivo(argv[2]);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *resolucoesDaHeuristica = resolveSudokuHeuristica(sudokus);
    escreveArquivo(resolucoesDaHeuristica, argv[2], "heuristica"); 


    //imprimirFilaSu(sudokus);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *ResolucoesDaForcaBruta = resolveSudokuForcaBruta(sudokus);
    escreveArquivo(ResolucoesDaForcaBruta, argv[2], "forca bruta");

    printf("-------------------------------------------------------------------------------\n");

    destroiFila(sudokus);
    destroiFila(resolucoesDaHeuristica);
    destroiFila(ResolucoesDaForcaBruta);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./backtracking.h"
#include "./heuristica.h"
#include "./leitura.h"
#include "./saida.h"
#include "./cronometro.h"  //no linux é show
#include "./estrutura-de-dados/filaSu.h"

double tempoDecorrido = 0.0;
int DimensaoSudoku = 9;

int main(int arg, char *argv[]){
    printf("-------------------------------------------------------------------------------\n");

    Fila* sudokus = leitura(argv[1]);
    //imprimirFilaSu(sudokus);
    
    //cria ou zera o arquivo;
    initArquivo(argv[2]);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *sudHeu = resolveSudokuHeuristica(sudokus);
    escreveArquivo(sudHeu, argv[2], "heuristica"); 


    //imprimirFilaSu(sudokus);

    printf("-------------------------------------------------------------------------------\n");
    
    Fila *sudBruta = resolveSudokuForcaBruta(sudokus);
    escreveArquivo(sudBruta, argv[2], "forca bruta");

    printf("-------------------------------------------------------------------------------\n");

    destroiFilaSu(sudokus);
    destroiFilaSu(sudHeu);
    destroiFilaSu(sudBruta);

    return 0;
}
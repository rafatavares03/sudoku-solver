#include <stdio.h>
#include <stdlib.h>
#include "./sudoku.h"
#include "./backtracking.h"
#include "./heuristica.h"
#include "./leitura.h"
#include "./saida.h"
#include "./cronometro.h"  //no linux é show
#include "./estrutura-de-dados/lista.h"
#include "./estrutura-de-dados/filaSu.h"

double tempoDecorrido = 0.0;

int main(int arg, char *argv[]){
    Fila* sudokus = leitura(argv[1]);
    //imprimirFilaSu(sudokus);
    
    //cria ou zera o arquivo;
    initArquivo(argv[2]);
    
    Fila *sudHeu = criaFilaSu();
    sudHeu = resolveSudokuHeuristica(sudokus);
    escreveArquivo(sudHeu, argv[2], "heuristica"); 

    printf("------\n");
    
    Fila *sudBruta = criaFilaSu();
    sudBruta = resolveSudokuForcaBruta(sudokus);
    escreveArquivo(sudBruta, argv[2], "forca bruta");


    destroiFilaSu(sudokus);
    return 0;
}
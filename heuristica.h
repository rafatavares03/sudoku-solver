#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "./estrutura-de-dados/lista.h"
#include "./estrutura-de-dados/filaSu.h"


typedef struct Posicao{
    Lista *possibilidade;
    int valor;
    int ehFixo;
} Posicao;

typedef struct Sudoku {
    Posicao **matriz;
} Sudoku;

Sudoku *criaSudoku();
void destroiSudokuStruct(Sudoku *sudoku);
void imprimeSudokuStruct(Sudoku *sudoku);
Fila *resolveSudokuHeuristica(Fila *sudokus);


#endif
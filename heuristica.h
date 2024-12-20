#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "./estrutura-de-dados/fila.h"
#include "sudoku.h"

Sudoku *criaSudoku();
void destroiSudokuStruct(Sudoku *sudoku);
void imprimeSudokuStruct(Sudoku *sudoku);
Fila *resolveSudokuHeuristica(Fila *sudokus);

#endif
#ifndef SUDOKU_H
#define SUDOKU_H

extern int DimensaoSudoku;
extern int DimensaoGrid;

char **alocaSudoku();
int** alocaSudokuInt();
void destroiSudoku(char** sudoku);
void destroiSudokuInt(int** sudoku);
int **copiaSudoku(int **original);
int posicaoSegura(int **sudoku, int num, int linha, int coluna);
#endif
#ifndef SUDOKU_H
#define SUDOKU_H

char **alocaSudoku();
int** alocaSudokuInt();
void destroiSudoku(char** sudoku);
void destroiSudokuInt(int** sudoku);
int **copiaSudoku(int **original);
#endif
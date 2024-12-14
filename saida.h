#ifndef SAIDA_H
#define SAIDA_H

#include "./estrutura-de-dados/filaSu.h"

void imprimeSudoku(int** sudoku);
void escreveArquivo(Fila *sudokus, char *path);

#endif
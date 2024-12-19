#ifndef SAIDA_H
#define SAIDA_H

#include "./estrutura-de-dados/fila.h"

void imprimeSudoku(int** sudoku);
void escreveArquivo(Fila *sudokus, char *path, char *operacion);
void initArquivo(char *path);

#endif
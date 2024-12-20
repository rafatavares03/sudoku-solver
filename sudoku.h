#ifndef SUDOKU_H
#define SUDOKU_H

extern int DimensaoSudoku;
extern int DimensaoGrid;

//=========================================================================//
// sudoku normal
int** alocaSudokuInt();
void destroiSudokuInt(int** sudoku);
int **copiaSudoku(int **original);
int posicaoSegura(int **sudoku, int num, int linha, int coluna);

//=========================================================================//
//sudoku de struct
typedef struct Posicao{
    int *possibilidade;
    int valor;
    int ehFixo;
} Posicao;

typedef struct Sudoku {
    Posicao **matriz;
} Sudoku;

void destroiSudokuStruct(Sudoku *sudoku);
Sudoku *criaSudoku();
int seguro(Posicao **matriz, int linha, int coluna, int numero);
int **structPraMatriz(Sudoku *sudoku);
void preencheSudoku(Sudoku *sudoku, int **sudokuInicial);
//=========================================================================//
#endif
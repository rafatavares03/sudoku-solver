#ifndef FILA_H
#define FILA_H

typedef struct No {
    int **sudoku;        
    struct No *prox;
} NO;

typedef struct {
    NO *inicio;
    NO *final;
    int tamanho;
} Fila;

Fila *criaFila();
void destroiFila(Fila *fila);
int enfileirar(Fila *fila, int** sudoku);
int desenfileirar(Fila *fila);
int estaVaziaFila(Fila *fila);
void imprimirFila(Fila *fila);
int tamanhoFila(Fila *fila);

#endif
#ifndef FILA_H
#define FILA_H

typedef struct No {
    int **sudoku;        
    struct No *prox;
} NO;

typedef struct {
    NO *inicio;
    NO *final;
} Fila;

typedef NO NO_Fila;  


Fila *criaFilaSu();
void destroiFilaSu(Fila *fila);
int enfileirarSu(Fila *fila, int** sudoku);
int desenfileirarSu(Fila *fila);
int estaVaziaSu(Fila *fila);
void imprimirFilaSu(Fila *fila);
int tamanhoFilaSu(Fila *fila);

#endif
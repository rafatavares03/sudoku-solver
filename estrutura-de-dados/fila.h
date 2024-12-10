#ifndef FILA_H
#define FILA_H
typedef struct NO {
    int dados;        
    struct NO *prox;
} NO;

typedef struct Fila{
    int quantidade;
    NO *inicio;
    NO *final;
} Fila;


Fila *criaFila();
void destroiFila(Fila *fila);
int enfileirar(Fila *fila, int dados);
int desenfileirar(Fila *fila);
int verTopo(Fila *fila);
int estaVazia(Fila *fila);
void imprimirFila(Fila *fila);
int tamanhoFila(Fila *fila);
int existeNaFila(Fila *fila, int numero);

#endif
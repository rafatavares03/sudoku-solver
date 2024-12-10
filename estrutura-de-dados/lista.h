#ifndef LISTA_H
#define LISTA_H

typedef struct Lista{
    int quantidade;
    int *dados;
} Lista;

Lista *criaLista();
int removeElemento(Lista *l, int elemento);
int insereElemento(Lista *l, int elemento);
int estaVaziaLista(Lista *l);
int estaCheiaLista(Lista *l);
void destroiLista(Lista *l);
int buscaElemento(Lista *l, int elemento);

#endif
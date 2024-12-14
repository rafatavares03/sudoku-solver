#include <stdio.h>
#include <stdlib.h>
#include "./lista.h"

#define MAX 36

Lista *criaLista(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    if(l != NULL) {
        l->dados = (int*)malloc(MAX * sizeof(int));
        l->quantidade = 0;
    }
    return l;
}

void destroiLista(Lista *l) {
    if(l == NULL) return;
    free(l->dados);
    free(l);
}

int estaVaziaLista(Lista *l){
    if(l == NULL) return -1;
    return l->quantidade == 0;
}

int estaCheiaLista(Lista *l) {
    if(l == NULL) return -1;
    return l->quantidade == MAX;
}

int insereElemento(Lista *l, int elemento) {
    if(l == NULL) return -1;
    if(estaCheiaLista(l)) return 0;
    if(buscaElemento(l, elemento) != -1) return 1;
    l->dados[l->quantidade] = elemento;
    l->quantidade++;
    return 1;
}

int buscaElemento(Lista *l, int elemento) {
    if(l == NULL) return -1;
    if(estaVaziaLista(l)) return -1;
    for(int i = 0; i < l->quantidade; i++) {
        if(l->dados[i] == elemento) return i;
    }
    return -1;
}

int removeElemento(Lista *l, int elemento) {
    if(l == NULL) return -1;
    if(estaVaziaLista(l)) return 0;
    int indice = buscaElemento(l, elemento);
    if(indice == -1) return 0;
    for(int i = indice+1; i < l->quantidade; i++) {
        l->dados[i-1] = l->dados[i];
    }
    l->quantidade--;
    return 1;
}
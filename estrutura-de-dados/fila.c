#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fila.h"

NO *criaNO() {
    NO *no = (NO*)malloc(sizeof(NO));
    return no;
}

void destroiNO(NO *no){
    free(no);
}

Fila *criaFila(){
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    if(fila != NULL){
        fila->inicio = fila->final = NULL;
        fila->quantidade = 0;
    }
    return fila;
}

void destroiFila(Fila *fila) {
    if(fila == NULL) return;
    while(fila->inicio != NULL){
        NO *aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        destroiNO(aux);
    }
    free(fila);
}

int estaVazia(Fila *fila) {
    if(fila == NULL) return 0;
    return fila->quantidade == 0;
}

int enfileirar(Fila *fila, int num) {
    if(fila == NULL) return 0;
    NO *novo = criaNO();
    novo->dados = num;
    novo->prox = NULL;
    if(estaVazia(fila)){
        fila->inicio = novo;
    } else {
        fila->final->prox = novo;
    }   
    fila->final = novo;
    fila->quantidade++;
    return 1;
}

int desenfileirar(Fila *fila) {
    if(fila == NULL) return 0;
    if(estaVazia(fila)) return 0;
    NO *aux = fila->inicio;
    fila->inicio = aux->prox;
    if(fila->final == aux) fila->final = aux->prox;
    destroiNO(aux);
    fila->quantidade--;
    return 1;
}

int verTopo(Fila *fila) {
    if(fila == NULL) return 0;
    return fila->inicio->dados;
}

void imprimirFila(Fila *fila){
    if (fila == NULL) return;
    NO *aux = fila->inicio;
    while (aux != NULL){
        printf("%d ", aux->dados); 
        aux = aux->prox;
    }
    printf("\n");
}

int tamanhoFila(Fila *fila){
    if(fila == NULL) return -1;
    return fila->quantidade;
}

int existeNaFila(Fila *fila, int numero) {
    if (fila == NULL || fila->inicio == NULL) {
        return 0; 
    }

    NO *atual = fila->inicio;
    while (atual != NULL) {
        if (atual->dados == numero) {
            return 1;
        }
        atual = atual->prox;
    }

    return 0;
}

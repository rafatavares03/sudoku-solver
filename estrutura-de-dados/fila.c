#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./fila.h"
#include "../sudoku.h"
#include "../saida.h"

NO *criaNO() {
    NO *no = (NO*)malloc(sizeof(NO));
    no->prox = NULL;
    no->sudoku = NULL;
    return no;
}

void destroiNO(NO *no){
    destroiSudokuInt(no->sudoku);
    free(no);
}

Fila *criaFila(){
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    if(fila != NULL){
        fila->inicio = fila->final = NULL;
        fila->tamanho = 0;
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

int estaVaziaFila(Fila *fila) {
    if(fila == NULL) return 0;
    return fila->tamanho == 0;
}

int enfileirar(Fila *fila, int **sudoku) {
    if(fila == NULL) return 0;
    NO *novo = criaNO();
    novo->sudoku = sudoku;
    
    if(estaVaziaFila(fila)){
        fila->inicio = novo;
    } else {
        fila->final->prox = novo;
    }   
    fila->final = novo;
    fila->tamanho++;
    return 1;
}

int desenfileirar(Fila *fila) {
    if(fila == NULL) return 0;
    if(estaVaziaFila(fila)) return 0;
    NO *aux = fila->inicio;
    fila->inicio = aux->prox;
    if(fila->final == aux) fila->final = aux->prox;
    destroiNO(aux);
    fila->tamanho++;
    return 1;
}

void imprimirFila(Fila *fila){
    if (fila == NULL) return;
    NO *aux = fila->inicio;
    int number = 1;
    while (aux != NULL){
        printf("%d\n", number); number++;
        imprimeSudoku(aux->sudoku);
        aux = aux->prox;
    }
    printf("\n");
}

int tamanhoFila(Fila *fila){
    if(fila == NULL) return -1;
    return fila->tamanho;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./filaSu.h"
#include "../sudoku.h"
#include "../saida.h"

NO *criaNOSu() {
    NO *no = (NO*)malloc(sizeof(NO));
    if(no != NULL){
        no->sudoku = alocaSudokuInt();
    }
    return no;
}

void destroiNOSu(NO *no){
    destroiSudokuInt(no->sudoku);
    free(no);
}

Fila *criaFilaSu(){
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    if(fila != NULL){
        fila->inicio = fila->final = NULL;
    }
    return fila;
}

void destroiFilaSu(Fila *fila) {
    if(fila == NULL) return;
    while(fila->inicio != NULL){
        NO *aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        destroiNOSu(aux);
    }
    free(fila);
}

int estaVaziaSu(Fila *fila) {
    if(fila == NULL) return 0;
    return (fila->inicio == NULL && fila->final == NULL) ? 1 : 0;
}

int enfileirarSu(Fila *fila, int **sudoku) {
    if(fila == NULL) return 0;
    NO *novo = criaNOSu();
    novo->sudoku = sudoku;
    novo->prox = NULL;
    if(estaVaziaSu(fila)){
        fila->inicio = novo;
    } else {
        fila->final->prox = novo;
    }   
    fila->final = novo;
    return 1;
}

int desenfileirarSu(Fila *fila) {
    if(fila == NULL) return 0;
    if(estaVaziaSu(fila)) return 0;
    NO *aux = fila->inicio;
    fila->inicio = aux->prox;
    if(fila->final == aux) fila->final = aux->prox;
    destroiNOSu(aux);
    return 1;
}

void imprimirFilaSu(Fila *fila){
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

int tamanhoFilaSu(Fila *fila){
    if(fila == NULL) return -1;

    int tamanho = 0;  
    NO *aux = fila->inicio;  

    while(aux != NULL){
        tamanho++;           
        aux = aux->prox;     
    }

    return tamanho;  
}

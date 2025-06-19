#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

struct Vetor {
    int* elementos;
    int tamanho;
    int capacidade;
};

Vetor* criarVetor(int capacidadeInicial) {
    Vetor* vetor = (Vetor*)malloc(sizeof(Vetor));
    if (vetor == NULL) {
        return NULL;
    }
    vetor->elementos = (int*)malloc(capacidadeInicial * sizeof(int));
    if (vetor->elementos == NULL) {
        free(vetor);
        return NULL;
    }
    vetor->tamanho = 0;
    vetor->capacidade = capacidadeInicial;
    return vetor;
}

int inserirElemento(Vetor* vetor, int elemento) {
    if (vetor == NULL) {
        return 0;
    }
    if (vetor->tamanho == vetor->capacidade) {
        vetor->capacidade *= 2;
        int* temp = (int*)realloc(vetor->elementos, vetor->capacidade * sizeof(int));
        if (temp == NULL) {
            return 0;
        }
        vetor->elementos = temp;
    }
    vetor->elementos[vetor->tamanho] = elemento;
    vetor->tamanho++;
    return 1;
}

int removerElemento(Vetor* vetor, int posicao) {
    if (vetor == NULL || posicao < 0 || posicao >= vetor->tamanho) {
        return 0;
    }
    for (int i = posicao; i < vetor->tamanho - 1; i++) {
        vetor->elementos[i] = vetor->elementos[i + 1];
    }
    vetor->tamanho--;
    return 1;
}

int consultarElemento(Vetor* vetor, int posicao, int* elemento) {
    if (vetor == NULL || posicao < 0 || posicao >= vetor->tamanho) {
        return 0;
    }
    *elemento = vetor->elementos[posicao];
    return 1;
}

void imprimirVetor(Vetor* vetor) {
    if (vetor == NULL) {
        return;
    }
    printf("[");
    for (int i = 0; i < vetor->tamanho; i++) {
        printf("%d", vetor->elementos[i]);
        if (i < vetor->tamanho - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void removerVetor(Vetor* vetor) {
    if (vetor != NULL) {
        free(vetor->elementos);
        free(vetor);
    }
}

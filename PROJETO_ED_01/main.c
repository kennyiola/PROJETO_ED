/*
** Função: Algoritmo de vetor dinâmico
** Autor : Genilson Pereira & Matheus Henrique
** Data : 19/06/2025
** Observações:
*/

#include <stdio.h>
#include "vetor.h"

int main() {
    Vetor* vetor = criarVetor(2);

    inserirElemento(vetor, 10);
    inserirElemento(vetor, 20);
    inserirElemento(vetor, 30);

    printf("Vetor: ");
    imprimirVetor(vetor);

    int elemento;
    if (consultarElemento(vetor, 1, &elemento)) {
        printf("Elemento na posição 1: %d\n", elemento);
    }

    removerElemento(vetor, 0);
    printf("Vetor após remoção: ");
    imprimirVetor(vetor);

    removerVetor(vetor);

    return 0;
}

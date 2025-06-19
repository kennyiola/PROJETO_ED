#ifndef VETOR_H
#define VETOR_H

typedef struct Vetor Vetor;

Vetor* criarVetor(int capacidadeInicial);
int inserirElemento(Vetor* vetor, int elemento);
int removerElemento(Vetor* vetor, int posicao);
int consultarElemento(Vetor* vetor, int posicao, int* elemento);
void imprimirVetor(Vetor* vetor);
void removerVetor(Vetor* vetor);

#endif

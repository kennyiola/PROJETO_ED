/*
** Função     : Sistema de Registro de Estudantes com Lista, Pilha, Fila e Deque
** Autor      : Matheus Henrique e Genilson Pereira
** Data       : 19/06/25
** Observações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int matricula;
    float notas[3];
} Estudante;

typedef struct Nodo {
    Estudante aluno;
    struct Nodo *proximo;
} Nodo;

typedef struct Pilha {
    float historico[100][3];
    int topo;
} Pilha;

typedef struct Fila {
    Estudante alunos[100];
    int inicio;
    int fim;
} Fila;

typedef struct Deque {
    Estudante alunos[100];
    int inicio;
    int fim;
} Deque;

Nodo *lista = NULL;
Pilha pilha;
Fila fila;
Deque deque;

void inicializar() {
    pilha.topo = -1;
    fila.inicio = 0;
    fila.fim = 0;
    deque.inicio = 50;
    deque.fim = 50;
}

void adicionarEstudante() {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    printf("Nome: ");
    scanf(" %[^\n]", novo->aluno.nome);
    printf("Matricula: ");
    scanf("%d", &novo->aluno.matricula);
    printf("Notas (3): ");
    scanf("%f %f %f", &novo->aluno.notas[0], &novo->aluno.notas[1], &novo->aluno.notas[2]);
    novo->proximo = lista;
    lista = novo;
}

void listarEstudantes() {
    Nodo *p = lista;
    while (p != NULL) {
        printf("Nome: %s, Matricula: %d, Notas: %.2f %.2f %.2f\n", p->aluno.nome, p->aluno.matricula, p->aluno.notas[0], p->aluno.notas[1], p->aluno.notas[2]);
        p = p->proximo;
    }
}

Nodo* buscarEstudante(int matricula) {
    Nodo *p = lista;
    while (p != NULL) {
        if (p->aluno.matricula == matricula) {
            return p;
        }
        p = p->proximo;
    }
    return NULL;
}

void atualizarNotas() {
    int m;
    printf("Matricula do aluno: ");
    scanf("%d", &m);
    Nodo *aluno = buscarEstudante(m);
    if (aluno != NULL) {
        pilha.topo++;
        pilha.historico[pilha.topo][0] = aluno->aluno.notas[0];
        pilha.historico[pilha.topo][1] = aluno->aluno.notas[1];
        pilha.historico[pilha.topo][2] = aluno->aluno.notas[2];
        printf("Novas notas (3): ");
        scanf("%f %f %f", &aluno->aluno.notas[0], &aluno->aluno.notas[1], &aluno->aluno.notas[2]);
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

void adicionarFilaMatricula() {
    if (fila.fim < 100) {
        printf("Nome: ");
        scanf(" %[^\n]", fila.alunos[fila.fim].nome);
        printf("Matricula: ");
        scanf("%d", &fila.alunos[fila.fim].matricula);
        fila.fim++;
    } else {
        printf("Fila cheia.\n");
    }
}

void removerFilaMatricula() {
    if (fila.inicio < fila.fim) {
        printf("Aluno matriculado: %s\n", fila.alunos[fila.inicio].nome);
        fila.inicio++;
    } else {
        printf("Fila vazia.\n");
    }
}

void adicionarInicioDeque() {
    if (deque.inicio > 0) {
        deque.inicio--;
        printf("Nome: ");
        scanf(" %[^\n]", deque.alunos[deque.inicio].nome);
        printf("Matricula: ");
        scanf("%d", &deque.alunos[deque.inicio].matricula);
    } else {
        printf("Deque cheio no inicio.\n");
    }
}

void adicionarFimDeque() {
    if (deque.fim < 100) {
        printf("Nome: ");
        scanf(" %[^\n]", deque.alunos[deque.fim].nome);
        printf("Matricula: ");
        scanf("%d", &deque.alunos[deque.fim].matricula);
        deque.fim++;
    } else {
        printf("Deque cheio no fim.\n");
    }
}

void calcularMedia() {
    int m;
    printf("Matricula do aluno: ");
    scanf("%d", &m);
    Nodo *aluno = buscarEstudante(m);
    if (aluno != NULL) {
        float media = (aluno->aluno.notas[0] + aluno->aluno.notas[1] + aluno->aluno.notas[2]) / 3;
        printf("Media: %.2f\n", media);
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

int main() {
    int opcao;
    inicializar();
    do {
        printf("\n1-Adicionar Estudante\n2-Listar Estudantes\n3-Atualizar Notas\n4-Adicionar Fila Matricula\n5-Remover Fila Matricula\n6-Adicionar Inicio Deque\n7-Adicionar Fim Deque\n8-Calcular Media\n0-Sair\n");
        scanf("%d", &opcao);
        if (opcao == 1) adicionarEstudante();
        if (opcao == 2) listarEstudantes();
        if (opcao == 3) atualizarNotas();
        if (opcao == 4) adicionarFilaMatricula();
        if (opcao == 5) removerFilaMatricula();
        if (opcao == 6) adicionarInicioDeque();
        if (opcao == 7) adicionarFimDeque();
        if (opcao == 8) calcularMedia();
    } while (opcao != 0);
    return 0;
}
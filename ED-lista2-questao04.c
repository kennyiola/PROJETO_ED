/*
** Função     : Sistema de gerenciamento de tarefas (To-Do List) com Lista, Pilha, Fila, Deque e Recursividade
** Autor      : Matheus Henrique e Genilson Pereira
** Data       : 19/06/25
** Observações: Sistema simples com operações básicas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char descricao[100];
    int prioridade;
    int dataVencimento;
} Tarefa;

typedef struct Nodo {
    Tarefa tarefa;
    struct Nodo *proximo;
} Nodo;

typedef struct Pilha {
    Tarefa tarefas[100];
    int topo;
} Pilha;

typedef struct Fila {
    Tarefa tarefas[100];
    int inicio;
    int fim;
} Fila;

typedef struct Deque {
    Tarefa tarefas[100];
    int inicio;
    int fim;
} Deque;

Nodo *todoList = NULL;
Pilha pilhaConcluidas;
Fila filaAgendadas;
Deque dequeTarefas;

void inicializar() {
    pilhaConcluidas.topo = -1;
    filaAgendadas.inicio = 0;
    filaAgendadas.fim = 0;
    dequeTarefas.inicio = 50;
    dequeTarefas.fim = 50;
}

void adicionarInicioLista() {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    printf("Descricao: ");
    scanf(" %[^\n]", novo->tarefa.descricao);
    printf("Prioridade (1-3): ");
    scanf("%d", &novo->tarefa.prioridade);
    printf("Data de vencimento (DDMMYYYY): ");
    scanf("%d", &novo->tarefa.dataVencimento);
    novo->proximo = todoList;
    todoList = novo;
}

void adicionarFimLista() {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    printf("Descricao: ");
    scanf(" %[^\n]", novo->tarefa.descricao);
    printf("Prioridade (1-3): ");
    scanf("%d", &novo->tarefa.prioridade);
    printf("Data de vencimento (DDMMYYYY): ");
    scanf("%d", &novo->tarefa.dataVencimento);
    novo->proximo = NULL;
    if (todoList == NULL) {
        todoList = novo;
    } else {
        Nodo *p = todoList;
        while (p->proximo != NULL) {
            p = p->proximo;
        }
        p->proximo = novo;
    }
}

void listarTarefas() {
    Nodo *p = todoList;
    while (p != NULL) {
        printf("Descricao: %s, Prioridade: %d, Vencimento: %d\n", p->tarefa.descricao, p->tarefa.prioridade, p->tarefa.dataVencimento);
        p = p->proximo;
    }
}

void concluirTarefa() {
    if (todoList != NULL) {
        pilhaConcluidas.topo++;
        pilhaConcluidas.tarefas[pilhaConcluidas.topo] = todoList->tarefa;
        Nodo *temp = todoList;
        todoList = todoList->proximo;
        free(temp);
        printf("Tarefa concluida e movida para pilha.\n");
    } else {
        printf("Lista vazia.\n");
    }
}

void agendarTarefa() {
    if (filaAgendadas.fim < 100) {
        printf("Descricao: ");
        scanf(" %[^\n]", filaAgendadas.tarefas[filaAgendadas.fim].descricao);
        printf("Prioridade (1-3): ");
        scanf("%d", &filaAgendadas.tarefas[filaAgendadas.fim].prioridade);
        printf("Data de vencimento (DDMMYYYY): ");
        scanf("%d", &filaAgendadas.tarefas[filaAgendadas.fim].dataVencimento);
        filaAgendadas.fim++;
    } else {
        printf("Fila cheia.\n");
    }
}

void moverTarefaAgendada() {
    if (filaAgendadas.inicio < filaAgendadas.fim) {
        Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
        novo->tarefa = filaAgendadas.tarefas[filaAgendadas.inicio];
        novo->proximo = todoList;
        todoList = novo;
        filaAgendadas.inicio++;
        printf("Tarefa agendada movida para To-Do List.\n");
    } else {
        printf("Nenhuma tarefa agendada.\n");
    }
}

void adicionarInicioDeque() {
    if (dequeTarefas.inicio > 0) {
        dequeTarefas.inicio--;
        printf("Descricao: ");
        scanf(" %[^\n]", dequeTarefas.tarefas[dequeTarefas.inicio].descricao);
    } else {
        printf("Deque cheio no inicio.\n");
    }
}

void adicionarFimDeque() {
    if (dequeTarefas.fim < 100) {
        printf("Descricao: ");
        scanf(" %[^\n]", dequeTarefas.tarefas[dequeTarefas.fim].descricao);
        dequeTarefas.fim++;
    } else {
        printf("Deque cheio no fim.\n");
    }
}

int contarTarefas(Nodo *p) {
    if (p == NULL) {
        return 0;
    } else {
        return 1 + contarTarefas(p->proximo);
    }
}

int main() {
    int opcao;
    inicializar();
    do {
        printf("\n1-Adicionar Inicio Lista\n2-Adicionar Fim Lista\n3-Listar Tarefas\n4-Concluir Tarefa\n5-Agendar Tarefa\n6-Mover Agendada\n7-Adicionar Inicio Deque\n8-Adicionar Fim Deque\n9-Contar Tarefas\n0-Sair\n");
        scanf("%d", &opcao);
        if (opcao == 1) adicionarInicioLista();
        if (opcao == 2) adicionarFimLista();
        if (opcao == 3) listarTarefas();
        if (opcao == 4) concluirTarefa();
        if (opcao == 5) agendarTarefa();
        if (opcao == 6) moverTarefaAgendada();
        if (opcao == 7) adicionarInicioDeque();
        if (opcao == 8) adicionarFimDeque();
        if (opcao == 9) printf("Total de tarefas: %d\n", contarTarefas(todoList));
    } while (opcao != 0);
    return 0;
}
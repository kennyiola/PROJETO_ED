/*
** Função: Algoritmo de fila para agendamento de consultas médicas
** Autor : Genilson Pereira & Matheus Henrique
** Data : 20/06/2025
** Observações:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    char nome[50];
    int idade;
    char cpf[15];
} Paciente;

#define MAX_MEDICO 5

typedef struct {
    Paciente pacientes[MAX_MEDICO];
    int inicio;
    int fim;
    int quantidade;
} FilaMedico;

void inicializarFilaMedico(FilaMedico *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->quantidade = 0;
}

bool filaMedicoCheia(FilaMedico *fila) {
    return fila->quantidade == MAX_MEDICO;
}

bool filaMedicoVazia(FilaMedico *fila) {
    return fila->quantidade == 0;
}

bool enfileirarMedico(FilaMedico *fila, Paciente paciente) {
    if (filaMedicoCheia(fila)) {
        return false;
    }

    fila->fim = (fila->fim + 1) % MAX_MEDICO;
    fila->pacientes[fila->fim] = paciente;
    fila->quantidade++;
    return true;
}
Paciente desenfileirarMedico(FilaMedico *fila) {
    Paciente paciente;
    if (filaMedicoVazia(fila)) {
        strcpy(paciente.nome, "VAZIO"); 
        paciente.idade = -1;
        strcpy(paciente.cpf, "VAZIO");
        return paciente;
    }

    paciente = fila->pacientes[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_MEDICO;
    fila->quantidade--;
    return paciente;
}
typedef struct Node {
    Paciente paciente;
    struct Node *proximo;
} Node;

typedef struct {
    Node *inicio;
    Node *fim;
    int quantidade;
} FilaEnfermagem;

void inicializarFilaEnfermagem(FilaEnfermagem *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
}

bool filaEnfermagemVazia(FilaEnfermagem *fila) {
    return fila->inicio == NULL;
}

void enfileirarEnfermagem(FilaEnfermagem *fila, Paciente paciente) {
    Node *novoNode = (Node *)malloc(sizeof(Node));
    if (novoNode == NULL) {
        perror("Erro ao alocar memória para novo nó");
        exit(EXIT_FAILURE);
    }
    novoNode->paciente = paciente;
    novoNode->proximo = NULL;

    if (filaEnfermagemVazia(fila)) {
        fila->inicio = novoNode;
    } else {
        fila->fim->proximo = novoNode;
    }
    fila->fim = novoNode;
    fila->quantidade++;
}

Paciente desenfileirarEnfermagem(FilaEnfermagem *fila) {
    Paciente paciente;
    if (filaEnfermagemVazia(fila)) {
        strcpy(paciente.nome, "VAZIO");
        paciente.idade = -1;
        strcpy(paciente.cpf, "VAZIO");
        return paciente;
    }

    Node *temp = fila->inicio;
    paciente = temp->paciente;
    fila->inicio = fila->inicio->proximo;
    fila->quantidade--;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    return paciente;
}

Paciente cadastrarPaciente() {
    Paciente paciente;
    printf("Nome do paciente: ");
    scanf(" %[^\n]", paciente.nome); 

    printf("Idade do paciente: ");
    scanf("%d", &paciente.idade);

    printf("CPF do paciente: ");
    scanf(" %s", paciente.cpf);

    return paciente;
}

void exibirPacientes(void *fila, char tipo, int (*quantidadeFuncao)(void*), Paciente (*desenfileirarFuncao)(void*)) {
    int quantidade = quantidadeFuncao(fila);
    if (quantidade == 0) {
        printf("Nenhum paciente agendado para %s.\n", (tipo == 'M') ? "Médico" : "Enfermagem");
        return;
    }

    printf("Pacientes agendados para %s:\n", (tipo == 'M') ? "Médico" : "Enfermagem");
    for (int i = 0; i < quantidade; ++i) {
        Paciente paciente = desenfileirarFuncao(fila);
        if (strcmp(paciente.nome, "VAZIO") != 0) { 
            printf("  Nome: %s, Idade: %d, CPF: %s\n", paciente.nome, paciente.idade, paciente.cpf);
            if(tipo == 'M'){
                enfileirarMedico((FilaMedico*)fila,paciente);
            }else{
                enfileirarEnfermagem((FilaEnfermagem*)fila, paciente);
            }
        }
    }
}
int quantidadeFilaMedico(void* fila){
    return ((FilaMedico*)fila)->quantidade;
}

Paciente desenfileirarFilaMedico(void* fila){
    return desenfileirarMedico((FilaMedico*)fila);
}

int quantidadeFilaEnfermagem(void* fila){
    return ((FilaEnfermagem*)fila)->quantidade;
}

Paciente desenfileirarFilaEnfermagem(void* fila){
    return desenfileirarEnfermagem((FilaEnfermagem*)fila);
}

int main() {
    FilaMedico filaMedico;
    FilaEnfermagem filaEnfermagem;
    inicializarFilaMedico(&filaMedico);
    inicializarFilaEnfermagem(&filaEnfermagem);

    int opcao;
    do {
        printf("\n=== Sistema de Agendamento de Consultas ===\n");
        printf("1. Agendar consulta com Médico\n");
        printf("2. Agendar consulta com Enfermagem\n");
        printf("3. Listar agendamentos Médico\n");
        printf("4. Listar agendamentos Enfermagem\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Paciente paciente = cadastrarPaciente();
                if (enfileirarMedico(&filaMedico, paciente)) {
                    printf("Consulta com Médico agendada com sucesso!\n");
                } else {
                    printf("A fila do médico está cheia. Não é possível agendar.\n");
                }
                break;
            }
            case 2: {
                Paciente paciente = cadastrarPaciente();
                enfileirarEnfermagem(&filaEnfermagem, paciente);
                printf("Consulta com Enfermagem agendada com sucesso!\n");
                break;
            }
            case 3:
                exibirPacientes(&filaMedico, 'M', quantidadeFilaMedico, desenfileirarFilaMedico);
                break;
            case 4:
                exibirPacientes(&filaEnfermagem, 'E', quantidadeFilaEnfermagem, desenfileirarFilaEnfermagem);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    while (!filaEnfermagemVazia(&filaEnfermagem)) {
        desenfileirarEnfermagem(&filaEnfermagem);
    }
}
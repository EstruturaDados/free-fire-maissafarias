#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

Item mochila[MAX_ITENS];
int totalItens = 0;
bool estaOrdenadoPorNome = false;

// Função para adicionar item
void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &mochila[totalItens].prioridade);
    } while (mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5);

    totalItens++;
    estaOrdenadoPorNome = false; // novo item pode quebrar a ordenação
    printf("Item adicionado com sucesso!\n");
}

// Função para listar todos os itens
void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

// Ordenação com insertion sort
void ordenarMochila(CriterioOrdenacao criterio) {
    int comparacoes = 0;

    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            bool cond = false;

            if (criterio == NOME)
                cond = strcmp(mochila[j].nome, chave.nome) > 0;
            else if (criterio == TIPO)
                cond = strcmp(mochila[j].tipo, chave.tipo) > 0;
            else if (criterio == PRIORIDADE)
                cond = mochila[j].prioridade > chave.prioridade;

            comparacoes++;
            if (!cond) break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }

    printf("Mochila ordenada com sucesso (%d comparações realizadas).\n", comparacoes);
    estaOrdenadoPorNome = (criterio == NOME);
}

// Busca binária por nome
void buscarBinariaPorNome() {
    if (!estaOrdenadoPorNome) {
        printf("A mochila precisa estar ordenada por nome para usar busca binária.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int inicio = 0, fim = totalItens - 1, comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(mochila[meio].nome, nomeBusca);
        if (cmp == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
                   mochila[meio].nome,
                   mochila[meio].tipo,
                   mochila[meio].quantidade,
                   mochila[meio].prioridade);
            printf("Comparações feitas: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Item não encontrado após %d comparações.\n", comparacoes);
}

// Menu de ordenação
void menuOrdenacao() {
    int escolha;
    printf("\n--- MENU DE ORDENAÇÃO ---\n");
    printf("1. Ordenar por nome\n");
    printf("2. Ordenar por tipo\n");
    printf("3. Ordenar por prioridade\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            ordenarMochila(NOME);
            break;
        case 2:
            ordenarMochila(TIPO);
            break;
        case 3:
            ordenarMochila(PRIORIDADE);
            break;
        default:
            printf("Opção inválida.\n");
    }
}

// Função principal com menu
int main() {
    int opcao;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Adicionar item\n");
        printf("2. Listar itens\n");
        printf("3. Ordenar mochila\n");
        printf("4. Buscar item por nome (binária)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                listarItens();
                break;
            case 3:
                menuOrdenacao();
                break;
            case 4:
                buscarBinariaPorNome();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
#include <stdio.h>
#include <string.h>

// Definindo a struct do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor para armazenar os itens
Item mochila[10];
int totalItens = 0;

// Função para adicionar item
void adicionarItem() {
    if (totalItens >= 10) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Digite o tipo do item (ex: arma, cura, munição): ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;
    printf("Item adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem() {
    char nome[30];
    printf("Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            // Remove deslocando os próximos itens
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("Item removido com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }
}

// Função para listar os itens
void listarItens() {
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
    } else {
        printf("\nItens na mochila:\n");
        for (int i = 0; i < totalItens; i++) {
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
        }
    }
}

// Função principal com menu
int main() {
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}
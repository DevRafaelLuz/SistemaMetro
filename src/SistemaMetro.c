#include <stdio.h>
#include <stdlib.h>

#define MAX_ESTACOES 20

void exibirMenu() {
    printf("==== Sistema de Metro ====\n");
    printf("1. Inserir Aresta\n");
    printf("2. Remover Aresta\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void inserirAresta() {

}

void removerAresta() {

}

void exibirMatrizAtualizada() {

}
    
int main() {
    int opcao;

    do {
        system("cls");
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirAresta();
                break;
            case 2:
                removerAresta();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
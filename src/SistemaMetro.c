#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int numVertices;
    int **matrizAdj;
}Grafo;

Grafo* criarGrafo(int numVertices){
    Grafo *grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->matrizAdj = (int**) malloc(numVertices * sizeof(int*));
    for(int i = 0; i < numVertices; i++){
        grafo->matrizAdj[i] = (int*) calloc(numVertices, sizeof(int));
    }
    return grafo;
}

void exibirMenu() {
        printf("\n--- SISTEMA DE METRO ---\n");
        printf("1 - Remover ligacao entre estacoes\n");
        printf("2 - Exibir matriz das estacoes atualizada\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
}

void inicializarGrafoCompleto(Grafo *grafo){
    int matriz[20][20] = {
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1}
    };
    for(int i = 0; i < grafo->numVertices; i++){
        for(int j = 0; j < grafo->numVertices; j++){
            grafo->matrizAdj[i][j] = matriz[i][j];
        }
    }
}

void inserirAresta() {

}

void removerAresta(Grafo *grafo, int origem, int destino){
    if(origem < 0 || origem >= grafo->numVertices || destino < 0 || destino >= grafo->numVertices){
        printf("Erro: estacao invalida.\n");
        return;
    }
    if(grafo->matrizAdj[origem][destino] == 0){
        printf("Nao existe ligacao entre as estacoes %d e %d.\n", origem, destino);
        return;
    }
    grafo->matrizAdj[origem][destino] = 0;
    grafo->matrizAdj[destino][origem] = 0; 
    printf("Ligacao removida entre as estacoes %d e %d.\n", origem, destino);
}


void exibirMatriz(Grafo *grafo){
    printf("Matriz das estacoes:\n");
    for(int i = 0; i < grafo->numVertices; i++){
        for(int j = 0; j < grafo->numVertices; j++){
            printf("%d ", grafo->matrizAdj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int numEstacoes = 20;
    Grafo *metro = criarGrafo(numEstacoes);

    inicializarGrafoCompleto(metro);

    int opcao, origem, destino;
    do{
        system("cls");
        exibirMenu();
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                printf("Digite o numero da estacao de origem (de 0 a 19): ");
                scanf("%d", &origem);
                printf("Digite o numero da estacao de destino (de 0 a 19): ");
                scanf("%d", &destino);
                removerAresta(metro, origem, destino);
                break;
            case 2:
                exibirMatriz(metro);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }while(opcao != 0);
    
    // Liberacao memoria
    for(int i = 0; i < numEstacoes; i++){
        free(metro->matrizAdj[i]);
    }
    free(metro->matrizAdj);
    free(metro);

    return 0;
}

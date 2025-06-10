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
        printf("3 - Buscar caminho entre estacoes (BFS)\n");
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

void buscaLargura(Grafo *grafo, int origem, int destino) {
    int *visitado = (int*)calloc(grafo->numVertices, sizeof(int));
    int *fila = (int*)malloc(grafo->numVertices * sizeof(int));
    int *anterior = (int*)malloc(grafo->numVertices * sizeof(int));
    int inicio = 0, fim = 0, achou = 0;

    for(int i = 0; i < grafo->numVertices; i++) anterior[i] = -1;

    fila[fim++] = origem;
    visitado[origem] = 1;

    while(inicio < fim) {
        int atual = fila[inicio++];
        if(atual == destino) {
            achou = 1;
            break;
        }
        for(int i = 0; i < grafo->numVertices; i++) {
            if(grafo->matrizAdj[atual][i] && !visitado[i]) {
                fila[fim++] = i;
                visitado[i] = 1;
                anterior[i] = atual;
            }
        }
    }

    if(achou) {
        printf("Caminho: ");
        int caminho[grafo->numVertices], tam = 0, v = destino;
        while(v != -1) {
            caminho[tam++] = v;
            v = anterior[v];
        }
        for(int i = tam-1; i >= 0; i--) {
            printf("%d", caminho[i]);
            if(i > 0) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("Nao existe caminho entre as estacoes %d e %d.\n", origem, destino);
    }

    free(visitado);
    free(fila);
    free(anterior);
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
            case 3:
                printf("Digite o numero da estacao de origem (de 0 a 19): ");
                scanf("%d", &origem);
                printf("Digite o numero da estacao de destino (de 0 a 19): ");
                scanf("%d", &destino);
                buscaLargura(metro, origem, destino);
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

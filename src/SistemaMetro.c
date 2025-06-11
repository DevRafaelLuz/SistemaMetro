#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20

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
        printf("2 - Inserir ligacao entre estacoes\n");
        printf("3 - Exibir matriz das estacoes atualizada\n");
        printf("4 - Buscar caminho entre estacoes (BFS)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
}

void inicializarGrafoCompleto(Grafo *grafo){
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int i;

    FILE *arquivo = fopen("../../data/grafo.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo grafo.txt\n");
        exit(1);
    }

    for(i = 0; i < MAX_VERTICES; i++){
        for(int j = 0; j < MAX_VERTICES; j++){
            int valor;
            if (fscanf(arquivo, "%d;", &valor) != 1) {
                printf("Erro ao ler o arquivo grafo.txt na linha %d coluna %d\n", i+1, j+1);
                fclose(arquivo);
                exit(1);
            }
            matriz[i][j] = valor;
        }
    }

    for(i = 0; i < grafo->numVertices; i++){
        for(int j = 0; j < grafo->numVertices; j++){
            grafo->matrizAdj[i][j] = matriz[i][j];
        }
    }
    fclose(arquivo);
}

void inserirAresta(Grafo *grafo, int origem, int destino) {
	if (origem < 0 || origem >= grafo->numVertices || destino < 0 || destino >= grafo->numVertices) {
		printf("\nErro: estacao invalida!\n");
		return;
	} else if (origem == destino) {
		printf("\nErro: impossivel ligar uma estacao a ela mesma!\n");
		return;
	}
	
	if (grafo->matrizAdj[origem][destino] == 0) {
		grafo->matrizAdj[origem][destino] = 1;
		grafo->matrizAdj[destino][origem] = 1;
		printf("\nLigacao inserida com sucesso!\n");
	} else {
		printf("\nJa existe uma ligacao entre essas estacoes!\n");
	}
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
    Grafo *metro = criarGrafo(MAX_VERTICES);

    inicializarGrafoCompleto(metro);

    int opcao, origem, destino;

    system("cls");
    do{
        exibirMenu();
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                printf("Remover - Digite o numero da estacao de origem (de 0 a 19): ");
                scanf("%d", &origem);
                printf("Remover - Digite o numero da estacao de destino (de 0 a 19): ");
                scanf("%d", &destino);
                removerAresta(metro, origem, destino);
                break;
            case 2:
            	printf("Inserir - Digite o numero da estacao de origem (de 0 a 19): ");
            	scanf("%d", &origem);
            	printf("Inserir - Digite o numero da estacao de destino (de 0 a 19): ");
            	scanf("%d", &destino);
            	inserirAresta(metro, origem, destino);
            	break;
            case 3:
                exibirMatriz(metro);
                break;
            case 4:
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
    
    for(int i = 0; i < MAX_VERTICES; i++){
        free(metro->matrizAdj[i]);
    }
    free(metro->matrizAdj);
    free(metro);

    return 0;
}

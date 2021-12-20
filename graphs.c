#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "header.h"

/*
 * FUNÇÕES INTERNAS
 * Utilizadas somente em "graphs.c"
 */

// Retorna a quantidade de vértices em uma lista encadeada de vértices
// Parâmetros:
// graph -> ponteiro do primeiro elemento da lista encadeada de vértices
int getGraphSize(VerticesListElement* graph) {
    int graphSize = 0;
    
    while (graph != NULL)
    {
        graphSize++;
        graph = graph->next;
    }
    
    return graphSize;
}

// Retorna o vértice presente na lista encadeada de vértices na posição indicada por index
// Se o tamanho do grafo for menor ou igual a index, retorna NULL
// Parâmetros:
// graph -> Ponteiro para o primeiro vértice da lista encadeada de vértices
// index -> Posição do vértice, na lista encadeada de vértices, que será retornado (começa em 0)
VerticesListElement *getVertexByIndex(VerticesListElement *graph, int index) {
    int i = 0;
    while (1)
    {
        if (!graph || index == i) return graph;
        graph = graph->next;
        i++;
    }
}

// Consegue a posição do vértice na lista encadeada de vértices que possui o nomeEstacao dado
int getVertexIndexByName(VerticesListElement *graph, char *nomeEstacao) {
    int index = 0;
    while (graph != NULL && strcmp(graph->nomeEstacao, nomeEstacao))
    {
        graph = graph->next;
        index++;
    }
    
    return index;
}

// Recebe um array de registros e retorna o index do registro que possui codEstacao igual ao valor
// de codEstacao recebido como parâmetro
// Se o registro não for encontrado, retorna -1
// Parâmetros:
// regArray -> Array de registros a ser analisado
// arraySize -> Quantidade de registros salvos em regArray
// codEstacao -> codEstacao do registro que se quer encontrar
int getRegisterArrayIndexById(Register *regArray, int arraySize, int codEstacao)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (regArray[i].codEstacao == codEstacao)
        {
            return i;
        }
    }

    return -1;
}

// Adiciona o vertice a uma lista ordenada de vertices e retorna o topo da lista de vertices
VerticesListElement *addVertexToGraph(VerticesListElement *verticesListHead, int addedRegIndex, Register *regArray, int arrayAmount)
{
    VerticesListElement *verticeAux = NULL, *verticeAuxAnt = NULL;
    VerticesListElement *verticeInsert = NULL;

    if (verticesListHead == NULL)
    {
        verticesListHead = (VerticesListElement *)malloc(sizeof(VerticesListElement));
        strcpy(verticesListHead->nomeEstacao, regArray[addedRegIndex].nomeEstacao);
        verticesListHead->cor = 0;
        verticesListHead->next = NULL;
        verticesListHead->edgesListHead = NULL;
        return verticesListHead;
    }
    else
    {
        verticeAux = verticesListHead;
        while (verticeAux!=NULL)
        {
            if (strcmp(verticeAux->nomeEstacao, regArray[addedRegIndex].nomeEstacao) >= 0){
                if(strcmp(verticeAux->nomeEstacao, regArray[addedRegIndex].nomeEstacao) == 0){
                    return verticesListHead;
                }
                if(verticeAux==verticesListHead){
                    verticeInsert = (VerticesListElement *)malloc(sizeof(VerticesListElement));
                    strcpy(verticeInsert->nomeEstacao, regArray[addedRegIndex].nomeEstacao);
                    verticeInsert->cor = 0;
                    verticeInsert->edgesListHead =NULL;
                    verticeInsert->next = verticesListHead;
                    verticesListHead = verticeInsert;
                    return verticesListHead;
                }
                verticeInsert = (VerticesListElement *)malloc(sizeof(VerticesListElement));
                strcpy(verticeInsert->nomeEstacao, regArray[addedRegIndex].nomeEstacao);
                verticeInsert->cor = 0;
                verticeInsert->edgesListHead =NULL;
                verticeInsert->next = verticeAux;
                verticeAuxAnt->next = verticeInsert;
                return verticesListHead;
            }
            verticeAuxAnt = verticeAux;
            verticeAux = verticeAux->next;
        }
        verticeInsert = (VerticesListElement *)malloc(sizeof(VerticesListElement));
        strcpy(verticeInsert->nomeEstacao, regArray[addedRegIndex].nomeEstacao);
        verticeInsert->cor = 0;
        verticeInsert->edgesListHead = NULL;
        verticeInsert->next = NULL;
        verticeAuxAnt->next = verticeInsert;
        return verticesListHead;
    }   

}

// Adicina a aresta e linha para a estação de integracao a uma lista ordenada de arestas
void addEdgeIntegraToGraph(VerticesListElement *verticesListHead, int addedRegIndex, Register *regArray, int arrayAmount)
{
    EdgesListElement *edgeInsert = NULL, *edgeAux = NULL, *edgeAuxAnt = NULL;
    VerticesListElement *verticeAux = NULL;
    LinhasListElement *linhaInsert = NULL, *linhaAux = NULL, *linhaAuxAnt = NULL;
    int index;
    char nomeProxEstacao[MAX_NAME_LENGTH], nomeLinha[MAX_NAME_LENGTH];

    // Verifica se existe lista de vertices
    if (verticesListHead == NULL)
    {
        return;
    }

    // Verifica se existe próxima estação de integração
    if (regArray[addedRegIndex].codEstIntegra != -1)
    {
        index = getRegisterArrayIndexById(regArray, arrayAmount, regArray[addedRegIndex].codEstIntegra);
        strcpy(nomeProxEstacao, regArray[index].nomeEstacao);
        // Verifica se o nome da estacao codEstacao e diferente do nome da estacao codEstacaoIntegra
        if (strcmp(nomeProxEstacao, regArray[addedRegIndex].nomeEstacao) == 0)
        {
            return;
        }
        strcpy(nomeLinha, "Integracao");
        verticeAux = verticesListHead;

        // Encontra o vertice na lista de vertices para adicionar a aresta
        while (strcmp(verticeAux->nomeEstacao, regArray[addedRegIndex].nomeEstacao) != 0)
        {
            verticeAux = verticeAux->next;
            if (verticeAux == NULL)
            {
                // Para o caso de nao existir o vertice
                return;
            }
        }

        edgeAux = verticeAux->edgesListHead;
        edgeAuxAnt = verticeAux->edgesListHead;
        // Verifica se a aresta existe e adiciona ordenadamente
        while (edgeAux != NULL)
        {
            if (strcmp(nomeProxEstacao, edgeAux->nomeProxEst) <= 0)
            {
                // Se ja existe aresta ele ira verificar a linha
                if (strcmp(nomeProxEstacao, edgeAux->nomeProxEst) == 0)
                {
                    linhaAux = edgeAux->linhasListHead;
                    linhaAuxAnt = edgeAux->linhasListHead;
                    // Verifica se a linha esta na aresta e tenta adicionar ordenadamente
                    while (linhaAux != NULL)
                    {
                        if (strcmp(nomeLinha, linhaAux->nomeLinha) <= 0)
                        {
                            if (strcmp(nomeLinha, linhaAux->nomeLinha) == 0)
                            {
                                // Se ja existe a linha
                                return;
                            }
                            // Adiciona a linha
                            linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
                            strcpy(linhaInsert->nomeLinha, nomeLinha);
                            linhaInsert->next = linhaAux;
                            linhaAuxAnt->next = linhaInsert;
                            return;
                        }
                        linhaAuxAnt = linhaAux;
                        linhaAux = linhaAux->next;
                    }
                    // Adiciona a linha no final ou quando não tem linha
                    linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
                    strcpy(linhaInsert->nomeLinha, nomeLinha);
                    linhaInsert->next = NULL;
                    if (linhaAuxAnt == NULL)
                    {
                        edgeAux->linhasListHead = linhaInsert;
                    }
                    else
                    {
                        linhaAuxAnt->next = linhaInsert;
                    }
                    return;
                }
                // Adciona a aresta
                edgeInsert = (EdgesListElement *)malloc(sizeof(EdgesListElement));
                strcpy(edgeInsert->nomeProxEst, nomeProxEstacao);
                edgeInsert->distanciaProxEst = 0;
                if (edgeAux == edgeAuxAnt)
                {
                    edgeInsert->next = edgeAux;
                    verticeAux->edgesListHead = edgeInsert;
                }
                else
                {
                    edgeInsert->next = edgeAux;
                    edgeAuxAnt->next = edgeInsert;
                }
                linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
                strcpy(linhaInsert->nomeLinha, nomeLinha);
                linhaInsert->next = NULL;
                edgeInsert->linhasListHead = linhaInsert;
                return;
            }
            edgeAuxAnt = edgeAux;
            edgeAux = edgeAux->next;
        }
        // Adiciona a aresta no final ou quando nao tem aresta
        edgeInsert = (EdgesListElement *)malloc(sizeof(EdgesListElement));
        strcpy(edgeInsert->nomeProxEst, nomeProxEstacao);
        edgeInsert->distanciaProxEst = 0;
        edgeInsert->next = NULL;
        if (edgeAuxAnt == NULL)
        {
            verticeAux->edgesListHead = edgeInsert;
        }
        else
        {
            edgeAuxAnt->next = edgeInsert;
        }

        linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
        strcpy(linhaInsert->nomeLinha, nomeLinha);
        linhaInsert->next = NULL;
        edgeInsert->linhasListHead = linhaInsert;
        return;
    }
}

// Adicina a aresta com a linha (sem ser a de integracao) a uma lista ordenada de arestas
void addEdgeToGraph(VerticesListElement *verticesListHead, int addedRegIndex, Register *regArray, int arrayAmount)
{
    EdgesListElement *edgeInsert = NULL, *edgeAux = NULL, *edgeAuxAnt = NULL;
    VerticesListElement *verticeAux = NULL;
    LinhasListElement *linhaInsert = NULL, *linhaAux = NULL, *linhaAuxAnt = NULL;
    int index;
    char nomeProxEstacao[MAX_NAME_LENGTH], nomeLinha[MAX_NAME_LENGTH];

    // Verifica se existe lista de vertices
    if (verticesListHead == NULL)
    {
        return;
    }

    // Verifica se existe próxima estação
    if (regArray[addedRegIndex].codProxEstacao != -1)
    {
        index = getRegisterArrayIndexById(regArray, arrayAmount, regArray[addedRegIndex].codProxEstacao);
        strcpy(nomeProxEstacao, regArray[index].nomeEstacao);
        strcpy(nomeLinha, regArray[addedRegIndex].nomeLinha);
        verticeAux = verticesListHead;

        // Encontra o vertice na lista de vertices para adicionar a aresta
        while (strcmp(verticeAux->nomeEstacao, regArray[addedRegIndex].nomeEstacao) != 0)
        {
            verticeAux = verticeAux->next;
            if (verticeAux == NULL)
            {
                // Para o caso de nao existir o vertice
                return;
            }
        }

        edgeAux = verticeAux->edgesListHead;
        edgeAuxAnt = verticeAux->edgesListHead;
        // Verifica se a aresta existe e adiciona ordenadamente
        while (edgeAux != NULL)
        {
            if (strcmp(nomeProxEstacao, edgeAux->nomeProxEst) <= 0)
            {
                // Se ja existe aresta ele ira verificar a linha
                if (strcmp(nomeProxEstacao, edgeAux->nomeProxEst) == 0)
                {
                    linhaAux = edgeAux->linhasListHead;
                    linhaAuxAnt = edgeAux->linhasListHead;
                    // Verifica se a linha esta na aresta e tenta adicionar ordenadamente
                    while (linhaAux != NULL)
                    {
                        if (strcmp(nomeLinha, linhaAux->nomeLinha) <= 0)
                        {
                            if (strcmp(nomeLinha, linhaAux->nomeLinha) == 0)
                            {
                                // Se ja existe a linha
                                return;
                            }
                            // Adiciona a linha
                            linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
                            strcpy(linhaInsert->nomeLinha, nomeLinha);
                            if(linhaAux==linhaAuxAnt){
                                linhaInsert->next = linhaAux;
                                edgeAux->linhasListHead = linhaInsert;
                            }else{
                                linhaInsert->next = linhaAux;
                                linhaAuxAnt->next = linhaInsert;
                            }
                            return;
                        }
                        linhaAuxAnt = linhaAux;
                        linhaAux = linhaAux->next;
                    }
                    // Adiciona a linha no final ou quando não tem linha
                    linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
                    strcpy(linhaInsert->nomeLinha, nomeLinha);
                    linhaInsert->next = NULL;
                    if (linhaAuxAnt == NULL)
                    {
                        edgeAux->linhasListHead = linhaInsert;
                    }
                    else
                    {
                        linhaAuxAnt->next = linhaInsert;
                    }
                    return;
                }
                // Adciona a aresta
                edgeInsert = (EdgesListElement *)malloc(sizeof(EdgesListElement));
                strcpy(edgeInsert->nomeProxEst, nomeProxEstacao);
                edgeInsert->distanciaProxEst = regArray[addedRegIndex].distProxEstacao;
                if (edgeAux == edgeAuxAnt)
                {
                    edgeInsert->next = edgeAux;
                    verticeAux->edgesListHead = edgeInsert;
                }
                else
                {
                    edgeInsert->next = edgeAux;
                    edgeAuxAnt->next = edgeInsert;
                }

                linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
                strcpy(linhaInsert->nomeLinha, nomeLinha);
                linhaInsert->next = NULL;
                edgeInsert->linhasListHead = linhaInsert;
                return;
            }
            edgeAuxAnt = edgeAux;
            edgeAux = edgeAux->next;
        }
        // Adiciona a aresta no final ou quando nao tem aresta
        edgeInsert = (EdgesListElement *)malloc(sizeof(EdgesListElement));
        strcpy(edgeInsert->nomeProxEst, nomeProxEstacao);
        edgeInsert->distanciaProxEst = regArray[addedRegIndex].distProxEstacao;
        edgeInsert->next = NULL;
        if (edgeAuxAnt == NULL)
        {
            verticeAux->edgesListHead = edgeInsert;
        }
        else
        {
            edgeAuxAnt->next = edgeInsert;
        }

        linhaInsert = (LinhasListElement *)malloc(sizeof(LinhasListElement));
        strcpy(linhaInsert->nomeLinha, nomeLinha);
        linhaInsert->next = NULL;
        edgeInsert->linhasListHead = linhaInsert;
        return;
    }
}

// Lê um arquivo binário e retorna um vetor com todos os registros contidos nele
Register *allRegistersToArray(FILE *inFile, int *arraySize)
{
    int chunkSize = 100; // Tamanho de cada "pedaço" alocado por cada malloc/realloc
    int currentAllocatedSize = chunkSize;

    Register *regArray = (Register *)malloc(currentAllocatedSize * sizeof(Register));
    *arraySize = 0;

    readHeader(inFile);
    Register reg;
    while ((reg = readRegister(inFile)).tamanhoRegistro)
    {
        if (reg.removido == '0')
        {
            // Adiciona o registro no vetor
            regArray[*arraySize] = reg;

            // Checa se precisa expandir o vetor
            (*arraySize)++;
            if (!((*arraySize) % chunkSize))
            {
                currentAllocatedSize += chunkSize;
                regArray = (Register *)realloc(regArray, currentAllocatedSize * sizeof(Register));
            }
        }
    }

    return regArray;
}

// Gera um grafo a partir de dados contidos em um arquivo binário
VerticesListElement *generateGraph(FILE *inFile)
{
    VerticesListElement *graph = NULL;
    // Cria um vetor com todos os registros
    int arraySize = 0;
    Register *regArray = allRegistersToArray(inFile, &arraySize);

    /* Adiciona os registros do vetor de registro no grafo
    for (int i = 0; i < arraySize; i++)
    {
        graph = addRegToGraph(graph, i, regArray, arraySize);
    }*/
    for (int i = 0; i < arraySize; i++){
        graph = addVertexToGraph(graph, i, regArray, arraySize);
    }

    for (int i = 0; i < arraySize; i++){
        addEdgeToGraph(graph, i, regArray, arraySize);
        addEdgeIntegraToGraph(graph, i, regArray, arraySize);
    }

    return graph;
}

// Limpa a memória utilizada por um caminho path
void freePath(Path *path)
{
    // NEEDS TO BE IMPLEMENTED
}

// Imprime um caminho definido pela variável path
void printPath(Path *path, int distance)
{
    int verticesAmount = 0;
    Path *pathCursor = path;

    // Calcula e imprime a distância e número de vértices percorridos
    while (pathCursor != NULL)
    {
        verticesAmount++;
        pathCursor = pathCursor->next;
    }
    printf("Numero de estacoes que serao percorridas: %d\n", verticesAmount - 1); // Desconsidera estação destino
    printf("Distancia que sera percorrida: %d\n", distance);

    // Imprime o caminho percorrido
    pathCursor = path;
    while (pathCursor != NULL)
    {
        printf("%s", pathCursor->nomeEstacao);

        pathCursor = pathCursor->next;
        if (pathCursor != NULL)
            printf(", ");
    }

    return;
}

// Retorna o index do caminho mais curto atual que não foi visitado
int getUnvisitedMinValueIndex(int *shortestDistances, int arraySize, char *visitedVertices) {
    int minValue = INT_MAX;
    int minValueIndex = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if ((shortestDistances[i] < minValue) && (!visitedVertices[i])) {
            minValue = shortestDistances[i];
            minValueIndex = i;
        }
    }
    return minValueIndex;
}

// Encontra e retorna o caminho mais rápido entre a estação origem e a estação destino
// Parâmetros:
// graph -> Ponteiro para a primeira estação no vetor de estações na lista de adjacências
// startingEstacao -> Nome da estação da qual iremos partir
// destEstacao -> Nome da estação na qual queremos chegar
// distance -> Aponta para o endereço que receberá a distância total do caminho obtido
Path *findPathDijkstra(VerticesListElement *graph, char *startingEstacao, char *destEstacao, int* distance)
{
    int graphSize = getGraphSize(graph);
    int startingEstacaoIndex = getVertexIndexByName(graph, startingEstacao);
    int destEstacaoIndex = getVertexIndexByName(graph, destEstacao);

    // Nos vetores abaixo, o valor na posição X mostra informações sobre o vértice na posição X
    // da lista encadeada de estações
    // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // 0 - vértice ainda não foi visitado (não marcado) / 1 - O vértice foi visitado (marcado)
    char *visitedVertices = (char*)calloc(graphSize, sizeof(char));
    // Distâncias mais curtas encontradas a partir do vértice de origem
    int *shortestDistances = (int*)malloc(graphSize * sizeof(int));
    // Vetor de antecessores, usado para reconstruir o caminho de distância mais curta -> -1 indica que não há antecessor
    int *antecessors = (int*)malloc(graphSize * sizeof(int));
    //Inicializa os valores dos vetores
    for (int i = 0; i < graphSize; i++)
    {
        antecessors[i] = -1;
        shortestDistances[i] = INT_MAX; // Máximo valor que um int pode assumir
        if (i == startingEstacaoIndex) shortestDistances[i] = 0; //Custo 0 para a origem
    }
    
    // Faz o loop enquanto a estação de destino não é visitada
    while (!(visitedVertices[destEstacaoIndex]))
    {
        // Seleciona o próximo vértice a ser analisado e o marca como visitado
        int currentVertexIndex = getUnvisitedMinValueIndex(shortestDistances, graphSize, visitedVertices);
        visitedVertices[currentVertexIndex] = 1;

        // Se chegou à estação destino, saia do loop
        if (currentVertexIndex == destEstacaoIndex) break;
        // Se a menor distância obtida foi a máxima, não há caminho para o destino, saia do loop
        if (shortestDistances[currentVertexIndex] == INT_MAX) break;

        // Atualiza a distâncias dos vértices adjacentes ao vértice sendo analisado
        VerticesListElement *currentVertex = getVertexByIndex(graph, currentVertexIndex);
        EdgesListElement *edge = currentVertex->edgesListHead;
        while(edge)
        {
            int connectedVertexIndex = getVertexIndexByName(graph, edge->nomeProxEst);
            int previousDistance = shortestDistances[connectedVertexIndex];
            int newDistance = edge->distanciaProxEst + shortestDistances[currentVertexIndex];
            // Se a nova distância for menor, atualiza
            if (newDistance < previousDistance) 
            {
                shortestDistances[connectedVertexIndex] = newDistance;
                antecessors[connectedVertexIndex] = currentVertexIndex;
            }

            edge = edge->next;
        }
    }
    
    // Constrói o caminho a partir do vetor de antecessores
    Path *shortestPath = (Path*)malloc(sizeof(Path));
    shortestPath->next = NULL;
    strcpy(shortestPath->nomeEstacao, destEstacao);
    int antecessor = antecessors[destEstacaoIndex];
    while(antecessor != -1) {
        Path *nextNode = shortestPath;
        Path *newNode = (Path*)malloc(sizeof(Path));
        newNode->next = nextNode;
        VerticesListElement *newNodeVertex = getVertexByIndex(graph, antecessor);
        strcpy(newNode->nomeEstacao, newNodeVertex->nomeEstacao);
        shortestPath = newNode;
        antecessor = antecessors[antecessor];
    }


    // Define a distância e retorna o caminho
    *distance = shortestDistances[destEstacaoIndex];
    free(visitedVertices); free(shortestDistances); free(antecessors);
    return shortestPath;
}

int achaCor(char *vertice, VerticesListElement *verticesListHead){
    VerticesListElement *verticeListAux = NULL;

    verticeListAux = verticesListHead;

    while (verticeListAux!=NULL)
    {
        if(strcmp(vertice,verticeListAux->nomeEstacao)==0){
            return verticeListAux->cor;
        }
        verticeListAux = verticeListAux->next;
    }
    return -1;
}

int mudaCor(int cor, char *vertice, VerticesListElement *verticesListHead){
    VerticesListElement *verticeListAux = NULL;

    verticeListAux = verticesListHead;

    while (verticeListAux!=NULL)
    {
        if(strcmp(vertice,verticeListAux->nomeEstacao)==0){
            verticeListAux->cor = cor;
            return cor;
        }
        verticeListAux = verticeListAux->next;
    }
    return -1;
}

VerticesListElement* achaVertice(char *nome, VerticesListElement *verticesListHead){
    VerticesListElement *verticeAux = NULL;

    verticeAux = verticesListHead;
    while(verticeAux!=NULL){
        if(strcmp(nome,verticeAux->nomeEstacao)==0){
            return verticeAux;
        }
        verticeAux = verticeAux->next;
    }
    return verticeAux;
}

//Faz a busca em profundidade e para ao encontrar o primeiro ciclo com o vertice inicial ou acabar a busca
Ant* buscaDF(VerticesListElement *verticesListHead, Ant *antList){
    VerticesListElement *verticeAux = NULL, *verticeAuxProx = NULL;
    EdgesListElement *arestaAux = NULL;
    Ant *antInsert = NULL;
    char verticeAtual[MAX_NAME_LENGTH], verticeProx[MAX_NAME_LENGTH];

    strcpy(verticeAtual, antList->nome);
    mudaCor(1, verticeAtual, verticesListHead);

    verticeAux = achaVertice(verticeAtual, verticesListHead);
    arestaAux = verticeAux->edgesListHead;
    while (achaCor(antList->nome, verticesListHead)!=2)
    {
        strcpy(verticeProx,arestaAux->nomeProxEst);
        verticeAuxProx = achaVertice(verticeProx, verticesListHead);

        if(verticeAuxProx->cor==0){
            strcpy(verticeAtual,verticeProx);
            verticeAuxProx->cor = 1;
            antInsert = (Ant*) malloc(sizeof(Ant));
            strcpy(antInsert->nome,verticeProx);
            antInsert->next = NULL;
        }
        if(verticeAuxProx->cor==1){
            if(strcmp(antList->nome,verticeProx)==0){
                antInsert = (Ant*) malloc(sizeof(Ant));
                strcpy(antInsert->nome,verticeProx);
                antInsert->next = NULL;
                return antList;
            }
            arestaAux = arestaAux->next;
        }
        if(verticeAuxProx->cor==2){

        }
        
    }
    return antList;
    
}

/*
 * FUNÇÕES EXTERNAS
 * Utilizadas fora de "graphs.c"
 * Essas funções estão declaradas em "header.h"
 */

// Gera e imprime um grafo a partir de um arquivo binário
void printGraph(FILE *inFile)
{
    VerticesListElement *verticesListHead = generateGraph(inFile);

    VerticesListElement *vertexCursor = verticesListHead;
    // Loop responsável pela impressão dos vértices
    while (vertexCursor != NULL)
    {
        printf("%s", vertexCursor->nomeEstacao);

        EdgesListElement *edgeCursor = vertexCursor->edgesListHead;
        // Loop responsável pela impressão das arestas
        while (edgeCursor != NULL)
        {
            printf(" %s %d", edgeCursor->nomeProxEst, edgeCursor->distanciaProxEst);

            LinhasListElement *linhaCursor = edgeCursor->linhasListHead;
            // Loop responsável pela impressão das linhas
            while (linhaCursor != NULL)
            {
                printf(" %s", linhaCursor->nomeLinha);
                linhaCursor = linhaCursor->next;
            }

            edgeCursor = edgeCursor->next;
        }

        vertexCursor = vertexCursor->next;
        if (vertexCursor != NULL)
            printf("\n");
    }
}

// Imprime o caminho mais rápido entre dois nós utiliziando o algoritmo de Dijkstra
// Parâmetros:
// Infile -> Arquivo binário cujo dados serão usados para criar o grafo
// startingEstacao -> Estação de origem
// destEstacao -> Estação de destino, onde se quer chegar
void printDijkstra(FILE *inFile, char *startingEstacao, char *destEstacao)
{
    VerticesListElement *graph = generateGraph(inFile);
    int distance;
    Path *fastestPath = findPathDijkstra(graph, startingEstacao, destEstacao, &distance);

    if (strcmp(fastestPath->nomeEstacao, destEstacao)) printPath(fastestPath, distance);
    else printf("Não existe caminho entre as estações solicitadas.");

    freePath(fastestPath);
}

void printCiclo(FILE *inFile, char *startingEstacao)
{
    VerticesListElement *graph = generateGraph(inFile);
   // int distance, nEstacoes;
    Ant *antList=NULL;

    antList = (Ant*) malloc(sizeof(Ant));
    antList->next = NULL;
    strcpy(antList->nome, startingEstacao);

    antList = buscaDF(graph, antList);

}
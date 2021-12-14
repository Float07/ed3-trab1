#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"



/*
* FUNÇÕES INTERNAS
* Utilizadas somente em "graphs.c"
*/

//Encontra o registro com o codEstacao dado e retorna seu index no array regArray
//Se o registro não for encontrado, retorna -1
int getRegisterArrayIndexById (Register* regArray, int arraySize, int codEstacao) {
    for (int i = 0; i < arraySize; i++)
    {
        if (regArray[i].codEstacao == codEstacao) {
            return i;
        }
    }

    return -1;
}

//Adiciona o vertice (Nome da estacao no registro) a uma lista ordenada de vertices e retorna a cabeca da lista de vertices
VerticesListElement* addVertexToGraph(VerticesListElement* verticesListHead, int addedRegIndex, Register* regArray, int arrayAmount){
    VerticesListElement * verticeAux = NULL;
    VerticesListElement * verticeInsert = NULL;

    if(verticesListHead==NULL){
        verticesListHead = (VerticesListElement*) malloc(sizeof(VerticesListElement));
        strcpy (verticesListHead->nomeEstacao, regArray[addedRegIndex].nomeEstacao);
        verticesListHead->next = NULL;
        verticesListHead->edgesListHead = NULL;
        return verticesListHead; 
    }else{

        if(verticesListHead->next==NULL){

            if (strcmp(verticesListHead->nomeEstacao,regArray[addedRegIndex].nomeEstacao)>=0)
            {
                if (strcmp(verticesListHead->nomeEstacao,regArray[addedRegIndex].nomeEstacao)==0){
                    return verticesListHead;
                }
                verticeInsert = (VerticesListElement*) malloc(sizeof(VerticesListElement));
                strcpy(verticeInsert->nomeEstacao,regArray[addedRegIndex].nomeEstacao);
                verticeInsert->edgesListHead = NULL;
                verticeInsert->next = verticesListHead;
                verticesListHead = verticeInsert;
                return verticesListHead;
            }else{
                verticeInsert = (VerticesListElement*) malloc(sizeof(VerticesListElement));
                strcpy(verticeInsert->nomeEstacao,regArray[addedRegIndex].nomeEstacao);
                verticeInsert->edgesListHead = NULL;
                verticeInsert->next = NULL;
                verticesListHead->next = verticeInsert;
                return verticesListHead;
            }

        }else{
            verticeAux = verticesListHead;
            while (1)
            {
                if(strcmp(verticeAux->next->nomeEstacao,regArray[addedRegIndex].nomeEstacao)>=0){
                    if (strcmp(verticeAux->nomeEstacao,regArray[addedRegIndex].nomeEstacao)==0){
                        return verticesListHead;
                    }
                    verticeInsert = (VerticesListElement*) malloc(sizeof(VerticesListElement));
                    strcpy(verticeInsert->nomeEstacao,regArray[addedRegIndex].nomeEstacao);   
                    verticeInsert->edgesListHead = NULL;
                    verticeInsert->next = verticeAux->next;
                    verticeAux->next=verticeInsert;
                    return verticesListHead;

                }else{
                    verticeAux = verticeAux->next;
                    if(verticeAux->next->next==NULL){
                        if (strcmp(verticeAux->next->nomeEstacao,regArray[addedRegIndex].nomeEstacao)>=0)
                        {
                            if (strcmp(verticeAux->next->nomeEstacao,regArray[addedRegIndex].nomeEstacao)==0){
                                return verticesListHead;
                            }
                            verticeInsert = (VerticesListElement*) malloc(sizeof(VerticesListElement));
                            strcpy(verticeInsert->nomeEstacao,regArray[addedRegIndex].nomeEstacao);
                            verticeInsert->edgesListHead = NULL;
                            verticeInsert->next = verticeAux->next;
                            verticeAux->next = verticeInsert;
                            return verticesListHead;
                        }else{
                            verticeInsert = (VerticesListElement*) malloc(sizeof(VerticesListElement));
                            strcpy(verticeInsert->nomeEstacao,regArray[addedRegIndex].nomeEstacao);
                            verticeInsert->edgesListHead = NULL;
                            verticeInsert->next = NULL;
                            verticeAux->next->next = verticeInsert;
                            return verticesListHead;
                        }                        
                    }
                }
            } 
        }    
    }
    return verticesListHead;
}

//Adicino a aresta para a linha de integracao a uma lista ordenada de arestas
void addEdgeIntegraToGraph(VerticesListElement* verticesListHead, int addedRegIndex, Register* regArray, int arrayAmount){
    EdgesListElement *edgeInsert = NULL, *edgeAux = NULL, *edgeAuxAnt = NULL;
    VerticesListElement *verticeAux = NULL;
    LinhasListElement *linhaInsert = NULL, *linhaAux=NULL, *linhaAuxAnt = NULL;
    int index;
    char nomeProxEstacao[MAX_NAME_LENGTH], nomeLinha[MAX_NAME_LENGTH];

    //Verifica se existe lista de vertices
    if(verticesListHead==NULL){
        return;
    }

    //Verifica se existe próxima estação de integração
    if(regArray[addedRegIndex].codEstIntegra!=-1){
        index = getRegisterArrayIndexById(regArray, arrayAmount, regArray[addedRegIndex].codEstIntegra);
        strcpy(nomeProxEstacao,regArray[index].nomeEstacao);
        strcpy(nomeLinha,"Integra");
        verticeAux = verticesListHead;
        
        //Encontra o vertice na lista de vertices para adicionar a aresta
        while (strcmp(verticeAux->nomeEstacao,regArray[addedRegIndex].nomeEstacao)!=0)
        {
            verticeAux = verticeAux->next;
            if(verticeAux==NULL){
                //Para o caso de nao existir o vertice
                return;
            }
        }

        edgeAux = verticeAux->edgesListHead;
        edgeAuxAnt = edgeAux;
        //Verifica se a aresta existe e adiciona ordenadamente
        while (edgeAux!=NULL)
        {
           if(strcmp(nomeProxEstacao, edgeAux->nomeProxEst)<=0){
               //Se ja existe aresta ele ira verificar a linha
               if(strcmp(nomeProxEstacao, edgeAux->nomeProxEst)==0){
                   linhaAux = edgeAux->linhasListHead;
                   linhaAuxAnt = linhaAux;
                   //Verifica se a linha esta na aresta e tenta adicionar ordenadamente
                   while (linhaAux!=NULL)
                   {
                       if(strcmp(nomeLinha,linhaAux->nomeLinha)<=0){
                           if (strcmp(nomeLinha,linhaAux->nomeLinha)==0)
                           {
                               //Se ja existe a linha
                               return;
                           }
                           //Adiciona a linha
                           linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
                           strcpy(linhaInsert->nomeLinha,nomeLinha);
                           linhaInsert->next = linhaAux;
                           linhaAuxAnt->next = linhaInsert;
                           return;
                       }
                       linhaAuxAnt = linhaAux;
                       linhaAux = linhaAux->next;
                   }
                   //Adiciona a linha no final
                   linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
                   strcpy(linhaInsert->nomeLinha,nomeLinha);
                   linhaInsert->next = linhaAux;
                   linhaAuxAnt->next = linhaInsert;
                   return;
               }
               //Adciona a aresta
               edgeInsert = (EdgesListElement*) malloc (sizeof(EdgesListElement));
               strcpy(edgeInsert->nomeProxEst,nomeProxEstacao);
               edgeInsert->distanciaProxEst = regArray[addedRegIndex].distProxEstacao;
               edgeInsert->next = edgeAux;
               edgeAuxAnt->next = edgeInsert;
               linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
               strcpy(linhaInsert->nomeLinha,nomeLinha);
               linhaInsert->next = NULL;
               edgeAux->linhasListHead = linhaInsert;
               return;
           }
           edgeAuxAnt = edgeAux;
           edgeAux = edgeAux->next;
        }
        //Adiciona a aresta no final
        edgeInsert = (EdgesListElement*) malloc (sizeof(EdgesListElement));
        strcpy(edgeInsert->nomeProxEst,nomeProxEstacao);
        edgeInsert->distanciaProxEst = 0;
        edgeInsert->next = edgeAux;
        edgeAuxAnt->next = edgeInsert;
        linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
        strcpy(linhaInsert->nomeLinha,nomeLinha);
        linhaInsert->next = NULL;
        edgeAux->linhasListHead = linhaInsert;
        return;
    }
}

//Adicino a aresta (Proxima estacao e distancia) com a linha (sem ser a de integracao) a uma lista ordenada de arestas
void addEdgeToGraph(VerticesListElement* verticesListHead, int addedRegIndex, Register* regArray, int arrayAmount){
    EdgesListElement *edgeInsert = NULL, *edgeAux = NULL, *edgeAuxAnt = NULL;
    VerticesListElement *verticeAux = NULL;
    LinhasListElement *linhaInsert = NULL, *linhaAux=NULL, *linhaAuxAnt = NULL;
    int index;
    char nomeProxEstacao[MAX_NAME_LENGTH], nomeLinha[MAX_NAME_LENGTH];

    //Verifica se existe lista de vertices
    if(verticesListHead==NULL){
        return;
    }

    //Verifica se existe próxima estação
    if(regArray[addedRegIndex].codProxEstacao!=-1){
        index = getRegisterArrayIndexById(regArray, arrayAmount, regArray[addedRegIndex].codProxEstacao);
        strcpy(nomeProxEstacao,regArray[index].nomeEstacao);
        strcpy(nomeLinha,regArray[addedRegIndex].nomeLinha);
        verticeAux = verticesListHead;
        
        //Encontra o vertice na lista de vertices para adicionar a aresta
        while (strcmp(verticeAux->nomeEstacao,regArray[addedRegIndex].nomeEstacao)!=0)
        {
            verticeAux = verticeAux->next;
            if(verticeAux==NULL){
                //Para o caso de nao existir o vertice
                return;
            }
        }

        edgeAux = verticeAux->edgesListHead;
        edgeAuxAnt = edgeAux;
        //Verifica se a aresta existe e adiciona ordenadamente
        while (edgeAux!=NULL)
        {
           if(strcmp(nomeProxEstacao, edgeAux->nomeProxEst)<=0){
               //Se ja existe aresta ele ira verificar a linha
               if(strcmp(nomeProxEstacao, edgeAux->nomeProxEst)==0){
                   linhaAux = edgeAux->linhasListHead;
                   linhaAuxAnt = linhaAux;
                   //Verifica se a linha esta na aresta e tenta adicionar ordenadamente
                   while (linhaAux!=NULL)
                   {
                       if(strcmp(nomeLinha,linhaAux->nomeLinha)<=0){
                           if (strcmp(nomeLinha,linhaAux->nomeLinha)==0)
                           {
                               //Se ja existe a linha
                               return;
                           }
                           //Adiciona a linha
                           linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
                           strcpy(linhaInsert->nomeLinha,nomeLinha);
                           linhaInsert->next = linhaAux;
                           linhaAuxAnt->next = linhaInsert;
                           return;
                       }
                       linhaAuxAnt = linhaAux;
                       linhaAux = linhaAux->next;
                   }
                   //Adiciona a linha no final
                   linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
                   strcpy(linhaInsert->nomeLinha,nomeLinha);
                   linhaInsert->next = linhaAux;
                   linhaAuxAnt->next = linhaInsert;
                   return;
               }
               //Adciona a aresta
               edgeInsert = (EdgesListElement*) malloc (sizeof(EdgesListElement));
               strcpy(edgeInsert->nomeProxEst,nomeProxEstacao);
               edgeInsert->distanciaProxEst = regArray[addedRegIndex].distProxEstacao;
               edgeInsert->next = edgeAux;
               edgeAuxAnt->next = edgeInsert;
               linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
               strcpy(linhaInsert->nomeLinha,nomeLinha);
               linhaInsert->next = NULL;
               edgeAux->linhasListHead = linhaInsert;
               return;
           }
           edgeAuxAnt = edgeAux;
           edgeAux = edgeAux->next;
        }
        //Adiciona a aresta no final
        edgeInsert = (EdgesListElement*) malloc (sizeof(EdgesListElement));
        strcpy(edgeInsert->nomeProxEst,nomeProxEstacao);
        edgeInsert->distanciaProxEst = regArray[addedRegIndex].distProxEstacao;
        edgeInsert->next = edgeAux;
        if(edgeAux==NULL){
            verticeAux->edgesListHead = edgeInsert;
        }else{
            edgeAuxAnt->next = edgeInsert;
        }
        linhaInsert = (LinhasListElement*) malloc (sizeof(LinhasListElement));
        strcpy(linhaInsert->nomeLinha,nomeLinha);
        linhaInsert->next = NULL;
        edgeAux->linhasListHead = linhaInsert;
        return;
    }
}

/* Ele ira adicinar a linha na funcao de adicionar aresta
void addLinhaToGraph(){
    return;
}
*/

//Adiciona um registro ao grafo
VerticesListElement* addRegToGraph (VerticesListElement* verticesListHead, int addedRegIndex,
                                    Register* regArray, int arrayAmount) {
    
    if(addedRegIndex>arrayAmount){
        return NULL;
    }

    verticesListHead = addVertexToGraph(verticesListHead, addedRegIndex, regArray, arrayAmount);

    addEdgeToGraph(verticesListHead, addedRegIndex, regArray, arrayAmount);
    addEdgeIntegraToGraph(verticesListHead, addedRegIndex, regArray, arrayAmount);

    return verticesListHead;
    
}

//Lê um arquivo binário e retorna um vetor com todos os registros contidos nele
Register* allRegistersToArray (FILE* inFile, int* arraySize) {
    int chunkSize = 100; //Tamanho de cada "pedaço" alocado por cada malloc/realloc
    int currentAllocatedSize = chunkSize;

    Register* regArray = (Register*) malloc(currentAllocatedSize*sizeof(Register));
    *arraySize = 0;

    readHeader(inFile);
    Register reg;
    while ((reg = readRegister(inFile)).tamanhoRegistro)
    {
        if (reg.removido == '0') {
            //Adiciona o registro no vetor
            regArray[*arraySize] = reg;
            
            //Checa se precisa expandir o vetor
            (*arraySize)++;
            if (!((*arraySize)%chunkSize))
            {
                currentAllocatedSize += chunkSize;
                regArray = (Register*) realloc(regArray, currentAllocatedSize*sizeof(Register));
            }
        }
        
    }
    
    return regArray;
}

//Gera um grafo a partir de dados contidos em um arquivo binário
VerticesListElement* generateGraph (FILE* inFile) {
    VerticesListElement* graph = NULL;
    //Cria um vetor com todos os registros
    int arraySize = 0;
    Register* regArray = allRegistersToArray(inFile, &arraySize);
   
    //Adiciona os registros do vetor de registro no grafo
    for(int i=0; i<arraySize; i++){
        graph = addRegToGraph(graph, i, regArray, arraySize);
    }
    
    
    return graph;
}

//Limpa a memória utilizada por um caminho path
void freePath (Path* path) {
    //NEEDS TO BE IMPLEMENTED
}

//Imprime um caminho definido pela variável path
void printPath (Path* path) {
    int verticesAmount = 0;
    int totalDistance = 0;
    Path* pathCursor = path;

    //Calcula e imprime a distância e número de vértices percorridos
    while (pathCursor != NULL)
    {
        verticesAmount++;
        totalDistance += pathCursor->distance;
        
        pathCursor = pathCursor->next;
    }
    printf("Numero de estacoes que serao percorridas: %d\n", verticesAmount);
    printf("Distancia que sera percorrida: %d\n", totalDistance);

    //Imprime o caminho percorrido
    pathCursor = path;
    while (pathCursor != NULL)
    {
        printf("%s", pathCursor->nomeEstacao);

        pathCursor = pathCursor->next;
        if (pathCursor != NULL) printf(", ");
    }
    
    return;
}

//Encontra e retorna o caminho mais rápido entre a estação origem e a estação destino
//Parâmetros:
//graph -> Ponteiro para a primeira estação no vetor de estações na lista de adjacências
//startingEstacao -> Nome da estação da qual iremos partir
//destEstacao -> Nome da estação na qual queremos chegar
Path* findPathDijkstra (VerticesListElement* graph, char* startingEstacao, char* destEstacao) {
    
    //NEEDS IMPLEMENTATION

}

/*
* FUNÇÕES EXTERNAS
* Utilizadas fora de "graphs.c"
* Essas funções estão declaradas em "header.h"
*/

//Gera e imprime um grafo a partir de um arquivo binário
void printGraph (FILE* inFile) {
    VerticesListElement* verticesListHead = generateGraph(inFile);

    VerticesListElement* vertexCursor = verticesListHead;
    //Loop responsável pela impressão dos vértices
    while (vertexCursor != NULL)
    {
        printf("%s", vertexCursor->nomeEstacao);
        
        EdgesListElement* edgeCursor = vertexCursor->edgesListHead;
        //Loop responsável pela impressão das arestas
        while (edgeCursor != NULL)
        {
            printf(" %s %d", edgeCursor->nomeProxEst, edgeCursor->distanciaProxEst);

            LinhasListElement* linhaCursor = edgeCursor->linhasListHead;
            //Loop responsável pela impressão das linhas
            while (linhaCursor != NULL)
            {
                printf(" %s", linhaCursor->nomeLinha);
                linhaCursor = linhaCursor->next;
            }

            edgeCursor = edgeCursor->next;
        }
        

        vertexCursor = vertexCursor->next;
        if (vertexCursor != NULL) printf("\n");
    }
    
}

//Imprime o caminho mais rápido entre dois nós utiliziando o algoritmo de Dijkstra
//Parâmetros:
//Infile -> Arquivo binário cujo dados serão usados para criar o grafo
//startingEstacao -> Estação de origem
//destEstacao -> Estação de destino, onde se quer chegar
void printDijkstra (FILE* inFile, char* startingEstacao, char* destEstacao) {
    VerticesListElement* graph = generateGraph(inFile);
    Path* fastestPath = findPathDijkstra(graph, startingEstacao, destEstacao);

    printPath(fastestPath);

    freePath(fastestPath);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"



/*
* FUNÇÕES INTERNAS
* Utilizadas somente em "graphs.c"
*/

VerticesListElement* addVertexToGraph();
EdgesListElement* addEdgeToGraph();
LinhasListElement* addLinhaToGraph();

//Adiciona um registro ao grafo
VerticesListElement* addRegToGraph (VerticesListElement* verticesArrayHead, int addedRegIndex,
                                    Register* regArray, int arrayAmount) {
    return NULL;
}

//Lê um arquivo binário e retorna um vetor com todos os registros contidos nele
Register* allRegistersToArray (FILE* inFile, int* arraySize) {
    int chunkSize = 100; //Tamanho de cada "pedaço" alocado por cada malloc/realloc
    int currentAllocatedSize = chunkSize;

    Register* regArray = (Register*) malloc(currentAllocatedSize*sizeof(Register));
    *arraySize = 0;

    Register reg;
    while ((reg = readRegister(inFile)).tamanhoRegistro)
    {
        if (!reg.removido) {
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
    //Cria um vetor com todos os registros
    int arraySize = 0;
    Register* regArray = allRegistersToArray(inFile, &arraySize);
   
    //NEEDS IMPLEMENTATION
    
    return NULL;
}

/*
* FUNÇÕES EXTERNAS
* Utilizadas fora de "graphs.c"
* Essas funções estão declaradas em "header.h"
*/

//Gera e imprime um grafo a partir de um arquivo binário
void printGraph (FILE* inFile) {
    VerticesListElement* verticesArrayHead = generateGraph(inFile);

    VerticesListElement* vertexCursor = verticesArrayHead;
    //Loop responsável pela impressão dos vértices
    while (vertexCursor != NULL)
    {
        printf("%s", vertexCursor->nomeEstacao);
        
        EdgesListElement* edgeCursor = vertexCursor->edgesListHead;
        //Loop responsável pela impressão das arestas
        while (edgeCursor != NULL)
        {
            printf(", %s, %d", edgeCursor->nomeProxEst, edgeCursor->distanciaProxEst);

            LinhasListElement* linhaCursor = edgeCursor->linhasListHead;
            //Loop responsável pela impressão das linhas
            while (linhaCursor != NULL)
            {
                printf(", %s", linhaCursor->nomeLinha);
                linhaCursor = linhaCursor->next;
            }

            edgeCursor = edgeCursor->next;
        }
        

        vertexCursor = vertexCursor->next;
        if (vertexCursor != NULL) printf("\n");
    }
    
}

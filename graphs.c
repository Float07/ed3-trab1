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
    int chunkSize = 100;

    return NULL;
}

//Gera um grafo a partir de dados contidos em um arquivo binário
VerticesListElement* generateGraph (FILE* inFile) {
    VerticesListElement* verticesArrayHead = NULL;
   
    //NEEDS IMPLEMENTATION
    
    return verticesArrayHead;
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

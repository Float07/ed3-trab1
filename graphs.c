#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//NEEDS TO BE IMPLEMENTED
VerticesListElement* addRegToGraph(VerticesListElement* verticesArrayHead, Register reg);

//Gera um grafo a partir de dados contidos em um arquivo binário
VerticesListElement* generateGraph (FILE* inFile) {
    VerticesListElement* verticesArrayHead = NULL;
    readHeader(inFile);

    Register reg;
    while ((reg = readRegister(inFile)).tamanhoRegistro)
    {
        if (!reg.removido) {
            verticesArrayHead = addRegToGraph(verticesArrayHead, reg);
        }
    }
    
    return verticesArrayHead;
}

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

VerticesListElement* addVertex(VerticesListElement* verticesArrayHead, Register reg);

//Gera um grafo a partir de dados contidos em um arquivo binário
VerticesListElement* generateGraph (FILE* inFile) {
    VerticesListElement* verticesArrayHead = NULL;
    readHeader(inFile);

    Register reg;
    while ((reg = readRegister(inFile)).tamanhoRegistro)
    {
        verticesArrayHead = addVertex(verticesArrayHead, reg);
    }
    
    return verticesArrayHead;
}

//Gera e imprime um grafo a partir de um arquivo binário
void printGraph (FILE* inFile) {
    VerticesListElement* verticesArrayHead = generateGraph(inFile);

    VerticesListElement* cursor = verticesArrayHead;
    while (cursor != NULL)
    {
        printf("%s, ", cursor->nomeEstacao);
        
        

        cursor = cursor->next;
    }
    
}

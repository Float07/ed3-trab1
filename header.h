#ifndef MY__HEADER__H__   /* Include guard */
#define MY__HEADER__H__

//Tamanho máximo de um nomeEstacao ou nomeLinha
//Esse tamanho é o suficiente para qualquer nome comum e torna o programa menos suscetível a erro
//que usar alocação dinâmica
#define MAX_NAME_LENGTH 1024

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//registers.c
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//Usado para representar um registro.
struct Register{
    //Campos de tamanho fixo para gerenciamento
    char removido;      //1 byte
    int tamanhoRegistro;        //4 bytes
    long proxLista;     //8 bytes
    //Campos de tamanho fixo
    int codEstacao;     //4 bytes
    int codLinha;       //4 bytes
    int codProxEstacao; //4 bytes
    int distProxEstacao;//4 bytes
    int codLinhaIntegra;//4 bytes
    int codEstIntegra;  //4 bytes
    //Tamanho total dos campos fixos = 37 - 5 (removido e tamanhoRegistro não contam)

    //Campos de tamanho variável
    char nomeEstacao[MAX_NAME_LENGTH];
    char nomeLinha[MAX_NAME_LENGTH];
};
typedef struct Register Register;

//Tipo de dado que salva os campos de um registro como strings.
//Esse tipo é convertido para o tipo Register.
struct RegisterStr{
    //Campos de tamanho fixo
    char codEstacao[32];
    char codLinha[32];
    char codProxEstacao[32];
    char distProxEstacao[32];
    char codLinhaIntegra[32];
    char codEstIntegra[32];
    //Campos de tamanho variável
    char nomeEstacao[MAX_NAME_LENGTH];
    char nomeLinha[MAX_NAME_LENGTH];
};
typedef struct RegisterStr RegisterStr;

//Tipo para representar o cabeçalho do arquivo binário
struct FileHeader{
    char status;
    long topoLista;
    int nroEstacoes;
    int nroParesEstacao;
};
typedef struct FileHeader FileHeader;

void deleteMatchingBin(FILE* outFile, char* fields, int* intValues, char** strValues);
int printBin(FILE* inFile);
void readCSV(FILE* inFile, FILE* outFile);
void printMatchingBin(FILE* inFile, char* fields, int* intValues, char** strValues);
long* getAllMatchingRegistersOffset(FILE* inFile, char* fields, int* intValues, char** strValues);
void updateRegisterByOffset(FILE* outFile, long offset, char* fields, int* intValues, char** strValues);
Register registerStrToRegister(RegisterStr registerStr);
void insertRegister(FILE* outFile, Register reg);
void setConsistency(char consistency, FILE* outFile);
FileHeader readHeader(FILE* inFile);
Register readRegister(FILE* inFile);
void printRegister(Register reg);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//graphs.c
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//Um elemento de uma lista encadeada de linhas
typedef struct LinhasListElement LinhasListElement;
struct LinhasListElement
{
    char nomeLinha[MAX_NAME_LENGTH];
    LinhasListElement* next;
};

//Um elemento de uma lista encadeada de arestas
typedef struct EdgesListElement EdgesListElement;
struct EdgesListElement
{
    char nomeProxEst[MAX_NAME_LENGTH];
    int distanciaProxEst;
    LinhasListElement* linhasListHead;
    EdgesListElement* next;
};

//Um elemento de uma lista encadeada de vértices
typedef struct VerticesListElement VerticesListElement;
struct VerticesListElement {
    char nomeEstacao[MAX_NAME_LENGTH];
    EdgesListElement* edgesListHead;
    VerticesListElement* next;
};

//Representa um caminho no grafo
//Cada nó representa um destino e a distância para chegar nele a partir do nó anterior
typedef struct Path Path;
struct Path
{
    char nomeEstacao[MAX_NAME_LENGTH];
    Path* next;
};


void printGraph(FILE* inFile);
void printDijkstra (FILE* inFile, char* startingEstacao, char* destEstacao);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//funcoesFornecidas.c
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);


#endif 

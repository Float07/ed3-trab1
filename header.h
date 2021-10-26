#ifndef MY__HEADER__H__   /* Include guard */
#define MY__HEADER__H__

//Tamanho máximo de um nomeEstacao ou nomeLinha
//Esse tamanho é o suficiente para qualquer nome comum e torna o programa menos suscetível a erro
//que usar alocação dinâmica
#define MAX_NAME_LENGTH 1024

//registers.c

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

void deleteMatchingBin(FILE* outFile, char* fields, int* intValues, char** strValues);
void printBin(FILE* inFile);
void readCSV(FILE* inFile, FILE* outFile);
void printMatchingBin(FILE* inFile, char* fields, int* intValues, char** strValues);
long* getAllMatchingRegistersOffset(FILE* inFile, char* fields, int* intValues, char** strValues);
void updateRegisterByOffset(FILE* outFile, long offset, char* fields, int* intValues, char** strValues);
Register registerStrToRegister(RegisterStr registerStr);
void insertRegister(FILE* outFile, Register reg);

//funcoesFornecidas.c
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);


#endif 

#ifndef MY__HEADER__H__   /* Include guard */
#define MY__HEADER__H__

//Tamanho máximo de um nomeEstacao ou nomeLinha
//Esse tamanho é o suficiente para qualquer nome comum e torna o programa menos suscetível a erro
//que usar alocação dinâmica
#define MAX_NAME_LENGTH 1024

typedef struct Register Register;


//registers.c
void deleteMatchingBin(FILE* outFile, char* fields, int* intValues, char** strValues);
void printBin(FILE* inFile);
void readCSV(FILE* inFile, FILE* outFile);
void printMatchingBin(FILE* inFile, char* fields, int* intValues, char** strValues);

//funcoesFornecidas.c
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);


#endif 

#ifndef MY__HEADER__H__   /* Include guard */
#define MY__HEADER__H__


typedef struct Register Register;


void printBin(FILE* inFile);
void readCSV(FILE* inFile, FILE* outFile);

void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);


#endif 

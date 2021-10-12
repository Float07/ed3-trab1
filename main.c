#include <stdio.h>
#include "header.h"

//Tamanho máximo dos nomes dos arquivos de input e output
#define MAX_FILENAME_SIZE 256

int main(int argc, char *argv[]) {
    //FILE* csvInput = fopen("estacoes.csv", "r");
    //FILE* binOutput = fopen("binario.bin", "wb");

    //readCSV(csvInput, binOutput);

    //fclose(csvInput);
    //fclose(binOutput);

    //FILE* binInput = fopen("binario.bin", "rb");

    //printBin(binInput);

    //fclose(binInput);

    int funcionalidade; //Irá registrar a funcionalidade escolhida pelo usuário

    scanf("%d", &funcionalidade);

    switch (funcionalidade)
    {
    //Leitura de um csv e escrita no binário
    //Ao finalizar roda a função binarioNaTela()
    case 1:;
        char inputFileName[MAX_FILENAME_SIZE];
        char outputFileName[MAX_FILENAME_SIZE];
        scanf("%s %s", inputFileName, outputFileName);

        FILE* csvInput = fopen(inputFileName, "r");
        FILE* binOutput = fopen(outputFileName, "wb");

        readCSV(csvInput, binOutput);

        fclose(csvInput);
        fclose(binOutput);
        
        binarioNaTela(outputFileName);

        break;
    
    default:
        break;
    }
}
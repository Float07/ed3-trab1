#include <stdio.h>
#include <string.h>
#include "header.h"

//Tamanho máximo dos nomes dos arquivos de input e output
#define MAX_FILENAME_SIZE 256

/*
* Funções correspondentes a cada funcionalidade
* Elas serão chamadas em um switch-case localizado na main
*/
void funcionalidade1() {
        char inputFileName[MAX_FILENAME_SIZE];
        char outputFileName[MAX_FILENAME_SIZE];
        scanf("%s %s", inputFileName, outputFileName);

        FILE* csvInput = fopen(inputFileName, "r");
        FILE* binOutput = fopen(outputFileName, "wb");

        readCSV(csvInput, binOutput);

        fclose(csvInput);
        fclose(binOutput);
        
        binarioNaTela(outputFileName);

        return;
}

void funcionalidade2() {
        char inputFileName[MAX_FILENAME_SIZE];
        scanf("%s", inputFileName);

        FILE* inFile = fopen(inputFileName, "rb");
        printBin(inFile);
        fclose(inFile);

        return;
}

//Lê input do usuário para conseguir os critérios de busca
//Os parâmetros que são ponteiros terão os valores apontados modificados durante a execução
//Parâmetros:
//*qtdCampos -> quantidade de campos que serão considerados durante a busca
//*fields -> deve ser um vetor de tamanho 8 com todos seus elementos iguais a 0
//  Após a execução, cada elemento desse vetor irá indicar se cada um dos 8 campos será considerado durante a busca
//  1 - Será considerado / 2 - Não será considerado
//*intValues -> deve ser um vetor de tamanho 6
//  Após a execução, cada elemento desse vetor indica o valor desejado de cada um dos 6 campos de inteiro
//  Elementos correspondentes a campos que não serão considerados durante a busca podem assumir qualquer valor
//*strValues -> deve ser um vetor de tamanho dois, cada elemento apontando para uma string de tamanho MAX_FILENAME_SIZE
//   Após a execução, cada elemento desse vetor indica o valor desejado de cada um dos 2 campos de string
//  Elementos correspondentes a campos que não serão considerados durante a busca podem assumir qualquer valor
//
//Os elementos desses 3 vetores representam os campos na mesma ordem que os campos aparecem nos registros
//Os valores obtidos nessa função serão utilizados na função "getNextMatchingRegister" no módulo "registers.c"
void getSearchCriteria(int qtdCampos, char* field, int* intValues, char** strValues) {

    //Recebe quais campos serão analisados e quais os valores desejados
    for (int i = 0; i < qtdCampos; i++)
    {
        char nomeCampo[64];
        scanf("%s", nomeCampo);

        if(!strcmp(nomeCampo, "codEstacao")){
            field[0] = 1;
            scanf("%d", &(intValues[0]));
        }else if(!strcmp(nomeCampo, "codLinha")){
            field[1] = 1;
            scanf("%d", &(intValues[1]));
        }else if(!strcmp(nomeCampo, "codProxEstacao")){
            field[2] = 1;
            scanf("%d", &(intValues[2]));
        }else if(!strcmp(nomeCampo, "distProxEstacao")){
            field[3] = 1;
            scanf("%d",&(intValues[3]));
        }else if(!strcmp(nomeCampo, "codLinhaIntegra")){
            field[4] = 1;
            scanf("%d", &(intValues[4]));
        }else if(!strcmp(nomeCampo, "codEstIntegra")){
            field[5] = 1;
            scanf("%d", &(intValues[5]));
        }else if(!strcmp(nomeCampo, "nomeEstacao")){
            field[6] = 1;
            scan_quote_string(strValues[0]);
        }else if(!strcmp(nomeCampo, "nomeLinha")){
            field[7] = 1;
            scan_quote_string(strValues[1]);
        }
    }
    
}

void funcionalidade3() {
    //Veja a documentação de getSearchCriteria para melhor entender o significado de fields, intValues e strValues
    int qtdCampos;
    char fileName[MAX_FILENAME_SIZE];
    char fields[] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    int intValues[] = {0, 0, 0, 0, 0, 0}; 

    char str1[MAX_NAME_LENGTH];
    char str2[MAX_NAME_LENGTH];
    char* strValues[2];
    strValues[0] = str1;
    strValues[1] = str2;

    scanf("%s", fileName);
    scanf("%d", &qtdCampos);

    getSearchCriteria(qtdCampos, fields, intValues, strValues);

    FILE* inFile = fopen(fileName, "rb");
    printMatchingBin(inFile, fields, intValues, strValues);
    fclose(inFile);

    return;
}


int main(int argc, char *argv[]) {
    int funcionalidade; //Irá registrar a funcionalidade escolhida pelo usuário

    scanf("%d", &funcionalidade);

    switch (funcionalidade)
    {
    //Leitura de um csv e escrita no binário
    //Ao finalizar roda a função binarioNaTela()
    case 1:
        funcionalidade1();
        break;
    
    //Imprime todos os dados de um arquivo binário
    case 2:
        funcionalidade2();
        break;

    //Imprime todos os registros que atendem a um critério
    case 3:
        funcionalidade3();
        break;

    default:
        break;
    }
}
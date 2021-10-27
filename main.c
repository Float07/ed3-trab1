#include <stdio.h>
#include <stdlib.h>
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
        FILE* binOutput = fopen(outputFileName, "wb+");

        readCSV(csvInput, binOutput);

        fclose(csvInput);
        fclose(binOutput);
        
        binarioNaTela(outputFileName);

        return;
}

void funcionalidade2() {
        char inputFileName[MAX_FILENAME_SIZE];
        int imprimiu=0;
        scanf("%s", inputFileName);

        FILE* inFile = fopen(inputFileName, "rb");
        imprimiu = printBin(inFile);
        if(imprimiu==0){
            printf("Registro inexistente.");
        }
        fclose(inFile);

        return;
}

//Lê input do usuário para conseguir os critérios de busca ou campos a serem atualizados
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
void getSearchCriteria(int qtdCampos, char* fields, int* intValues, char** strValues) {

    //Recebe quais campos serão analisados e quais os valores desejados
    for (int i = 0; i < qtdCampos; i++)
    {
        char nomeCampo[64];
        scanf("%s", nomeCampo);

        if(!strcmp(nomeCampo, "codEstacao")){
            fields[0] = 1;
            scanf("%d", &(intValues[0]));
        }else if(!strcmp(nomeCampo, "codLinha")){
            fields[1] = 1;
            scanf("%d", &(intValues[1]));
        }else if(!strcmp(nomeCampo, "codProxEstacao")){
            fields[2] = 1;
            scanf("%d", &(intValues[2]));
        }else if(!strcmp(nomeCampo, "distProxEstacao")){
            fields[3] = 1;
            scanf("%d",&(intValues[3]));
        }else if(!strcmp(nomeCampo, "codLinhaIntegra")){
            fields[4] = 1;
            scanf("%d", &(intValues[4]));
        }else if(!strcmp(nomeCampo, "codEstIntegra")){
            fields[5] = 1;
            scanf("%d", &(intValues[5]));
        }else if(!strcmp(nomeCampo, "nomeEstacao")){
            fields[6] = 1;
            scan_quote_string(strValues[0]);
        }else if(!strcmp(nomeCampo, "nomeLinha")){
            fields[7] = 1;
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
    if (inFile == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return;
    }
    
    printMatchingBin(inFile, fields, intValues, strValues);
    fclose(inFile);

    return;
}

void funcionalidade4() {
    //Veja a documentação de getSearchCriteria para melhor entender o significado de fields, intValues e strValues
    int qtdRemocoes;
    char fileName[MAX_FILENAME_SIZE];
    char fields[] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    int intValues[] = {0, 0, 0, 0, 0, 0}; 

    char str1[MAX_NAME_LENGTH];
    char str2[MAX_NAME_LENGTH];
    char* strValues[2];
    strValues[0] = str1;
    strValues[1] = str2;

    scanf("%s", fileName);
    scanf("%d", &qtdRemocoes);

    for (int i = 0; i < qtdRemocoes; i++)
    {
        int qtdCampos;
        scanf("%d", &qtdCampos);

        getSearchCriteria(qtdCampos, fields, intValues, strValues);
        
        FILE* outFile = fopen(fileName, "rb+");
        deleteMatchingBin(outFile, fields, intValues, strValues);
        fclose(outFile);
    }

    binarioNaTela(fileName);
    
    return;
}

void funcionalidade5() {
    //Register reg;
    char fileName[FILENAME_MAX];
    scanf("%s", fileName);
    FILE* outFile = fopen(fileName, "rb+");
    
    int qtdeInsercoes;
    scanf("%d", &qtdeInsercoes);

    for (int i = 0; i < qtdeInsercoes; i++)
    {
        RegisterStr regStr;

        scanf("%s", regStr.codEstacao);
        if(!strcmp(regStr.codEstacao, "NULO"))
            strcpy(regStr.codEstacao, "");

        scan_quote_string(regStr.nomeEstacao);

        scanf("%s", regStr.codLinha);
        if(!strcmp(regStr.codLinha, "NULO"))
            strcpy(regStr.codLinha, "");
        
        scan_quote_string(regStr.nomeLinha);

        scanf("%s", regStr.codProxEstacao);
        if(!strcmp(regStr.codProxEstacao, "NULO"))
            strcpy(regStr.codProxEstacao, "");

        scanf("%s", regStr.distProxEstacao);
        if(!strcmp(regStr.distProxEstacao, "NULO"))
            strcpy(regStr.distProxEstacao, "");

        scanf("%s", regStr.codLinhaIntegra);
        if(!strcmp(regStr.codLinhaIntegra, "NULO"))
            strcpy(regStr.codLinhaIntegra, "");
        
        scanf("%s", regStr.codEstIntegra);
        if(!strcmp(regStr.codEstIntegra, "NULO"))
            strcpy(regStr.codEstIntegra, "");
        
        Register reg = registerStrToRegister(regStr);
        
        insertRegister(outFile, reg);
    }
    
    fclose(outFile);

    binarioNaTela(fileName);
    
    return;
}

void funcionalidade6() {
     //Veja a documentação de getSearchCriteria para melhor entender o significado de fields, intValues e strValues
    int qtdUpdates;
    char fileName[MAX_FILENAME_SIZE];

    char fields[] = {0, 0, 0, 0, 0, 0, 0, 0};
    char fieldsUpdate[] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    int intValues[] = {0, 0, 0, 0, 0, 0};
    int intValuesUpdate[] = {0, 0, 0, 0, 0, 0}; 

    char str1[MAX_NAME_LENGTH];
    char str2[MAX_NAME_LENGTH];
    char* strValues[2];
    strValues[0] = str1;
    strValues[1] = str2;
    char str1Update[MAX_NAME_LENGTH];
    char str2Update[MAX_NAME_LENGTH];
    char* strValuesUpdate[2];
    strValues[0] = str1Update;
    strValues[1] = str2Update;

    scanf("%s", fileName);
    scanf("%d", &qtdUpdates);

    //Realiza a quantidade requisitada de atualizações
    for (int i = 0; i < qtdUpdates; i++)
    {
        //Coleta os critérios de busca
        int qtdeParametrosBusca;
        scanf("%d", &qtdeParametrosBusca);
        getSearchCriteria(qtdeParametrosBusca, fields, intValues, strValues);

        //Coleta as informações sobre como o registro será atualizado
        int qtdeParametrosUpdate;
        scanf("%d", &qtdeParametrosUpdate);
        getSearchCriteria(qtdeParametrosUpdate, fieldsUpdate, intValuesUpdate, strValuesUpdate);

        //Recebe os offsets dos registros a serem atualizados
        FILE* outFile = fopen(fileName, "rb+");
        long* offsets = getAllMatchingRegistersOffset(outFile, fields, intValues, strValues);

        //Atualiza os registros nos offsets recebidos com as informações desejadas
        for (int j = 0; j < offsets[0]; j++)
        {
            updateRegisterByOffset(outFile, offsets[j+1], fieldsUpdate, intValuesUpdate, strValuesUpdate);
        }
        

        fclose(outFile);
    }
    
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
    
    case 4:
        funcionalidade4();
        break;
    
    case 5:
        funcionalidade5();

    case 6:
        funcionalidade6();
        break;

    default:
        break;
    }
}
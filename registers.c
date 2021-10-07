//Este módulo lida principalmente com funções diretamente relacionadas a registros ou arquivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 1024 //Tamanho máximo de um nomeEstacao ou nomeLinha

//Usado para representar um registro.
struct Register{
    //Campos de tamanho fixo para gerenciamento
    char removido;      //1 byte
    int tamanho;        //4 bytes
    long proxLista;     //8 bytes
    //Campos de tamanho fixo
    int codEstacao;     //4 bytes
    int codLinha;       //4 bytes
    int codProxEstacao; //4 bytes
    int distProxEstacao;//4 bytes
    int codLinhaIntegra;//4 bytes
    int codEstIntegra;  //4 bytes
    //Tamanho total dos campos fixos = 37

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

/*
* FUNÇÕES DE DEBUGGING
* Utilizadas para ajudar no desenvolvimento do código.
*/

//Imprime uma variável do tipo RegisterStr
void printRegisterStr(RegisterStr reg) {
    printf("codEstacao:%s\n", reg.codEstacao);
    printf("codLinha:%s\n", reg.codLinha);
    printf("codProxEstacao:%s\n", reg.codProxEstacao);
    printf("distProxEstacao:%s\n", reg.distProxEstacao);
    printf("codLinhaIntegra:%s\n", reg.codLinhaIntegra);
    printf("codEstIntegra:%s\n", reg.codEstIntegra);
    printf("nomeEstacao:%s\n", reg.nomeEstacao);
    printf("nomeLinha:%s\n", reg.nomeLinha);
    return;
}



/*
* FUNÇÕES INTERNAS
* Utilizadas somente em "aux.c"
*/

//Transforma dado do tipo RegisterStr no tipo Register
Register registerStrToRegister(RegisterStr registerStr) {
    Register reg;

    reg.removido = 0;
    reg.tamanho = 37; //Tamanho inicial, desconsiderando os campos de tamanho variável
    reg.proxLista = -1;


    //Transforma strings de registerStr em inteiros para reg
    //Caso os valores que podem ser nulos sejam strings vazias, o inteiro salvo é -1
    reg.codEstacao = atoi(registerStr.codEstacao);

    if(strlen(registerStr.codLinha))
        reg.codLinha = atoi(registerStr.codLinha);
    else
        reg.codLinha = -1;

    if(strlen(registerStr.codProxEstacao))
        reg.codProxEstacao = atoi(registerStr.codProxEstacao);
    else
        reg.codProxEstacao = -1;

    if(strlen(registerStr.distProxEstacao))
        reg.distProxEstacao = atoi(registerStr.distProxEstacao);
    else
        reg.distProxEstacao = -1;

    if(strlen(registerStr.codLinhaIntegra))
        reg.codLinhaIntegra = atoi(registerStr.codLinhaIntegra);
    else
        reg.codLinhaIntegra = -1;

    if(strlen(registerStr.codEstIntegra))
        reg.codEstIntegra = atoi(registerStr.codEstIntegra);
    else
        reg.codEstIntegra = -1;

    //Copia strings dos campos de tamanho variável
    strcpy(reg.nomeEstacao, registerStr.nomeEstacao);
    strcpy(reg.nomeLinha, registerStr.nomeLinha);

    return reg;
}

//Transforma uma linha do .csv para um tipo RegisterStr
Register stringToRegister(char* registerStr) {
    RegisterStr recoveredRegister;
    int i, j;

    //Cada bloco de código a seguir recupera um campo do registro
    for (i = 0; registerStr[i] != ','; i++)
    {
        recoveredRegister.codEstacao[i] = registerStr[i];
    }
    recoveredRegister.codEstacao[i] = '\0';
    
    j = i + 1;
    for (i = 0; registerStr[j+i] != ','; i++)
    {
        recoveredRegister.nomeEstacao[i] = registerStr[j+i];
    }
    recoveredRegister.nomeEstacao[i] = '\0';

    j += i + 1;
    for (i = 0; registerStr[j+i] != ','; i++)
    {
        recoveredRegister.codLinha[i] = registerStr[j+i];
    }
    recoveredRegister.codLinha[i] = '\0';

    j += i + 1;
    for (i = 0; registerStr[j+i] != ','; i++)
    {
        recoveredRegister.nomeLinha[i] = registerStr[j+i];
    }
    recoveredRegister.nomeLinha[i] = '\0';

    j += i + 1;
    for (i = 0; registerStr[j+i] != ','; i++)
    {
        recoveredRegister.codProxEstacao[i] = registerStr[j+i];
    }
    recoveredRegister.codProxEstacao[i] = '\0';

    j += i + 1;
    for (i = 0; registerStr[j+i] != ','; i++)
    {
        recoveredRegister.distProxEstacao[i] = registerStr[j+i];
    }
    recoveredRegister.distProxEstacao[i] = '\0';

    j += i + 1;
    for (i = 0; registerStr[j+i] != ','; i++)
    {
        recoveredRegister.codLinhaIntegra[i] = registerStr[j+i];
    }
    recoveredRegister.codLinhaIntegra[i] = '\0';

    j += i + 1;
    for (i = 0; registerStr[j+i] != '\n' && registerStr[j+i] != '\0'; i++)
    {
        recoveredRegister.codEstIntegra[i] = registerStr[j+i];
    }
    recoveredRegister.codEstIntegra[i] = '\0';

    Register reg = registerStrToRegister(recoveredRegister);

    return reg;
}

//Imprime os valores de um dado do tipo Register
void printRegister(Register reg) {
    int codEstacao = reg.codEstacao;

    char nomeEstacao[MAX_NAME_LENGTH];
    strcpy(nomeEstacao, reg.nomeEstacao);

    char codLinha[32];
    sprintf(codLinha, "%d", reg.codLinha);
    if(!strcmp(codLinha, "-1"))
        strcpy(codLinha, "NULO");

    char nomeLinha[MAX_NAME_LENGTH];
    strcpy(nomeLinha, reg.nomeLinha);
    if(!strlen(nomeLinha))
        strcpy(nomeLinha, "NULO");

    char codProxEstacao[32];
    sprintf(codProxEstacao, "%d", reg.codProxEstacao);
    if(!strcmp(codProxEstacao, "-1"))
        strcpy(codProxEstacao, "NULO");
    
    char distProxEstacao[32];
    sprintf(distProxEstacao, "%d", reg.distProxEstacao);
    if(!strcmp(distProxEstacao, "-1"))
        strcpy(distProxEstacao, "NULO");

    char codLinhaIntegra[32];
    sprintf(codLinhaIntegra, "%d", reg.codLinhaIntegra);
    if(!strcmp(codLinhaIntegra, "-1"))
        strcpy(codLinhaIntegra, "NULO");

    char codEstIntegra[32];
    sprintf(codEstIntegra, "%d", reg.codEstIntegra);
    if(!strcmp(codEstIntegra, "-1"))
        strcpy(codEstIntegra, "NULO");

    printf("%d %s %s %s %s %s %s %s", codEstacao, nomeEstacao, codLinha, nomeLinha, codProxEstacao,
    distProxEstacao, codLinhaIntegra, codEstIntegra);

    return;
}

//Escreve o cabeçalho no arquivo binário
int writeHeader(FILE* outFile, FileHeader fileHeader) {
    fwrite(&(fileHeader.status), sizeof(char), 1, outFile);
    fwrite(&(fileHeader.topoLista), sizeof(long), 1, outFile);
    fwrite(&(fileHeader.nroEstacoes), sizeof(int), 1, outFile);
    fwrite(&(fileHeader.nroParesEstacao), sizeof(int), 1, outFile);

    return 0;
}


/*
* FUNÇÕES EXTERNAS
* Utilizadas fora de "aux.c"
*/

//Função responsável por ler o csv e escrever os dados no arquivo binário
void readCSV(FILE* inFile, FILE* outFile) {
    char buff[MAX_NAME_LENGTH*2];

    FileHeader fileHeader;
    fileHeader.status = 1;
    fileHeader.topoLista = -1;
    fileHeader.nroEstacoes = -1;
    fileHeader.nroParesEstacao = -1;
    writeHeader(outFile, fileHeader);

    fgets(buff, (MAX_NAME_LENGTH*2)-4, (FILE*)inFile); //Pula a primeira linha (cabeçalho)
    while(1) {
        if(fgets(buff, (MAX_NAME_LENGTH*2)-4, (FILE*)inFile) == NULL)
            break;

        Register reg = stringToRegister(buff);
        
        printRegister(reg);
        printf("\n");
    }

    return; 
}

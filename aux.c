#include <stdio.h>
#include <string.h>

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
    char nomeEstacao[1024];
    char nomeLinha[1024];
};
typedef struct RegisterStr RegisterStr;

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

//Transforma uma linha do .csv para um tipo RegisterStr
RegisterStr stringToRegisterStr(char* registerStr){
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

    return recoveredRegister;
}

/*
* FUNÇÕES EXTERNAS
* Utilizadas fora de "aux.c"
*/

//Função responsável por ler o csv e escrever os dados no arquivo binário
void readCSV(FILE* inFile) {
    char buff[2048];

    fgets(buff, 2044, (FILE*)inFile); //Pula a primeira linha (cabeçalho)
    while(1) {
        if(fgets(buff, 2044, (FILE*)inFile) == NULL)
            break;

        RegisterStr reg = stringToRegisterStr(buff);
        
        printRegisterStr(reg);
        printf("\n");
    }

    return; 
}

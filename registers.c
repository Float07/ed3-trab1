//Este módulo lida principalmente com funções diretamente relacionadas a registros ou arquivos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


//Quantidade de bytes do header no arquivo binário
#define BIN_HEADER_SIZE 17 

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
* Utilizadas somente em "registers.c"
*/

//Transforma dado do tipo RegisterStr no tipo Register
Register registerStrToRegister(RegisterStr registerStr) {
    Register reg;

    reg.removido = '0';
    reg.tamanhoRegistro = 32 + 2; //Tamanho inicial mais o tamanho dos dois pipes, desconsiderando os campos de tamanho variável
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

    //Copia strings dos campos de tamanho variável e soma no tamanho do registro
    strcpy(reg.nomeEstacao, registerStr.nomeEstacao);
    strcpy(reg.nomeLinha, registerStr.nomeLinha);
    reg.tamanhoRegistro += strlen(reg.nomeLinha) + strlen(reg.nomeEstacao);

    return reg;
}

//Transforma uma linha do .csv para um tipo Register
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
    for (i = 0; registerStr[j+i] != '\r' && registerStr[j+i] != '\n' && registerStr[j+i] != '\0'; i++)
    {
        recoveredRegister.codEstIntegra[i] = registerStr[j+i];
    }
    recoveredRegister.codEstIntegra[i] = '\0';

    Register reg = registerStrToRegister(recoveredRegister);

    return reg;
}

//Imprime os valores de um dado do tipo Register
void printRegister(Register reg) {
    if (reg.removido == '1')
        return;

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

    printf("%d %s %s %s %s %s %s %s ", codEstacao, nomeEstacao, codLinha, nomeLinha, codProxEstacao,
    distProxEstacao, codLinhaIntegra, codEstIntegra);

    return;
}



//Escreve o cabeçalho no arquivo binário
int writeHeader(FILE* outFile, FileHeader fileHeader) {
    fseek(outFile, 0, SEEK_SET);

    fwrite(&(fileHeader.status), sizeof(char), 1, outFile);
    fwrite(&(fileHeader.topoLista), sizeof(long), 1, outFile);
    fwrite(&(fileHeader.nroEstacoes), sizeof(int), 1, outFile);
    fwrite(&(fileHeader.nroParesEstacao), sizeof(int), 1, outFile);

    return 0;
}

//Muda o status do arquivo binário para consistente ou inconsistente
void setConsistency(char consistency, FILE* outFile) {
    fseek(outFile, 0, SEEK_SET);
    fwrite(&consistency, sizeof(char), 1, outFile);
    return;
}

//Escreve um registro no arquivo binário
int writeRegister(FILE* outFile, Register reg) {
    //Escreve campos de tamanho fixo
    fwrite(&(reg.removido), sizeof(char), 1, outFile);
    fwrite(&(reg.tamanhoRegistro), sizeof(int), 1, outFile);
    fwrite(&(reg.proxLista), sizeof(long), 1, outFile);
    fwrite(&(reg.codEstacao), sizeof(int), 1, outFile);
    fwrite(&(reg.codLinha), sizeof(int), 1, outFile);
    fwrite(&(reg.codProxEstacao), sizeof(int), 1, outFile);
    fwrite(&(reg.distProxEstacao), sizeof(int), 1, outFile);
    fwrite(&(reg.codLinhaIntegra), sizeof(int), 1, outFile);
    fwrite(&(reg.codEstIntegra), sizeof(int), 1, outFile);

    //Escreve os dois campos de tamanho variável
    fwrite(reg.nomeEstacao, sizeof(char), strlen(reg.nomeEstacao), outFile);
    fwrite("|", sizeof(char), 1, outFile);

    fwrite(reg.nomeLinha, sizeof(char), strlen(reg.nomeLinha), outFile);
    fwrite("|", sizeof(char), 1, outFile);

    return 0;
}

//Lê o header do binário, retorna um FileHeader, e posiciona o cursor logo após o header
FileHeader readHeader(FILE* inFile) {
    fseek(inFile, 0, SEEK_SET);

    FileHeader fileHeader;

    fread(&(fileHeader.status), sizeof(char), 1, inFile);
    fread(&(fileHeader.topoLista), sizeof(long), 1, inFile);
    fread(&(fileHeader.nroEstacoes), sizeof(int), 1, inFile);
    fread(&(fileHeader.nroParesEstacao), sizeof(int), 1, inFile);

    return fileHeader;
}

//Lê um registro do arquivo binário e retorna um Register
//O cursor deve estar previamente posicionado no primeiro byte do registro
//No final da execução, o cursor será posicionado no primeiro byte do registro seguinte
//Caso chegue ao final do arquivo, será retornado um registro com tamanhoRegistro = 0
Register readRegister(FILE* inFile) {
    Register reg;
    char tempString[MAX_NAME_LENGTH];

    //Leitura dos campos de tamanho fixo
    if (fread(&(reg.removido), sizeof(char), 1, inFile) == 0) {
        //Retorna um registro de tamanho 0 se chegou ao final do arquivo
        reg.tamanhoRegistro = 0;
        return reg;
    }
    fread(&(reg.tamanhoRegistro), sizeof(int), 1, inFile);  
    if (reg.removido == '1') {
        //Se o registro foi removido, posiciona o cursor no final do registro removido e o retorna
       fseek(inFile, reg.tamanhoRegistro, SEEK_CUR);
       return reg; 
    }

    fread(&(reg.proxLista), sizeof(long), 1, inFile);
    fread(&(reg.codEstacao), sizeof(int), 1, inFile);
    fread(&(reg.codLinha), sizeof(int), 1, inFile);
    fread(&(reg.codProxEstacao), sizeof(int), 1, inFile);
    fread(&(reg.distProxEstacao), sizeof(int), 1, inFile);
    fread(&(reg.codLinhaIntegra), sizeof(int), 1, inFile);
    fread(&(reg.codEstIntegra), sizeof(int), 1, inFile);
    int tamanhoRestante = reg.tamanhoRegistro - 32;

    //Leitura dos dois campos de tamanho variável
    for (int i = 0; i < MAX_NAME_LENGTH; i++)
    {
        char c = getc(inFile);
        tamanhoRestante--;
        if(c == '|'){
            tempString[i] = '\0';
            break;
        }
        else{
            tempString[i] = c;
        }
    }
    strcpy(reg.nomeEstacao, tempString);
    

    for (int i = 0; i < MAX_NAME_LENGTH; i++)
    {
        char c = getc(inFile);
        tamanhoRestante--;
        if(c == '|'){
            tempString[i] = '\0';
            break;
        }
        else{
            tempString[i] = c;
        }
    }
    strcpy(reg.nomeLinha, tempString);

    //Pula o "lixo" caso exista. Caso não exista, tamanhoRestante será igual a 0
    fseek(inFile, tamanhoRestante, SEEK_CUR);

    return reg;
}

//Recebe um registro e verifica se ele atende ao critério de busca
//Retorna: um valor diferente de 0 se os campos sendo checados assumem o valor desejado, senão retorna 0
//Parâmetros:
//*reg -> registro que será checado
//Veja a documentação de "getNextMatchingRegister" para descrição dos outros parâmetros
int checkRegister(Register reg, char* fields, int* intValues, char** strValues) {
    if(reg.removido == '1')
        return 0;
    
    if(fields[0]){
        if(reg.codEstacao != intValues[0])
            return 0;
    }
    
    if(fields[1]){
        if(reg. codLinha != intValues[1])
            return 0;
    }
    if(fields[2]){
        if(reg.codProxEstacao != intValues[2])
            return 0;
    }
    if(fields[3]){
        if(reg.distProxEstacao != intValues[3])
            return 0;
    }
    
    if(fields[4]){
        if(reg.codLinhaIntegra != intValues[4])
            return 0;
    }
    
    if(fields[5]){
        if(reg.codEstIntegra != intValues[5])
            return 0;
    }
    
    if(fields[6]){
        if(strcmp(reg.nomeEstacao, strValues[0]))
            return 0;
    }
    
    if(fields[7]){
        if (strcmp(reg.nomeLinha, strValues[1]))
            return 0;
    }

    //Todas as verificações realizadas foram um sucesso!
    return 1;
}

//Retorna o próximo registro (buscando a partir do cursor do arquivo) que atende ao critério de busca
//Caso o fim do arquivo seja alcançado sem que o critério seja atendido, é retornado um registro com taramnhoRegistro = 0
//O cursor do arquivo deve estar posicionado no início de um registro 
//Caso um registro seja encontrado, o cursor será posicionado no primeiro byte do registro seguinte
//Caso não seja encontrado um registro, o cursor será posicionado no final do arquivo
//Parâmetros:
//*inFile -> Arquivo no qual será buscado um registro que atende ao critério 
//*fields -> vetor que indica quais campos serão considerados. 1 - Será considerado / 0 - Não será considerado
//  É um vetor de 8 elementos, onde cada elemento indica se os seguintes campos serão considerados, nessa ordem:
//  codEstacao, codLinha, codProxEstacao, distProxEstacao, codLinhaIntegra, codEstIntegra, nomeEstacao, nomeLinha
//*intValues -> Valores desejados para os campos do tipo inteiro
//  É um vetor de 6 inteiros, onde cada elemento indica o valor desejado para os seguintes campos, nessa ordem:
//  codEstacao, codLinha, codProxEstacao, distProxEstacao, codLinhaIntegra, codEstIntegra
//*strValues -> Valores desejados para os campos do tipo string
//  É um vetor de 2 strings, onde cada string indica o valor desejado para os seguintes campos, nessa ordem:
//  nomeEstacao, nomeLinha
//Os elementos de intValue ou strValue que indicam campos que não serão usados na busca podem assumir qualquer valor
Register getNextMatchingRegister(FILE* inFile, char* fields, int* intValues, char** strValues) {
    Register reg;
    
    while ((reg = readRegister(inFile)).tamanhoRegistro 
            && !checkRegister(reg, fields, intValues, strValues));
    
    return reg;
}

//Mesmo funcionamento de "getNextMatchingRegister", mas retorna o offset do registro, e não o registro em si
//Caso não exista registro que atenda aos requisitos, é retornado -1
//Caso um registro seja encontrado, o cursor será posicionado no primeiro byte do registro seguinte
//Caso não seja encontrado um registro, o cursor será posicionado no final do arquivo
//Parâmetros:
//*curOffset -> Offset onde o cursor do arquivo está posicionado atualmente
//*regSize -> Ponteiro para um inteiro onde será salvo o tamanho do registro encontrado (deve ser NULO caso não se deseje saber o tamanho do registro) 
//Veja a documentação de "getNextMatchingRegister" para descrição dos outros parâmetros
long getNextMatchingRegisterOffset(FILE* inFile, char* fields, int* intValues, char** strValues, long curOffset, int* regSize) {
    fseek(inFile, curOffset, SEEK_SET);
    Register reg;

    while ((reg = readRegister(inFile)).tamanhoRegistro 
            && !checkRegister(reg, fields, intValues, strValues))
    {
        //Soma 5 devido aos campos "removido" e "tamanhoRegistro", que não estão inclusos no "tamanhoRegistro"
        curOffset += reg.tamanhoRegistro + 5;
    }
    
    if(regSize) {
        *regSize = reg.tamanhoRegistro;
    }

    if(reg.tamanhoRegistro)
        return curOffset;
    else
        return -1;
}

//Retorna um vetor com todos os offsets dos registros que atendem a um critério de busca
//O primeiro elemento do vetor indica quantos offsets estão presentes no restante do vetor
//Parâmetros
//Veja a documentação de "getNextMatchingRegister" para descrição dos parâmetros
long* getAllMatchingRegistersOffset(FILE* inFile, char* fields, int* intValues, char** strValues) {
    long* offsets;
    offsets = (long*)malloc(sizeof(long) * 1);

    long offset = BIN_HEADER_SIZE;//Offset inicializa para o primeiro byte após o header
    int regSize;//Receberá o tamanho do registro recuperado por referência
    while((offset = getNextMatchingRegisterOffset(inFile, fields, intValues, strValues, offset, &regSize)) != -1){
        offsets[0]++;
        offsets = (long*)realloc(offsets, (offsets[0]+1)*sizeof(long));
        offsets[offsets[0]] = offset;
        offset += regSize + 5;
    }

    return offsets;
}

//Marca um registro como deletado, dado seu offset no arquivo binário
//Altera os campos "removido" e "proxLista" do registro
//Não altera o campo "topoLista" do cabeçalho
//Parâmetros:
//*outFile -> Arquivo no qual o registro será deletado
//*offset -> Posição do primeiro byte do registro a ser deletado
//*listHead -> Offset do topo da lista encadeada de registros removidos
void deleteRegisterByOffset(FILE* outFile, long offset, long listHead) {
    fseek(outFile, offset, SEEK_SET);

    fwrite("1", sizeof(char), 1, outFile);//Marca como removido
    fseek(outFile, 4, SEEK_CUR);//Avança para o campo "proxLista"
    fwrite(&listHead, sizeof(long), 1, outFile);//Aponta para o registro removido anteriormente

    return;
}

//Deleta todos os registros nos offsets de um dado vetor
//Atualiza os campos "removido" e "proxLista" dos registro e o campo "topoLista" do cabeçalho
//Parâmetros:
//*outFile -> Arquivo no qual serão deletados os registros
//  O arquivo deve estar aberto no modo "rb+"
//*offsets -> Vetor de offsets de registros. O primeiro elemento indica a quantidade de offsets presentes
void deleteRegistersByOffset(FILE* outFile, long* offsets) {
    FileHeader FileHeader = readHeader(outFile);
    long topoList = FileHeader.topoLista;

    int offsetsAmount = (int)offsets[0];
    for (size_t i = 0; i < offsetsAmount; i++)
    {
        deleteRegisterByOffset(outFile, offsets[i+1], topoList);
        topoList = offsets[i+1];
    }

    FileHeader.topoLista = topoList;
    writeHeader(outFile, FileHeader);
    
    return;
}

/*
* FUNÇÕES EXTERNAS
* Utilizadas fora de "aux.c"
* Essas funções estão declaradas em "header.h"
*/

//Imprime os registros de um binário que atendem ao critério de busca
//Parâmetros:
//*inFile -> Arquivo binário que terá seus valores impressos
//Veja a documentação de "getNextMatchingRegister" para descrição dos outros parâmetros
void printMatchingBin(FILE* inFile, char* fields, int* intValues, char** strValues) {
    readHeader(inFile);

    Register reg;
    while ((reg = getNextMatchingRegister(inFile, fields, intValues, strValues)).tamanhoRegistro){
        printRegister(reg);
        printf("\n");
    }
    
    return;
}

//Lê o binário e imprime as informações de todos os registros não removidos
void printBin(FILE* inFile) {
    //Avança para o primeiro byte após o header
    readHeader(inFile);

    Register reg;
    while ((reg = readRegister(inFile)).tamanhoRegistro > 0) {
        printRegister(reg);
        printf("\n");
    }
}

//Função responsável por ler o csv e escrever os dados no arquivo binário
void readCSV(FILE* inFile, FILE* outFile) {
    //Tamanho máximo do registro que será lido é MAX_NAME_LENGTH*3 por registro
    //Esse tamanho é o suficiente para qualquer registro comum e previne erros que poderiam acontecer
    //se alocação dinâmicafosse utilizada
    char buff[MAX_NAME_LENGTH*3];

    //Cria dado do tipo FileHeader, para escrita do cabeçalho
    FileHeader fileHeader;
    fileHeader.status = '0';
    fileHeader.topoLista = -1;
    fileHeader.nroEstacoes = -1;
    fileHeader.nroParesEstacao = -1;
    writeHeader(outFile, fileHeader);

    fgets(buff, (MAX_NAME_LENGTH*3)-2, (FILE*)inFile); //Pula a primeira linha (cabeçalho)
    while(1) {
        if(fgets(buff, (MAX_NAME_LENGTH*3)-2, (FILE*)inFile) == NULL)
            break;

        Register reg = stringToRegister(buff);
        
        writeRegister(outFile, reg);
    }

    setConsistency('1', outFile);

    return; 
}

//Remove todos os registros que atendem a um critério de busca
//Parâmetros:
//*outFile -> Arquivo binário de onde os registros serão removidos
//  O arquivo deve estar aberto como "rb+"
void deleteMatchingBin(FILE* outFile, char* fields, int* intValues, char** strValues) {
    long* offsets = getAllMatchingRegistersOffset(outFile, fields, intValues, strValues);
    
    for (int i = 0; i < offsets[0]; i++)
    {
        deleteRegistersByOffset(outFile, offsets);
    }
    

    free(offsets);
    return;
}

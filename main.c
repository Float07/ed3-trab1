#include <stdio.h>
#include "header.h"

int main(int argc, char *argv[]) {
    FILE* csvInput = fopen("estacoes.csv", "r");
    FILE* binOutput = fopen("binario.bin", "wb");

    readCSV(csvInput, binOutput);

    fclose(csvInput);
    fclose(binOutput);
}
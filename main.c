#include <stdio.h>
#include "header.h"

int main(int argc, char *argv[]) {
    FILE* csvInput = fopen("estacoes.csv", "r");

    readCSV(csvInput);

    fclose(csvInput);
}
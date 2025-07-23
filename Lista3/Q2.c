#include <stdio.h>
#include <stdlib.h>
#include <string.h> 







int main () {

    FILE *fp_in;
    FILE *fp_out;

    fp_in == fopen("L2Q2.in", "r");
    if(fp_in == NULL) {
        perror("Erro ao abrir o arquivo solicitado");
        return EXIT_FAILURE;
    }

    fp_out == fopen("L2Q2.out", "w");
    if(fp_out == NULL) {
        perror("Erro ao abrir o arquivo solicitado");
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    





    fclose(fp_in);
    fclose(fp_out);

    return 0;
}
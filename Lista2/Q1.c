//Dupla: Mariana Santos (20242160028) e Thais Menezes (20242160013)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LISTAS 100
#define MAX_ELEMENTOS 100
#define MAX_LINHA 3001

typedef struct {
    int numeros[MAX_ELEMENTOS];
    int qtd;
    int soma;
    int posicao;
} Lista;

int compararElementos(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compararSoma(const void *a, const void *b) {
    Lista *l1 = (Lista *)a;
    Lista *l2 = (Lista *)b;

    if (l1->soma != l2->soma)
        return l2->soma - l1->soma;

    return l2->posicao - l1->posicao;
}

void process_line(char *linha, FILE *fp_out) {
    Lista listas[MAX_LISTAS];
    int total = 0;
    int ordem = 0;

    char *token = strtok(linha, " \n");
    while (token != NULL) {
        if (strcmp(token, "start") == 0) {
            Lista nova;
            nova.qtd = 0;
            nova.soma = 0;
            nova.posicao = ordem++;

            token = strtok(NULL, " \n");
            while (token != NULL && strcmp(token, "start") != 0) {
                int num = atoi(token);
                nova.numeros[nova.qtd++] = num;
                nova.soma += num;
                token = strtok(NULL, " \n");
            }

            qsort(nova.numeros, nova.qtd, sizeof(int), compararElementos);

            listas[total++] = nova;
        } else {
            token = strtok(NULL, " \n");
        }
    }

    int manter[MAX_LISTAS] = {0};
    for (int i = total - 1; i >= 0; i--) {
        int duplicado = 0;
        for (int j = i + 1; j < total; j++) {
            if (listas[i].soma == listas[j].soma) {
                duplicado = 1;
                break;
            }
        }
        if (!duplicado) {
            manter[i] = 1;
        }
    }

    Lista finais[MAX_LISTAS];
    int total_finais = 0;
    for (int i = 0; i < total; i++) {
        if (manter[i]) {
            finais[total_finais++] = listas[i];
        }
    }

    qsort(finais, total_finais, sizeof(Lista), compararSoma);

    for (int i = 0; i < total_finais; i++) {
        if (i > 0) fprintf(fp_out, " ");
        fprintf(fp_out, "start");
        for (int j = 0; j < finais[i].qtd; j++) {
            fprintf(fp_out, " %d", finais[i].numeros[j]);
        }
    }
    fprintf(fp_out, "\n");
}

int main() {
    FILE *fp_in = fopen("L1Q1.in", "r");
    FILE *fp_out = fopen("L1Q1.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir o arquivo solicitado");
        return 1;
    }

    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), fp_in)) {
        size_t len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n') {
            linha[len - 1] = '\0';
        }

        process_line(linha, fp_out);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
//Dupla: Mariana Santos (20242160028) e Thais Menezes (20242160013)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 500
#define MAX_LINE_LENGTH 1024

typedef struct {
    float x, y;
    float distance;
} Ponto;

float distanciaEuclidiana(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

int comparar_pontos(const void *a, const void *b) {
    Ponto *p1 = (Ponto*)a;
    Ponto *p2 = (Ponto*)b;
    if (p1->distance < p2->distance) return -1;
    if (p1->distance > p2->distance) return 1;
    return 0;
}

void print_float(FILE *saida, float valor) {
    if (fabs(valor - (int)valor) < 0.005)
        fprintf(saida, "%d", (int)valor);
    else
        fprintf(saida, "%.2f", valor);
}

int processar_linha(char *linha, Ponto pontos[]) {
    char *ptr = linha;
    int n = 0;
    if (strncmp(ptr, "points", 6) == 0) ptr += 6;
    while (*ptr && n < MAX_POINTS) {
        if (*ptr == '(') {
            ptr++;
            float x, y;
            if (sscanf(ptr, "%f,%f", &x, &y) == 2) {
                pontos[n].x = x;
                pontos[n].y = y;
                pontos[n].distance = distanciaEuclidiana(pontos[n]);
                n++;
                while (*ptr && *ptr != ')') ptr++;
                if (*ptr == ')') ptr++;
            }
        } else {
            ptr++;
        }
    }
    return n;
}

int main() {
    FILE *entrada = fopen("L0Q1.in", "r");
    FILE *saida   = fopen("L0Q1.out", "w");
    if (!entrada || !saida) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, sizeof(linha), entrada)) {
        linha[strcspn(linha, "\n")] = '\0';
        Ponto pontos[MAX_POINTS], original[MAX_POINTS];
        int n = processar_linha(linha, pontos);

        for (int i = 0; i < n; i++)
            original[i] = pontos[i];

        qsort(pontos, n, sizeof(Ponto), comparar_pontos);

        for (int i = 0; i < n; i++) {
            if (i > 0) fprintf(saida, " ");
            fprintf(saida, "(");
            print_float(saida, pontos[i].x);
            fprintf(saida, ",");
            print_float(saida, pontos[i].y);
            fprintf(saida, ")");
        }

        float total = 0;
        for (int i = 1; i < n; i++) {
            float dx = original[i].x - original[i-1].x;
            float dy = original[i].y - original[i-1].y;
            total += sqrt(dx*dx + dy*dy);
        }
        float atalho = 0;
        if (n > 1) {
            float dx = original[n-1].x - original[0].x;
            float dy = original[n-1].y - original[0].y;
            atalho = sqrt(dx*dx + dy*dy);
        }

        fprintf(saida, " distance ");
        print_float(saida, total);
        fprintf(saida, " shortcut ");
        print_float(saida, atalho);
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}
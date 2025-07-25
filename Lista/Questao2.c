//Dupla: Mariana Santos (20242160028) e Thais Menezes (20242160013)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define LINHA_MAX 1024
#define TOKEN_MAX 255

typedef struct {
    double x;
    double y;
    double distancia;
    char txt_original[255];
} Pontos;

int str_ponto(const char *str, double *x, double *y, char *txt_original) {
    char temp[64];
    char *virgula, *end1, *end2;
    size_t len = strlen(str);

    if (len < 3 || str[0] != '(' || str[len-1] != ')') return 0;

    strncpy(temp, str+1, len-2);
    temp[len-2] = '\0';

    virgula = strchr(temp, ',');
    if (!virgula) return 0;

    *virgula = '\0';
    *x = strtod(temp, &end1);
    *y = strtod(virgula+1, &end2);

    if (*end1 != '\0' || *end2 != '\0') return 0;

    strncpy(txt_original, str, 254);
    txt_original[254] = '\0';
    return 1;
}

int str_inteiro(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (!*str) return 0;
    
    char *end;
    strtol(str, &end, 10);
    return *end == '\0';
}

int str_float(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (!*str) return 0;
    
    char *end;
    strtod(str, &end);
    if (*end != '\0') return 0;
    
    // Deve ter exatamente um ponto decimal
    const char *p = strchr(str, '.');
    return p != NULL && strchr(p+1, '.') == NULL;
}

int comparar_pontos(const void *a, const void *b) {
    double d1 = ((Pontos *)a)->distancia;
    double d2 = ((Pontos *)b)->distancia;
    return (d1 > d2) - (d1 < d2);
}

int comparar_inteiros(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int comparar_double(const void *a, const void *b) {
    double diff = *(double *)a - *(double *)b;
    return (diff > 0) - (diff < 0);
}

int comparar_string(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    FILE *fp_in = fopen("L0Q2.in", "r");
    FILE *fp_out = fopen("L0Q2.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir arquivos");
        if (fp_in) fclose(fp_in);
        if (fp_out) fclose(fp_out);
        return 1;
    }

    char linha[LINHA_MAX];
    
    while (fgets(linha, sizeof(linha), fp_in)) {
        linha[strcspn(linha, "\n")] = '\0';
        
        char *tokens[TOKEN_MAX];
        int qtde_tokens = 0;
        
        char *token = strtok(linha, " ");
        while (token && qtde_tokens < TOKEN_MAX) {
            tokens[qtde_tokens++] = token;
            token = strtok(NULL, " ");
        }

        char *strings[TOKEN_MAX];
        int ints[TOKEN_MAX];
        double floats[TOKEN_MAX];
        Pontos points[TOKEN_MAX];
        int num_string = 0, num_inteiro = 0, num_float = 0, num_pontos = 0;

        for (int i = 0; i < qtde_tokens; i++) {
            double x, y;
            char original[255];
            
            if (str_ponto(tokens[i], &x, &y, original)) {
                points[num_pontos].x = x;
                points[num_pontos].y = y;
                points[num_pontos].distancia = sqrt(x*x + y*y);
                strcpy(points[num_pontos].txt_original, original);
                num_pontos++;
            }
            else if (str_inteiro(tokens[i])) {
                ints[num_inteiro++] = atoi(tokens[i]);
            }
            else if (str_float(tokens[i])) {
                floats[num_float++] = atof(tokens[i]);
            }
            else {
                strings[num_string++] = tokens[i];
            }
        }

        // Ordenação
        qsort(strings, num_string, sizeof(char *), comparar_string);
        qsort(ints, num_inteiro, sizeof(int), comparar_inteiros);
        qsort(floats, num_float, sizeof(double), comparar_double);
        qsort(points, num_pontos, sizeof(Pontos), comparar_pontos);

        // Saída
        fprintf(fp_out, "str:");
        for (int i = 0; i < num_string; i++) {
            fprintf(fp_out, "%s%s", (i > 0 ? " " : ""), strings[i]);
        }

        fprintf(fp_out, " int:");
        for (int i = 0; i < num_inteiro; i++) {
            fprintf(fp_out, "%s%d", (i > 0 ? " " : ""), ints[i]);
        }

        fprintf(fp_out, " float:");
        for (int i = 0; i < num_float; i++) {
            fprintf(fp_out, "%s%.15g", (i > 0 ? " " : ""), floats[i]);
        }

        fprintf(fp_out, " p:");
        for (int i = 0; i < num_pontos; i++) {
            fprintf(fp_out, "%s%s", (i > 0 ? " " : ""), points[i].txt_original);
        }

        fprintf(fp_out, "\n");
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
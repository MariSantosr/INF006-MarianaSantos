//Dupla: Mariana Santos (20242160028) e Thais Menezes (20242160013)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define LINE_MAX 1024
#define TOKEN_MAX 255

typedef struct {
  double x;
  double y;
  double distancia;
  char txt_original[255];
} Pontos;

//Função para identificar Pontos
int ponto (const char *str, double *x, double *y, char *txt_original){
    char temp[64];
    char *virgula, *xstr, *ystr, *end1, *end2;
    size_t len = strlen(str);

    if (str[0] != '(' || str[len - 1] != ')') return 0;

    strncpy(temp, str + 1, len - 2);  
    temp[len - 2] = '\0';  

    virgula = strchr(temp, ',');
    if (!virgula) return 0;

    *virgula = '\0';  
    xstr = temp;
    ystr = virgula + 1;

    *x = strtod(xstr, &end1);
    *y = strtod(ystr, &end2);

    if (*end1 != '\0' || *end2 != '\0') return 0;  

    strcpy(txt_original, str);  
    return 1;
}

//Função para identificar Int
//Função para identificar Float
//Função para identificar String 


int main (){

  FILE *fp_in = fopen("L0Q2.in", "r");
  FILE *fp_out = fopen("L0Q2.out", "w");

  if (!fp_in || !fp_out) {
      perror("Erro ao abrir o arquivo solicitado");
      return 1;
  } 



  
fclose(fp_in);
fclose(fp_out);

  return 0;

}//fim do main
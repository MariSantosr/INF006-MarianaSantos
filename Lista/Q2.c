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
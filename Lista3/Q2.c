//Dupla: Mariana Santos (20242160028) e Thais Menezes (20242160013)

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct No {
    struct No *esq;
    struct No *dir;
    int valor;
} No;


No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        perror("Erro na alocação de memória do Nó");
        exit(EXIT_FAILURE);
    }
    novoNo->valor = valor;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

No* inserir(int valor, No* raiz) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    if (valor == raiz->valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    }
    else { 
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz; 
}

int subArvoreSoma(No* no) {
    if (no == NULL) {
        return 0; 
    }
    return no->valor + subArvoreSoma(no->esq) + subArvoreSoma(no->dir);
}

void percorrerPreOrdemEImprimir(No* raiz, FILE* fp_out) {
    if (raiz == NULL) {
        return;
    }

    int somaDireita = subArvoreSoma(raiz->dir);
    int somaEsquerda = subArvoreSoma(raiz->esq);
    int somaDiferença = somaDireita - somaEsquerda;

    fprintf(fp_out, "%d (%d) ", raiz->valor, somaDiferença);

    percorrerPreOrdemEImprimir(raiz->esq, fp_out);

    percorrerPreOrdemEImprimir(raiz->dir, fp_out);
}

void excluirArvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    excluirArvore(raiz->esq);  
    excluirArvore(raiz->dir); 
    free(raiz);  
    
}

int main () {

    FILE *fp_in;
    FILE *fp_out;
    char linha[801];

    fp_in = fopen("L2Q2.in", "r");
    if(fp_in == NULL) {
        perror("Erro ao abrir o arquivo solicitado");
        return EXIT_FAILURE;
    }

    fp_out = fopen("L2Q2.out", "w");
    if(fp_out == NULL) {
        perror("Erro ao abrir o arquivo solicitado");
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    while (fgets(linha, sizeof(linha), fp_in) != NULL) {
        No* raiz = NULL;
        
        char *ptr = linha;
        int valor;        
        int qtdeCaractereLido;

        while (sscanf(ptr, "%d%n", &valor, &qtdeCaractereLido) == 1) {
            raiz = inserir(raiz, valor);
            ptr += qtdeCaractereLido;
            
            while (*ptr == ' ' || *ptr == '\t') {
                ptr++;
            }
        }
        
        percorrerPreOrdemEImprimir(raiz, fp_out);
        fprintf(fp_out, "\n");

        excluirArvore(raiz);
    }

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}
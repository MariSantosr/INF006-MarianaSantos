//Dupla: Mariana Santos (20242160028) e Thais Menezes (20242160013)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct No {
    struct No *esq;
    struct No *dir;
    int valor;
} No;

typedef struct {
    int valor;
    int profundidade;
} infoNo;

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

No* inserir(No* raiz, int valor) {
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

No* encontrarNoMenor(No* no) {
    while (no != NULL && no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

No* removerNo(No* raiz, int valor) {
    if (raiz == NULL) {
        return inserir(raiz, valor);
    }

    if (valor < raiz->valor) {
        raiz->esq = removerNo(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = removerNo(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL) {
            No* temporario = raiz->dir;
            free(raiz);
            return temporario;
        } else if (raiz->dir == NULL) {
            No* temporario = raiz->esq;
            free(raiz);
            return temporario;
        }

        No* temporario = encontrarNoMenor(raiz->dir);

        raiz->valor = temporario->valor;

        raiz->dir = removerNo(raiz->dir, temporario->valor);
    }

    return raiz;

}

void coletarInfoNo(No* raiz, int profundidadeAtual, infoNo** lista, int* contador, int* capacidade) {
    if (raiz == NULL) {
        return;
    }

    coletarInfoNo(raiz->esq, profundidadeAtual + 1, lista, contador, capacidade);

    if (*contador >= *capacidade) {
        *capacidade *= 2;
        *lista = (infoNo*)realloc(*lista, *capacidade * sizeof(infoNo));
        if (*lista == NULL) {
            perror("Erro na alocação de memória da lista de Nós");
            exit(EXIT_FAILURE);
        }
    }

    (*lista)[*contador].valor = raiz->valor;
    (*lista)[*contador].profundidade = profundidadeAtual;
    (*contador)++;

    coletarInfoNo(raiz->dir, profundidadeAtual + 1, lista, contador, capacidade);
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

    fp_in = fopen("L2Q3.in", "r");
    if(fp_in == NULL) {
        perror("Erro ao abrir o arquivo solicitado");
        return EXIT_FAILURE;
    }

    fp_out = fopen("L2Q3.out", "w");
    if(fp_out == NULL) {
        perror("Erro ao abrir o arquivo solicitado");
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    while (fgets(linha, sizeof(linha), fp_in) != NULL) {
        No* raiz = NULL;

        char *ptr_AtualCaractere = linha;
        int valor;
        char tipoOperacao;
        int qtdeCaracterLido;

        while (*ptr_AtualCaractere != '\0') {
            while (*ptr_AtualCaractere == ' ' || *ptr_AtualCaractere == '\t' || *ptr_AtualCaractere == '\n') {
                ptr_AtualCaractere++;
            }
            if (*ptr_AtualCaractere == '\0') break;

            tipoOperacao = 'a';
            if (*ptr_AtualCaractere == 'a' || *ptr_AtualCaractere == 'r') {
                tipoOperacao = *ptr_AtualCaractere;
                ptr_AtualCaractere++;
                while (*ptr_AtualCaractere == ' ' || *ptr_AtualCaractere == '\t') {
                    ptr_AtualCaractere++;
                }
            }

            if (sscanf(ptr_AtualCaractere, "%d%n", &valor, &qtdeCaracterLido) == 1) {
                if (tipoOperacao == 'a') {
                    raiz = inserir(raiz, valor);
                } else if (tipoOperacao == 'r') {
                    raiz = removerNo(raiz, valor);
                }
                ptr_AtualCaractere += qtdeCaracterLido;
            } else {
                ptr_AtualCaractere++;
            }
        }

        infoNo* listaNos = NULL;

        int qtdeNos = 0;
        int capacidadeNos = 10;
        listaNos = (infoNo*)malloc(capacidadeNos * sizeof(infoNo));

        if (listaNos == NULL) {
            perror("Erro ao alocar memória inicial para a lista de nós.");
            fclose(fp_in);
            fclose(fp_out);
            excluirArvore(raiz);
            return EXIT_FAILURE;
        }

        coletarInfoNo(raiz, 0, &listaNos, &qtdeNos, &capacidadeNos);

        int i;

        for (i = 0; i < qtdeNos; i++) {
            fprintf(fp_out, "%d (%d)%s", listaNos[i].valor, listaNos[i].profundidade,
                    (i == qtdeNos - 1) ? "" : " ");
        }
        fprintf(fp_out, "\n");

        free(listaNos);
        listaNos = NULL;

        excluirArvore(raiz);
    }

    fclose(fp_in);
    fclose(fp_out);

    return 0;

}
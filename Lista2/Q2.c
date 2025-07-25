//Dupla: Mariana Santos (20242160028) e Thais Menezes (20242160013)

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define LINHA_MAX 3001 
#define TAM_NOMES_MAX 100 
#define PILHAS_NOMES_MAX 100 
#define TAM_BUFFER_SAIDA_MAX (PILHAS_NOMES_MAX * (TAM_NOMES_MAX + 6 + 1) + PILHAS_NOMES_MAX * 10)

typedef struct {
    char nomes[PILHAS_NOMES_MAX][TAM_NOMES_MAX];
    int topoPilha;
}Pilha;

void inicializar_pilha(Pilha *p) {
    p->topoPilha = -1;
}

int retornar_pilhaVazia(Pilha *p) {
    return (p->topoPilha == -1);
}

int retornar_pilhaCheia(Pilha *p) {
    return (p->topoPilha == PILHAS_NOMES_MAX - 1);
}

void push_novoNomeTopoPilha(Pilha *p, const char *nome) {
    if (retornar_pilhaCheia(p)) return;
    p->topoPilha++;
    strcpy(p->nomes[p->topoPilha], nome);
}

char* pop_removerNomeTopoPilha(Pilha *p) {
    if (retornar_pilhaVazia(p)) return NULL;
    return p->nomes[p->topoPilha--];
}

void adicionar_operacaoBufferSaida(char *buffer, const char *op, int *primeira_op_ptr) {
    if (!(*primeira_op_ptr)) {
        strcat(buffer, " ");
    }
    strcat(buffer, op);
    *primeira_op_ptr = 0;
}

void processar_linha(char *linha, FILE *fp_out) {
    Pilha p;
    inicializar_pilha(&p);

    char temp_nomes_pop[PILHAS_NOMES_MAX][TAM_NOMES_MAX]; 
    int temp_contador_pop;

    char saida_buffer[TAM_BUFFER_SAIDA_MAX];
    saida_buffer[0] = '\0';

     int primeira_op = 1;

    char *token = strtok(linha, " ");
    while (token != NULL) {
        char novo_nome[TAM_NOMES_MAX];
        strcpy(novo_nome, token);

        temp_contador_pop = 0;

        while (!retornar_pilhaVazia(&p) && strcmp(p.nomes[p.topoPilha], novo_nome) > 0) {
            strcpy(temp_nomes_pop[temp_contador_pop], pop_removerNomeTopoPilha(&p));
            temp_contador_pop++;
        }

        if (temp_contador_pop > 0) {
            char pop_op_str[20];
            sprintf(pop_op_str, "%dx-pop", temp_contador_pop);
            adicionar_operacaoBufferSaida(saida_buffer, pop_op_str, &primeira_op);
        }

        push_novoNomeTopoPilha(&p, novo_nome);
        char push_op_str[TAM_NOMES_MAX + 6];
        sprintf(push_op_str, "push-%s", novo_nome);
        adicionar_operacaoBufferSaida(saida_buffer, push_op_str, &primeira_op);

        for (int i = temp_contador_pop - 1; i >= 0; i--) {
            push_novoNomeTopoPilha(&p, temp_nomes_pop[i]);
            sprintf(push_op_str, "push-%s", temp_nomes_pop[i]);
            adicionar_operacaoBufferSaida(saida_buffer, push_op_str, &primeira_op);
        }
    
        token = strtok(NULL, " "); 
    }

    fprintf(fp_out, "%s\n", saida_buffer);
}


int main () {

    FILE *fp_in = fopen("L1Q2.in", "r");
    FILE *fp_out = fopen("L1Q2.out", "w");

    if (!fp_in || !fp_out) {
        perror("Erro ao abrir o arquivo solicitado");
        return 1;
    }

    char linha[LINHA_MAX]; 

    while (fgets(linha, sizeof(linha), fp_in)) {
        size_t linhaTamanho = strlen(linha);
        if (linhaTamanho > 0 && linha[linhaTamanho - 1] == '\n') {
            linha[linhaTamanho - 1] = '\0'; 
        }

        processar_linha(linha, fp_out);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
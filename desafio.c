#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct node {
    int dados;
    struct node* prox;
};

typedef struct node node;

void firstFit(node** pont_cabeca, int tamProcesso[], int n);
void bestFit(node** pont_cabeca, int tamProcesso[], int n);
int gerarLista(node** pont_cabeca);
void mostrarLista(node* no1);
void adicionarElemento(node** pont_cabeca, int novo_dado);

int main() {
    srand(time(NULL));

    node* cabeca = NULL;

    int num_elementos = gerarLista(&cabeca);

    mostrarLista(cabeca);

    int num = 0;

    int *tam_processos = (int *)malloc(num_elementos * sizeof(int));

    for (int i = 0; i < num_elementos; i++) {
        tam_processos[i] = rand() % 100 + 1;
    }

    do {
        puts("Escolha 1 para o First Fit\n\n2 para sair do programa");
        scanf("%d", &num);

        switch (num) {
            case 1:
                firstFit(&cabeca, tam_processos, num_elementos);
                break;
            
        }

    } while (num != 2);

    free(tam_processos);

    return 0;
}

void firstFit(node** pont_cabeca, int tamProcesso[], int n) {
    node* atual = *pont_cabeca;

    printf("\nNúmero do processo\tTamanho do processo\tNúmero do bloco\n");
    for (int i = 0; i < n; i++) {
        int tamProcessoAtual = tamProcesso[i];
        int alocado = 0;

        while (atual != NULL) {
            if (atual->dados >= tamProcessoAtual) {
                printf("%d\t\t\t%d\t\t\t\t%d\n", i + 1, tamProcessoAtual, atual->dados);
                atual->dados -= tamProcessoAtual;
                alocado = 1;
                break;
            }
            atual = atual->prox;
        }

        if (!alocado) {
            printf("%d\t\t\t%d\t\t\t\tnão foi alocado\n", i + 1, tamProcessoAtual);
        }

        atual = *pont_cabeca; 
    }
}

void bestFit(node** pont_cabeca, int tamProcesso[], int n) {
    node* atual = *pont_cabeca;

    printf("\nNúmero do processo\tTamanho do processo\tNúmero do bloco\n");
    for (int i = 0; i < n; i++) {
        int tamProcessoAtual = tamProcesso[i];
        int alocado = 0;
        node* melhorBloco = NULL;

        while (atual != NULL) {
            if (atual->dados >= tamProcessoAtual && (!melhorBloco || atual->dados < melhorBloco->dados)) {
                melhorBloco = atual;
            }
            atual = atual->prox;
        }

        if (melhorBloco != NULL) {
            printf("%d\t\t\t%d\t\t\t\t%d\n", i + 1, tamProcessoAtual, melhorBloco->dados);
            melhorBloco->dados -= tamProcessoAtual;
            alocado = 1;
        }

        if (!alocado) {
            printf("%d\t\t\t%d\t\t\t\tnão foi alocado\n", i + 1, tamProcessoAtual);
        }

        atual = *pont_cabeca; 
    }
}

void adicionarElemento(node** pont_cabeca, int novo_dado) {
    node* novo_no = (node*)malloc(sizeof(node));
    node* ultimo = *pont_cabeca;

    novo_no->dados = novo_dado;
    novo_no->prox = NULL;

    if (*pont_cabeca == NULL) {
        *pont_cabeca = novo_no;
        return;
    }
    while (ultimo->prox != NULL) {
        ultimo = ultimo->prox;
    }
    ultimo->prox = novo_no;
}

void mostrarLista(node* no1) {
    while (no1 != NULL) {
        printf("%d ->", no1->dados);
        no1 = no1->prox;
    }
    printf("NULL\n");
}

int gerarLista(node** pont_cabeca) {
    int tam_lista = rand() % 10 + 1; // Gera um número aleatório de processos (1 a 10)
    
    for (int i = 0; i < tam_lista; i++) {
        adicionarElemento(pont_cabeca, rand() % 100 + 1);
    }
    
    return tam_lista;
}

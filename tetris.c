#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca fila[TAM];
    int inicio;
    int fim;
    int qtd;
} Fila;

Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I','O','T','L'};
    p.nome = tipos[rand()%4];
    p.id = rand()%1000;
    return p;
}

void inicializar(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    for(int i=0;i<TAM;i++){
        f->fila[f->fim] = gerarPeca();
        f->fim = (f->fim + 1) % TAM;
        f->qtd++;
    }
}

int cheia(Fila *f) {
    return f->qtd == TAM;
}

int vazia(Fila *f) {
    return f->qtd == 0;
}

void enqueue(Fila *f) {
    if(cheia(f)) return;
    f->fila[f->fim] = gerarPeca();
    f->fim = (f->fim + 1) % TAM;
    f->qtd++;
}

void dequeue(Fila *f) {
    if(vazia(f)) return;
    f->inicio = (f->inicio + 1) % TAM;
    f->qtd--;
}

void exibir(Fila *f) {
    printf("\nFila de Peças:\n");
    int i = f->inicio;
    for(int c = 0; c < f->qtd; c++) {
        Peca p = f->fila[i];
        printf("[%c | %d] ", p.nome, p.id);
        i = (i + 1) % TAM;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Fila f;
    inicializar(&f);
    int op;

    while(1) {
        printf("\n=== TETRIS STACK - NIVEL NOVATO ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if(op == 1) dequeue(&f);
        else if(op == 2) {
            dequeue(&f);
            enqueue(&f);
        }
        else if(op == 3) exibir(&f);
        else if(op == 0) break;
    }

    return 0;
}
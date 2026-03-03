#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 5

// Estrutura da Peça
typedef struct {
    int id;
    char tipo; // I, O, T, L, J, S, Z
} Peca;

// Estrutura da Fila Circular
typedef struct {
    Peca itens[TAMANHO];
    int frente;
    int tras;
    int total;
} FilaTretis;

// Função para gerar uma peça aleatoria
Peca gerarPeca(){
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    Peca nova;
    nova.id = rand() % 1000 + 100; // ID entre 100 e 1099
    nova.tipo = tipos[rand() % 7];
    return nova;
}

//Inicializa a fila com 5 peças
void inicializarFila(FilaTretis *f) {
    f->frente = 0;
    f->tras = -1;
    f->total = 0;

    printf("Gerando fila inicial...\n");
    for (int i = 0; i < TAMANHO; i++) {
        f->tras = (f->tras + 1) % TAMANHO;
        f->itens[f->tras] = gerarPeca();
        f->total++;
    }
}

// Visualizar a fila
void exibirFila(FilaTretis f) {
    printf("\n--- FILA DE PECAS ATUAL ---\n");
    if (f.total == 0) {
        printf("Fila vazia!\n");
        return;
    }
    int i = f.frente;
    for (int cont = 0; cont < f.total; cont++) {
        printf("[%d] Peca: %c (ID: %d)\n", cont + 1, f.itens[i].tipo, f.itens[i].id);
        i = (i + 1) % TAMANHO;
    }
    printf("---------------------------\n"); 
}

// Jogar (Dequeue) e Inserir nova (Enqueue)
void JogarPeca(FilaTretis *f) {
    if (f->total == 0) {
        printf("ERRO: Nenhuma peca para jogar!\n");
        return;
    }

    // Remove a peça da frente
    Peca jogada = f->itens[f->frente];
    printf("\n>>> Voce jogou a peca %c (ID: %d)!\n", jogada.tipo, jogada.id);

    f->frente = (f->frente + 1) % TAMANHO;
    f->total--;

    // Insere automaticamente uma nova no final para manter 5
    f->tras = (f->tras + 1) % TAMANHO;
    f->itens[f->tras] = gerarPeca();
    f->total++;

    printf("Nova peca %c adicionada a fila de espera.\n", f->itens[f->tras].tipo);  
}

int main() {
    srand(time(NULL));
    FilaTretis fila;
    int opcao;

    inicializarFila(&fila);

    do
    {
        exibirFila(fila);
        printf("\n1. Jogar Peca\n2. Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            JogarPeca(&fila);
            break;
        case 2:
            printf("Saindo do Tetris Stack...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao !=2);
    return 0;
}


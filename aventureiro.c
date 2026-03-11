#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    int id;
    char tipo; 
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int frente, tras, total;
} FilaCircular;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} PilhaReserva;

// Função de apoio
Peca gerarPeca(){
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    Peca nova = {rand() % 900 + 100, tipos[rand() % 7]};
    return nova;
}

void inicializarFila(FilaCircular *f) {
    f->frente = 0; f->tras = -1; f->total = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->total++;
    }
}

void inicializarPilha(PilhaReserva *p) {
    p->topo = -1; // Pilha começa vazia
}

// Lógica do jogo
void exibirEsEstado(FilaCircular f, PilhaReserva p) {
    printf("\n=== STATUS DO JOGO ====\n");
    printf("FILA (proximas): ");
    int idx = f.frente;
    for (int i = 0; i < f.total; i++) {
        printf("[%c] ", f.itens[idx].tipo);
        idx = (idx + 1) % TAM_FILA;
    }

    printf("\nPILHA (Reserva): ");
    if (p.topo == -1) printf("Vazia");
    else {
        for (int i = 0; i <= p.topo; i++) printf("[%c] ", p.itens[i].tipo);
    }
    printf("\n=====================\n");
}

void JogarPeca(FilaCircular *f) {
    Peca p = f->itens[f->frente];
    printf("\n[!] Voce JOGOU a peca %c (ID: %d)\n", p.tipo, p.id);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = gerarPeca();
}

void reservarPeca(FilaCircular *f, PilhaReserva *p) {
    if (p->topo == TAM_PILHA - 1) {
        printf("\n[X] ERRO: Pilha de reserva cheia!\n");
        return;
    }
    // Push: Pega da frente da fila e coloca na pilha
    Peca paraReserva = f->itens[f->frente];
    p->topo++;
    p->itens[p->topo] = paraReserva;

    printf("\n[+] Peca %c enviada para a reserva.\n", paraReserva.tipo);

    // Repõe a fila
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = gerarPeca();
}

void usarReserva(PilhaReserva *p) {
    if (p->topo == -1) {
        printf("\n[X] ERRO: Nao ha pecas na reserva!\n");
        return;
    }
    //Pop: Tira o que entrou por último
    Peca usada = p->itens[p->topo];
    p->topo--;
    printf("\n[!] Voce USOU a peca reservada %c (ID: %d)\n", usada.tipo, usada.id);
    
}

int main() {
    srand(time(NULL));
    FilaCircular fila;
    PilhaReserva pilha;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do
    {
        exibirEsEstado(fila, pilha);
        printf("\n1- Jogar | 2-Reservar | 3-Usar Reserva |0-Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
        case 1: JogarPeca(&fila); break;
        case 2: reservarPeca(&fila, &pilha); break;
        case 3: usarReserva(&pilha); break;
        case 0: printf("Saindo...\n"); break;
        default: printf("Opcao invalida!\n");
        }
    } while (opcao !=0);
    
    return 0;
}


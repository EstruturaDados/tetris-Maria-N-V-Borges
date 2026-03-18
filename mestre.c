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

// Funções base
Peca gerarPeca(){
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    Peca nova = {rand() % 900 + 100, tipos[rand() % 7]};
    return nova;
}

void inicializar(FilaCircular *f, PilhaReserva *p) {
    f->frente = 0; f->tras = -1; f->total = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca();
        f->total++;
    }
    p->topo = -1;
}

void exibir(FilaCircular f, PilhaReserva p) {
    printf("\n=== STATUS DO JOGO ====\n");
    printf("\n[FILA]: ");
    int idx = f.frente;
    for (int i = 0; i < f.total; i++) {
        printf("%c ", f.itens[idx].tipo);
        idx = (idx + 1) % TAM_FILA;
    }

    printf(" | [PILHA]: ");
    if (p.topo == -1) printf("Vazia");
    for (int i = 0; i <= p.topo; i++) printf("%c ", p.itens[i].tipo);
    printf("\n");
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

// Funcionalidades Mestre

void trocarPecas(FilaCircular *f, PilhaReserva *p) {
    if (p->topo == -1) {
        printf("\n[!] Erro: Pilha vazia para troca!\n");
        return;
    }
    Peca temp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("\n[OK] Pecas trocadas com sucesso!\n");
}

void inverterFilaPlha(FilaCircular *f, PilhaReserva *p) {
    printf("\n[!] Invertendo estruturas...\n");
    //Exemplo: Movemos o que dá da pilha para a fila e vice-versa
    //Nota: Esta é uma operação complexa que exige cuidado com os tamanhos 
    if (p->topo != -1) {
        Peca temp = f->itens[f->frente];
        f->itens[f->frente] = p->itens[p->topo];
        p->itens[p->topo] = temp;
    }
    
}

// Para o "Desfazer", precisa de uma varíavel global ou struct para salvar o estado anterior
Peca ultimaPecaJogada;
int temBackup = 0;


void JogarPeca(FilaCircular *f) {
    ultimaPecaJogada = f->itens[f->frente];
    temBackup = 1;
    printf("\n[>] JOGOU: %c\n", ultimaPecaJogada.tipo);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = gerarPeca();
}

void desfazer(FilaCircular *f) {
    if (!temBackup) {
        printf("\n[!] Nada para desfazer!\n");
        return;
    }
    // Lógica reserva da Fila Circular
    f->tras = (f->tras - 1 + TAM_FILA) % TAM_FILA;
    f->frente = (f->frente - 1 + TAM_FILA) % TAM_FILA;
    f->itens[f->frente] = ultimaPecaJogada;
    temBackup = 0;
    printf("\n[REV] Ultima jogada desfeita!\n");
    
}

int main() {
    srand(time(NULL));
    FilaCircular fila; PilhaReserva pilha;
    int op;
    inicializar(&fila, &pilha);

    do {
        exibir(fila, pilha);
        printf("\n1-Jogar | 2-Reservar | 3-Usar | 4-Trocar | 5-Desfazer | 6-Inverter | 0-Sair\nEscolha: ");
        scanf("%d", &op);
        switch (op) {
        case 1: JogarPeca(&fila); break;
        case 2: /* lógica do nível anterior*/ break;
        case 3: reservarPeca(&fila, &pilha), usarReserva(&pilha); break;
        case 4: trocarPecas(&fila, &pilha); break;
        case 5: desfazer(&fila); break;
        case 6: inverterFilaPlha(&fila, &pilha); break;
        }
    } while (op !=0);
    return 0;
}


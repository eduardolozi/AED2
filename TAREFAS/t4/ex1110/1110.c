#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int num;
} Item;

typedef struct No {
    Item item;
    struct No *prox;
} No;

typedef struct Lista {
    No *primeiro;
    No *ultimo;
    int tam;
} Lista;

void criaLista(Lista *lista);

void insereNum(int numero, Lista *lista);

void printLista(Lista lista);

void jogo(Lista *lista);

int main() {
    Lista lista;
    int qtd;

    do {
        criaLista(&lista);
        scanf("%d", &qtd);
        if(qtd != 0) {
            insereNum(qtd, &lista);
            printLista(lista);
            jogo(&lista);
        }
    } while(qtd != 0);
    
    return 0;
}

void criaLista(Lista *lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tam = 0;
    return;
}

void insereNum(int numero, Lista *lista) {
    int i = 0;
    for(i=0;i<numero;i++) {
        No *novo = (No*)malloc(sizeof(No));
        novo->item.num = i+1;

        if(lista->primeiro == NULL) {
            lista->primeiro = novo;
            lista->ultimo = novo;
            novo->prox = NULL;
        } else {
            lista->ultimo->prox = novo;
            lista->ultimo = novo;
            novo->prox = NULL;
        }
        lista->tam++;
    }
    return;
}

void printLista(Lista lista) {
    No* aux = (No*)malloc(sizeof(No));
    aux = lista.primeiro;
    while(aux != NULL) {
        printf("%d\n", aux->item.num);
        aux = aux->prox;
    }
}

void jogo(Lista *lista) { 
    int i = 0;
    while(lista->tam > 1) {
        if(i == 0) {
            printf("Discarded cards: ");
            i++;
        }
        No *aux = (No*)malloc(sizeof(No));
        aux = lista->primeiro;
        lista->ultimo->prox = lista->primeiro->prox;
        lista->ultimo = lista->primeiro->prox;
        lista->primeiro = lista->primeiro->prox->prox;
        
        if(lista->tam > 2) {
            printf("%d, ", aux->item.num);
        }
        else printf("%d\n", aux->item.num);
        free(aux);
        lista->tam--;
    }
    printf("Remaining card: %d\n", lista->primeiro->item.num);
    free(lista->primeiro);
    return;
}

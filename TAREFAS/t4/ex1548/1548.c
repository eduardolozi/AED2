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

int ordenaLista(Lista *lista);

void freeLista(Lista *lista);

int main() {
    Lista lista;
    int qtd, nota, i, numero, j;
    int *res;
    scanf("%d", &qtd);
    res = (int*)malloc(qtd*sizeof(int));

    for(i=0;i<qtd;i++) {
        criaLista(&lista);
        scanf("%d", &numero);
        for(j=0;j<numero;j++) {
            scanf("%d", &nota);
            insereNum(nota, &lista);
        }
        res[i] = ordenaLista(&lista);
        freeLista(&lista);
    }

    for(i=0;i<qtd;i++) {
        printf("%d\n", res[i]);
    }

    return 0;
}

void criaLista(Lista *lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tam = 0;
    return;
}

void insereNum(int numero, Lista *lista) {
    No *novo = (No*)malloc(sizeof(No));
    novo->item.num = numero;

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
    return;
}

int ordenaLista(Lista *lista) {
    int i, j, cont, imoveis=0, ctot=0;
    No *aux = (No*)malloc(sizeof(No));
    No *temp = (No*)malloc(sizeof(No));
    int swap;
    int *vet = (int*)malloc(lista->tam*sizeof(int));

    aux = lista->primeiro;
    for(i=0;i<lista->tam;i++) {
        vet[i] = aux->item.num;
        aux = aux->prox;
    }
    
    aux = lista->primeiro;
    for(i=0;i<lista->tam-1;i++) {
        cont = 0;
        temp = aux->prox;
        for(j=i+1;j<lista->tam;j++) {
            if(aux->item.num < temp->item.num) {
                swap = aux->item.num;
                aux->item.num = temp->item.num;
                temp->item.num = swap;
            }
        }
        aux = aux->prox;
    }

    aux = lista->primeiro;
    for(i=0;i<lista->tam;i++) {
        if(aux->item.num == vet[i]) imoveis++;
        aux = aux->prox;
    }

    free(vet);

    return imoveis;
}


void freeLista(Lista *lista) {
    No *aux = (No*)malloc(sizeof(No));
    while(lista->primeiro != NULL) {
        aux = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        free(aux);
    }
}
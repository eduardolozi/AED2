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
    int tam, pares, impares;
} Lista;

void criaLista(Lista *lista);

void insereNum(int numero, Lista *lista);

void ordenaParesImpares(Lista *lista);

void printLista(Lista lista);

void freeLista(Lista *lista);

int main() {
    Lista lista;
    int i, qtd, numero;

    criaLista(&lista);

    scanf("%d", &qtd);

    for(i=0;i<qtd;i++) {
        scanf("%d", &numero);
        insereNum(numero, &lista);
    }

    ordenaParesImpares(&lista);
    printLista(lista);
    freeLista(&lista);

    return 0;
}

void criaLista(Lista *lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tam = 0;
    lista->impares = 0;
    lista->pares = 0;
    return;
}

void insereNum(int numero, Lista *lista) {
    No *novo = (No*)malloc(sizeof(No));
    novo->item.num = numero;
    if(numero % 2 == 0) lista->pares++;
    else lista->impares++;

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

void ordenaParesImpares(Lista *lista) {
    int i, j;
    No *aux = (No*)malloc(sizeof(No));
    No *temp = (No*)malloc(sizeof(No));
    int swap;

    aux = lista->primeiro;
    for(i=0;i<(lista->tam-1);i++) {
        if(aux->item.num % 2 != 0) {
            temp = aux->prox;
            for(j=i+1;j<lista->tam;j++) {
                if(temp->item.num % 2 == 0) {
                    swap = temp->item.num;
                    temp->item.num = aux->item.num;
                    aux->item.num = swap;
                }
                temp = temp->prox;
            }
        }
        aux = aux->prox;
    }

    aux = lista->primeiro;
    for(i=0;i<lista->tam-1;i++) {
        temp = aux->prox;
        
        if(i < lista->pares-1) {
            for(j=i+1;j<lista->pares;j++) {
                if(aux->item.num > temp->item.num) {
                    swap = aux->item.num;
                    aux->item.num = temp->item.num;
                    temp->item.num = swap;
                }
                temp = temp->prox;
            }
        }
        else if(i >= lista->pares && i < lista->tam-1) {
            for(j=i+1;j<lista->tam;j++) {
                if(aux->item.num < temp->item.num) {
                    swap = aux->item.num;
                    aux->item.num = temp->item.num;
                    temp->item.num = swap;
                }
                temp = temp->prox;
            }
        }

        aux = aux->prox;
    }

}

void printLista(Lista lista) {
    No* aux = (No*)malloc(sizeof(No));
    aux = lista.primeiro;
    while(aux != NULL) {
        printf("%d\n", aux->item.num);
        aux = aux->prox;
    }
}

void freeLista(Lista *lista) {
    No *aux = (No*)malloc(sizeof(No));
    while(lista->primeiro != NULL) {
        aux = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        free(aux);
    }
}
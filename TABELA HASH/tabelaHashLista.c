#include <stdio.h>
#include <stdlib.h>

//15 elementos -> 2 x 15 = 30 -> 31
#define TAM 31

typedef struct No {
    int num;
    struct No *proximo;
} No;

typedef struct Lista {
    No *inicio;
    int tam;
} Lista;

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->tam = 0;
}

void insereLista(Lista *lista, int chave) {
    No *novo = malloc(sizeof(No));
    novo->num = chave;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->tam++;
}

int buscaNaLista(Lista *lista, int chave) {
    No *aux = malloc(sizeof(No));
    aux = lista->inicio;
    while(aux != NULL && aux->num != chave) {
        aux = aux->proximo;
    }
    if(aux == NULL) return -1;
    else return aux->num;
}

void imprimeLista(Lista *lista) {
    No *aux = malloc(sizeof(No));
    aux = lista->inicio;
    while(aux != NULL) {
        if(aux->proximo == NULL) printf(" %d", aux->num);
        else printf(" %d  - ", aux->num);
        aux = aux->proximo;
    }
}

void inicializaTabela(Lista *tabela) {
    int i;
    for(i = 0; i < TAM; i++) inicializarLista(&tabela[i]);
}

int funcaoHash(int chave) {
    return (chave % TAM);
}

void insere(int chave, Lista *tabela) {
    int pos = funcaoHash(chave);
    insereLista(&tabela[pos], chave);
}

int busca(Lista *tabela, int chave) {
    int aux;
    int pos = funcaoHash(chave);
    aux = buscaNaLista(&tabela[pos], chave);
    if(aux != -1) return pos;
    return aux;
}

void imprimeTabela(Lista *tabela) {
    int i;
    for(i = 0; i < TAM; i++) {
        printf("POS %d: ", i);
        imprimeLista(&tabela[i]);
        printf("\n");
    }
}

int main() {
    Lista tabela[TAM];
    int opcao, pos, num;
    inicializaTabela(tabela);

    do {
        printf("0 - SAIR\n1 - INSERIR\n2 - BUSCAR\n3 - IMPRIMIR\n");
        scanf("%d", &opcao);
        switch (opcao) {
        case 0:
            break;
        case 1:
            printf("Digite a chave: ");
            scanf("%d", &num);
            insere(num, tabela);
            break;
        case 2:
            printf("Digite a chave: ");
            scanf("%d", &num);
            pos = busca(tabela, num);
            if(pos == -1) printf("A chave %d nao foi encontrada.\n");
            else printf("A chave %d esta na posicao %d\n", num, pos);
            break;
        case 3:
            imprimeTabela(tabela);
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    }while(opcao != 0);


    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int numero;
} Item;

typedef struct No {
    Item item;
    struct No *esq;
    struct No *dir;
} No;

void insere(No **raiz, int num) {
    if(*raiz == NULL) {
        *raiz = (No*)malloc(sizeof(No));
        (*raiz)->dir = NULL;
        (*raiz)->esq = NULL;
        (*raiz)->item.numero = num;
    } else {
        if(num < (*raiz)->item.numero) {
            insere(&(*raiz)->esq, num);
        }
        if(num > (*raiz)->item.numero) {
            insere(&(*raiz)->dir, num);
        }
    }
}

void imprime(No *raiz) {
    if(raiz != NULL) {
        imprime(raiz->esq);
        printf("%d ", raiz->item.numero);
        imprime(raiz->dir);
    }
}

int numeroNos(No *raiz) {
    if(raiz == NULL) return 0;
    else return 1 + numeroNos(raiz->esq) + numeroNos(raiz->dir);
}

int numeroFolhas(No *raiz) {
    if(raiz == NULL) return 0;
    else if(raiz->esq == NULL && raiz->esq == NULL) return 1;
    else return numeroFolhas(raiz->esq) + numeroFolhas(raiz->dir);
}

int alturaArvore(No *raiz) {
    if(raiz == NULL) return -1;
    else {
        int esq = alturaArvore(raiz->esq);
        int dir = alturaArvore(raiz->dir);
        if(esq > dir) return 1 + esq;
        else return 1 + dir;
    }
}

int busca(No *raiz, int num) {
    if(raiz == NULL) {
        return 0;
    } else {
        if(raiz->item.numero == num) return 1;
        if(num < raiz->item.numero) busca(raiz->esq, num);
        else busca(raiz->dir, num);
    }
}

void remover(No **raiz, int num) {
    if((*raiz) == NULL) {
        printf("Numero nao encontrado.\n");
        return;
    }
    else {
        if((*raiz)->item.numero == num) {
            //remove nós folhas
            if((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                free(raiz);
                *raiz = NULL;
                printf("Remocao concluida.\n");
            }
            //remove nós com apenas um filho
            else if((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
                No *aux = malloc(sizeof(No));
                if((*raiz)->esq != NULL) aux = (*raiz)->esq;
                else aux = (*raiz)->dir;
                free(raiz);
                *raiz = aux;
                printf("Remocao concluida.\n");
            }
            //remove nós com dois filhos
            else {
                No *aux = malloc(sizeof(No));
                aux = (*raiz)->esq;
                while(aux->dir != NULL) {
                    aux = aux->dir;
                }
                (*raiz)->item.numero = aux->item.numero;
                aux->item.numero = num;
                remover(&(*raiz)->esq, num);
            }
        }
        else {
            //percorremos a arvore para tentar achar o numero
            if(num < (*raiz)->item.numero) remover(&(*raiz)->esq, num);
            else remover(&(*raiz)->dir, num);
        }
    }
}

int main() {
    No *raiz = NULL;
    int num, resp, tam, search, altura, folhas;

    do {
        printf("1 - INSERIR\n2 - IMPRIMIR\n3 - QUANTIDADE DE ITENS NA ARVORE\n4 - QUANTIDADE DE FOLHAS\n5 - ALTURA DA ARVORE\n6 - PROCURAR ELEMENTO\n7 - REMOVER ELEMENTO\n0 - SAIR\n");
        printf("Digite a opcao: ");
        scanf("%d", &resp);
        switch(resp){
            case 0:
                break;
            case 1:
                printf("Digite o numero: ");
                scanf("%d", &num);
                insere(&raiz, num);
                break;
            case 2:
                imprime(raiz);
                printf("\n");
                break;
            case 3:
                tam = numeroNos(raiz);
                printf("Numero de nos: %d\n", tam);
                break;
            case 4:
                folhas = numeroFolhas(raiz);
                printf("Numero de folhas: %d\n", folhas);
                break;
            case 5:
                altura = alturaArvore(raiz);
                printf("Altura da arvore: %d\n", altura);
                break;
            case 6:
                scanf("%d", &num);
                search = busca(raiz, num);
                if(search == 1) printf("O numero %d foi encontrado.\n");
                else printf("O numero %d nao foi encontrado.\n");
                break;
            case 7:
                printf("Digite o numero que deseja excluir: ");
                scanf("%d", &num);
                remover(&raiz, num);
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
        printf("===========================================================================\n===========================================================================\n");
    } while(resp != 0);

    return  0;
} 
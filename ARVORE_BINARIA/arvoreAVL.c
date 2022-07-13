#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int num;
    struct No *esquerda, *direita;
    short altura;
} No;

No* novoNo(int num) {
    No *novo = malloc(sizeof(No));
    if(novo) {
        novo->num = num;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    } else printf("Erro ao alocar memoria");
    return novo;
}

short maior(short a, short b) {
    if(a > b) return a;
    else return b;
}

short alturaDoNo(No *no) {
    if(no == NULL) return -1;
    else return no->altura;
}

short fatorDeBalanceamento(No *no) {
    if(no == NULL) return 0;
    else return alturaDoNo(no->esquerda) - alturaDoNo(no->direita);
}

No* rotacaoEsquerda(No *raiz) {
    No *y, *f;

    y = raiz->direita;
    f = y->esquerda;

    y->esquerda = raiz;
    raiz->direita = f;

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

No* rotacaoDireita(No *raiz) {
    No *y, *f;

    y = raiz->esquerda;
    f = y->direita;

    y->direita = raiz;
    raiz->esquerda = f;

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

No* rotacaoDireitaEsquerda(No *raiz) {
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}

No* rotacaoEsquerdaDireita(No *raiz) {
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

No* balancear(No *raiz) {
    short fb = fatorDeBalanceamento(raiz);

    if(fb < -1 && fatorDeBalanceamento(raiz->direita) <= 0) raiz = rotacaoEsquerda(raiz);
    else if(fb < -1 && fatorDeBalanceamento(raiz->direita) > 0) raiz = rotacaoDireitaEsquerda(raiz);
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) >= 0) raiz = rotacaoDireita(raiz);
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) < 0) raiz = rotacaoEsquerdaDireita(raiz);

    return raiz;
}

No* inserir(No *raiz, int num) {
    if(raiz == NULL) raiz = novoNo(num);
    else {
        if(num < raiz->num) raiz->esquerda = inserir(raiz->esquerda, num);
        else if(num > raiz->num) raiz->direita = inserir(raiz->direita, num);
        else printf("Erro ao inserir, o numero %d já existe.\n", num);
    }

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;
    raiz = balancear(raiz);

    return raiz;
}

No* remover(No *raiz, int num) {
    if(raiz == NULL) {
        printf("Valor nao encontrado.\n");
        return NULL;
    }
    else {
        if(raiz->num == num) {
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                printf("Elemento removido.\n");
                return NULL;
            }
            else{
                if(raiz->esquerda != NULL && raiz->direita != NULL) {
                    No *aux = raiz->esquerda;
                    while(aux->direita != NULL) {
                        aux = aux->direita;
                    }
                    raiz->num = aux->num;
                    aux->num = num;
                    raiz->esquerda = remover(raiz->esquerda, num);
                    return raiz;
                }
                else {
                No *aux;
                if(raiz->esquerda != NULL) aux = raiz->esquerda;
                else aux = raiz->direita;
                free(raiz);
                printf("Elemento removido.\n");
                return aux;
                }
            } 
        }
        else {
            if(num < raiz->num) raiz->esquerda = remover(raiz->esquerda, num);
            else raiz->direita = remover(raiz->direita, num);
        }
    }

    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;
    raiz = balancear(raiz);

    return raiz;
}

// versao pra ficar mais apresentavel
void imprimir(No *raiz, int nivel) {
    int i;
    if(raiz) {
        imprimir(raiz->direita, nivel + 1);
        printf("\n\n");
        for(i=0;i<nivel;i++) printf("\t");
        printf("%d", raiz->num);
        imprimir(raiz->esquerda, nivel + 1);
    }
} 

void imprimirOrdenado(No *raiz) {
    if(raiz) {
        imprimirOrdenado(raiz->esquerda);
        printf("%d ", raiz->num);
        imprimirOrdenado(raiz->direita);
    }
}

int main() {
    int opcao, valor;
    No *raiz = NULL;

    do {    
        printf("1 - INSERIR\n2 - REMOVER\n3 - IMPRIMIR NO ESQUEMA DE ARVORE\n4 - IMPRIMIR EM ORDEM CRESCENTE\n0 - SAIR\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            break;
        case 1:
            printf("Digite o numero: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf("Digite o numero: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 3:
            imprimir(raiz, 1);
            printf("\n");
            break;
        case 4:
            imprimirOrdenado(raiz);
            printf("\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    }while(opcao != 0);


    return 0;
}
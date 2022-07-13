// Aplicação de uma calculadora pós-fixada usando Árvore Binária
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct No {
    float num;
    struct No *esquerda, *direita;
} No;

void insereNum(No **raiz, char num[]) {
    double numero;
    numero = atoi(num);
    if(*raiz == NULL) {
        (*raiz) = (No*)malloc(sizeof(No));
        (*raiz)->direita = NULL;
        (*raiz)->esquerda = NULL;
        (*raiz)->num = numero;
    }
    else {
        if(numero < (*raiz)->num) insereNum(&(*raiz)->esquerda, num);
        else insereNum(&(*raiz)->direita, num);
    }
}

float calcula(No *raiz, char op) {
    double res;

    switch(op) {
        case '+':
           if(raiz->direita == NULL) {
                res = raiz->num + raiz->esquerda->num;
            } else {
                res = raiz->num + raiz->direita->num;
            }
            break;
        case '-':
            if(raiz->direita == NULL) {
                res = raiz->num - raiz->esquerda->num;
            } else {
                res = raiz->num - raiz->direita->num;
            }
            break;
        case 'x':
            if(raiz->direita == NULL) {
                res = raiz->num * raiz->esquerda->num;
            } else {
                res = raiz->num * raiz->direita->num;
            }
            break;
        case '/':
            if(raiz->direita == NULL) {
                res = raiz->num / raiz->esquerda->num;
            } else {
                res = raiz->num / raiz->direita->num;
            }
            break;
        case '^':
            if(raiz->direita == NULL) {
                res = pow(raiz->num, raiz->esquerda->num);
            } else {
                res = pow(raiz->num, raiz->direita->num);
            }
            break;
    }
    return res;
} 

void remover(No **raiz, char **numero) {
    float num = atoi(numero);
    if((*raiz) == NULL) {
        printf("Numero nao encontrado.\n");
        return;
    }
    else {
        if((*raiz)->num == num) {
            //remove nós folhas
            if((*raiz)->esquerda == NULL && (*raiz)->direita == NULL) {
                free(raiz);
                *raiz = NULL;
            }
            //remove nós com apenas um filho
            else if((*raiz)->esquerda == NULL || (*raiz)->direita == NULL) {
                No *aux = malloc(sizeof(No));
                if((*raiz)->esquerda != NULL) aux = (*raiz)->esquerda;
                else aux = (*raiz)->direita;
                free(raiz);
                *raiz = aux;
            }
            //remove nós com dois filhos
             else {
                No *aux = malloc(sizeof(No));
                aux = (*raiz)->esquerda;
                while(aux->direita != NULL) {
                    aux = aux->direita;
                }
                (*raiz)->num = aux->num;
                aux->num = num;
                remover(&(*raiz)->esquerda, numero);
            }
        }
        else {
            //percorremos a arvore para tentar achar o numero
            if(num < (*raiz)->num) remover(&(*raiz)->esquerda, numero);
            else remover(&(*raiz)->direita, numero);
        }
    }
}

int main() {
    No *raiz = NULL;
    char resp, op;
    char numero1[6], numero2[6];
    double res;

    do{
        printf("Escreva a expressao na notacao pos-fixada (OPERANDOS: +, -, x, /, ^)\n");
        scanf("%[^\n]%*c", numero1);
        scanf("%[^\n]%*c", numero2);
        scanf("%c%*c", &op);
        if(op != '+' && op != '-' && op != 'x' && op != '/' && op != '^') {
            printf("Operacao impossivel de ser realizada.\n");
        }
        insereNum(&raiz, numero1);
        insereNum(&raiz, numero2);
        res = calcula(raiz, op);
        printf("O resultado e: %.2lf\n", res);
        remover(&raiz, numero1);
        remover(&raiz, numero2);
        printf("Fazer mais operacoes? [S/N]: ");
        scanf("%c%*c", &resp);
    }while(resp != 'N' && resp != 'n');
    
    return 0;
}

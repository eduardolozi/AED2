#include <stdio.h>
#include <stdlib.h>

//15 elementos -> tamanho = 2 * elementos (primo mais proximo) = 30 -> 31
#define TAM 31

void inicializaTabela(int *tabela) {
    int i;
    for(i = 0; i < TAM; i++) tabela[i] = 0;
}

int funcaoHash(int chave) {
    return (chave % TAM);
}

void insere(int chave, int *tabela) {
    int pos = funcaoHash(chave);
    while(tabela[pos] != 0) {
        pos++;
        if(pos > TAM) pos = 0;
    }
    tabela[pos] = chave;
}

int busca(int *tabela, int chave) {
    int aux;
    int pos = funcaoHash(chave);
    aux = pos;
    while(tabela[pos] != chave) {
        if(tabela[pos] == 0) return -1; //se a chave for 0, quer dizer que o elemento não esta inserido ainda
        pos++;
        if(pos > TAM) pos = 0;
        if(pos == aux) return -1; // isso acontece quando é dada uma volta completa no vetor
    }
    return pos;
}

void imprimeTabela(int *tabela) {
    int i;
    for(i = 0; i < TAM; i++) {
        printf("POS %d: %d\n", i, tabela[i]);
    }
}

int main() {
    int tabela[TAM], opcao, pos, num;
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
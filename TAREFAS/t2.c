// Realiza o CRUD e ordenaçao de uma lista circular duplamente encadeada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    float nota1, nota2, media;
    int matricula;
    char nome[50], curso[50];
} Aluno;

typedef struct No{
    Aluno item;
    struct No *proximo;
    struct No *anterior;
} No;

typedef struct Lista{
    struct No *primeiro;
    struct No *ultimo;
    int tamanho;
} Lista;

void init(Lista *lista);

void addStudent(Lista *lista);

int validationMat(Lista lista, int mat);

void updateStudent(Lista *lista);

void deleteStudent(Lista *lista);

void ordenaMedias(Lista *lista);

void readList(Lista lista);

void liberaMemoria(Lista *lista);

int main() {
    Lista lista;
    char resp;

    init(&lista);

    do{
        printf("Você deseja inserir um aluno? Digite S ou N: ");
        scanf("%c%*c", &resp);
        if(resp != 'S' && resp != 'N') {
            while(resp != 'S' && resp != 'N') {
                printf("Digite S ou N: ");
                scanf("%c%*c", &resp);
            }
        }
        if(resp == 'S') {
            addStudent(&lista);
        }
    }while(resp != 'N');
    system("clear||cls");

    do{
        printf("Você deseja atualizar os dados de algum aluno? Digite S ou N: ");
        scanf("%c%*c", &resp);
        if(resp != 'S' && resp != 'N') {
            while(resp != 'S' && resp != 'N') {
                printf("Digite S ou N: ");
                scanf("%c%*c", &resp);
            }
        }
        if(resp == 'S') {
            system("clear||cls");
            readList(lista);
            updateStudent(&lista);
        }
    }while(resp != 'N');

    do{
        printf("Você deseja excluir um aluno? Digite S ou N: ");
        scanf("%c%*c", &resp);
        if(resp != 'S' && resp != 'N') {
            while(resp != 'S' && resp != 'N') {
                printf("Digite S ou N: ");
                scanf("%c%*c", &resp);
            }
        }
        if(resp == 'S') {
            printf("\n");
            readList(lista);
            if(lista.tamanho==0) {
                printf("Impossível excluir mais alunos.\n");
                break;
            }
            deleteStudent(&lista);
        }
    }while(resp != 'N');

    printf("\n");
    printf("Você quer ver como a lista se encontra? Digite S ou N\n");
    scanf("%c%*c", &resp);
    if(resp != 'S' && resp != 'N') {
            while(resp != 'S' && resp != 'N') {
                printf("Digite S ou N: ");
                scanf("%c%*c", &resp);
            }
    }
    if(resp == 'S') {
        system("clear||cls");
        readList(lista);
    }

    printf("\n");
    printf("Você quer ordenar a lista em relação às médias? Digite S ou N\n");
    scanf("%c%*c", &resp);
    if(resp != 'S' && resp != 'N') {
            while(resp != 'S' && resp != 'N') {
                printf("Digite S ou N: ");
                scanf("%c%*c", &resp);
            }
    }
    if(resp == 'S') {
        system("clear||cls");
        ordenaMedias(&lista);
        printf("A lista ordenada se encontra assim:\n");
        readList(lista);
    }

    liberaMemoria(&lista);

    return 0;
}

void init(Lista *lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
}

void addStudent(Lista *lista) {
    No *novo = (No*) malloc(sizeof(No));
    No *aux = (No*) malloc(sizeof(No));
    Aluno student;
    int i, res;

    validation:
    printf("Insira o nome do aluno: ");
    scanf("%[^\n]%*c", student.nome);

    printf("Insira o número da matrícula: ");
    scanf("%d%*c", &student.matricula);
    if(lista->tamanho >= 1) res = validationMat(*lista, student.matricula);
    if(res == 1) goto validation;

    printf("Insira o curso: ");
    scanf("%[^\n]%*c", student.curso);

    printf("Insira a nota1: ");
    scanf("%f%*c", &student.nota1);
    if(student.nota1 > 10 || student.nota1 < 0) {
        while(student.nota1 > 10 || student.nota1 < 0) {
            printf("Nota impossível. Insira novamente a Nota1: ");
            scanf("%f%*c", &student.nota1);
        }   
    }

    printf("Insira a nota2: ");
    scanf("%f%*c", &student.nota2);
    if(student.nota2 > 10 || student.nota2 < 0) {
        while(student.nota2 > 10 || student.nota2 < 0) {
            printf("Nota impossível. Insira novamente a Nota2: ");
            scanf("%f%*c", &student.nota2);
        }   
    }

    student.media = (student.nota1 + student.nota2) / 2.0;

    novo->item = student;
    if(lista->tamanho == 0) {
        novo->proximo = NULL;
        novo->anterior = NULL;
        lista->primeiro = novo;
        lista->ultimo = novo;
    } else {
        novo->anterior = lista->ultimo; //novo->anterior aponta pra quem lista->anterior apontava
        novo->proximo = lista->primeiro; //novo->proximo aponta pra quem lista->primeiro apontava
        lista->primeiro->anterior = novo; //o primeiro elemento aponta (<--) pro novo primeiro elemento
        lista->primeiro = novo; //lista->primeiro agora aponta para novo (se torna o primeiro elemento)
        lista->ultimo->proximo = novo;
    }
    lista->tamanho++;
}

int validationMat(Lista lista, int mat) {
    if(lista.tamanho == 1 && lista.primeiro->item.matricula == mat) return 1;
    else if(lista.tamanho == 1 && lista.primeiro->item.matricula != mat) return 0;

    int aux = lista.primeiro->item.matricula;
    int i = 0;
    while(i != 2 && lista.primeiro->item.matricula != mat) {
        if(lista.primeiro->item.matricula == aux) i++;
        lista.primeiro = lista.primeiro->proximo;
    }
    if(i==2) return 0;
    return 1;
}

void updateStudent(Lista *lista) {
    int option, mat, resp;

    printf("Insira a matrícula do aluno que deseja alterar: ");
    scanf("%d%*c", &mat);
    resp = validationMat(*lista, mat);

    if(resp == 0) {
        printf("Não foi encontrado nenhum aluno com essa matrícula.\n");
        return;
    } else {
        char letra;
        No *aux = (No*)malloc(sizeof(No));
        Aluno temporario;
        int j;
        float nota1, nota2;
        
        if(lista->tamanho == 1 && lista->primeiro->item.matricula == mat) aux = lista->primeiro;    
        if(lista->tamanho > 1) {
            aux = lista->primeiro;
            while(aux->item.matricula != mat) {
                aux = aux->proximo;
            }
        }
        temporario = aux->item;

        do {
            printf("O que deseja mudar no esudante?\n[1]Nome\n[2]Matrícula\n[3]Curso\n[4]Nota1\n[5]Nota2\nInsira o número da opção: ");
            scanf("%d%*c", &option);

            switch(option) {
                case 1:
                    printf("Insira o novo nome: ");
                    scanf("%[^\n]%*c", aux->item.nome);
                    break;
                case 2:
                    newMat:
                    printf("Insira a nova matrícula: ");
                    scanf("%d%*c", &mat);
                    j = validationMat(*lista, mat);
                    if(j == 1) goto newMat;
                    else aux->item.matricula = mat;                 
                    break;
                case 3:
                    printf("Insira o novo curso do aluno: ");
                    scanf("%[^\n]%*c", aux->item.curso);
                    break;
                case 4:
                    printf("Insira a nova nota1 do aluno: ");
                    scanf("%f%*c", &nota1);
                    if(nota1 > 10 || nota1 < 0) {
                        while(nota1 > 10 || nota1 < 0) {
                            printf("Nota impossível. Insira a nota corretamente: ");
                            scanf("%f%*c", &nota1);
                        }
                    }
                    aux->item.nota1 = nota1;
                    break;
                case 5:
                    printf("Insira a nova nota2 do aluno: ");
                    scanf("%f%*c", &nota2);
                    if(nota2 > 10 || nota2 < 0) {
                        while(nota2 > 10 || nota2 < 0) {
                            printf("Nota impossível. Insira a nota corretamente: ");
                            scanf("%f%*c", &nota2);
                        }
                    }
                    aux->item.nota2 = nota2;
                    break;
                default: 
                    printf("Opção inválida.\n");
                    break;
            }
            printf("Você deseja alterar outro dado no estudante? Digite S/N: ");
            scanf("%c%*c", &letra);  
        }while(letra != 'N');

        aux->item.media = (aux->item.nota1 + aux->item.nota2) / 2.0;

        system("clear||cls");
        printf("------------ REGISTRO DO ALUNO ANTES DAS MUDANÇAS ------------\n");
        printf("Nome: %s\nMatrícula: %d\nCurso: %s\nNota 1: %.2f\nNota 2 : %.2f\n", temporario.nome, temporario.matricula, temporario.curso, temporario.nota1, temporario.nota2);
        printf("------------ REGISTRO DO ALUNO DEPOIS DAS MUDANÇAS ------------\n");
        printf("Nome: %s\nMatrícula: %d\nCurso: %s\nNota 1: %.2f\nNota 2 : %.2f\n", aux->item.nome, aux->item.matricula, aux->item.curso, aux->item.nota1, aux->item.nota2);
    }
}

void deleteStudent(Lista *lista) {
    int mat;

    printf("Insira a matrícula do aluno que deseja excluir: ");
    scanf("%d%*c", &mat);  

    if(lista->tamanho == 1 &&lista->primeiro->item.matricula != mat) {
        printf("ALUNO NÃO ENCONTRADO.\n");
        return;
    } else if(lista->tamanho == 1 && lista->primeiro->item.matricula == mat) {
        printf("O aluno %s(%d) foi removido.\n", lista->primeiro->item.nome, lista->primeiro->item.matricula);       
        lista->primeiro = NULL;
        lista->ultimo = NULL;
        lista->tamanho--;
    } else {
        No *aux = (No*)malloc(sizeof(No));
        int i = 0;
        aux = lista->primeiro;
        while(aux->item.matricula != mat && i!=2) {
            if(aux == lista->primeiro) i++;
            aux = aux->proximo;
        }
        if(i==2) {
            printf("ALUNO NÃO ENCONTRADO.\n");
            return;
        }
        if(aux == lista->ultimo) {
            lista->ultimo = aux->anterior;
        }
        if(aux == lista->primeiro) {
            lista->primeiro = aux->proximo;
        }
        printf("O aluno %s(%d) foi removido.\n", aux->item.nome, aux->item.matricula);
        aux->anterior->proximo = aux->proximo;
        aux->proximo->anterior = aux->anterior;
        free(aux);
        lista->tamanho--;
    }
}

void readList(Lista lista) {
    if(lista.tamanho == 0) {
        printf("Lista vazia.\n");
        return;
    }
    else {
        
        while(lista.primeiro != lista.ultimo) { 
            printf("Nome: %s\n", lista.primeiro->item.nome);
            printf("Numero da matricula: %d\n", lista.primeiro->item.matricula);
            printf("Curso: %s\n", lista.primeiro->item.curso);
            printf("Nota 1: %.2f\n", lista.primeiro->item.nota1);
            printf("Nota 2: %.2f\n", lista.primeiro->item.nota2);
            printf("Média: %.2f\n", ((lista.primeiro->item.nota1 + lista.primeiro->item.nota2)/2.0));
            printf("------------------------------------------------\n");
            lista.primeiro = lista.primeiro->proximo;
        }
        // falta ler o ultimo elemento, dessa forma, fazemos isso mais uma vez apenas
        printf("Nome: %s\n", lista.primeiro->item.nome);
        printf("Numero da matricula: %d\n", lista.primeiro->item.matricula);
        printf("Curso: %s\n", lista.primeiro->item.curso);
        printf("Nota 1: %.2f\n", lista.primeiro->item.nota1);
        printf("Nota 2: %.2f\n", lista.primeiro->item.nota2);
        printf("Média: %.2f\n", ((lista.primeiro->item.nota1 + lista.primeiro->item.nota2)/2.0));
        printf("------------------------------------------------\n");
    }
}

void liberaMemoria(Lista *lista) {
    No *aux = (No*) malloc(sizeof(No));

    if(lista->tamanho == 0) {
        return;
    }
    else {
        aux = lista->primeiro;
        while(aux != lista->ultimo) { // desaloca ate o penultimo elemento, quando chegar no ultimo ele para
            aux = aux->proximo;
            free(aux->anterior);
        }
        free(aux); //desaloca o ultimo elemento da lista, que nao havia sido desalocado no while
    }
}

void ordenaMedias(Lista *lista) {
    No *temp1 = (No*) malloc(sizeof(No));
    No *temp2 = (No*) malloc(sizeof(No));
    Aluno swap;
    int i, j;

    temp1 = lista->primeiro;
    for(i=0;i<(lista->tamanho-1);i++) {
        temp2 = temp1->proximo;
        for(j=i+1;j<lista->tamanho;j++) {
            if(temp1->item.media < temp2->item.media) {
                swap = temp1->item;
                temp1->item = temp2->item;
                temp2->item = swap;
            }
            temp2 = temp2->proximo;
        }
        temp1 = temp1->proximo;
    }
}
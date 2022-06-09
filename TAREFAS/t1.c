#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 50

typedef struct aluno{
    float nota1, nota2;
    int matricula;
    char nome[50], curso[50];
} Aluno;

typedef struct lista{
    Aluno students[MAXTAM];
    int primeiro, ultimo;
} Lista;


void create(Lista *lista);

void addStudent(Lista *lista, Aluno student);

int validationName(Lista lista, Aluno student);

void readList(Lista lista);

int main() {
    Lista lista;
    Aluno student;
    char resp;

    create(&lista);

    do{
        addStudent(&lista, student);
        printf("Você deseja inserir mais um aluno? Digite S ou N: ");
        scanf("%c%*c", &resp);
        if(resp != 'S' && resp != 'N') {
            while(resp != 'S' && resp != 'N') {
                printf("Digite S ou N: ");
                scanf("%c%*c", &resp);
            }
        }
    }while(resp != 'N');

    printf("\n");
    readList(lista);
    return 0;
}

void create(Lista *lista) {
    lista->primeiro = 0;
    lista->ultimo = lista->primeiro;
}

void addStudent(Lista *lista, Aluno student) {
    int i;
    if(lista->ultimo == MAXTAM) {
        printf("Lista cheia. Impossível colocar o aluno.\n");
        return;
    }

    validation:
    printf("Digite o nome do aluno: ");
    scanf("%[^\n]", student.nome);
    printf("Digite a matricula do aluno: ");
    scanf("%d%*c", &student.matricula);
    if(lista->ultimo > 0) {
        for(i=lista->primeiro;i<lista->ultimo;i++) {
            if(lista->students[i].matricula == student.matricula) {
                printf("Aluno já inserido. Insira outro novamente.\n");
                goto validation;
            }
        }
    }
    printf("Digite o curso do aluno: ");
    scanf("%[^\n]", student.curso);
    printf("Digite a nota1 do aluno: ");
    scanf("%f", &student.nota1);
    if(student.nota1 > 10 || student.nota1 < 0) {
        while(student.nota1 > 10 || student.nota1 < 0) {
            printf("Nota impossível. Insira novamente a Nota1: ");
            scanf("%f", &student.nota1);
        }   
    }
    printf("Digite a nota2 do aluno: ");
    scanf("%f", &student.nota2);
    if(student.nota2 > 10 || student.nota2 < 0) {
        while(student.nota2 > 10 || student.nota2 < 0) {
            printf("Nota impossível. Insira novamente a Nota2: ");
            scanf("%f", &student.nota2);
        }   
    }
    
    lista->students[lista->ultimo] = student;
    lista->ultimo++;
}

void readList(Lista lista) {
    int i;
    for(i=lista.primeiro;i<lista.ultimo;i++) {
        printf("Nome: %s\n", lista.students[i].nome);
        printf("Numero da matricula: %d\n", lista.students[i].matricula);
        printf("Curso: %s\n", lista.students[i].curso);
        printf("Nota 1: %.2f\n", lista.students[i].nota1);
        printf("Nota 2: %.2f\n", lista.students[i].nota2);
        printf("------------------------------------------------\n");
    }
}
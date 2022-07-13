/* Código que administra uma lista de, no máximo, 50 alunos. Cada aluno possui nome, matrícula, curso, nota 1 e nota 2. 
As funções são de criação, leitura, atualização e exclusão. */

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

void deleteStudent(Lista *lista, int matricula);

void updateStudent(Lista *lista);

void readList(Lista lista);

int main() {
    Lista lista;
    Aluno student;
    char resp;
    int mat;

    create(&lista);

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
            addStudent(&lista, student);
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
            readList(lista);
            if(lista.ultimo==0) {
                printf("Impossível excluir mais alunos.\n");
                break;
            }
            printf("\nDigite a matrícula do aluno que deseja remover: ");
            scanf("%d%*c", &mat);
            deleteStudent(&lista, mat);
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
    scanf("%[^\n]%*c", student.nome);
    printf("Digite a matricula do aluno: ");
    scanf("%d%*c", &student.matricula);
    if(lista->ultimo > 0) {
        for(i=lista->primeiro;i<lista->ultimo;i++) {
            if(lista->students[i].matricula == student.matricula) {
                printf("Matricula já inserida. Insira o aluno corretamente.\n");
                goto validation;
            }
        }
    }
    printf("Digite o curso do aluno: ");
    scanf("%[^\n]%*c", student.curso);
    printf("Digite a nota1 do aluno: ");
    scanf("%f%*c", &student.nota1);
    if(student.nota1 > 10 || student.nota1 < 0) {
        while(student.nota1 > 10 || student.nota1 < 0) {
            printf("Nota impossível. Insira novamente a Nota1: ");
            scanf("%f%*c", &student.nota1);
        }   
    }
    printf("Digite a nota2 do aluno: ");
    scanf("%f%*c", &student.nota2);
    if(student.nota2 > 10 || student.nota2 < 0) {
        while(student.nota2 > 10 || student.nota2 < 0) {
            printf("Nota impossível. Insira novamente a Nota2: ");
            scanf("%f%*c", &student.nota2);
        }   
    }
    
    lista->students[lista->ultimo] = student;
    lista->ultimo++;
}

void deleteStudent(Lista *lista, int matricula) {
    int i=0, j;

    for(i=0;i<lista->ultimo;i++) {
        if(lista->students[i].matricula == matricula) break;
    }
    if(i == lista->ultimo) {
        printf("Aluno não encontrado.\n");
        return;
    }
    system("clear||cls");
    printf("\n----- O aluno %s (%d) foi excluído -----\n", lista->students[i].nome, lista->students[i].matricula);
    for(j=i;j<lista->ultimo;j++) {
        lista->students[j] = lista->students[j+1];
    }
    lista->ultimo--;
}

void updateStudent(Lista *lista) {
    int i, mat, option, j;
    char resp, newName;
    float nota1, nota2;
    Aluno temp;

    printf("\nDigite a matrícula do estudante: ");
    scanf("%d%*c", &mat);
    for(i=0;i<lista->ultimo;i++) {
        if(lista->students[i].matricula == mat) break;
    }
    if(i == lista->ultimo) {
        printf("Aluno não encontrado.\n");
        return;
    }
    temp = lista->students[i];

    do{
        printf("O que deseja mudar no esudante?\n[1]Nome\n[2]Matrícula\n[3]Curso\n[4]Nota1\n[5]Nota2\nInsira o número da opção: ");
        scanf("%d%*c", &option);
        switch(option) {
            case 1:
                printf("Insira o novo nome: ");
                scanf("%[^\n]%*c", lista->students[i].nome);
                break;
            case 2:
                newMat:
                printf("Insira a nova matrícula: ");
                scanf("%d%*c", &mat);
                for(j=lista->primeiro;j<lista->ultimo;j++) {
                    if(lista->students[j].matricula == mat) {
                        printf("Matricula já inserida. Insira a matrícula corretamente.\n");
                        goto newMat;
                    }
                }
                lista->students[i].matricula = mat;
                break;
            case 3:
                printf("Insira o novo curso do aluno: ");
                scanf("%[^\n]%*c", lista->students[i].curso);
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
                lista->students[i].nota1 = nota1;
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
                lista->students[i].nota2 = nota2;
                break;
            default: 
                printf("Opção inválida.\n");
                break;
        }
        printf("Deseja alterar mais dados do estudante? Digite S ou N: ");
        scanf("%c%*c", &resp);
    }while(resp != 'N');
    system("clear||cls");
    printf("Registro do aluno antes das mudanças:\nNome: %s\nMatrícula: %d\nCurso: %s\nNota 1: %.2f\nNota 2 : %.2f\n------------------------------------------------\n", temp.nome, temp.matricula, temp.curso, temp.nota1, temp.nota2);
    printf("Registro do aluno depois das mudanças:\nNome: %s\nMatrícula: %d\nCurso: %s\nNota 1: %.2f\nNota 2 : %.2f\n------------------------------------------------\n", lista->students[i].nome, lista->students[i].matricula, lista->students[i].curso, lista->students[i].nota1, lista->students[i].nota2);
}

void readList(Lista lista) {
    int i;
    printf("\n");
    if(lista.ultimo == 0) {
        printf("--- LISTA VAZIA ---\n");
        return;
    }
    for(i=lista.primeiro;i<lista.ultimo;i++) {
        printf("Nome: %s\n", lista.students[i].nome);
        printf("Numero da matricula: %d\n", lista.students[i].matricula);
        printf("Curso: %s\n", lista.students[i].curso);
        printf("Nota 1: %.2f\n", lista.students[i].nota1);
        printf("Nota 2: %.2f\n", lista.students[i].nota2);
        printf("Média: %.2f\n", ((lista.students[i].nota1 + lista.students[i].nota2)/2.0));
        printf("------------------------------------------------\n");
    }
}
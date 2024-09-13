#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discipline.h"
#include "../error.h"

Discipline *allocate_discipline() 
{
    Discipline *new_subject = (Discipline*) malloc(sizeof(Discipline));
    check_allocation(new_subject, "allocate discipline\n");
    
    new_subject->discipline_code = 0;
    strcpy(new_subject->discipline_name, "");
    new_subject->period = 0;
    new_subject->workload = 0;
    new_subject->left = NULL;
    new_subject->right = NULL;

    return new_subject;
}

Discipline_Tree *create_discipline_tree()
{
    Discipline_Tree *new = (Discipline_Tree *)malloc(sizeof(Discipline_Tree));
    check_allocation(new, "create discipline tree");

    new->root = allocate_discipline();

    return new;
}

void deallocate_discipline(Discipline *discipline) 
{
    if (discipline != NULL) {
        //
        free(discipline);
    }
}

void deallocate_discipline_tree(Discipline_Tree *root) 
{
    if (root != NULL) {
        //
        free(root);
    }
}

void printf_discipline(Discipline discipline)
{
    printf("%d\n", discipline.discipline_code);
    printf("%d\n", discipline.period);
    printf("%d\n", discipline.workload);
    printf("%s\n", discipline.discipline_name);
}

// Função que retorna um número incrementado a cada chamada
int get_code(int course_code) {
    static int discipline_code = 0; 
    char str[20];
    sprintf(str, "%d%04d", course_code, discipline_code++); 
    return atoi(str); // Transforma a string gerada em número
}

Discipline* insert_discipline(Discipline *root, Discipline *new_subject) {
    Discipline *result = root;

    if (root == NULL) {
        result = new_subject;
    } else if (strcmp(root->discipline_name, new_subject->discipline_name) == 0) {
        
        printf("Discipline with name %s already exists!\n", root->discipline_name);
        
    } else if (new_subject->discipline_code < root->discipline_code) {
        
        root->left = insert_discipline(root->left, new_subject);
    } else if (new_subject->discipline_code > root->discipline_code) {

        root->right = insert_discipline(root->right, new_subject);
    }

    return result;
}


// void register_discipline(Discipline **root, Course *course)
// {
//     int temp = 0;

//     // Aloca memória para um novo curso
//     Discipline *new = allocate_discipline();
//     check_allocation(new, "register discipline");
    
//     printf("Enter discipline name: ");
//     setbuf(stdin, NULL);
//     scanf("%[^\n]", new->discipline_name);

//     new->discipline_code = GET_DISCIPLINE_CODE();

//     do
//     {
//         printf("---------- WORKLOAD ----------\n1 - 30 hours\n2 - 60 hours\n3 - 90 hours\n");
//         scanf("%d", &temp);

//         switch(temp)
//         {
//         case 1:  new->workload = HOURS_30; break;
//         case 2:  new->workload = HOURS_60; break;
//         case 3:  new->workload = HOURS_90; break;
//         default: break;
//         }
//     } 
//     while(!valid_answer(1, 3, temp));

//     do {
//         printf("The course %s has %d periods, where the %s discipline will be placed\n",
//         course->course_name, course->num_periods, new->discipline_name);
//         scanf("%d", &temp);
//     } 
//     while(!valid_answer(1, course->num_periods, temp));
//     new->period = temp;


//     // Insere o curso na árvore de cursos 
//     // TODO: make a better solution
//     if(root == NULL)
//         insert_discipline(*root, new);
//     else
//         *root = new;
    
//     printf("Discipline successfully registered!\n");
// }

// Another solucion
void register_discipline(Discipline **root, Course *course)
{
    int temp = 0;
    int exists = 0; 
    char discipline_name[100];

    // Pega o nome da disciplina para comparar
    printf("Enter discipline name: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", discipline_name);

    // Verifica se a disciplina já existe na árvore
    if (find_discipline(*root, discipline_name)) {
        printf("Discipline with name %s already exists!\n", discipline_name);
        exists = 1; // Marca que a disciplina já existe
    }

    if (!exists) {

        Discipline *new = allocate_discipline();
        check_allocation(new, "register discipline");

        strcpy(new->discipline_name, discipline_name);
        new->discipline_code = GET_DISCIPLINE_CODE(course->course_code);

        do
        {
            printf("---------- WORKLOAD ----------\n1 - 30 hours\n2 - 60 hours\n3 - 90 hours\n");
            scanf("%d", &temp);

            switch(temp)
            {
                case 1:  new->workload = HOURS_30; break;
                case 2:  new->workload = HOURS_60; break;
                case 3:  new->workload = HOURS_90; break;
                default: break;
            }
        } 
        while(!valid_answer(1, 3, temp));

        do {
            printf("The course %s has %d periods, where the %s discipline will be placed\n",
            course->course_name, course->num_periods, new->discipline_name);
            scanf("%d", &temp);
        } 
        while(!valid_answer(1, course->num_periods, temp));
        new->period = temp;

        if (*root == NULL)
            *root = new;
        else
            insert_discipline(*root, new);

        printf("Discipline successfully registered!\n");
    }
}
Discipline* find_discipline(Discipline *root, const char *name) {
    Discipline *result = NULL;

    while (root != NULL) {
        int cmp = strcmp(name, root->discipline_name);
        if (cmp == 0) {
            result = root; // Encontrou a disciplina
            root = NULL; // Para sair do loop
        } else if (cmp < 0) {
            root = root->left; 
        } else {
            root = root->right; 
        }
    }

    return result;
}


void remove_subject(Course *course, int discipline_code)
{
    if(course == NULL)
        return;

    // TODO: finish course fist
}
void show_disciplines(Discipline *root)
{
    // print_error("show_course, root value invalid or not allocated");
    if (root != NULL)
    {
        // Mostra os cursos em ordem (caminhamento em ordem)
        show_disciplines(root->left);      
        printf_discipline(*root);          
        show_disciplines(root->right);     
    }
}

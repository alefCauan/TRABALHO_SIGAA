#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjetc.h"
#include "../error.h"

// TODO: change all names 
Subject *allocate_subject() 
{
    Subject *new_subject = (Subject*) malloc(sizeof(Subject));
    check_allocation(new_subject, "allocate subject\n");
    
    if (new_subject != NULL) 
    {
        new_subject->subject_code = 0;
        strcpy(new_subject->subject_name, "");
        new_subject->period = 0;
        new_subject->workload = 0;
        new_subject->left = NULL;
        new_subject->right = NULL;
    }

    return new_subject;
}

Subject_Tree *create_subject_tree()
{
    Subject_Tree *new = (Subject_Tree *)malloc(sizeof(Subject_Tree));
    check_allocation(new, "create subject tree");

    new->root = allocate_subject();

    return new;
}

void deallocate_subject(Subject *subject) 
{
    if (subject != NULL) {
        //
        free(subject);
    }
}

void deallocate_subject_tree(Subject_Tree *root) 
{
    if (root != NULL) {
        //
        free(root);
    }
}

void printf_subject(Subject subject)
{
    printf("%d\n", subject.subject_code);
    printf("%d\n", subject.period);
    printf("%d\n", subject.workload);
    printf("%s\n", subject.subject_name);
}

// Função que retorna um número incrementado a cada chamada
int get_code() 
{
    static int subject_code = 0; 
    // char str[20];
    // sprintf(str, "%d%d%04d"); // TODO: course code + static value  

    return subject_code++;
}

Subject *insert_discipline(Subject *root, Subject *new_subject) 
{
    if(root == NULL)
        return root;

    // Compara o código da disciplina para determinar a posição
    if (strcmp(root->subject_name, new_subject->subject_name) == 0) 
    {
        printf("Discipline with name %s already exists!\n", root->subject_name);
        return root;
    }

    // Inserção recursiva na subárvore da esquerda ou direita
    if (new_subject->subject_code < root->subject_code) 
        root->left = insert_discipline(root->left, new_subject);
    else if (new_subject->subject_code > root->subject_code) 
        root->right = insert_discipline(root->right, new_subject);

    return root;
}

void register_subject(Subject **root, Course *course)
{
    int temp = 0;

    // Aloca memória para um novo curso
    Subject *new = allocate_subject();
    check_allocation(new, "register subject");
    
    printf("Enter subject name: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", new->subject_name);

    new->subject_code = GET_SUBJECT_CODE();

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
        printf("The course %s has %d periods, where the %s subject will be placed\n",
        course->course_name, course->num_periods, new->subject_name);
        scanf("%d", &temp);
    } 
    while(!valid_answer(1, course->num_periods, temp));
    new->period = temp;


    // Insere o curso na árvore de cursos 
    // TODO: make a better solution
    if(root == NULL)
        insert_discipline(*root, new);
    else
        *root = new;
    
    printf("Subject successfully registered!\n");
}

void remove_subject(Course *course, int subject_code)
{
    if(course == NULL)
        return;

    // TODO: finish course fist
}
void show_subjects(Subject *root)
{
    // print_error("show_course, root value invalid or not allocated");
    if (root == NULL)
        return;

    // Mostra os cursos em ordem (caminhamento em ordem)
    show_subjects(root->left);      
    printf_subject(*root);          
    show_subjects(root->right);     
}

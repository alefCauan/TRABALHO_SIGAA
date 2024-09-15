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
    if (discipline != NULL) 
    {
        free(discipline);
        discipline = NULL;
    }
}

void deallocate_discipline_tree(Discipline *root) 
{
    if (root != NULL) 
    {
        deallocate_discipline_tree(root->left);
        deallocate_discipline_tree(root->right);

        deallocate_discipline(root);
    }
}

Discipline *search_discipline(Discipline *root, int code)
{
    Discipline *result = NULL;

    if(root->discipline_code == code || root == NULL)
        result = root;
    if(code < root->discipline_code)
        result = search_discipline(root->left, code);
    else if(code > root->discipline_code)
        result = search_discipline(root->right, code);

    return result;
}

void printf_discipline(Discipline discipline)
{
    printf("code    %d\n", discipline.discipline_code);
    printf("period  %d\n", discipline.period);
    printf("worload %d\n", discipline.workload);
    printf("name    %s\n", discipline.discipline_name);
}

// Função que retorna um número incrementado a cada chamada
int get_code() 
{
    static int discipline_code = 0; 
    // char str[20];
    // sprintf(str, "%d%d%04d"); // TODO: course code + static value  

    return discipline_code++;
}

Discipline *insert_discipline(Discipline *root, Discipline *new_subject) 
{
    Discipline *result = NULL;
    if (root == NULL) 
        return new_subject;

    // Compara o código da disciplina para determinar a posição
    if (strcmp(root->discipline_name, new_subject->discipline_name) == 0) 
        printf("Discipline with name %s already exists!\n", root->discipline_name);
    else if (new_subject->discipline_code < root->discipline_code) 
        root->left = insert_discipline(root->left, new_subject);
    else if (new_subject->discipline_code > root->discipline_code) 
        root->right = insert_discipline(root->right, new_subject);

    return root;
}


void register_discipline(Discipline **root, Course *course)
{
    int temp = 0;

    // Aloca memória para um novo curso
    Discipline *new = allocate_discipline();
    check_allocation(new, "register discipline");
    
    printf("Enter discipline name: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", new->discipline_name);

    new->discipline_code = GET_DISCIPLINE_CODE();

    do {
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

    // Insere o curso na árvore de cursos 
    // TODO: make a better solution
    if(*root == NULL || (*root)->discipline_code == 0)
        *root = new;
    else
        insert_discipline(*root, new);
    
    printf("Discipline successfully registered!\n");
}

// TODO: verificar todos os alunos e ver se eles estão matriculados nessa disciplina
void remove_discipline(Discipline **root, int discipline_code)
{
    Discipline *current = *root;
    Discipline *parent = NULL;

    // Procura o nó a ser removido
    while (current != NULL && current->discipline_code != discipline_code) 
    {
        parent = current;
        if (discipline_code > current->discipline_code)
            current = current->right;
        else
            current = current->left;
    }

    // Se o nó não for encontrado
    if (current == NULL)
    {
        printf("Discipline code %d not found.\n", discipline_code);
        return;
    }

    // Caso 1: Nó sem filhos
    if (current->left == NULL && current->right == NULL)
    {
        if (parent == NULL) // Se é a raiz
            *root = NULL;
        else if (parent->right == current)
            parent->right = NULL;
        else
            parent->left = NULL;

        free(current);
    }
    // Caso 2: Nó com dois filhos
    else if (current->left != NULL && current->right != NULL)
    {
        // Encontrar o sucessor (menor valor na subárvore direita)
        Discipline *successor = current->right;
        Discipline *successor_parent = current;

        while (successor->left != NULL)
        {
            successor_parent = successor;
            successor = successor->left;
        }

        // Copiar os dados do sucessor para o nó atual
        current->discipline_code = successor->discipline_code;

        // Remover o sucessor da árvore
        if (successor_parent->left == successor)
            successor_parent->left = successor->right;
        else
            successor_parent->right = successor->right;

        free(successor);
    }
    // Caso 3: Nó com um filho
    else 
    {
        Discipline *child = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) // Se o nó é a raiz
            *root = child;
        else if (parent->right == current)
            parent->right = child;
        else
            parent->left = child;

        free(current);
    }
}

void show_disciplines(Discipline *root)
{
    if (root != NULL)
    {
        // Mostra as disciplinas em ordem (caminhamento em ordem)
        show_disciplines(root->left);      
        printf_discipline(*root);          
        show_disciplines(root->right);     
    }
}

// Função para mostrar todas as disciplinas de um determinado período de um curso
void show_disciplines_by_period(Discipline *root, int period)
{
    if(root != NULL)
    {
        show_disciplines_by_period(root->left, period);
        if(root->period == period) printf_discipline(*root);
        show_disciplines_by_period(root->right, period);
    }
}

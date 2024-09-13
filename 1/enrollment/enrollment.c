#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enrollment.h"
#include "../error.h"
#include "../discipline/discipline.h"

Enrollment *allocate_enrollment() 
{
    Enrollment *new_enrollment = (Enrollment*) malloc(sizeof(Enrollment));
    check_allocation(new_enrollment, "allocate enrollment");

    new_enrollment->discipline_code = 0;
    new_enrollment->left = NULL;
    new_enrollment->right = NULL;

    return new_enrollment;
}

Enrollment_Tree *create_enrollment_tree()
{
    Enrollment_Tree *new = (Enrollment_Tree *)malloc(sizeof(Enrollment_Tree));
    check_allocation(new, "create enrollment tree");

    new->root = allocate_enrollment();

    return new;
}

void deallocate_enrollment(Enrollment *enrollment) 
{
    if (enrollment != NULL) {
        free(enrollment);
    }
}

void deallocate_enrollment_tree(Enrollment_Tree *root) 
{
    if (root != NULL) 
    {
        //
        free(root);
    }
}

Enrollment *insert_enrol(Enrollment *root, Enrollment *new)
{
    if (root == NULL) 
        root = new;  
    else if (new->discipline_code < root->discipline_code) 
        root->left = insert_enrol(root->left, new);  
    else if (new->discipline_code > root->discipline_code) 
        root->right = insert_enrol(root->right, new); 
    else 
        print_error("insert enrol, code already inserted");

    return root;  // Único return
}

void register_enrollment(Enrollment *root, int discipline_code)
{
    Enrollment *new = allocate_enrollment();
    new->discipline_code = discipline_code;

    if(root->discipline_code == 0)
        root = new;
    else
        insert_enrol(root, new);
}

Enrollment *remove_enrollment(Enrollment *root, int discipline_code) 
{
    Enrollment *returnn;

    if (root == NULL) returnn = NULL;

    if (discipline_code < root->discipline_code) 
        root->left = remove_enrollment(root->left, discipline_code);
    else if (discipline_code > root->discipline_code)
        root->right = remove_enrollment(root->right, discipline_code);
    // Se o código da disciplina for encontrado, remover este nó
    else 
    {
        // Caso 1: o nó não tem filhos
        if (root->left == NULL && root->right == NULL) 
        {
            deallocate_enrollment(root);
            return NULL;
        }
        // Caso 2: o nó tem apenas um filho
        else if (root->left == NULL) 
        {
            returnn = root->right;
            deallocate_enrollment(root);
        }
        else if (root->right == NULL) 
        {
            returnn = root->left;
            deallocate_enrollment(root);
        }
        // Caso 3: o nó tem dois filhos
        else 
        {
            // Encontrar o sucessor (menor nó da subárvore da direita)
            Enrollment *temp = root->right;
            while (temp && temp->left != NULL)
                temp = temp->left;

            // Copiar os dados do sucessor para o nó atual
            root->discipline_code = temp->discipline_code;
            // Remover o sucessor
            root->right = remove_enrollment(root->right, temp->discipline_code);
        }
    }

    return returnn;
}

Enrollment *search_enrollment(Enrollment *root, int discipline_code) 
{
    Enrollment *result = NULL;  

    if (root == NULL || root->discipline_code == discipline_code) 
        result = root;
    else if (discipline_code < root->discipline_code) 
        result = search_enrollment(root->left, discipline_code);
    else 
        result = search_enrollment(root->right, discipline_code);

    return result;  
}

void enroll_period(Enrollment *root_enrol, Discipline *root_discipline, int period)
{
    if(root_discipline != NULL)
    {
        if(root_discipline->period == period)
            register_enrollment(root_enrol, root_discipline->discipline_code);

        enroll_period(root_enrol, root_discipline->left, period);
        enroll_period(root_enrol, root_discipline->right, period);
    }
}

// Função para mostrar todas as disciplinas de um determinado curso
void show_all_disciplines(Discipline *root);

// Função para mostrar todas as disciplinas de um determinado período de um curso
void show_disciplines_by_period(Discipline *root, int period);

// Função para mostrar todas as disciplinas que um determinado aluno está matriculado
void show_enrolled_disciplines(Student *student, Enrollment *root);
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enrollment.h"
#include "../error.h"

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
    if(root != NULL)
    {
        if(root->discipline_code < new->discipline_code)
            root = insert_enrol(root->left, new);
        else if(root->discipline_code > new->discipline_code)
            root = insert_enrol(root->right, new);
        else
            print_error("insert enrol, code already inserted");
    }

    return new;
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

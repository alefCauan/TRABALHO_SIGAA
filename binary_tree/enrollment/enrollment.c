#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enrollment.h"
#include "../error.h"
#include "../discipline/discipline.h"

Enrollment *allocate_enrollment() 
{
    Enrollment *new_enrollment = (Enrollment*) malloc(sizeof(Enrollment));
    ASSERT_ALLOC(new_enrollment, "allocate enrollment");

    new_enrollment->discipline_code = 0;
    new_enrollment->left = NULL;
    new_enrollment->right = NULL;

    return new_enrollment;
}

Enrollment_Tree *create_enrollment_tree()
{
    Enrollment_Tree *new = (Enrollment_Tree *)malloc(sizeof(Enrollment_Tree));
    ASSERT_ALLOC(new, "create enrollment tree");

    new->root = NULL;

    return new;
}

void deallocate_enrollment(Enrollment *enrollment) 
{
    if (enrollment != NULL) 
    {
        free(enrollment);
        enrollment = NULL;
    }
}

void deallocate_enrollment_tree(Enrollment *root) 
{
    if (root != NULL) 
    {
        deallocate_enrollment_tree(root->left);
        deallocate_enrollment_tree(root->right);

        deallocate_enrollment(root);
    }
}

Enrollment *search_enrollment(Enrollment *root, int discipline_code) 
{
    Enrollment *result = NULL;  

    if (root != NULL) 
    {
        if(root->discipline_code == discipline_code)
            result = root;
        else if (discipline_code < root->discipline_code) 
            result = search_enrollment(root->left, discipline_code);
        else 
            result = search_enrollment(root->right, discipline_code);
    }

    return result;  
}

bool insert_enrol(Enrollment **root, Enrollment *new)
{
    bool result = true;

    if ((*root) == NULL)
        (*root) = new;  
    else if (new->discipline_code < (*root)->discipline_code) 
        result = insert_enrol(&(*root)->left, new);  
    else if (new->discipline_code > (*root)->discipline_code) 
        result = insert_enrol(&(*root)->right, new);  
    else 
        result = false;

    return root;  
}

void register_enrollment(Enrollment **root, int discipline_code)
{
    Enrollment *new = allocate_enrollment();
    new->discipline_code = discipline_code;

    if (!insert_enrol(root, new))
    {
        RAISE_ERROR("insert enrol, code already inserted"); 
        deallocate_enrollment(new);
    }
}

void remove_case_no_children(Enrollment **head, Enrollment *parent, Enrollment *current)
{
    if (parent == NULL) // Se o nó removido é a raiz
        *head = NULL;
    else if (parent->right == current)
        parent->right = NULL;
    else
        parent->left = NULL;

    free(current);
}

void remove_case_one_child(Enrollment **head, Enrollment *parent, Enrollment *current)
{
    Enrollment *child = (current->left) ? current->left : current->right;

    if (parent == NULL) // Se o nó removido é a raiz
        *head = child;
    else if (parent->right == current)
        parent->right = child;
    else
        parent->left = child;

    deallocate_enrollment(current);
}


void remove_case_two_children(Enrollment *current)
{
    // Encontrar o sucessor (menor valor na subárvore direita)
    Enrollment *successor = current->right;
    Enrollment *successor_parent = current;

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

    deallocate_enrollment(successor);
}

bool remove_enrollment(Enrollment **head, int discipline_code)
{
    Enrollment *current = *head;
    Enrollment *parent;
    parent = NULL;
    bool result = true;

    // Procura o nó a ser removido
    while (current != NULL && current->discipline_code != discipline_code) 
    {
        parent = current;
        if (discipline_code > current->discipline_code)
            current = current->right;
        else
            current = current->left;
    }

    // Se o nó for encontrado
    if (current != NULL)
    {
        if (current->left == NULL && current->right == NULL)
            remove_case_no_children(head, parent, current);
        else if (current->left && current->right)
            remove_case_two_children(current);
        else
            remove_case_one_child(head, parent, current);
    }
    else
        result = false;

    return result;
}



void enroll_period(Enrollment **root_enrol, Discipline *root_discipline, int period)
{
    if(root_discipline != NULL)
    {
        if(root_discipline->period == period)
            register_enrollment(root_enrol, root_discipline->discipline_code);

        enroll_period(root_enrol, root_discipline->left, period);
        enroll_period(root_enrol, root_discipline->right, period);
    }
}

void show_enrolled_disciplines(Enrollment *root, Discipline *disc_root)
{
    if(root != NULL)
    {
        Discipline *show = search_discipline(disc_root, root->discipline_code);

        show_enrolled_disciplines(root->left, disc_root);
        line();
        printf("DISCIPLINE: %s\nCODE: %d\n", show->discipline_name, root->discipline_code);
        line();
        show_enrolled_disciplines(root->right, disc_root);
    }
}
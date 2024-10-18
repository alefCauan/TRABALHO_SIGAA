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

void remove_enrollment(Enrollment **head, int discipline_code)
{
    Enrollment *current; 
    current = *head;
    Enrollment *parent;
    parent = NULL;

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
    if (current != NULL)
    {
        // Caso 1: Nó sem filhos
        if (current->left == NULL && current->right == NULL)
        {
            if (parent == NULL) // Se é a raiz
                *head = NULL;
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

            free(successor);
        }
        // Caso 3: Nó com um filho
        else 
        {
            Enrollment *child = (current->left != NULL) ? 
                current->left : current->right;

            if (parent == NULL) // Se o nó é a raiz
                *head = child;
            else if (parent->right == current)
                parent->right = child;
            else
                parent->left = child;

            free(current);
        }
    }
    else
        RAISE_ERROR("remove enrol, discipline with this code has not found");
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

int is_enrolled_in_discipline(Enrollment *root, int discipline_code) {
    int enrolled = 0;  // Variável que indicará se a disciplina foi encontrada

    // Verificação recursiva na árvore de matrículas
    if (root != NULL) {
        if (root->discipline_code == discipline_code) {
            enrolled = 1;  // Marca que encontrou a disciplina
        }
        // Continua a busca na subárvore esquerda e direita
        int left_result = is_enrolled_in_discipline(root->left, discipline_code);
        int right_result = is_enrolled_in_discipline(root->right, discipline_code);

        // Se encontrar em qualquer lado, marca como encontrado
        if (left_result == 1 || right_result == 1) {
            enrolled = 1;
        }
    }

    return enrolled;  
}

int is_student_enrolled_in_discipline(Student_list *student_list, int discipline_code) {
    Student *current = student_list->first;
    int enrolled = 0;
    // verifica todos os alunos
    while (current != NULL) {
        if (is_enrolled_in_discipline(current->enrol_tree->root, discipline_code)) {
            enrolled = 1; // Se algum aluno estiver matriculado, retorna true
        }
        current = current->next;
    }
    return enrolled; // Nenhum aluno matriculado na disciplina
}

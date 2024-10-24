#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "discipline.h"
#include "../error.h"

Discipline *allocate_discipline() 
{
    Discipline *new_subject = (Discipline*) malloc(sizeof(Discipline));
    ASSERT_ALLOC(new_subject, "allocate discipline\n");
    
    new_subject->height = 1;
    new_subject->discipline_code = 0;
    strcpy(new_subject->discipline_name, "");
    new_subject->period = 0;
    new_subject->workload = 0;
    new_subject->left = NULL;
    new_subject->right = NULL;

    return new_subject;
}

Discipline_tree_avl *create_discipline_tree()
{
    Discipline_tree_avl *new = (Discipline_tree_avl *)malloc(sizeof(Discipline_tree_avl));
    ASSERT_ALLOC(new, "create discipline tree");

    new->root = NULL;

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

bool search_disc_name(Discipline *root, const char *name)
{
    bool result = false; 

    if (root != NULL) 
    {
        if (strcmp(root->discipline_name, name) == 0)
        {
            RAISE_ERROR("input data, name already used in the course");
            result = true;
        }
        else
        {
            result = search_disc_name(root->left, name);
            
            (result) ? 
                result : (result = search_disc_name(root->right, name));
        }
    }

    return result;
}

Discipline *search_discipline(Discipline *root, int code)
{
    Discipline *result = NULL;

    if(root == NULL)
        result = root;
    else if(root->discipline_code == code)
        result = root;
    else if(code < root->discipline_code)
        result = search_discipline(root->left, code);
    else if(code > root->discipline_code)
        result = search_discipline(root->right, code);

    return result;
}

int discipline_height(Discipline *root)
{
    int result = 0;

    if(root)
        result = root->height;

    return result;
}

int discipline_get_balance(Discipline *root)
{
    int result = 0;

    if(root)
        result = discipline_height(root->left) - discipline_height(root->right);

    return result;
}

Discipline *discipline_rotate_right(Discipline *ex_root)
{
    Discipline *new_root = ex_root->left;
    Discipline *leaf = new_root->right;

    new_root->right = ex_root;
    ex_root->left = leaf;

    ex_root->height = 1 + max(discipline_height(ex_root->left), discipline_height(ex_root->right));
    new_root->height = 1 + max(discipline_height(new_root->left), discipline_height(new_root->right));

    return new_root;
}

Discipline *discipline_rotate_left(Discipline *ex_root)
{
    Discipline *new_root = ex_root->right;
    Discipline *leaf = new_root->left;

    new_root->left = ex_root;
    ex_root->right = leaf;

    ex_root->height = 1 + max(discipline_height(ex_root->left), discipline_height(ex_root->right));
    new_root->height = 1 + max(discipline_height(new_root->left), discipline_height(new_root->right));

    return new_root;
}

Discipline *balance_discipline(Discipline *root)
{
    int balance = discipline_get_balance(root);

    // Caso 1: Desbalanceamento para a esquerda
    if (balance > 1)
    {
        // Se o filho direito está desbalanceado para a esquerda, fazer rotação dupla
        if (discipline_get_balance(root->left) < 0)
            root->left = discipline_rotate_left(root->left);

        root = discipline_rotate_right(root);
    }
    // Caso 2: Desbalanceamento para a direita
    else if (balance < -1)
    {
        // Se o filho esquerdo está desbalanceado para a direita, fazer rotação dupla
        if (discipline_get_balance(root->right) > 0)
            root->right = discipline_rotate_right(root->right);

        root = discipline_rotate_left(root);
    }

    // Atualizar a altura após a rotação
    root->height = 1 + max(discipline_height(root->left), discipline_height(root->right));

    return root;
}

bool insert_discipline(Discipline **root, Discipline *new_node) 
{
    bool result = true;

    if (*root == NULL)
        *root = new_node;
    else
    {
        if (new_node->discipline_code < (*root)->discipline_code)
            result = insert_discipline(&(*root)->left, new_node);
        else if (new_node->discipline_code > (*root)->discipline_code)
            result = insert_discipline(&(*root)->right, new_node);
        else
            result = false;

        (*root)->height = 1 + max(discipline_height((*root)->left), discipline_height((*root)->right));
        *root = balance_discipline(*root);
    }

    return result;
}

int get_disc_code(Discipline *root, int course_code)
{
    char str[20];
    srand(time(0));
    int random = 0;

    do {
        random = rand() % 99;
        sprintf(str, "%d%02d", course_code, random); 
    } 
    while(search_discipline(root, atoi(str)));

    return atoi(str); 
}


void register_discipline(Discipline **root, Course *course)
{
    int temp = 0;

    // Aloca memória para um novo curso
    Discipline *new = allocate_discipline();
    ASSERT_ALLOC(new, "register discipline");
    
    do {
        printf("Enter discipline name -> ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", new->discipline_name);
    } 
    while(search_disc_name((*root), new->discipline_name));

    new->discipline_code = GET_DISCIPLINE_CODE(*root, course->course_code);

    do {
        printf("---------- WORKLOAD ----------\n1 - 30 hours\n2 - 60 hours\n3 - 90 hours\n-> ");
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
        line();
        printf("The course %s has %d periods, where the %s discipline will be placed\n-> ",
        course->course_name, course->num_periods, new->discipline_name);
        scanf("%d", &temp);
        printf("\n");
    } 
    while(!valid_answer(1, course->num_periods, temp));

    new->period = temp;

    if(!insert_discipline(root, new))
    {
        RAISE_ERROR("insert discipline, this code already exists");
        deallocate_discipline(new);
    }
}

void remove_discipline_no_children(Discipline **root, Discipline *current, Discipline *parent)
{
    if (parent == NULL) // Se é a raiz
        *root = NULL;
    else if (parent->right == current)
        parent->right = NULL;
    else
        parent->left = NULL;

    deallocate_discipline(current);
}

void remove_discipline_one_child(Discipline **root, Discipline *current, Discipline *parent)
{
    Discipline *child = (current->left != NULL) ? current->left : current->right;

    if (parent == NULL) // Se o nó é a raiz
        *root = child;
    else if (parent->right == current)
        parent->right = child;
    else
        parent->left = child;

    deallocate_discipline(current);
}


void remove_discipline_two_children(Discipline **root, Discipline *current)
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

    deallocate_discipline(successor);
}

// TODO: Verificar todos os alunos e ver se eles estão matriculados nessa disciplina
bool remove_discipline(Discipline **root, Student *head, int discipline_code)
{
    Discipline *current = *root;
    Discipline *parent;
    parent = NULL;
    bool result = true;

    if(is_enrolled_discipline(head, discipline_code))
    {
        ///////////////
        result = false;
    }
    else
    {

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
            // Verifica os casos de remoção
            if (current->left == NULL && current->right == NULL) // Caso 1: Sem filhos
                remove_discipline_no_children(root, current, parent);
            else if (current->left != NULL && current->right != NULL) // Caso 2: Dois filhos
                remove_discipline_two_children(root, current);
            else // Caso 3: Um filho
                remove_discipline_one_child(root, current, parent);

            // Atualiza a altura e balanceia a árvore
            if (*root != NULL)
            {
                (*root)->height = max(discipline_height((*root)->left), discipline_height((*root)->right));
                *root = balance_discipline(*root);
            }
        }
        else
            result = false;
    }

    return result;
}

void show_disciplines(Discipline *root)
{
    if (root != NULL)
    {
        // Mostra as disciplinas em ordem (caminhamento em ordem)
        line();
        printf("NAME: %s\n", root->discipline_name);          
        printf("CODE: %d\n", root->discipline_code);                  
        line();          
        show_disciplines(root->left);      
        show_disciplines(root->right);     
    }
}

// Função para mostrar todas as disciplinas de um determinado período de um curso
void show_disciplines_by_period(Discipline *root, int period)
{
    if(root != NULL)
    {
        show_disciplines_by_period(root->left, period);
        if(root->period == period)
        {
            line();
            printf("NAME:   %s\n", root->discipline_name);          
            printf("CODE:   %d\n", root->discipline_code);                  
            printf("PERIOD: %d\n", root->period);                  
            line();    
        }
        show_disciplines_by_period(root->right, period);
    }
}


// Função auxiliar para verificar se algum aluno está matriculado na disciplina
bool is_enrolled_discipline(Student *head, int discipline_code) 
{
    Student *current_student = head;
    bool result = false;

    // Percorre todos os alunos
    while (current_student != NULL) 
    {
        // Verifica se o aluno está matriculado na disciplina (árvore de matrículas)
        if (search_enrollment(current_student->enrol_tree->root, discipline_code)) 
        {
            RAISE_ERROR("remove discipline, there are students enrolled!");
            result = true; // Aluno encontrado matriculado
        }
        
        // Próximo aluno
        current_student = current_student->next;
    }
    
    return result; // Nenhum aluno encontrado matriculado na disciplina
}
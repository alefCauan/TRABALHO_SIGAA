#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "course.h"
// #include "../subject/subjetc.h"
#include "../error.h"
#include "../discipline/discipline.h"

Course *allocate_course() 
{
    Course *new_course = (Course *) malloc(sizeof(Course));
    ASSERT_ALLOC(new_course, "allocate course");

    if (new_course != NULL) 
    {
        new_course->height = 1;
        new_course->course_code = -1;
        strcpy(new_course->course_name, "");
        new_course->num_periods = 0;
        new_course->discipline_tree = create_discipline_tree(); 
        new_course->left = NULL;
        new_course->right = NULL;
    }
    return new_course;
}

Course_tree_avl *create_course_tree() 
{
    Course_tree_avl *tree = (Course_tree_avl *) malloc(sizeof(Course_tree_avl));
    ASSERT_ALLOC(tree, "create couse tree");

    tree->root = NULL;
    
    return tree;
}

void deallocate_course(Course *course) 
{
    if (course != NULL) 
    {
        // Verifica se a árvore de disciplinas existe antes de desalocar
        if (course->discipline_tree != NULL) 
        {
            deallocate_discipline_tree(course->discipline_tree->root);
            course->discipline_tree = NULL;  
        }
        
        free(course);  
        course = NULL;  
    }
}

void deallocate_course_tree(Course *root) 
{
    if (root != NULL) 
    {
        deallocate_course_tree(root->left);
        deallocate_course_tree(root->right);

        deallocate_course(root);
    }
}

int course_height(Course *root)
{
    int result = 0;

    if(root)
        result = root->height;

    return result;
}

int course_get_balance(Course *root)
{
    int result = 0;

    if(root)
        result = course_height(root->left) - course_height(root->right);

    return result;
}

Course *course_rotate_right(Course *ex_root)
{
    Course *new_root = ex_root->left;
    Course *leaf = new_root->right;

    // Realiza a rotação
    new_root->right = ex_root;
    ex_root->left = leaf;

    // Atualiza as alturas
    ex_root->height = 1 + max(course_height(ex_root->left), course_height(ex_root->right));
    new_root->height = 1 + max(course_height(new_root->left), course_height(new_root->right));

    // Retorna a nova raiz
    return new_root;
}

Course *course_rotate_left(Course *ex_root)
{
    Course *new_root = ex_root->right;
    Course *leaf = new_root->left;

    // Realiza a rotação
    new_root->left = ex_root;
    ex_root->right = leaf;

    // Atualiza as alturas
    ex_root->height = 1 + max(course_height(ex_root->left), course_height(ex_root->right));
    new_root->height = 1 + max(course_height(new_root->left), course_height(new_root->right));

    return new_root;
}

Course *balance_course(Course *root)
{
    int balance = course_get_balance(root);
    Course *result = root;

    if(balance > 1)
    {
        if (course_get_balance(root->right) < 0)
            root->left = course_rotate_left(root->left);

        result = course_rotate_right(root);
    }
    else if(balance < -1)
    {
        if (course_get_balance(root->left) > 0)
            root->right = course_rotate_right(root->right);

        result = course_rotate_left(root);
    }

    return result;
}

bool insert_course(Course **root, Course *new_node) 
{
    bool result = 1;

    if ((*root) == NULL)
        (*root) = new_node;
    else
    {
        if (new_node->course_code < (*root)->course_code)
            result = insert_course(&(*root)->left, new_node);
        else if (new_node->course_code > (*root)->course_code)
            result = insert_course(&(*root)->right, new_node);
        
        (*root)->height = 1 + max(course_height((*root)->left), course_height((*root)->right));

        int balance = course_get_balance((*root));

        balance_course(*root);
    }

    return result;
}

int get_current_year() 
{
    time_t t = time(NULL);         
    struct tm *tm_info = localtime(&t); 

    int year = tm_info->tm_year + 1900; 
    return year;
}

Course *search_course_code(Course *root, int code)
{
    Course *result;
    result = NULL;

    if(root == NULL || root->course_code == code)
        result = root;
    else if(code < root->course_code)
        result = search_course_code(root->left, code);
    else if(code > root->course_code)
        result = search_course_code(root->right, code);

    return result;
}

int get_course_code(Course *root)
{
    char str[20];
    srand(time(0));
    int random = 0;

    do {
        random = rand() % 9999;
        sprintf(str, "%d%04d", get_current_year()%100, random);
    } 
    while(search_course_code(root, atoi(str)));

    return atoi(str); 
}

// bool insert_course(Course **root, Course *new_course) 
// {
//     bool result = true;

//     if (*root == NULL) 
//     {
//         *root = new_course;
//         printf("Course has been registered with code %d!\n", (*root)->course_code);
//     }
//     else if (new_course->course_code < (*root)->course_code) 
//         result = insert_course(&(*root)->left, new_course);
//     else if (new_course->course_code > (*root)->course_code) 
//         result = insert_course(&(*root)->right, new_course);
//     else
//         result = false;

//     return result;
// }


void register_course(Course **root) 
{
    // Aloca memória para um novo curso
    Course *new;
    new = allocate_course();
    ASSERT_ALLOC(new, "register course");

    // Recebe os dados do curso
    new->course_code = GET_COURSE_CODE(*root); 
    
    printf("Enter course name: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", new->course_name); 
    
    do {
        printf("Enter number of periods: ");
        scanf("%d", &new->num_periods);
    } 
    while(!valid_answer(1, 8, new->num_periods));
    
    if (!insert_course(root, new)) 
    {
        RAISE_ERROR("insert course, course with this code already exists");
        deallocate_course(new); 
    }
}

void show_courses(Course *root)
{
    if (root != NULL)
    {
        show_courses(root->left);      
        line();
        printf("Name:    %s\n", root->course_name);
        printf("Code:    %d\n", root->course_code);
        printf("Periods: %d\n", root->num_periods);
        line();
        show_courses(root->right);    
    }
}




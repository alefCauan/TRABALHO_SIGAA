#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"
// #include "../subject/subjetc.h"
#include "../error.h"


Course *allocate_course() 
{
    Course *new_course = (Course*) malloc(sizeof(Course));
    check_allocation(new_course, "allocate course");

    if (new_course != NULL) 
    {
        new_course->course_code = -1;
        strcpy(new_course->course_name, "");
        new_course->num_periods = 0;
        new_course->subject_tree = NULL; // TODO: ALLOC TREE
        new_course->left = NULL;
        new_course->right = NULL;
    }
    return new_course;
}

CourseTree *create_course_tree() 
{
    CourseTree *tree = (CourseTree*) malloc(sizeof(CourseTree));
    check_allocation(tree, "create couse tree");

    tree->root = allocate_course();
    
    return tree;
}

void deallocate_course(Course *course) 
{
    if (course != NULL) {
        // Desalocar árvore de disciplinas, se necessário
        free(course);
    }
}

void deallocate_course_tree(CourseTree *tree) 
{
    if (tree != NULL) {
        // Desalocar árvore de cursos, se necessário
        free(tree);
    }
}

void printf_course(Course course)
{
    printf("Name:    %s\n", course.course_name);
    printf("Code:    %d\n", course.course_code);
    printf("Periods: %d\n", course.num_periods);
}

Course *insert_course(Course *root, Course *new_course) 
{
    // Se a árvore estiver vazia, o novo curso se torna a raiz
    if (root == NULL) 
        return new_course;


    // Compara o código do curso para posicioná-lo corretamente na árvore
    if (new_course->course_code < root->course_code) 
        root->left = insert_course(root->left, new_course);
    else if (new_course->course_code > root->course_code) 
        root->right = insert_course(root->right, new_course);
    else
        printf("Course with code %d already exists!\n", root->course_code);
    
    return root;
}

void register_course(Course **root) 
{
    // Aloca memória para um novo curso
    Course *new = allocate_course();
    check_allocation(new, "register course");

    // Recebe os dados do curso
    printf("Enter course code: ");
    scanf("%d", &new->course_code);
    // new->course_code == GET_CODE(); 
    
    printf("Enter course name: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", new->course_name); 
    
    do {
        printf("Enter number of periods: ");
        scanf("%d", &new->num_periods);
    } 
    while(!valid_answer(1, 12, new->num_periods));
    
    // TODO: add discipline tree 

    // Insere o curso na árvore de cursos
    (root == NULL) ? insert_course(*root, new) : (*root = new);
    
    printf("Course successfully registered!\n");
}

void show_courses(Course *root)
{
    // print_error("show_course, root value invalid or not allocated");
    if (root == NULL)
        return;

    // Mostra os cursos em ordem (caminhamento em ordem)
    show_courses(root->left);      // Primeiro mostra a subárvore da esquerda
    if(root->course_code != -1) printf_course(*root);          // Mostra o curso atual
    show_courses(root->right);     // Mostra a subárvore da direita
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"
// #include "../subject/subjetc.h"


Course *allocate_course() 
{
    Course *new_course = (Course*) malloc(sizeof(Course));
    if (new_course != NULL) 
    {
        new_course->course_code = -1;
        strcpy(new_course->course_name, "");
        new_course->num_periods = 0;
        new_course->subject_tree = NULL;
        new_course->left = NULL;
        new_course->right = NULL;
    }
    return new_course;
}

CourseTree *create_course_tree() 
{
    CourseTree *tree = (CourseTree*) malloc(sizeof(CourseTree));
    
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

// Função que retorna um número incrementado a cada chamada
int get_code() 
{
    static int code_number = 0; // Variável estática para manter o estado
    return code_number++;
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
        printf("Course with code %d already exists!\n", new_course->course_code);
    
    return root;
}

void register_course(Course **root) 
{
    // Aloca memória para um novo curso
    Course *new = allocate_course();
    
    // Recebe os dados do curso
    printf("Enter course code: ");
    scanf("%d", &new->course_code);
    
    printf("Enter course name: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", new->course_name); 
    
    printf("Enter number of periods: ");
    scanf("%d", &new->num_periods);
    
    // Insere o curso na árvore de cursos
    *root = insert_course(*root, new);
    
    printf("Course successfully registered!\n");
}

void show_courses(Course *root)
{
    if (root == NULL)
        return;

    // Mostra os cursos em ordem (caminhamento em ordem)
    show_courses(root->left);      // Primeiro mostra a subárvore da esquerda
    if(root->course_code != -1) printf_course(*root);          // Mostra o curso atual
    show_courses(root->right);     // Mostra a subárvore da direita
}




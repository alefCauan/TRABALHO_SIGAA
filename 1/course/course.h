#ifndef COURSE_H
#define COURSE_H

// #include "../subject/subjetc.h"
// Definindo a macro para obter o número de registro
typedef struct Discipline Discipline;
typedef struct Discipline_Tree Discipline_Tree;

typedef struct Course {
    int course_code;
    char course_name[50];
    int num_periods;
    Discipline_Tree *tree;
    struct Course *left;
    struct Course *right; 
} Course;
// raiz de Course 
typedef struct CourseTree {
    Course *root;
} CourseTree;

// aloca memoria para a stuct course
Course *allocate_course();
// aloca memoria para a raiz da stuct course
CourseTree *create_course_tree();
// desaloca 1 elemento de course
void deallocate_course(Course *course);
// desaloca todos os elementos da arvore
void deallocate_course_tree(CourseTree *tree);

// auxiliar de register course
Course *insert_course(Course *root, Course *new_course);
// adiciona um novo curso na arvore
void register_course(Course **root); 
// mostra todos os cursos
void show_courses(Course *root);

#endif
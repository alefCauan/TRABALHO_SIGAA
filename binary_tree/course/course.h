#ifndef COURSE_H
#define COURSE_H

// predefinição
typedef struct Discipline Discipline;
typedef struct Discipline_Tree Discipline_Tree;

#define GET_COURSE_CODE(root) (get_course_code(root))

typedef struct Course {
    int course_code;
    char course_name[50];
    int num_periods;
    Discipline_Tree *discipline_tree;
    struct Course *left;
    struct Course *right; 
} Course;
// raiz de Course 
typedef struct Course_tree {
    Course *root;
} Course_tree;

// aloca memoria para a stuct course
Course *allocate_course();
// aloca memoria para a raiz da stuct course
Course_tree *create_course_tree();
// desaloca 1 elemento de course
void deallocate_course(Course *course);
// desaloca todos os elementos da arvore
void deallocate_course_tree(Course *root);
// retorna o ano atual
int get_current_year();
// busca o codigo de curso e retorna o curso com aquele codigo
Course *search_course_code(Course *root, int code);
// retorna um novo codigo de curso
int get_course_code(Course *root);
// auxiliar de register course
Course *insert_course(Course *root, Course *new_course);
// adiciona um novo curso na arvore
void register_course(Course **root); 
// mostra todos os cursos
void show_courses(Course *root);

#endif
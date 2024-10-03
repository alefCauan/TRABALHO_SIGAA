#ifndef COURSE_H
#define COURSE_H

#include <stdbool.h>

// predefinição
typedef struct Discipline Discipline;
typedef struct Discipline_tree_avl Discipline_tree_avl;

#define GET_COURSE_CODE(root) (get_course_code(root))

typedef struct Course {
    int course_code;
    int height;
    char course_name[50];
    int num_periods;
    Discipline_tree_avl *discipline_tree;
    struct Course *left;
    struct Course *right; 
} Course;
// raiz de Course 
typedef struct Course_tree_avl {
    Course *root;
} Course_tree_avl;

// aloca memoria para a stuct course
Course *allocate_course();
// aloca memoria para a raiz da stuct course
Course_tree_avl *create_course_tree();
// desaloca 1 elemento de course
void deallocate_course(Course *course);
// desaloca todos os elementos da arvore
void deallocate_course_tree(Course *root);


int course_height(Course *root);

int course_get_balance(Course *root);

Course *course_rotate_right(Course *ex_root);

Course *course_rotate_left(Course *ex_root);

Course *balance_course(Course *root);

// retorna o ano atual
int get_current_year();
// busca o codigo de curso e retorna o curso com aquele codigo
Course *search_course_code(Course *root, int code);
// retorna um novo codigo de curso
int get_course_code(Course *root);

// ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
// as disciplinas para permitir o cadastro do curso.
// {

// insere o novo curso na arvore de curso
bool insert_course(Course **root, Course *new_node);
// pega os dados do novo curso e chama a inserção
void register_course(Course **root); 
// mostra todos os cursos

// }

// vii) Mostrar todos os cursos do Campus.
// {

// mostra todos os cursos cadastrados na arvore
void show_courses(Course *root);

// }

#endif
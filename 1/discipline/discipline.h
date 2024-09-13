#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include "../course/course.h"
// gera um codigo da disciplina 
#define GET_DISCIPLINE_CODE() (get_code() + 1)

// enum para a carga horaria 
typedef enum {
    HOURS_30 = 30,
    HOURS_60 = 60,
    HOURS_90 = 90
}Workload;

// struct disciplina
typedef struct Discipline {
    int     discipline_code;        // codigo da disciplina
    char    discipline_name[50];   // nome da disciplina
    int     period;                 // periodo dessa disciplina
    int     workload;               // carga horaria 
    struct  Discipline *left;   
    struct  Discipline *right;  
} Discipline;

typedef struct Discipline_Tree {
    Discipline *root;
} Discipline_Tree;

// aloca a arvore de disciplinas
Discipline *allocate_discipline();
// aloca a raiz da arvore de disciplinas
Discipline_Tree *create_discipline_tree();
// desaloca um node da arvore de disciplinas 
void deallocate_discipline(Discipline *discipline);
// desaloca toda a arvore de disciplinas 
void deallocate_discipline_tree(Discipline_Tree *root);
// busca uma disciplina com um certo codigo e a retorna se encontrar 
Discipline *search_discipline(Discipline *root, int code);
// auxilir de show disciplines 
void printf_discipline(Discipline discipline);
// Função que retorna um codigo de disciplina 
int get_code();
// auxiliar de regirter discipline 
Discipline *insert_discipline(Discipline *root, Discipline *new_discipline);
// função de adicionar disciplinas 
void register_discipline(Discipline **root, Course *course);
// remove uma disciplina escolhida do curso 
void remove_discipline(Course *course, int discipline_code);
// mostra todas as disciplinas 
void show_disciplines(Discipline *root);

#endif
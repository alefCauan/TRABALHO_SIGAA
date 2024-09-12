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
    char    discipline_name[100];   // nome da disciplina
    int     period;                 // periodo dessa disciplina
    int     workload;               // carga horaria 
    struct  Discipline *left;   
    struct  Discipline *right;  
} Discipline;

typedef struct Discipline_Tree {
    Discipline *root;
} Discipline_Tree;

Discipline *allocate_discipline();
Discipline_Tree *create_discipline_tree();
void deallocate_discipline(Discipline *discipline);
void deallocate_discipline_tree(Discipline_Tree *root);
void printf_discipline(Discipline discipline);
// Função que retorna um número incrementado a cada chamada
int get_code();

Discipline *insert_discipline(Discipline *root, Discipline *new_discipline);
void register_discipline(Discipline **root, Course *course);
void remove_discipline(Course *course, int discipline_code);
void show_disciplines(Discipline *root);

#endif
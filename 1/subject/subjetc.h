#ifndef SUBJETC_H
#define SUBJETC_H

#include "../course/course.h"
#define GET_SUBJECT_CODE() (get_code() + 1)

typedef enum {
    HOURS_30 = 30,
    HOURS_60 = 60,
    HOURS_90 = 90
}Workload;
// struct disciplina
typedef struct Subject {
    int     subject_code;       // codigo da disciplina
    char    subject_name[100];  // nome da disciplina
    int     period;             // periodo dessa disciplina
    int     workload;           // carga horaria 
    struct  Subject *left;   
    struct  Subject *right;  
} Subject;

typedef struct Subject_Tree {
    Subject *root;
} Subject_Tree;


Subject *allocate_subject();
Subject_Tree *create_subject_tree();
void deallocate_subject(Subject *subject);
void deallocate_subject_tree(Subject_Tree *root);
void printf_subject(Subject subject);
// Função que retorna um número incrementado a cada chamada
int get_code();

Subject *insert_discipline(Subject *root, Subject *new_subject);
void register_subject(Subject **root, Course *course);
void remove_subject(Course *course, int subject_code);
void show_subjects(Subject *root);

#endif
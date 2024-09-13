#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "../student/student.h"
#include <stdbool.h>

// struct de matricula
typedef struct Enrollment {
    int discipline_code;
    struct Enrollment *left; 
    struct Enrollment *right; 
} Enrollment;

typedef struct Enrollment_Tree {
    Enrollment *root;
} Enrollment_Tree;


Enrollment *allocate_enrollment();
Enrollment_Tree *create_enrollment_tree();
void deallocate_enrollment(Enrollment *enrollment);
void deallocate_enrollment_tree(Enrollment_Tree *root);
// matricula o aluno em um perido 
void enroll_period(Enrollment *root_enrol, Discipline *root_discipline, int period);
Enrollment *insert_enrol(Enrollment *root, Enrollment *new);
void register_enrollment(Enrollment *root, int discipline_code);
Enrollment *remove_enrollment(Enrollment *root, int discipline_code);
Enrollment  *search_enrollment(Enrollment *root, int discipline_code);
// Função para mostrar todas as disciplinas de um determinado curso
void show_all_disciplines(Discipline *root);
// Função para mostrar todas as disciplinas de um determinado período de um curso
void show_disciplines_by_period(Discipline *root, int period);
// Função para mostrar todas as disciplinas que um determinado aluno está matriculado
void show_enrolled_disciplines(Student *student, Enrollment *root);


#endif
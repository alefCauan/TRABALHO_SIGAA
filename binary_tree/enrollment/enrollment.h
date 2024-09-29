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


// Aloca memória para uma nova matrícula e inicializa os campos necessários
Enrollment *allocate_enrollment();
// Cria uma nova árvore de matrículas para um aluno
Enrollment_Tree *create_enrollment_tree();
// Libera a memória de uma matrícula específica
void deallocate_enrollment(Enrollment *enrollment);
// Libera a memória da árvore de matrículas inteira
void deallocate_enrollment_tree(Enrollment *root);
// Matricula o aluno em todas as disciplinas de um determinado período
void enroll_period(Enrollment **root_enrol, Discipline *root_discipline, int period);
// Insere uma nova matrícula na árvore de matrículas
Enrollment *insert_enrol(Enrollment *root, Enrollment *new);
// Registra uma nova matrícula para um aluno com base no código da disciplina
void register_enrollment(Enrollment **root, int discipline_code);
// Remove uma matrícula específica da árvore de matrículas
void remove_enrollment(Enrollment **head, int discipline_code);
// Busca uma matrícula específica na árvore com base no código da disciplina
Enrollment *search_enrollment(Enrollment *root, int discipline_code);
// Mostra todas as disciplinas nas quais um aluno está matriculado
void show_enrolled_disciplines(Enrollment *root, Discipline *disc_root);


#endif
#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "../student/student.h"
#include <stdbool.h>

// struct de matricula
typedef struct Enrollment {
    int height;
    int discipline_code;
    struct Enrollment *left; 
    struct Enrollment *right; 
} Enrollment;

typedef struct Enrollment_tree_avl {
    Enrollment *root;
} Enrollment_tree_avl;


// Aloca memória para uma nova matrícula e inicializa os campos necessários
Enrollment *allocate_enrollment();
// Cria uma nova árvore de matrículas para um aluno
Enrollment_tree_avl *create_enrollment_tree();
// Libera a memória de uma matrícula específica
void deallocate_enrollment(Enrollment *enrollment);
// Libera a memória da árvore de matrículas inteira
void deallocate_enrollment_tree(Enrollment *root);
// Matricula o aluno em todas as disciplinas de um determinado período
void enroll_period(Enrollment **root_enrol, Discipline *root_discipline, int period);

int enrollment_height(Enrollment *root);

int enrollment_get_balance(Enrollment *root);

Enrollment *enrollment_rotate_right(Enrollment *ex_root);

Enrollment *enrollment_rotate_left(Enrollment *ex_root);

Enrollment *balance_enroll(Enrollment *root);

// iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
// uma disciplina do curso do aluno.
// {

// Insere uma nova matrícula na árvore de matrículas
bool insert_enrol(Enrollment **root, Enrollment *new_node);
// Registra uma nova matrícula para um aluno com base no código da disciplina
void register_enrollment(Enrollment **root, int discipline_code);

// }

// Busca uma matrícula específica na árvore com base no código da disciplina
Enrollment *search_enrollment(Enrollment *root, int discipline_code);

// x) Mostrar todas as disciplinas que um determinado aluno está matriculado
// {

// Mostra todas as disciplinas nas quais um aluno está matriculado
void show_enrolled_disciplines(Enrollment *root, Discipline *disc_root);

// }

void remove_case_no_children(Enrollment **head, Enrollment *parent, Enrollment *current);

void remove_case_one_child(Enrollment **head, Enrollment *parent, Enrollment *current);

void remove_case_two_children(Enrollment *current);

// xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno.
// {

// Remove uma matrícula específica da árvore de matrículas
bool remove_enrollment(Enrollment **head, int discipline_code);

// }

#endif
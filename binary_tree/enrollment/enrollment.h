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
// Percorre a lista verficando se os alunos estão matriculados
int is_student_enrolled_in_discipline(Student_list *student_list, int discipline_code);
// Verifica se o aluno esta matriculado na disciplina
int is_enrolled_in_discipline(Enrollment *root, int discipline_code);


// iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
// uma disciplina do curso do aluno.
// {

// Insere uma nova matrícula na árvore de matrículas
bool insert_enrol(Enrollment **root, Enrollment *new);
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

// xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno.
// {

// Remove uma matrícula específica da árvore de matrículas
void remove_enrollment(Enrollment **head, int discipline_code);

// }


#endif
#ifndef STUDENT_H
#define STUDENT_H

#include "../course/course.h"
typedef struct Enrollment Enrollment;
typedef struct Enrollment_Tree Enrollment_Tree;

#define GET_REGISTRATION(code) (get_registration(code))

// struct de notas
typedef struct Grade {
    int discipline_code;
    int semester;
    float final_grade;
    struct Grade *left;
    struct Grade *right;
} Grade;

typedef struct Grade_Tree {
   Grade *root;
} Grade_Tree;
// struct de estudante
typedef struct Student {
    int registration;
    char name[50];
    int course_code;
    Grade_Tree *grade_tree;
    Enrollment_Tree *enrol_tree;
    struct Student *next;
} Student;
// raiz de student
typedef struct Student_list {
    Student *first;
} Student_list;

// aloca a arvore de notas 
Grade *allocate_grade();
// aloca a arvore de estudante 
Student *allocate_student();
// aloca o root da arvore de estudante 
Student_list *create_student_list();
// desaloca um node de notas 
void deallocate_grade(Grade *grade);
// desaloca um node de estudante 
void deallocate_student(Student *student);
// desaloca toda a lista de estudantes 
void deallocate_student_list(Student_list *list);
// gerar a matricula do aluno
int get_registration(int course_code);
// retorna um node de grade que possui um codigo de disciplina especifico, se houver
Grade *search_grade(Grade *root, int discipline_code);
// busca estudante pela matricula
Student *search_student_by_registration(Student *first, int registration);

// i) Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que
// já tenha sido cadastrado na árvore de curso
// {

// insere o estudante na lista de estudantes do curso
void insert_student(Student_list **list, Student *new_student);
// pega os dados do novo estudante e chama a inserção 
void register_student(Student_list *list, Course *courses);

// }

// v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
// matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
// árvore de notas.
// {

// realiza a inserção do novo nó de notas na arvore
bool insert_grade(Grade **root, Grade *new);
// pega os dados referente a nota do aluno e chama a inserção
void register_grade(Student **student);

// }

// vi) Mostrar todos os alunos de um determinado curso.
// {

// mostra todos os estudantes de um curso especifico
void show_students_by_course(Student_list *list, int course_code);

// }

// xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.
// {

// mostra a nota de uma disciplina de um aluno
void show_grades(Student *student, Discipline *root, int period);

// }

// xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
// disciplina.
// {

// mostrar as notas de disciplinas de um aluno no periodo
void show_period_grade(Student *student, Discipline *discipline);

// }

// xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
// nota organizadas pelo período que a disciplina está cadastrada no curso.
// {

// Mostrar o histórico de um determinado aluno, organizadas
// pelo período que a disciplina está cadastrada no curso.
void show_history(Student *student, Discipline *root, int period);

// }

#endif
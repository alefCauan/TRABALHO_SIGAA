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
Student *search_student_by_registration(Student *first, int registration);
// auxiliar de regirster grade
Grade *insert_grade(Grade **root, Grade *new);
// adiciona notas de estudantes 
void register_grade(Student **student);
// adiciona um novo estudante na lista de estudantes 
void register_student(Student_list *list, Course *courses);
// mostra todos os estudantes de um curso especifico
void show_students_by_course(Student_list *list, int course_code);
// mostra a nota de uma disciplina de um aluno
void show_grades(Student *student, Discipline *root, int period);
// mostrar as notas de disciplinas de um aluno no periodo
void show_period_grade(Student *student, Discipline *discipline);
// Mostrar o histórico de um determinado aluno, organizadas
// pelo período que a disciplina está cadastrada no curso.
void show_history(Student *student, Discipline *root, int period);

#endif
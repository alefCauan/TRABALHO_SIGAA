#ifndef STUDENT_H
#define STUDENT_H

#include "../course/course.h"
typedef struct Enrollment Enrollment;
typedef struct Enrollment_Tree Enrollment_Tree;

// struct de notas
typedef struct Grade {
    int subject_code;
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
    int code;
    Grade_Tree *grade_tree;
    Enrollment_Tree *enrol_tree;
    struct Student *next;
} Student;
// raiz de student
typedef struct StudentList {
    Student *first;
} StudentList;

// aloca a arvore de notas 
Grade *allocate_grade();
// aloca a arvore de estudante 
Student *allocate_student();
// aloca o root da arvore de estudante 
StudentList *create_student_list();

// desaloca um node de notas 
void deallocate_grade(Grade *grade);
// desaloca um node de estudante 
void deallocate_student(Student *student);
// desaloca toda a lista de estudantes 
void deallocate_student_list(StudentList *list);
// auxilir de show students 
void printf_student(Student student);
// adiciona um novo estudante na lista de estudantes 
void register_student(StudentList *list);
// mostra todos os estudantes de um curso especifico
void show_students_by_course(StudentList *list, int course_code);
// adiciona notas de estudantes 
void register_grade(Student *student, int subject_code, int semester, float final_grade);
// mostra a nota de uma disciplina de um aluno
void show_grade(Student *student);
// mostrar as notas de disciplinas de um aluno no periodo
void show_period_grades(Student *student);
// Mostrar o histórico de um determinado aluno, organizadas
// pelo período que a disciplina está cadastrada no curso.
void show_history(Student *student);

#endif
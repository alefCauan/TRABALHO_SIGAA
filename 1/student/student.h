#ifndef STUDENT_H
#define STUDENT_H

#include "../course/course.h"
typedef struct Enrollment Enrollment;

// struct de notas
typedef struct Grade {
    int subject_code;
    int semester;
    float final_grade;
    struct Grade *left;
    struct Grade *right;
} Grade;

// struct de estudante
typedef struct Student {
    int registration;
    char name[100];
    int code;
    Grade *grade_tree;
    Enrollment *enrollment_tree;
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

#endif
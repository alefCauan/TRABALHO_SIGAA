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


Grade *allocate_grade();
Student *allocate_student();
StudentList *create_student_list();

void deallocate_grade(Grade *grade);
void deallocate_student(Student *student);
void deallocate_student_list(StudentList *list);
void printf_student(Student student);
// Função que retorna um número incrementado a cada chamada
void register_student(StudentList *list);
void show_students_by_course(StudentList *list, int course_code);
void register_grade(Student *student, int subject_code, int semester, float final_grade);

#endif
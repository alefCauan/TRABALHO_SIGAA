#ifndef STUDENT_H
#define STUDENT_H

// #include "../enrollment/enrollment.h"
#include "../course/course.h"

// Definindo a macro para obter o número de registro
#define GET_REGISTRATION() (get_registration())

// struct de notas
typedef struct Grade {
    int subject_code;
    int semester;
    float final_grade;
    struct Grade *left;
    struct Grade *right;
} Grade;

// struct de estudante
typedef struct Student Student;
// raiz de student
typedef struct StudentList StudentList;


Grade *allocate_grade();

Student *allocate_student();

StudentList *create_student_list();

void deallocate_grade(Grade *grade);

void deallocate_student(Student *student);

void deallocate_student_list(StudentList *list);

void printf_student(Student student);
// Função que retorna um número incrementado a cada chamada
int get_registration();
void register_student(StudentList *list);
void show_students_by_course(StudentList *list, Course_code course_code);

#endif
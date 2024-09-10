#ifndef STUDENT_H
#define STUDENT_H

// #include "../enrollment/enrollment.h"
#include "../course/course.h"

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

void register_student(StudentList *list, int registration, char name[], int course_code, CourseTree *courses);
void show_students_by_course(StudentList *list, int course_code);

#endif
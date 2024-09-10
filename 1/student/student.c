#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student *allocate_student() 
{
    Student *new_student = (Student*) malloc(sizeof(Student));
    if (new_student != NULL) 
    {
        new_student->registration = 0;
        strcpy(new_student->name, "");
        new_student->course_code = 0;
        new_student->grade_tree = NULL;
        new_student->enrollment_tree = NULL;
        new_student->next = NULL;
    }
    return new_student;
}

StudentList *create_student_list() 
{
    StudentList *list = (StudentList*) malloc(sizeof(StudentList));
    if (list != NULL) {
        list->first = NULL;
    }
    return list;
}

Grade *allocate_grade() 
{
    Grade *new_grade = (Grade*) malloc(sizeof(Grade));
    if (new_grade != NULL) {
        new_grade->subject_code = 0;
        new_grade->semester = 0;
        new_grade->final_grade = 0.0;
        new_grade->left = NULL;
        new_grade->right = NULL;
    }
    return new_grade;
}

void deallocate_grade(Grade *grade) 
{
    if (grade != NULL) {
        free(grade);
    }
}


void deallocate_student(Student *student) 
{
    if (student != NULL) {
        // Desalocar árvore de notas e árvore de matrículas, se necessário
        free(student);
    }
}

void deallocate_student_list(StudentList *list) 
{
    if (list != NULL) 
    {
        // Desalocar cada estudante individualmente
        Student *current = list->first;
        Student *next;
        while (current != NULL) {
            next = current->next;
            deallocate_student(current);
            current = next;
        }
        free(list);
    }
}


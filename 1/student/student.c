#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "../enrollment/enrollment.h"
#include "../course/course.h"
#include "../error.h"

Grade *allocate_grade() 
{
    Grade *new_grade = (Grade*) malloc(sizeof(Grade));
    check_allocation(new_grade, "allocate grade");

    if (new_grade != NULL) 
    {
        new_grade->subject_code = 0;
        new_grade->semester = 0;
        new_grade->final_grade = 0.0;
        new_grade->left = NULL;
        new_grade->right = NULL;
    }
    return new_grade;
}

Student *allocate_student() 
{
    Student *new_student = (Student*) malloc(sizeof(Student));
    check_allocation(new_student, "student node");

    if (new_student != NULL) 
    {
        new_student->registration = 0;
        strcpy(new_student->name, "");
        new_student->code = 0;
        new_student->code = 0;
        new_student->grade_tree = allocate_grade();
        new_student->enrollment_tree = NULL;
        new_student->next = NULL;
    }
    return new_student;
}

StudentList *create_student_list() 
{
    StudentList *list = (StudentList*) malloc(sizeof(StudentList));
    check_allocation(list, "create student");

    list->first = allocate_student();
    
    return list;
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
        if(student->grade_tree->semester != 0)
            deallocate_grade(student->grade_tree);
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

void printf_student(Student student)
{
    // TODO: more information
    printf("%s\n", student.name);
    printf("%d\n", student.code);
    printf("%04d\n", student.registration);
}

// Função que retorna um número incrementado a cada chamada
int get_registration() 
{
    static int registration_number = 0; // Variável estática para manter o estado
    return registration_number++;
}

void register_student(StudentList *list)
{
    char temp[100];
    int code;
    if(!CHECK_ALL_TRUE(list, list->first))
    {
        print_error("register_student, Studentlist not valid or allocate");
        return;
    }
    
    Student *new = allocate_student(), *aux;

    // TODO: new->enrollment_tree;
    // TODO: new->grade_tree;

    setbuf(stdin, NULL);
    scanf("%[^\n]", temp);
    strcpy(new->name, temp);
    new->code = 1; // TODO: new->code_course();
    new->registration = GET_REGISTRATION();

    if(list->first->code == 0)
        list->first = new;
    else
    {
        aux = list->first;
        while(aux->next)
            aux = aux->next;

        aux->next = new;
    }
}

void show_students_by_course(StudentList *list, int course_code)
{
    if(!CHECK_ALL_TRUE(list))
    {
        print_error("show_students_by_course, Studentlist not valid or allocate");
        return;
    }

    Student *aux = list->first;

    while(aux)
    {
        if(aux->code == course_code)
            printf_student(*aux);

        aux = aux->next;
    }
    
}



#include <stdio.h>
#include <stdlib.h>
#include "sigaa.h"
#include "course/course.h"
#include "error.h"
#include "discipline/discipline.h"
#include "enrollment/enrollment.h"

// i) Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que
// já tenha sido cadastrado na árvore de cursos.[OK]
// ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
// as disciplinas para permitir o cadastro do curso.[OK]
// iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
// seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
// disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
// horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90.[]
// iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
// uma disciplina do curso do aluno.[]
// v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
// matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
// árvore de notas.[]
// vi) Mostrar todos os alunos de um determinado curso.[OK]
// vii)Mostrar todos os cursos do Campus.[OK]
// viii)Mostrar todas as disciplinas de um determinado curso.[]
// ix) Mostrar todas as disciplinas de um determinado período de um curso.[]
// x) Mostrar todas as disciplinas que um determinado aluno está matriculado[]
// xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.[]
// xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
// disciplina.[]
// xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
// mesma.[]
// xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno.[]
// xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
// nota organizadas pelo período que a disciplina está cadastrada no curso.[] 


int main() 
{
    Course_tree *course_tree = create_course_tree();
    Student_list *student_list = create_student_list();

    main_menu(course_tree, student_list);

    deallocate_course_tree(course_tree->root);
    free(course_tree);
    deallocate_student_list(student_list);
    return 0;
}

void main_menu(Course_tree *course_tree, Student_list *student_list) 
{
    int option;
    do {
        printf("\n---- MAIN MENU ----\n");
        printf("1 - Manage Courses\n");
        printf("2 - Manage Students\n");
        printf("3 - Exit\n");
        printf("Enter choice -> ");
        scanf("%d", &option);

        switch (option) 
        {
            case 1: 
                course_menu(course_tree, student_list); 
                break;
            case 2: 
                int course_code;

                printf("Enter course code -> ");
                scanf("%d", &course_code);

                Course *course = search_course_code(course_tree->root, course_code);

                if (course) 
                    student_menu(student_list, course); 
                else 
                    RAISE_ERROR("input data, course not found!");
                break;
            case 3: 
                printf("\nExiting...\n"); 
                break;
            default: break;
        }
    } 
    while(!valid_answer(1, 3, option) || option != 3);
}

void course_menu(Course_tree *course_tree, Student_list *student_list) 
{
    int option;
    do {
        printf("\n---- COURSE MENU ----\n");
        printf("1 - Register a Course\n");
        printf("2 - Show All Courses\n");
        printf("3 - Manage Disciplines\n");
        printf("4 - Back to Main Menu\n");
        printf("Enter choice -> ");
        scanf("%d", &option);

        switch (option) 
        {
            case 1: 
                register_course(&course_tree->root); 
                break;
            case 2: 
                show_courses(course_tree->root); 
                break;
            case 3: 
                int course_code;

                printf("Enter course code -> ");
                scanf("%d", &course_code);

                Course *course = search_course_code(course_tree->root, course_code);

                if (course) 
                    discipline_menu(course, student_list);
                else 
                    RAISE_ERROR("input data, course not found!");

                break;
            case 4: 
                printf("\nReturning to Main Menu...\n"); 
                break;
            default: break;
        }
    } 
    while(!valid_answer(1, 4, option) || option != 4);
}

void discipline_menu(Course *course, Student_list *Student_list) 
{
    int option;
    do {
        printf("\n---- DISCIPLINE MENU ----\n");
        printf("1 - Register a Discipline\n");
        printf("2 - Show All Disciplines\n");
        printf("3 - Remove a Discipline\n");
        printf("4 - Show Disciplines by Period\n");
        printf("5 - Back to Course Menu\n");
        printf("Enter choice -> ");
        scanf("%d", &option);

        switch (option) 
        {
            case 1:
                register_discipline(&course->discipline_tree->root, course); 
                break;
            case 2:
                show_disciplines(course->discipline_tree->root); 
                break;
            case 3: 
                int discipline_code;

                printf("Enter discipline code to remove -> ");
                scanf("%d", &discipline_code);

                if (is_student_enrolled_in_discipline(Student_list, discipline_code))
                    RAISE_ERROR("Has a student enrolled in this dicipline");
                else
                remove_discipline(&course->discipline_tree->root, discipline_code);

                break;
            case 4: 
                int period;

                printf("Enter period -> ");
                scanf("%d", &period);

                show_disciplines_by_period(course->discipline_tree->root, period);
                break;
            case 5: 
                printf("Returning to Course Menu...\n"); 
                break;
            default: break;
        }
    } 
    while(!valid_answer(1, 5, option) || option != 5);
}

void student_menu(Student_list *student_list, Course *course) 
{
    int option;
    do {
        printf("\n---- STUDENT MENU ----\n");
        printf("1. Register a Student\n");
        printf("2. Show Students by Course\n");
        printf("3. Register Grades\n");
        printf("4. Show Student Grades\n");
        printf("5. Show Enrollment History\n");
        printf("6. Show Student enrollment\n");
        printf("7. Enroll period\n");
        printf("8. Back to Main Menu\n");
        printf("Enter choice -> ");
        scanf("%d", &option);

        switch (option) 
        {
            case 1:
                register_student(student_list, course);
                break;
            case 2: 

                show_students_by_course(student_list, course->course_code);
                break;
            case 3: 
            {
                int registration;

                printf("Enter student registration -> ");
                scanf("%d", &registration);

                Student *student = search_student_by_registration(student_list->first, registration);

                if (student) 
                    register_grade(&student);
                else 
                    RAISE_ERROR("input data, student not found!");

                break;
            }
            case 4: 
            {
                int registration, period;

                printf("Enter student registration -> ");
                scanf("%d", &registration);

                Student *student = search_student_by_registration(student_list->first, registration);

                if (student) 
                {
                    printf("enter enrollment period -> ");
                    scanf("%d", &period);

                    show_grades(student, course->discipline_tree->root, period);
                } 
                else 
                    RAISE_ERROR("input data, student not found!");
                
                break;
            }
            case 5: 
            {
                int registration;

                printf("Enter student registration -> ");
                scanf("%d", &registration);

                Student *student = search_student_by_registration(student_list->first, registration);

                if (student) 
                {
                    /////////////////////////////////////////////
                    for(int i = 1; i <= course->num_periods; i++)
                        show_history(student, course->discipline_tree->root, i);
                } 
                else 
                    RAISE_ERROR("input data, student not found!");
                break;
            }
            case 6: 
            {
                int registration = 0;

                printf("Enter student registration -> ");
                scanf("%d", &registration);

                Student *student = search_student_by_registration(student_list->first, registration);

                if(student)
                    show_enrolled_disciplines(student->enrol_tree->root, course->discipline_tree->root);
                else
                    RAISE_ERROR("input data, student not found!");
                
                break;
            }
            case 7:

                int registration = 0, periods = 0;

                printf("Enter student registration -> ");
                scanf("%d", &registration);

                Student *student = search_student_by_registration(student_list->first, registration);

                if(student)
                {
                    if( student->enrol_tree->root != NULL )
                        RAISE_ERROR("enroll_tree, student is already enrolled");
                    else
                    {
                        do{
                            printf("enroll in which period (?)\n-> ");
                            scanf("%d", &periods);
                        }  
                        while(!valid_answer(1, course->num_periods, periods));
                        
                        enroll_period(&student->enrol_tree->root, course->discipline_tree->root, periods);
                    }
                }
                else
                    RAISE_ERROR("input data, stduent not found!");

                break;
            case 8:
                printf("\nReturning to Main Menu...\n");
                break;
            default: break;
        }
    } 
    while(!valid_answer(1, 8, option) || option != 8);
}




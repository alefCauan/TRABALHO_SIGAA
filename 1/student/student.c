#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"
#include "../enrollment/enrollment.h"
#include "../course/course.h"
#include "../discipline/discipline.h"
#include "../error.h"

Grade *allocate_grade() 
{
    Grade *new_grade = (Grade *) malloc(sizeof(Grade));
    ASSERT_ALLOC(new_grade, "allocate grade");

    new_grade->discipline_code = 0;
    new_grade->semester = 0;
    new_grade->final_grade = 0.0;
    new_grade->left = NULL;
    new_grade->right = NULL;
    
    return new_grade;
}

Grade_Tree *create_grade_tree()
{
    Grade_Tree *new = (Grade_Tree *)malloc(sizeof(Grade_Tree));
    ASSERT_ALLOC(new, "create grade tree");

    new->root = allocate_grade();

    return new;
}

Student *allocate_student() 
{
    Student *new_student = (Student*) malloc(sizeof(Student));
    ASSERT_ALLOC(new_student, "student node");

    new_student->registration = 0;
    strcpy(new_student->name, "");
    new_student->course_code = 0;
    new_student->grade_tree = create_grade_tree();
    new_student->enrol_tree = create_enrollment_tree();
    new_student->next = NULL;
    
    return new_student;
}

Student_list *create_student_list() 
{
    Student_list *list = (Student_list*) malloc(sizeof(Student_list));
    ASSERT_ALLOC(list, "create student");

    list->first = allocate_student();
    
    return list;
}

void deallocate_grade(Grade *grade) 
{
    if (grade != NULL) 
    {
        free(grade);
        grade = NULL;
    }
}

void deallocate_grade_tree(Grade *root)
{
    if(root != NULL)
    {
        deallocate_grade_tree(root->left);
        deallocate_grade_tree(root->right);
        
        deallocate_grade(root);
    }
}

void deallocate_student(Student *student) 
{
    if (student != NULL) 
    {
        // Desalocar árvore de notas e árvore de matrículas, se necessário
        deallocate_enrollment_tree(student->enrol_tree->root);
        deallocate_grade_tree(student->grade_tree->root);

        free(student);
        student = NULL;
    }
}

void deallocate_student_list(Student_list *list) 
{
    if (list != NULL) 
    {
        Student *current = list->first;
        Student *next;

        while (current != NULL) 
        {
            next = current->next;
            deallocate_student(current);
            current = next;
        }
        // Desaloca a estrutura da lista
        free(list);
    }
}

int get_registration(int course_code)
{
    time_t t;
    static int enrol_code = 0; 
    char str[20];

    sprintf(str, "%d%04d", course_code, enrol_code++); 
    return atoi(str); 
}

void register_student(Student_list *list, Course *courses)
{
    char temp[50];

    if(list && courses)
    {
        Student *new = allocate_student(), *aux = list->first, *prev = NULL;

        setbuf(stdin, NULL);
        printf("Student name: ");
        scanf("%[^\n]", temp);
        strcpy(new->name, temp);

        do {
            printf("course code: ");
            scanf("%d", &new->course_code);
        } while(!search_course_code(courses, new->course_code));

        new->registration = GET_REGISTRATION(new->course_code);
        
        enroll_period(&new->enrol_tree->root, courses->discipline_tree->root, 1); // TODO: optional

        // Se a lista estiver vazia
        if(list->first == NULL)
        {
            list->first = new;
            return;
        }
        // Inserção em ordem alfabética
        while(aux != NULL && is_alphabetical(aux->name, new->name))
        {
            prev = aux;
            aux = aux->next;
        }
        // Inserção no início
        if(prev == NULL)
        {
            new->next = list->first;
            list->first = new;
        }
        else
        {
            new->next = aux;
            prev->next = new;
        }
    }
    else
        RAISE_ERROR("register student, no student lists or course tree");
}

void show_students_by_course(Student_list *list, int course_code)
{    
    if(list != NULL && list->first != NULL)
    {
        Student *aux = list->first;

        while(aux)
        {
            if(aux->course_code == course_code)
            {
                line();
                printf("NAME:.......... %s\n", aux->name);
                printf("REGISTRATION... %d\n", aux->registration);
                // printf("COURSE......... %d", aux->course_code);
            }
            aux = aux->next;
        }
    }
    else
        RAISE_ERROR("show_students_by_course, Studentlist not valid or allocate");
}

Grade *search_grade(Grade *root, int discipline_code) 
{
    Grade *result = NULL;  

    if (root != NULL)
    {
        if(root->discipline_code == discipline_code)
            result = root;
        else if (discipline_code < root->discipline_code) 
            result = search_grade(root->left, discipline_code);
        else 
            result = search_grade(root->right, discipline_code);
    }
    
    return result;  
}

Grade *insert_grade(Grade **root, Grade *new)
{
    if (*root == NULL)
        *root = new;
    else if (new->discipline_code < (*root)->discipline_code)
        insert_grade(&(*root)->left, new);
    else if (new->discipline_code > (*root)->discipline_code)
        insert_grade(&(*root)->right, new);
    else 
        RAISE_ERROR("insert grade, discipline code already inserted");

    return *root; 
}

void register_grade(Student **student)
{
    Enrollment *check;
    check = NULL;

    int discipline_code = 0, semester = 0;
    float score = 0.0f;

    // Loop até encontrar uma matrícula válida ou o usuário decidir sair
    while (check == NULL || discipline_code != -1)
    {
        printf("Enter the discipline code (or -1 to exit): ");
        scanf("%d", &discipline_code);

        if (discipline_code == -1) 
        {
            line();
            printf("leaving the register operation...\n");
            line();
        }
        else 
        {
            check = search_enrollment((*student)->enrol_tree->root, discipline_code);

            if (check == NULL) 
                RAISE_ERROR("register grade, student has no enrol with this code");
        }
    }

    if(discipline_code != -1)
    {
        // Validar a nota entre 0 e 10
        do {
            printf("Enter the score: ");
            scanf("%f", &score);
        } 
        while (!validf_answer(0, 10, score));

        // Validar o semestre (entre 1 e 2)
        do {
            printf("Enter the semester (1 or 2): ");
            scanf("%d", &semester);
        } 
        while (!valid_answer(1, 2, semester));

        // A matrícula foi confirmada anteriormente, agora processar a nota
        Grade *new_grade;
        new_grade =  allocate_grade();

        new_grade->discipline_code = discipline_code;
        new_grade->final_grade = score;
        new_grade->semester = semester;

        insert_grade(&(*student)->grade_tree->root, new_grade);  // Insere a nota na árvore de notas
        remove_enrollment(&(*student)->enrol_tree->root, discipline_code);  // Remove a matrícula correspondente

        printf("Grade registered for discipline [%d] with score %.2f\n", discipline_code, score);
    }
}
// Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.
void show_grades(Student *student, Discipline *root, int period)
{
    if(root != NULL)
    {
        Grade *show = search_grade(student->grade_tree->root, root->discipline_code);

        if(root->period == period && show != NULL)
        {
            printf("Disciplina: %s\n", root->discipline_name);
            printf("Code:       %d\n", root->discipline_code);
            printf("Score:      %f\n", show->final_grade);
        }

        show_grades(student, root->left, period);
        show_grades(student, root->right, period);
    }
}

// mostra a nota de uma disciplina de um aluno, período e a carga horária da disciplina.
void show_period_grade(Student *student, Discipline *discipline)
{
    Grade *show = search_grade(student->grade_tree->root, discipline->discipline_code);

    if(show != NULL)
    {
        printf("Score:    %f\n", show->final_grade);
        printf("Period:   %d\n", discipline->period);
        printf("Workload: %d\n", discipline->workload);
    }
    else
        RAISE_ERROR("show period grades, the student has not completed or enrolled in this subject");
}

// show student history
void show_history(Student *student, Discipline *root, int period)
{
    if(root != NULL)
    {
        Grade *show = search_grade(student->grade_tree->root, root->discipline_code);
        
        show_history(student, root->right, period);
        if(root->period == period)
            printf("[Score: %.2f, Descipline: %s]\n", show->final_grade, root->discipline_name);
        show_history(student, root->left, period);
    }
}

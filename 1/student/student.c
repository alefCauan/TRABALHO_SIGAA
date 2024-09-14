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
    check_allocation(new_grade, "allocate grade");

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
    check_allocation(new, "create grade tree");

    new->root = allocate_grade();

    return new;
}

Student *allocate_student() 
{
    Student *new_student = (Student*) malloc(sizeof(Student));
    check_allocation(new_student, "student node");

    new_student->registration = 0;
    strcpy(new_student->name, "");
    new_student->course_code = 0;
    new_student->grade_tree = create_grade_tree();
    new_student->enrol_tree = create_enrollment_tree();
    new_student->next = NULL;
    
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
    if (student != NULL) {
        // Desalocar árvore de notas e árvore de matrículas, se necessário
        if(student->grade_tree->root->semester != 0)
            deallocate_grade_tree(student->grade_tree->root);
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

int get_current_year() 
{
    time_t t = time(NULL);         
    struct tm *tm_info = localtime(&t); 

    int year = tm_info->tm_year + 1900; 
    return year;
}

int get_registration(int course_code)
{
    time_t t;
    static int enrol_code = 0; 
    char str[20];

    sprintf(str, "%4d%04d%04d", get_current_year(), course_code, enrol_code++); 
    return atoi(str); 
}

void printf_student(Student student)
{
    // TODO: more information
    printf("%s\n", student.name);
    printf("%d\n", student.course_code);
    printf("%04d\n", student.registration);
}

void register_student(StudentList *list, Course *courses)
{
    char temp[50];
    int code;

    if(!CHECK_ALL_TRUE(list, list->first))
        print_error("register_student, Studentlist not valid or allocate");
    else if(courses->course_code != 0)
    {

        Student *new = allocate_student(), *aux;

        setbuf(stdin, NULL);
        printf("Student name: ");
        scanf("%[^\n]", temp);
        strcpy(new->name, temp);

        do {
            printf("course code: ");
            scanf("%d", &new->course_code);
        } 
        while(!search_course_code(courses, new->course_code));

        new->registration = GET_REGISTRATION(new->course_code);
        enroll_period(&new->enrol_tree->root, courses->discipline_tree->root, 1); // TODO: optional 

        if(list->first->course_code == 0)
            list->first = new;
        else
        {
            aux = list->first;
            while(aux->next)
                aux = aux->next;

            aux->next = new;
        }
    }
    else
        print_error("register student, there is no courses in the campus");
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
        if(aux->course_code == course_code)
            printf_student(*aux);

        aux = aux->next;
    }
    
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
        print_error("insert grade, discipline code already inserted");

    return *root; 
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

void register_grade(Student **student)
{
    float score;
    int discipline_code, semester;

    // TODO: verificação
    printf("discipline code: "), scanf("%d", &discipline_code);
    printf("score: "), scanf("%f", &score);
    printf("semester: "), scanf("%d", &semester);

    if (search_enrollment((*student)->enrol_tree->root, discipline_code)) 
    {
        Grade *new = allocate_grade();
        new->discipline_code = discipline_code;
        new->final_grade = score;
        new->semester = semester;

        insert_grade(&(*student)->grade_tree->root, new);
        remove_enrollment(&(*student)->enrol_tree->root, discipline_code);
        printf("Grade registered for discipline [%d] with score %.2f\n", discipline_code, score);
    }
    else
        print_error("register grade, student has no enrol with this code");
}

// Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.
void show_grades(Student *student, Discipline *root, int period)
{
    if(root != NULL)
    {
        Grade *show = search_grade(student->grade_tree->root, root->discipline_code);

        if(root->period == period && show != NULL)
        {
            printf("Code: %d\n", root->discipline_code);
            printf("Disciplina: %s\n", root->discipline_name);
            printf("Score: %f\n", show->final_grade);
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
        print_error("show period grades, the student has not completed or enrolled in this subject");
}

// show student history
void show_history(Student *student, Discipline *root, int period)
{
    if(root != NULL)
    {
        Grade *show = search_grade(student->grade_tree->root, root->discipline_code);
        
        if(root->period == period)
            printf("[Score: %.2f, Descipline: %s]\n", show->final_grade, root->discipline_name);

        show_history(student, root->right, period);
        show_history(student, root->left, period);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "course.h"
// #include "../subject/subjetc.h"
#include "../error.h"
#include "../discipline/discipline.h"


Course *allocate_course() 
{
    Course *new_course = (Course *) malloc(sizeof(Course));
    ASSERT_ALLOC(new_course, "allocate course");

    if (new_course != NULL) 
    {
        new_course->course_code = -1;
        strcpy(new_course->course_name, "");
        new_course->num_periods = 0;
        new_course->discipline_tree = create_discipline_tree(); 
        new_course->left = NULL;
        new_course->right = NULL;
    }
    return new_course;
}

Course_tree *create_course_tree() 
{
    Course_tree *tree = (Course_tree *) malloc(sizeof(Course_tree));
    ASSERT_ALLOC(tree, "create couse tree");

    tree->root = NULL;
    
    return tree;
}

void deallocate_course(Course *course) 
{
    if (course != NULL) 
    {
        // Verifica se a árvore de disciplinas existe antes de desalocar
        if (course->discipline_tree != NULL) 
        {
            deallocate_discipline_tree(course->discipline_tree->root);
            course->discipline_tree = NULL;  
        }
        
        free(course);  
        course = NULL;  
    }
}

void deallocate_course_tree(Course *root) 
{
    if (root != NULL) 
    {
        deallocate_course_tree(root->left);
        deallocate_course_tree(root->right);

        deallocate_course(root);
    }
}

int get_current_year() 
{
    time_t t = time(NULL);         
    struct tm *tm_info = localtime(&t); 

    int year = tm_info->tm_year + 1900; 
    return year;
}

Course *search_course_code(Course *root, int code)
{
    Course *result;
    result = NULL;

    if(root == NULL || root->course_code == code)
        result = root;
    else if(code < root->course_code)
        result = search_course_code(root->left, code);
    else if(code > root->course_code)
        result = search_course_code(root->right, code);

    return result;
}

int get_course_code(Course *root)
{
    char str[20];
    int random = 0;

    do {
        random = rand() % 9999;
        sprintf(str, "%d%04d", get_current_year() % 100, random);
    } 
    while(search_course_code(root, atoi(str)));

    return atoi(str); 
}


Course *insert_course(Course *root, Course *new_course) 
{
    if (root == NULL) {
        root = new_course;

    }
    else if (new_course->course_code < root->course_code) 
        root->left = insert_course(root->left, new_course);
    else if (new_course->course_code > root->course_code) 
        root->right = insert_course(root->right, new_course);
    else{
        printf("Course with code %d already exists!\n", root->course_code);
    }
    return root;
}

void register_course(Course **root) 
{
    // Aloca memória para um novo curso
    Course *new;
    new = allocate_course();
    ASSERT_ALLOC(new, "register course");

    new->course_code = GET_COURSE_CODE(*root); 
    
    printf("Enter course name: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", new->course_name); 
    
    do {
        printf("Enter number of periods: ");
        scanf("%d", &new->num_periods);
    } 
    while(!valid_answer(1, 8, new->num_periods));
    
    *root = insert_course(*root, new); 
    
    printf("Course successfully registered!\n");
}

void show_courses(Course *root)
{
    if (root != NULL)
    {
        show_courses(root->left);      
        line();
        printf("Name:    %s\n", root->course_name);
        printf("Code:    %d\n", root->course_code);
        printf("Periods: %d\n", root->num_periods);
        line();
        show_courses(root->right);    
    }
}

void shuffle_courses(Course *courses, int n) {
    if (n > 1) {
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            // troca courses[i] com courses[j]
            Course temp = courses[i];
            courses[i] = courses[j];
            courses[j] = temp;
        }
    }
}

void measure_insertion_time(Course_tree *course_tree) {
    int n;
    printf("Digite o número de cursos a serem inseridos para o teste: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("O número de cursos deve ser positivo.\n");
        return;
    }

    // Alocar memória para o array de tempos de inserção
    double *insertion_times = (double *)malloc(n * sizeof(double));
    if (!insertion_times) {
        printf("Falha na alocação de memória para os tempos de inserção.\n");
        return;
    }

    // Alocar memória para os cursos de teste
    Course *courses = (Course *)malloc(n * sizeof(Course));
    if (!courses) {
        printf("Falha na alocação de memória.\n");
        free(insertion_times);
        return;
    }

    // Gerar cursos de teste com dados fictícios
    for (int i = 0; i < n; i++) {
        courses[i].course_code = get_course_code(course_tree->root);
        sprintf(courses[i].course_name, "Curso_Teste_%d", i + 1);
        courses[i].num_periods = 8;  // Exemplo fixo; ajuste conforme necessário
        courses[i].discipline_tree = create_discipline_tree();
        courses[i].left = NULL;
        courses[i].right = NULL;
    }

    // Embaralhar a ordem dos cursos
    shuffle_courses(courses, n);

    // Medir o tempo de inserção
    double total_time = 0.0;
    for (int i = 0; i < n; i++) {
        // Criar um novo curso
        Course *new_course = allocate_course();
        if (!new_course) {
            RAISE_ERROR("falha na alocação do curso");
        }

        new_course->course_code = courses[i].course_code;
        strcpy(new_course->course_name, courses[i].course_name);
        new_course->num_periods = courses[i].num_periods;
        new_course->discipline_tree = courses[i].discipline_tree;
        new_course->left = NULL;
        new_course->right = NULL;

        // Medir o tempo de inserção
        clock_t start = clock();
        course_tree->root = insert_course(course_tree->root, new_course);
        clock_t end = clock();

        // Armazenar o tempo de inserção em milissegundos
        insertion_times[i] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Tempo em milissegundos
        total_time += insertion_times[i]; // Acumular o tempo total
    }

    // Exibir os tempos de inserção individuais 
    // for (int i = 0; i < n; i++) {
    //     printf("Tempo de inserção do curso %d: %f milissegundos\n", i + 1, insertion_times[i]);
    // }

    // Calcular e exibir o tempo total e médio
    printf("Tempo total de inserção de %d cursos: %f milissegundos\n", n, total_time);
    printf("Tempo médio de inserção de cada elemento em milissegundos: %f\n", total_time / n);

    // Liberar memória
    free(insertion_times);
    free(courses);
}
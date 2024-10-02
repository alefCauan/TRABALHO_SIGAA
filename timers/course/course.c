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


void copy_course_tree(Course *source, Course **destination) {
    if (source == NULL) {
        *destination = NULL;
        return;
    }
    
    // Aloca memória para o novo nó da árvore
    *destination = allocate_course();
    (*destination)->course_code = source->course_code;
    strcpy((*destination)->course_name, source->course_name);
    (*destination)->num_periods = source->num_periods;
    (*destination)->discipline_tree = source->discipline_tree; // Assume que a árvore de disciplinas não precisa de cópia profunda

    // Recursivamente copia os filhos esquerdo e direito
    copy_course_tree(source->left, &((*destination)->left));
    copy_course_tree(source->right, &((*destination)->right));
}
int generate_sequential_course_code(int index) {
    int year_part = get_current_year() % 100;  // Obtém os dois últimos dígitos do ano
    int base_code = 1000 + index;  // Gera um código base sequencial a partir de 1001, 1002, etc.

    // Combina os dois dígitos do ano com o código fixo
    char str[20];
    sprintf(str, "%d%04d", year_part, base_code);

    return atoi(str);  // Retorna o código gerado
}

Course *remove_course(Course *root, int code) {
    if (root == NULL) {
        return NULL;
    }
    
    if (code < root->course_code) {
        root->left = remove_course(root->left, code);
    } else if (code > root->course_code) {
        root->right = remove_course(root->right, code);
    } else {
        // Encontrou o curso a ser removido
        Course *temp = NULL;

        // Caso 1: nó com apenas um filho ou nenhum
        if (root->left == NULL) {
            temp = root->right;
            deallocate_course(root);
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;
            deallocate_course(root);
            return temp;
        }

        // Caso 2: nó com dois filhos
        // Obtém o menor valor na subárvore à direita
        temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        // Copia o valor do menor nó para este nó
        root->course_code = temp->course_code;
        strcpy(root->course_name, temp->course_name);
        root->num_periods = temp->num_periods;

        // Remove o nó duplicado
        root->right = remove_course(root->right, temp->course_code);
    }
    
    return root;
}
void measure_insertion_time(Course_tree *original_tree) {
    int n;
    printf("Digite o número de inserções a serem realizadas para o teste: ");
    scanf("%d", &n);

    if (n <= 0) {
        RAISE_ERROR("O número de inserções tem que ser positivo");
    }

    // Alocar memória para o array de tempos de inserção
    double *insertion_times = (double *)malloc(n * sizeof(double));
    if (!insertion_times) {
        RAISE_ERROR("Falha na alocação de memória para os tempos de inserção");
    }

    double total_time = 0.0;
    for (int i = 0; i < n; i++) {
        // Alocar um novo curso para cada inserção
        Course *new_course = allocate_course();
        if (!new_course) {
            free(insertion_times);
            RAISE_ERROR("Falha na alocação de memória para o curso.");
        }

        // Gera um código único para o novo curso
        new_course->course_code = generate_sequential_course_code(50);
        strcpy(new_course->course_name, "Curso_Teste");
        new_course->num_periods = 8;  // Exemplo fixo

        // Assegure-se de criar uma árvore de disciplinas única para cada curso
        new_course->discipline_tree = create_discipline_tree();
        new_course->left = NULL;
        new_course->right = NULL;

        // Medir o tempo de inserção
        clock_t start = clock();
        original_tree->root = insert_course(original_tree->root, new_course);
        clock_t end = clock();

        remove_course(original_tree->root, 241050);

        // Armazenar o tempo de inserção em milissegundos
        insertion_times[i] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        total_time += insertion_times[i]; // Acumular o tempo total
    }

    // Exibir o tempo total e médio de inserção
    printf("Tempo total de inserção de %d vezes: %f milissegundos\n", n, total_time);
    printf("Tempo médio de inserção de cada elemento em milissegundos: %f\n", total_time / n);

    // Liberar memória
    free(insertion_times);
}

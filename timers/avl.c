#include <stdio.h>
#include <stdlib.h>
#include "../avl_tree/course/course.h"
#include "../avl_tree/discipline/discipline.h"
#include "../avl_tree/enrollment/enrollment.h"
#include "../avl_tree/student/student.h"
#include "../avl_tree/error.h"

#include <time.h>
#include <string.h>

void shuffle_array(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Escolhe um índice aleatório
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void remove_course(Course **root, int course_code) {
    // Caso base: árvore vazia
    if (*root != NULL) {    
    // Se o curso a ser removido é menor que o curso atual, vá para a esquerda
    if (course_code < (*root)->course_code) {
        remove_course(&(*root)->left, course_code);
    }
    // Se o curso a ser removido é maior que o curso atual, vá para a direita
    else if (course_code > (*root)->course_code) {
        remove_course(&(*root)->right, course_code);
    }
    // Caso em que o curso é encontrado
    else {
        // Caso 1: nó com apenas um filho ou sem filhos
        if ((*root)->left == NULL) {
            Course *temp = (*root)->right;
            free(*root);  // Libera a memória do curso removido
            *root = temp; // Atualiza o ponteiro da raiz
        } else if ((*root)->right == NULL) {
            Course *temp = (*root)->left;
            free(*root);
            *root = temp; // Atualiza o ponteiro da raiz
        } else {
            // Caso 2: nó com dois filhos
            // Encontra o menor curso da subárvore direita (o sucessor)
            Course *successor = (*root)->right;
            while (successor && successor->left != NULL) {
                successor = successor->left;
            }

            // Copia os dados do sucessor para o nó atual
            (*root)->course_code = successor->course_code;
            strcpy((*root)->course_name, successor->course_name);
            (*root)->num_periods = successor->num_periods;

            // Remove o sucessor
            remove_course(&(*root)->right, successor->course_code);
        }
    }
    if (*root != NULL) {
    *root = balance_course(*root);
    }
    }
}

int generate_sequential_course_code(int index) {
    int year_part = get_current_year() % 100;  // Obtém os dois últimos dígitos do ano
    int base_code = 1000 + index;  // Gera um código base sequencial a partir de 1001, 1002, etc.

    // Combina os dois dígitos do ano com o código fixo
    char str[20];
    sprintf(str, "%d%04d", year_part, base_code);

    return atoi(str);  // Retorna o código gerado
}

// Implementação da função para medir o tempo de busca
double measure_search_time(Grade *grade_tree_root, int discipline) {
    clock_t start_time, end_time;
    double total_time = 0.0; // Tempo total gasto em todas as buscas

        // Alocar memória para o array de tempos de inserção
    double *search_times = (double *)malloc(30 * sizeof(double));
    if (!search_times) {
        RAISE_ERROR("Falha na alocação de memória para os tempos de busca");
    }

    for (int i = 0; i < 30; i++) {
        start_time = clock(); // Início da medição do tempo

        Grade *found_grade = search_grade(grade_tree_root, discipline);

        end_time = clock(); // Fim da medição do tempo
        search_times[i] = ((double)(end_time - start_time)) * 1000000 / CLOCKS_PER_SEC; // Calcula o tempo em microssegundos
        total_time += search_times[i]; // Acumula o tempo total

    }
    for (int i = 0; i < 30; i++)
    {
        printf("%f\n", search_times[i]);
    }
    
    free(search_times);
    return total_time; 
}

double measure_insertion_time(Course_tree_avl *original_tree, int insertions_number) {
    

    if (insertions_number <= 0) {
        RAISE_ERROR("O número de inserções tem que ser positivo");
    }

    // Alocar memória para o array de tempos de inserção
    double *insertion_times = (double *)malloc(insertions_number * sizeof(double));
    if (!insertion_times) {
        RAISE_ERROR("Falha na alocação de memória para os tempos de inserção");
    }

    double total_time = 0.0;
    for (int i = 0; i < insertions_number; i++) {
        // Alocar um novo curso para cada inserção
        Course *new_course = allocate_course();
        if (!new_course) {
            free(insertion_times);
            RAISE_ERROR("Falha na alocação de memória para o curso.");
        }

        // Gera um código único para o novo curso
        new_course->course_code = 241050;
        strcpy(new_course->course_name, "Curso_Teste");
        new_course->num_periods = 8;  // Exemplo fixo

        // Assegure-se de criar uma árvore de disciplinas única para cada curso
        new_course->discipline_tree = create_discipline_tree();
        new_course->left = NULL;
        new_course->right = NULL;

        // Medir o tempo de inserção
        clock_t start = clock();
        insert_course(&original_tree->root, new_course);
        clock_t end = clock();

        // printf("inserindo pela %d vez\n", i);
        remove_course(&original_tree->root, 241050);

        // Armazenar o tempo de inserção em milissegundos
        insertion_times[i] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;
        total_time += insertion_times[i]; // Acumular o tempo total
    }
    for (int i = 0; i < insertions_number; i++)
    {
        printf("%f\n", insertion_times[i]);
    }
    
    // Liberar memória
    free(insertion_times);
    return total_time;
}
void insertion_test(){
    int insertions_number;
    int quant = 10000;

    int ids[10000];
        for (int i = 0; i < 10000; i++) {
            ids[i] = i + 1;
        }
        shuffle_array(ids, 10000);  // Embaralha os IDs
        
    // Inicializa a árvore de cursos
    Course_tree_avl *course_tree = create_course_tree();  // Cria a árvore de cursos vazia
    // Pré-aloca 30 cursos fictícios e os insere na árvore em ordem
    for (int i = quant; i >= 0; i--) {
        Course *new_course = allocate_course();  // Aloca memória para o novo curso

        // Gera um código sequencial de acordo com o índice
        new_course->course_code = i;
        printf("%d\n", new_course->course_code);
        // Define um nome fictício para o curso
        sprintf(new_course->course_name, "Curso_%d", i + 1);

        new_course->num_periods = 8;  // Exemplo fixo para os períodos

        // Insere o curso na árvore (em ordem devido à sequência de códigos)
        insert_course(&course_tree->root, new_course);
    }

    printf("Digite o número de inserções a serem realizadas para o teste: ");
    scanf("%d", &insertions_number);
    // Chama a função para medir o tempo de inserção do mesmo curso na árvore
    double total_time = measure_insertion_time(course_tree, insertions_number);


    // Exibir o tempo total e médio de inserção
    printf("Tempo total de inserção de %d vezes: %f microssegundos\n", insertions_number, total_time);
    printf("Tempo médio de inserção de cada elemento em microssegundos: %f\n", total_time / insertions_number);
    
    deallocate_course_tree(course_tree->root);
    free(course_tree);
}

int search_test() {    
    int quant = 10000;
    int discipline; 

    int ids[quant];
        for (int i = 0; i < quant; i++) {
            ids[i] = i + 1;
        }
        shuffle_array(ids, quant);  

    Course_tree_avl *course_tree = create_course_tree();  
    Course *new_course = allocate_course();  
    new_course->course_code = get_course_code(course_tree->root);
    sprintf(new_course->course_name, "Curso_teste");
    new_course->num_periods = 8; 

    // Insere o curso na árvore
    insert_course(&course_tree->root, new_course);

    Student_list *student_list = create_student_list();
    Student *student = allocate_student();

    // Adicionar as notas na árvore
    for (int i = quant; i >= 0; i--) {
        Grade *grade = allocate_grade();
        grade->discipline_code = i;
        grade->semester = 3;
        grade->final_grade = rand() % 10;
        insert_grade(&student->grade_tree->root, grade);
        printf("%d ", i);
    }
    
    printf("\nDigite o codigo da disciplina para buscar a nota: ");
    scanf("%d", &discipline);
    double total_time = measure_search_time(student->grade_tree->root, discipline);
    

    // Calcular e imprimir o tempo médio de busca
    double average_time = total_time / 30; // Calcula a média
    printf("Tempo total de busca: %f microssegundos\n", total_time);
    printf("Tempo médio de busca: %f microssegundos\n", average_time);

    deallocate_student(student); 

    return 0;
}
int main()
{
   insertion_test();
//  search_test();
    return 0;
}




//Cresente 2
// 127.000000
// 54.000000
// 54.000000
// 55.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 55.000000
// 54.000000
// 54.000000
// 57.000000
// 54.000000
// 107.000000
// 55.000000
// 54.000000
// 54.000000
// 57.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// 54.000000
// Tempo total de busca: 1755.000000 microssegundos
// Tempo médio de busca: 58.500000 microssegundos

//decrescente 2
// 151.000000
// 60.000000
// 59.000000
// 58.000000
// 58.000000
// 63.000000
// 63.000000
// 62.000000
// 58.000000
// 58.000000
// 65.000000
// 59.000000
// 59.000000
// 59.000000
// 78.000000
// 63.000000
// 59.000000
// 59.000000
// 59.000000
// 58.000000
// 58.000000
// 59.000000
// 59.000000
// 59.000000
// 58.000000
// 59.000000
// 59.000000
// 58.000000
// 58.000000
// 59.000000
// Tempo total de busca: 1894.000000 microssegundos
// Tempo médio de busca: 63.133333 microssegundos

//aleatorio 2
// 84.000000
// 59.000000
// 59.000000
// 59.000000
// 58.000000
// 58.000000
// 59.000000
// 59.000000
// 58.000000
// 59.000000
// 58.000000
// 58.000000
// 59.000000
// 59.000000
// 58.000000
// 59.000000
// 59.000000
// 140.000000
// 59.000000
// 59.000000
// 59.000000
// 59.000000
// 59.000000
// 59.000000
// 59.000000
// 58.000000
// 59.000000
// 59.000000
// 59.000000
// Tempo total de busca: 1870.000000 microssegundos
// Tempo médio de busca: 62.333333 microssegundos

///// INSERÇÃO ///////

//aleatorio
// 11.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 3.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 2.000000
// 2.000000
// 2.000000
// 2.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 3.000000
// 2.000000
// 3.000000
// 2.000000
// 3.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 2.000000
// Tempo total de inserção de 30 vezes: 78.000000 microssegundos
// Tempo médio de inserção de cada elemento em microssegundos: 2.600000

// crescente 
// 10.000000
// 3.000000
// 3.000000
// 2.000000
// 2.000000
// 2.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 3.000000
// 3.000000
// 3.000000
// 2.000000
// 2.000000
// 2.000000
// Tempo total de inserção de 30 vezes: 79.000000 microssegundos
// Tempo médio de inserção de cada elemento em microssegundos: 2.633333

//decrescente
// 8.000000
// 1.000000
// 2.000000
// 1.000000
// 1.000000
// 1.000000
// 14.000000
// 5.000000
// 3.000000
// 3.000000
// 3.000000
// 3.000000
// 3.000000
// 3.000000
// 3.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 2.000000
// 3.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// 2.000000
// 2.000000
// 3.000000
// Tempo total de inserção de 30 vezes: 90.000000 microssegundos
// Tempo médio de inserção de cada elemento em microssegundos: 3.000000
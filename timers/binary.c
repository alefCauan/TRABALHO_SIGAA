#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "binary.h"
#include "../binary_tree/course/course.h"
#include "../binary_tree/discipline/discipline.h"
#include "../binary_tree/enrollment/enrollment.h"
#include "../binary_tree/student/student.h"
#include "../binary_tree/error.h"
// #include "logic.c"

void shuffle_array(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // Escolhe um índice aleatório
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void search_test() {    

    int quant = 1000;
    int discipline; // O codigo disciplina que será buscada a nota

    int ids[1000];
    for (int i = 0; i < 1000; i++) {
        ids[i] = i + 1;
    }
    shuffle_array(ids, 1000);  // Embaralha os IDs
    
    Course_tree *course_tree = create_course_tree();  
    Course *new_course = allocate_course();  
    new_course->course_code = get_course_code(course_tree->root);
    sprintf(new_course->course_name, "Curso_teste");
    new_course->num_periods = 8; 

    // Insere o curso na árvore
    insert_course(&course_tree->root, new_course);

    Student_list *student_list = create_student_list();
    Student *student = allocate_student();

    // Discipline *discipline = allocate_discipline();
    // int discipline_code = 240000;
    // discipline->discipline_code = discipline_code;
    // sprintf(discipline->discipline_name, "ED2");
    // discipline->period = 8;

    float balanced_grades[30] = {
        0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8,
        2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8,
        4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8
    };

/*
                     2.8
                   /     \
                1.4       4.4
               /  \      /   \
            0.6   2.0   3.6   5.2
           / \     \     / \    / \
         0.2  1.0   2.4 3.4  5.0  5.4
        /      /    /     \     \
      0.0    2.2  3.2      4.0   5.6
*/


    // Adicionar as notas na árvore
    for (int i = 0; i < quant; i++) {
        Grade *grade = allocate_grade();
        grade->discipline_code = ids[i];
        grade->semester = 2;
        grade->final_grade = rand() % 10;
        insert_grade(&student->grade_tree->root, grade);
        printf("%d ", ids[i]);
    }
    
    // Medir o tempo de busca de uma nota específica na disciplina
    printf("\n Digite o codigo da disciplina que será buscada a nota");
    scanf("%d", &discipline);
    double total_time = measure_search_time(student->grade_tree->root, discipline);
    

    // Calcular e imprimir o tempo médio de busca
    double average_time = total_time / 30; // Calcula a média
    printf("Tempo total de busca: %f microssegundos\n", total_time);
    printf("Tempo médio de busca: %f microssegundos\n", average_time);

    deallocate_student(student); 

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
void insertion_test() {

    int insertions_number;
    // Inicializa a árvore de cursos
    Course_tree *course_tree = create_course_tree();  // Cria a árvore de cursos vazia

    // Preenche um array com números de 1 a 1000 e embaralha
    int ids[1000];
    for (int i = 0; i < 1000; i++) {
        ids[i] = i + 1;
    }
    shuffle_array(ids, 1000);  // Embaralha os IDs

    // Pré-aloca 30 cursos fictícios e os insere na árvore com IDs aleatórios
    for (int i = 0; i < 1000; i++) {
        Course *new_course = allocate_course();  // Aloca memória para o novo curso

        // Atribui um código aleatório e único do array embaralhado
        new_course->course_code = i;
        printf("%d\n", new_course->course_code);

        // Define um nome fictício para o curso
        sprintf(new_course->course_name, "Curso_%d", i + 1);

        new_course->num_periods = 8;  // Exemplo fixo para o número de períodos

        // Insere o curso na árvore
        insert_course(&course_tree->root, new_course);
    }

    printf("Digite o número de inserções a serem realizadas para o teste: ");
    scanf("%d", &insertions_number);

    // Chama a função para medir o tempo de inserção na árvore
    double total_time = measure_insertion_time(course_tree, insertions_number);

    printf("Tempo total de inserção de 30 vezes: %f microssegundos\n", total_time);
    printf("Tempo médio de inserção de cada elemento em microssegundos: %f\n", total_time / 30);

    // Libera a memória alocada para a árvore
    deallocate_course_tree(course_tree->root);
    free(course_tree);
}

// Implementação da função para medir o tempo de busca
double measure_search_time(Grade *grade_tree_root, int discipline) {
    const int iterations = 30; // Número de iterações 
    clock_t start_time, end_time;
    double total_time = 0.0; // Tempo total gasto em todas as buscas

    // Alocar memória para o array de tempos de inserção
    double *search_times = (double *)malloc(30 * sizeof(double));
    if (!search_times) {
        RAISE_ERROR("Falha na alocação de memória para os tempos de inserção");
    }
    for (int i = 0; i < iterations; i++) {
        start_time = clock(); // Início da medição do tempo

        Grade *found_grade = search_grade(grade_tree_root, discipline);

        end_time = clock(); // Fim da medição do tempo
        search_times[i]  = ((double)(end_time - start_time)) * 1000000 / CLOCKS_PER_SEC; 
        total_time += search_times[i]; // Acumula o tempo total

        for (int i = 0; i < 30; i++)
        {
            printf("%f\n", search_times[i]);
        }

    }

    // Liberar memória
    free(search_times);

    return total_time; 
}

double measure_insertion_time(Course_tree *original_tree, int insertions_number) {

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

int main()
{
//   insertion_test();
    search_test();
    return 0;
}

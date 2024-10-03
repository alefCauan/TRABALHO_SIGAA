#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sigaa.h"  // Certifique-se de que este cabeçalho contém a definição correta de Course, Course_tree e funções relacionadas

// Gera códigos de curso sequenciais


int main() {
    // Inicializa a árvore de cursos
    Course_tree *course_tree = create_course_tree();  // Cria a árvore de cursos vazia

 int insertion_order[30] = {
        16, 8, 24, 4, 12, 20, 28,
        2, 6, 10, 14, 18, 22, 26, 30,
        1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29
    };
    // Pré-aloca 30 cursos fictícios e os insere na árvore em ordem
    for (int i = 0; i < 30; i++) {
        Course *new_course = allocate_course();  // Aloca memória para o novo curso

        // Gera um código sequencial de acordo com o índice
        new_course->course_code = generate_sequential_course_code(insertion_order[i]);
        printf("%d\n", new_course->course_code);
        // Define um nome fictício para o curso
        sprintf(new_course->course_name, "Curso_%d", i + 1);

        new_course->num_periods = 8;  // Exemplo fixo para os períodos

        // Insere o curso na árvore (em ordem devido à sequência de códigos)
        insert_course(&course_tree->root, new_course);
    }

    // Chama a função para medir o tempo de inserção do mesmo curso na árvore
    measure_insertion_time(course_tree);

    // Libera memória da árvore
    deallocate_course_tree(course_tree->root);
    free(course_tree);

    return 0;
}
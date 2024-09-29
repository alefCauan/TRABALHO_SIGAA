#include <stdio.h>
#include "sigaa.h"  // Certifique-se de que este cabeçalho contém a definição correta de funções necessárias

int main() {
    Course_tree course_tree;
    // Inicializa a árvore de cursos, por exemplo:
    course_tree.root = NULL;  // Supondo que você tenha um campo `root` na struct Course_tree

    // Chama a função para medir o tempo de inserção
    measure_insertion_time(&course_tree);

    // Aqui você pode adicionar outras operações, se necessário

    return 0;
}

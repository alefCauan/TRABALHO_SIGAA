#ifndef AVL_H
#define AVL_H

#include <time.h>
#include "../avl_tree/course/course.h"
#include "../avl_tree/student/student.h"

#define POVOAR 11000
#define LIMITE 10000

typedef enum {
    CRESCENTE,
    DESCRESCENTE,
    RANDOM
} Type;

// Função para medir o tempo em microsegundos
double get_time_micro(clock_t start, clock_t end);
// Função para povoar a árvore com x elementos (LIMITE)
void povoar_tree(Enrollment **root, Type type);
// Função para realizar as inserções adicionais (30 elementos)
void insert_elements(Enrollment *root, int start_value, int change);
// Função para medir o tempo de busca de 30 elementos na árvore
void search_elements(Enrollment *root, Type type);

#endif
#ifndef BINARY_H
#define BINARY_H

#include "../binary_tree/course/course.h"
#include "../binary_tree/student/student.h"

int teste();

// Implementação da função para medir o tempo de busca
double measure_search_time(Grade *grade_tree_root, int discipline);

void measure_insertion_time(Course_tree *original_tree);

#endif
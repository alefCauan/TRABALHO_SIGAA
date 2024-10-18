#ifndef AVL_H
#define AVL_H

#include "../avl_tree/course/course.h"
#include "../avl_tree/student/student.h"

void insertion_test();

// Implementação da função para medir o tempo de busca
double measure_search_time(Grade *grade_tree_root, int discipline);

double measure_insertion_time(Course_tree_avl *original_tree, int insertions_number);

#endif
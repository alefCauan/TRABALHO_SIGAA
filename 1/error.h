#ifndef ERROR_H
#define ERROR_H
#include <stdbool.h>
// Definindo a macro para verificar múltiplos parâmetros
#define CHECK_ALL_TRUE(...) (check_all_true(__VA_ARGS__, NULL))

int check_all_true(void *first, ...);

// Checa a alocação de memoria 
void check_allocation(void *pointer, const char *mensage);

// função simples para relatar um "erro" ou ação invalida
void print_error(const char *error_message);

bool valid_answer(int min, int max, int answer);

#endif

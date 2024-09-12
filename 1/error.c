#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "error.h"

int check_all_true(void *first, ...) 
{
    va_list args;
    va_start(args, first);

    int result = 1; // Assume que todos são verdadeiros
    void *current = first;

    while (current != NULL) {
        if (!current) {
            result = 0; // Se algum parâmetro for falso, retorna 0
            break;
        }
        current = va_arg(args, void *);
    }

    va_end(args);
    return result;
}

// Checa a alocação de memoria 
void check_allocation(void *pointer, const char *mensage) 
{
    if(!pointer) 
    {
        fprintf(stderr, "Erro ao alocar memória para %s: %d - %s\n", mensage, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// função simples para relatar um "erro" ou ação invalida
void print_error(const char *error_message) 
{
    ///////
    fprintf(stderr, "ERROR: in %s\n", error_message);
}

bool valid_answer(int min, int max, int answer) 
{
    // TODO: error mensage
    return answer >= min && answer <= max;
}


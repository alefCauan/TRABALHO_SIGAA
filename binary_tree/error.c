#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include "error.h"

void line() { printf("---------------------------------------------------------------\n"); }

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

// Checa a alocação de memoria de um ponteiro 
void check_allocation(void *pointer, const char *mensage) 
{
    if(!pointer) 
    {
        fprintf(stderr, "ERRO: ao alocar memória para %s: %d - %s\n", mensage, errno, strerror(errno));
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
    bool result = (answer >= min && answer <= max);

    if(!result)
    {
        line();
        (answer > max) ? 
            RAISE_ERROR("data input, input greater than maximum parameter") : 
            RAISE_ERROR("data input, input less than minimum parameter");
        line();
    }
    
    return result;
}

// (float) valida uma resposta dentro de um certo limite
bool validf_answer(float min, float max, float answer)
{
    bool result = (answer >= min && answer <= max);

    if(!result)
    {
        line();
        (answer > max) ? 
            RAISE_ERROR("data input, input greater than maximum parameter") : 
            RAISE_ERROR("data input, input less than minimum parameter");
        line();
    }
    
    return result;
}


bool is_alphabetical(char __string[], char __compare[])
{
    int i = 0, result = -1;

    while(result == -1)
    {
        if(END_STRING(__string[i]))
            result = true;
        else if(END_STRING(__compare[i]))
            result = false;
        else 
        {
            if(tolower(__string[i]) < tolower(__compare[i]))
                result = true;
            else if(tolower(__string[i]) > tolower(__compare[i]))
                result = false;
            else 
                i++;
        }
    }

    return result;
}


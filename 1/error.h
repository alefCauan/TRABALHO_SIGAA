#ifndef ERROR_H
#define ERROR_H
#include <stdbool.h>

#define CHECK_ALL_TRUE(...) (check_all_true(__VA_ARGS__, NULL))
#define RAISE_ERROR(message) (print_error(message))
#define ASSERT_ALLOC(pointer, message) (check_allocation(pointer, message))
#define END_STRING(c) ((c != ' ' && c == '\0') ? (true) : (false))

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: AINDA NÃO IMPLEMEMENTADO!\n", __FILE__, __LINE__); \
        exit(1); \
    } while(0)

// linha
void line();
int check_all_true(void *first, ...);
// Checa a alocação de memoria 
void check_allocation(void *pointer, const char *mensage);
// função simples para relatar um "erro" ou ação invalida
void print_error(const char *error_message); 
// valida uma resposta dentro de um certo limite
bool valid_answer(int min, int max, int answer);
// (float) valida uma resposta dentro de um certo limite
bool validf_answer(float min, float max, float answer);
// retorna verdadeiro se uma string estiver em ordem
// de forma alfabetica com sua comparação
bool is_alphabetical(char __string[], char __compare[]);

#endif

// #ifdef ERROR_IMPLEMENTATION // TODO: IMPLEMENTATION


// #endif

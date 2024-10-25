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

#define POVOAR 11000
#define LIMITE 10000

typedef enum {
    CRESCENTE,
    DESCRESCENTE,
    RANDOM
} Type;

// Função para medir o tempo em microsegundos
double get_time_micro(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000000; // Convertendo para microsegundos
}

// Função para povoar a árvore com x elementos (LIMITE)
void povoar_tree(Enrollment **root, Type type)
{
    int data[LIMITE];
    if (type == CRESCENTE)
    {
        for (int i = 0; i < LIMITE; i++) 
        {
            data[i] = i;
            register_enrollment(root, data[i]);
        }
    }
    else if (type == DESCRESCENTE)
    {
        for (int i = LIMITE - 1; i >= 0; i--) 
        {
            data[i] = i;
            register_enrollment(root, data[i]);
        }
    }
    else
    {
        for (int i = 0; i < LIMITE; i++) 
            data[i] = i;

        // Embaralhando os valores
        for (int i = LIMITE - 1; i > 0; i--) 
        {
            int j = rand() % (i + 1);
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }

        // Inserindo valores embaralhados
        for (int i = 0; i < LIMITE; i++) 
        {
            register_enrollment(root, data[i]);
        }
    }
}

// Função para realizar as inserções adicionais (30 elementos)
void insert_elements(Enrollment *root, int start_value, int change)
{
    int contagem = 0;
    for (int i = 0; contagem < 30; i += change) 
    {
        contagem += 1;
        clock_t start_insert = clock();
        register_enrollment(&root, start_value + (contagem * change));
        clock_t end_insert = clock();
        double insert_time = get_time_micro(start_insert, end_insert);
        
        printf("%.1f\n",insert_time);
    }
}


// Função para medir o tempo de busca de 30 elementos na árvore
void search_elements(Enrollment *root, Type type)
{
    for (int i = 0; i < 30; i++) 
    {
        int search_code = rand() % LIMITE; // Pegando um valor aleatório para buscar

        clock_t start_search = clock();
        search_enrollment(root, search_code); // Função de busca
        clock_t end_search = clock();

        double search_time = get_time_micro(start_search, end_search);

        printf("%.1f\n", search_time);
    }
}

int main()
{
    Enrollment *root = NULL;

    // Povoando a árvore com CRESCENTE
    printf("INSERT CRESCENTE\n");
    povoar_tree(&root, CRESCENTE);
    insert_elements(root, LIMITE, 1);
    printf("SEARCH CRESCENTE\n");
    search_elements(root, CRESCENTE); // Medindo o tempo de busca
    deallocate_enrollment(root);

    Enrollment *rooot = NULL;
    printf("INSERT DECRESCENTE\n");
    // Povoando a árvore com DESCRESCENTE
    povoar_tree(&rooot, DESCRESCENTE);
    insert_elements(rooot, 0, -1);
    printf("SEARCH DECRESCENTE\n");
    search_elements(rooot, DESCRESCENTE); // Medindo o tempo de busca
    deallocate_enrollment(rooot);

    Enrollment *roooot = NULL;

    printf("INSERT RANDOM\n");
    // Povoando a árvore com RANDOM
    povoar_tree(&roooot, RANDOM);
    insert_elements(roooot, LIMITE, 1);
    printf("SEARCH RANDOM\n");
    search_elements(roooot, RANDOM); // Medindo o tempo de busca
    deallocate_enrollment(roooot);

    return 0;
}
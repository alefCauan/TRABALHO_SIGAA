#ifndef DISCIPLINE_H
#define DISCIPLINE_H

#include <stdbool.h>
#include "../course/course.h"
// gera um codigo da disciplina 
#define GET_DISCIPLINE_CODE(root, code) (get_disc_code(root, code))

// enum para a carga horaria 
typedef enum {
    HOURS_30 = 30,
    HOURS_60 = 60,
    HOURS_90 = 90
}Workload;

// struct disciplina
typedef struct Discipline {
    int height;
    int     discipline_code;        // codigo da disciplina
    char    discipline_name[50];   // nome da disciplina
    int     period;                 // periodo dessa disciplina
    int     workload;               // carga horaria 
    struct  Discipline *left;   
    struct  Discipline *right;  
} Discipline;

typedef struct Discipline_tree_avl {
    Discipline *root;
} Discipline_tree_avl;

// aloca a arvore de disciplinas
Discipline *allocate_discipline();
// aloca a raiz da arvore de disciplinas
Discipline_tree_avl *create_discipline_tree();
// desaloca um node da arvore de disciplinas 
void deallocate_discipline(Discipline *discipline);
// desaloca toda a arvore de disciplinas 
void deallocate_discipline_tree(Discipline *root);
// verifica se a nova disciplina possui o nome de uma já existente
bool search_disc_name(Discipline *root, const char *name);
// busca uma disciplina com um certo codigo e a retorna se encontrar 
Discipline *search_discipline(Discipline *root, int code);

int discipline_height(Discipline *root);

int discipline_get_balance(Discipline *root);

Discipline *discipline_rotate_right(Discipline *ex_root);

Discipline *discipline_rotate_left(Discipline *ex_root);

bool insert_discipline(Discipline **root, Discipline *new_node);


// Função que retorna um codigo de disciplina 
int get_disc_code(Discipline *root, int course_code);

// iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
// seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
// disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
// horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90.
// {

// insere a nova disicplina da arvore de disciplinas de um curso 
bool insert_discipline(Discipline **root, Discipline *new_discipline);
// pega os dados da nova disciplina e chama a inserção
void register_discipline(Discipline **root, Course *course);
// remove uma disciplina escolhida do curso 

// } 

// viii)Mostrar todas as disciplinas de um determinado curso.
// {

// mostra todas as disciplinas 
void show_disciplines(Discipline *root);

// }

// ix) Mostrar todas as disciplinas de um determinado período de um curso.
// {

// Mostra todas as disciplinas de um determinado período de um curso
void show_disciplines_by_period(Discipline *root, int period);

// }

// xiii)Remover uma disciplina de um determinado curso
// desde que não tenha nenhum aluno matriculado na mesma.
// {

// remove a disciplina de um curso
void remove_discipline(Discipline **root, int discipline_code);

// }

#endif
#include <stdio.h>
#include <stdlib.h>
// #include "sigaa.h"
// #include "student/student.h"
#include "course/course.h"
#include "discipline/discipline.h"
#include "enrollment/enrollment.h"

// i) Cadastrar alunos a qualquer momento na lista, de forma que só possa cadastrar um código de curso que
// já tenha sido cadastrado na árvore de cursos.[OK]
// ii) Cadastrar cursos a qualquer momento na árvore de curso, de forma que o usuário não precise cadastrar
// as disciplinas para permitir o cadastro do curso.[OK]
// iii) Cadastrar disciplinas a qualquer momento em uma árvore de disciplinas de um determinado curso, ou
// seja, um disciplina só pode ser cadastrada se o curso já estiver sido cadastrado, além disso, o período da
// disciplina deve ser válido, ou seja, estar entre 1 e a quantidade máxima de períodos do curso. A carga
// horária da disciplina deve ser múltiplo de 15, variando entre 30 e 90.[]
// iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
// uma disciplina do curso do aluno.[]
// v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
// matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
// árvore de notas.[]
// vi) Mostrar todos os alunos de um determinado curso.[OK]
// vii)Mostrar todos os cursos do Campus.[OK]
// viii)Mostrar todas as disciplinas de um determinado curso.[]
// ix) Mostrar todas as disciplinas de um determinado período de um curso.[]
// x) Mostrar todas as disciplinas que um determinado aluno está matriculado[]
// xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.[]
// xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
// disciplina.[]
// xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
// mesma.[]
// xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno.[]
// xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
// nota organizadas pelo período que a disciplina está cadastrada no curso.[] 

    void course_menu(Course_tree *course_tree);
    void student_menu(Student_list *student_list, Course_tree *course_tree);
    void discipline_menu(Course_tree *course_tree, Student_list *student_list);

    void show_general_menu() {
        printf("Menu Geral:\n");
        printf("1. Gerenciar Cursos\n");
        printf("2. Gerenciar Alunos\n");
        printf("3. Gerenciar Disciplinas\n");
        printf("4. Sair\n");
    }

    int main() {
        Course_tree *course_tree = create_course_tree();
        Student_list *student_list = create_student_list();

        int choice;
        do {
            show_general_menu();
            printf("Escolha uma opção: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    course_menu(course_tree);
                    break;
                case 2:
                    student_menu(student_list, course_tree);
                    break;
                case 3:
                    discipline_menu(course_tree, student_list);
                    break;
                case 4:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        } while (choice != 4);

        // Libere a memória aqui
        deallocate_course_tree(course_tree->root);
        deallocate_student_list(student_list);

        return 0;
    }

    void course_menu(Course_tree *course_tree) {
        int choice;
        do {
            printf("\nMenu de Cursos:\n");
            printf("1. Cadastrar Curso\n");
            printf("2. Mostrar Cursos\n");
            printf("3. Retornar ao Menu Geral\n");
            printf("Escolha uma opção: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    register_course(&course_tree->root);
                    break;
                case 2:
                    show_courses(course_tree->root);
                    break;
                case 3:
                    printf("Retornando ao Menu Geral...\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        } while (choice != 3);
    }
    void student_menu(Student_list *student_list, Course_tree *course_tree) {
        int choice;
        do {
            printf("\nMenu de Alunos:\n");
            printf("1. Cadastrar Aluno\n");
            printf("2. Mostrar Alunos por Curso\n");
            printf("3. Matricular Aluno em Disciplina\n");
            printf("4. Retornar ao Menu Geral\n");
            printf("Escolha uma opção: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: {
                    int course_code;
                    printf("Digite o código do curso: ");
                    scanf("%d", &course_code);
                    Course *course = search_course_code(course_tree->root, course_code);
                    if (course) {
                        register_student(student_list, course);
                    } else {
                        printf("Curso não encontrado.\n");
                    }
                    break;
                }
                case 2: {
                    int course_code;
                    printf("Digite o código do curso: ");
                    scanf("%d", &course_code);
                    show_students_by_course(student_list, course_code);
                    break;
                }
                case 3: {
                    int student_registration, course_code, discipline_code;
                    
                    printf("Digite a matrícula do aluno: ");
                    scanf("%d", &student_registration);

                    Student *student = search_student_by_registration(student_list->first, student_registration);
                    if (student == NULL) {
                        printf("Aluno não encontrado.\n");
                        break;
                    }

                    printf("Digite o código do curso: ");
                    scanf("%d", &course_code);
                    Course *course = search_course_code(course_tree->root, course_code);
                    if (course == NULL) {
                        printf("Curso não encontrado.\n");
                        break;
                    }

                    printf("Digite o código da disciplina: ");
                    scanf("%d", &discipline_code);
                    Discipline *discipline = search_discipline(course->discipline_tree->root, discipline_code);
                    if (discipline == NULL) {
                        printf("Disciplina não encontrada no curso.\n");
                        break;
                    }

                    register_enrollment(&student->enrol_tree->root, discipline_code);
                    printf("Aluno matriculado na disciplina com sucesso.\n");

                    break;
                }
                case 4:
                    printf("Retornando ao Menu Geral...\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        } while (choice != 4);
    }

    void discipline_menu(Course_tree *course_tree, Student_list *student_list) {
        int choice;
        do {
            printf("\nMenu de Disciplinas:\n");
            printf("1. Cadastrar Disciplina\n");
            printf("2. Mostrar Disciplinas por Curso\n");
            printf("3. Mostrar Disciplinas por Período\n");
            printf("4. Mostrar Disciplinas de um Aluno\n");
            printf("5. Mostrar Notas de Disciplinas de um Aluno\n");
            printf("6. Mostrar Nota de uma Disciplina de um Aluno\n");
            printf("7. Retornar ao Menu Geral\n");
            printf("Escolha uma opção: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: {
                    int course_code;
                    printf("Digite o código do curso: ");
                    scanf("%d", &course_code);
                    Course *course = search_course_code(course_tree->root, course_code);
                    if (course) {
                        register_discipline(&course->discipline_tree->root, course);
                    } else {
                        printf("Curso não encontrado.\n");
                    }
                    break;
                }
                case 2: {
                    int course_code;
                    printf("Digite o código do curso: ");
                    scanf("%d", &course_code);
                    Course *course = search_course_code(course_tree->root, course_code);
                    if (course) {
                        show_disciplines(course->discipline_tree->root);
                    } else {
                        printf("Curso não encontrado.\n");
                    }
                    break;
                }
                case 3: {
                    int course_code, period;
                    printf("Digite o código do curso: ");
                    scanf("%d", &course_code);
                    Course *course = search_course_code(course_tree->root, course_code);
                    if (course) {
                        printf("Digite o período: ");
                        scanf("%d", &period);
                        show_disciplines_by_period(course->discipline_tree->root, period);
                    } else {
                        printf("Curso não encontrado.\n");
                    }
                    break;
                }
                case 4: {
                    int student_registration;
                    printf("Digite a matrícula do aluno: ");
                    scanf("%d", &student_registration);
                    Student *student = search_student_by_registration(student_list->first, student_registration);
                    if (student) {
                        show_enrolled_disciplines(student->enrol_tree->root, student->grade_tree->root);
                    } else {
                        printf("Aluno não encontrado.\n");
                    }
                    break;
                }
                case 5: {
                    int student_registration, period;
                    printf("Digite a matrícula do aluno: ");
                    scanf("%d", &student_registration);
                    Student *student = search_student_by_registration(student_list->first, student_registration);
                    if (student) {
                        printf("Digite o período: ");
                        scanf("%d", &period);
                        show_grades(student, student->grade_tree->root, period);
                    } else {
                        printf("Aluno não encontrado.\n");
                    }
                    break;
                }
                case 6: {
                    int student_registration, discipline_code;
                    printf("Digite a matrícula do aluno: ");
                    scanf("%d", &student_registration);
                    printf("Digite o código da disciplina: ");
                    scanf("%d", &discipline_code);
                    Student *student = search_student_by_registration(student_list->first, student_registration);
                    if (student) {
                        show_grades(student, student->grade_tree->root, discipline_code);
                    } else {
                        printf("Aluno não encontrado.\n");
                    }
                    break;
                }
                case 7:
                    printf("Retornando ao Menu Geral...\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        } while (choice != 7);
}

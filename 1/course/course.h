#ifndef COURSE_H
#define COURSE_H

// #include "../subject/subjetc.h"
// Definindo a macro para obter o número de registro
#define GET_CODE() (get_code() + 1)
typedef struct Subject Subject;

typedef struct Course {
    int course_code;
    char course_name[100];
    int num_periods;
    Subject *subject_tree;
    struct Course *left;
    struct Course *right; 
} Course;
// raiz de Course 
typedef struct CourseTree {
    Course *root;
} CourseTree;
// codigos de curso
// typedef enum {
//     COURSE_MATHEMATICS =        1001,
//     COURSE_PHYSICS =            1002,
//     COURSE_CHEMISTRY =          1003,
//     COURSE_BIOLOGY =            1004,
//     COURSE_COMPUTER_SCIENCE =   1005,
//     COURSE_MAX
// }Course_code;
// Course_code choose_course();

Course *allocate_course();

CourseTree *create_course_tree();

void deallocate_course(Course *course);

void deallocate_course_tree(CourseTree *tree);


int get_code();

Course *insert_course(Course *root, Course *new_course);
void register_course(Course **root); 
void show_courses(Course *root);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course.h"

Course *allocate_course() 
{
    Course *new_course = (Course*) malloc(sizeof(Course));
    if (new_course != NULL) {
        new_course->course_code = 0;
        strcpy(new_course->course_name, "");
        new_course->num_periods = 0;
        new_course->subject_tree = NULL;
        new_course->left = NULL;
        new_course->right = NULL;
    }
    return new_course;
}

CourseTree *create_course_tree() 
{
    CourseTree *tree = (CourseTree*) malloc(sizeof(CourseTree));
    if (tree != NULL) {
        tree->root = NULL;
    }
    return tree;
}

void deallocate_course(Course *course) 
{
    if (course != NULL) {
        // Desalocar árvore de disciplinas, se necessário
        free(course);
    }
}

void deallocate_course_tree(CourseTree *tree) 
{
    if (tree != NULL) {
        // Desalocar árvore de cursos, se necessário
        free(tree);
    }
}


#ifndef COURSE_H
#define COURSE_H

#include "../subjetct/subjetc.h";

// struct curso
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


void register_course(CourseTree *tree, int course_code, char name[], int num_periods);
void show_courses(CourseTree *tree);

#endif
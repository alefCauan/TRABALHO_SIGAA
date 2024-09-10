#ifndef COURSE_H
#define COURSE_H

// #include "../subject/subjetc.h"

// typedef struct Subject Subject;

// struct curso
typedef struct Course  Course;
// raiz de Course 
typedef struct CourseTree CourseTree;


void register_course(CourseTree *tree, int course_code, char name[], int num_periods);
void show_courses(CourseTree *tree);

#endif
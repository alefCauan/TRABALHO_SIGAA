#ifndef COURSE_H
#define COURSE_H

// #include "../subject/subjetc.h"

// typedef struct Subject Subject;

// struct curso
typedef struct Course Course;
// raiz de Course 
typedef struct CourseTree CourseTree;
// codigos de curso
typedef enum {
    COURSE_MATHEMATICS =        1001,
    COURSE_PHYSICS =            1002,
    COURSE_CHEMISTRY =          1003,
    COURSE_BIOLOGY =            1004,
    COURSE_COMPUTER_SCIENCE =   1005
}Course_code;

void register_course(CourseTree *tree, int course_code, char name[], int num_periods);
void show_courses(CourseTree *tree);

#endif
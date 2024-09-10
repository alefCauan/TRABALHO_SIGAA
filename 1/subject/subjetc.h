#ifndef SUBJETC_H
#define SUBJETC_H

#include "../course/course.h"

// struct disciplina
typedef struct Subject {
    int subject_code;
    char subject_name[100];
    int period;
    int workload;
    struct Subject *left; 
    struct Subject *right; 
} Subject;

void register_subject(Course *course, int subject_code, char name[], int period, int workload);
void remove_subject(Course *course, int subject_code);
void show_subjects(Course *course);

#endif
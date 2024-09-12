#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "../student/student.h"

// struct de matricula
typedef struct Enrollment {
    int course_code;
    struct Enrollment *left; 
    struct Enrollment *right; 
} Enrollment;

typedef struct Enrollment_Tree {
    Enrollment *root;
} Enrollment_Tree;

Enrollment_Tree *create_enrollment_tree();

int get_registration();
void register_enrollment(Student *student);
void remove_enrollment(Student *student, int course_code);

#endif
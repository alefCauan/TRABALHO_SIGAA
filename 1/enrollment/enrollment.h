#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "../student/student.h"

// struct de matricula
typedef struct Enrollment {
    int discipline_code;
    struct Enrollment *left; 
    struct Enrollment *right; 
} Enrollment;

typedef struct Enrollment_Tree {
    Enrollment *root;
} Enrollment_Tree;

Enrollment_Tree *create_enrollment_tree();

// adiciona um nova matricula 
void register_enrollment(Enrollment *root, int discipline_code);
// remove uma matricula 
Enrollment *remove_enrollment(Enrollment *root, int discipline_code) ;

#endif
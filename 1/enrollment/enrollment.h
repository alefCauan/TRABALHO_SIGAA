#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include "../student/student.h"

// struct de matricula
typedef struct Enrollment {
    int subject_code;
    struct Enrollment *left; 
    struct Enrollment *right; 
} Enrollment;

// void register_enrollment(Student *student, int subject_code);
// void remove_enrollment(Student *student, int subject_code);
// void register_grade(Student *student, int subject_code, int semester, float final_grade);

#endif
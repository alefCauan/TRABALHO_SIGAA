#include <stdio.h>
#include <stdlib.h>
#include "enrollment.h"

Enrollment *allocate_enrollment() 
{
    Enrollment *new_enrollment = (Enrollment*) malloc(sizeof(Enrollment));
    if (new_enrollment != NULL) {
        new_enrollment->subject_code = 0;
        new_enrollment->left = NULL;
        new_enrollment->right = NULL;
    }
    return new_enrollment;
}

void deallocate_enrollment(Enrollment *enrollment) 
{
    if (enrollment != NULL) {
        free(enrollment);
    }
}

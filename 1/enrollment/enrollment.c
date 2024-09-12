#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enrollment.h"
#include "../error.h"

Enrollment *allocate_enrollment() 
{
    Enrollment *new_enrollment = (Enrollment*) malloc(sizeof(Enrollment));
    check_allocation(new_enrollment, "allocate enrollment");

    new_enrollment->course_code = 0;
    new_enrollment->left = NULL;
    new_enrollment->right = NULL;

    return new_enrollment;
}

Enrollment_Tree *create_enrollment_tree()
{
    Enrollment_Tree *new = (Enrollment_Tree *)malloc(sizeof(Enrollment_Tree));
    check_allocation(new, "create enrollment tree");

    new->root = allocate_enrollment();

    return new;
}

void deallocate_enrollment(Enrollment *enrollment) 
{
    if (enrollment != NULL) {
        free(enrollment);
    }
}

void deallocate_enrollment_tree(Enrollment_Tree *root) 
{
    if (root != NULL) 
    {
        //
        free(root);
    }
}

void register_enrollment(Student *student)
{
    
}
void remove_enrollment(Student *student, int course_code);
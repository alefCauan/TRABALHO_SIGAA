#include <stdio.h>
#include <stdlib.h>
#include "subjetc.h"
#include <string.h>

Subject *allocate_subject() 
{
    Subject *new_subject = (Subject*) malloc(sizeof(Subject));
    if (new_subject != NULL) {
        new_subject->subject_code = 0;
        strcpy(new_subject->subject_name, "");
        new_subject->period = 0;
        new_subject->workload = 0;
        new_subject->left = NULL;
        new_subject->right = NULL;
    }
    return new_subject;
}

void deallocate_subject(Subject *subject) 
{
    if (subject != NULL) {
        free(subject);
    }
}

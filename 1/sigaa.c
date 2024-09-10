#include <stdio.h>
#include <stdlib.h>
// #include "sigaa.h"
#include "student/student.h"

int main()
{
    StudentList *list = create_student_list();

    register_student(list);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
// #include "sigaa.h"
#include "student/student.h"
// #include "course/course.h"

int main()
{
    StudentList *list = create_student_list();
    register_student(list);
    register_student(list);
    show_students_by_course(list, 1);
    deallocate_student_list(list);

    // CourseTree *tree = create_course_tree();
    // register_course(&tree->root);
    // show_courses(tree->root);
    // deallocate_course_tree(tree);
    
    return 0;
}
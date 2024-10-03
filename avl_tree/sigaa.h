#ifndef SIGAA_H
#define SIGAA_H

#include "student/student.h"
#include "course/course.h"

void main_menu();
void course_menu(Course_tree_avl *course_tree);
void discipline_menu(Course *course);
void student_menu(Student_list *student_list, Course_tree_avl *course_tree);

#endif
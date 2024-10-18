#ifndef SIGAA_H
#define SIGAA_H

#include "student/student.h"
#include "course/course.h"

void main_menu(Course_tree *course_tree, Student_list *student_list);
void course_menu(Course_tree *course_tree, Student_list *student_list);
void discipline_menu(Course *course, Student_list *student_list);
void student_menu(Student_list *student_list, Course *course);

#endif
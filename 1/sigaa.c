#include <stdio.h>
#include <stdlib.h>
#include "sigaa.h"

void register_student(StudentList *list, int registration, char name[], int course_code, CourseTree *courses);
void register_course(CourseTree *tree, int course_code, char name[], int num_periods);
void register_subject(Course *course, int subject_code, char name[], int period, int workload);
void register_enrollment(Student *student, int subject_code);
void register_grade(Student *student, int subject_code, int semester, float final_grade);
void show_students_by_course(StudentList *list, int course_code);
void show_courses(CourseTree *tree);
void show_subjects(Course *course);
void remove_subject(Course *course, int subject_code);
void remove_enrollment(Student *student, int subject_code);
#include <stdio.h>
#include <stdlib.h>
// #include "sigaa.h"
// #include "student/student.h"
#include "course/course.h"
#include "discipline/discipline.h"
#include "enrollment/enrollment.h"

int main()
{
    // ESTUDENT EXAMPLE
    // CourseTree *tree = create_course_tree();
    // register_course(&tree->root);
    // StudentList *list = create_student_list();
    // register_student(list, tree->root);
    // register_student(list, tree->root);

    // show_students_by_course(list, 1234);
    // deallocate_student_list(list);
    // deallocate_course_tree(tree);

    // COURSE EXAMPLE
    // CourseTree *tree = create_course_tree();
    // register_course(&tree->root);
    // register_course(&tree->root);
    // show_courses(tree->root);
    // deallocate_course_tree(tree);
    
    // DISCIPLINE EXAMPLE
    // CourseTree *tree = create_course_tree();
    // register_course(&tree->root);
    // Discipline_Tree *discipline = create_discipline_tree();
    // register_discipline(&discipline->root, tree->root);
    // show_disciplines(discipline->root);
    // deallocate_course_tree(tree);
    // deallocate_discipline_tree(discipline);

    // TODO: Test enrollment and grade 
    CourseTree *tree = create_course_tree();
    StudentList *list = create_student_list();

    register_course(&tree->root);
    
    register_discipline(&tree->root->discipline_tree->root, tree->root);
    register_discipline(&tree->root->discipline_tree->root, tree->root);
    register_discipline(&tree->root->discipline_tree->root, tree->root);
    
    register_student(list, tree->root);
    // register_student(list, tree);

    register_grade(&list->first);
    register_grade(&list->first);
    register_grade(&list->first);

    show_disciplines(tree->root->discipline_tree->root);
    show_grades(list->first, tree->root->discipline_tree->root, 1);
    printf("///////////////\n");
    show_period_grade(list->first, tree->root->discipline_tree->root);
    printf("///////////////\n");
    show_history(list->first, tree->root->discipline_tree->root, 1);

    deallocate_student_list(list);
    deallocate_course_tree(tree);
    

    return 0;
}
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
    // Course_tree *tree = create_course_tree();
    // register_course(&tree->root);
    // Student_list *list = create_student_list();
    // register_student(list, tree->root);
    // register_student(list, tree->root);
    // register_student(list, tree->root);
    // register_student(list, tree->root);
    // register_student(list, tree->root);

    // show_students_by_course(list, 1234);
    // deallocate_student_list(list);
    // deallocate_course_tree(tree->root);

    /////////// COURSE EXAMPLE ///////////////
    // Course_tree *tree = create_course_tree();
    // register_course(&tree->root);
    // register_course(&tree->root);
    // show_courses(tree->root);
    // deallocate_course_tree(tree->root);
    
    /////// DISCIPLINE EXAMPLE ////////////
    // Course_tree *tree = create_course_tree();
    // register_course(&tree->root);
    // Discipline_Tree *discipline = create_discipline_tree();
    // register_discipline(&discipline->root, tree->root);
    // register_discipline(&discipline->root, tree->root);
    // register_discipline(&discipline->root, tree->root);
    // show_disciplines(discipline->root);
    // deallocate_course_tree(tree->root);
    // deallocate_discipline_tree(discipline->root);


    ////////// Grade example /////////////
    // Course_tree *tree = create_course_tree();
    // Student_list *list = create_student_list();
    // register_course(&tree->root);
    // register_discipline(&tree->root->discipline_tree->root, tree->root);
    // register_discipline(&tree->root->discipline_tree->root, tree->root);
    // register_discipline(&tree->root->discipline_tree->root, tree->root);
    // register_student(list, tree->root);
    // register_student(list, tree->root);
    // register_grade(&list->first);
    // register_grade(&list->first);
    // register_grade(&list->first);
    // show_disciplines(tree->root->discipline_tree->root);
    // show_grades(list->first, tree->root->discipline_tree->root, 1);
    // printf("///////////////\n");
    // show_period_grade(list->first, tree->root->discipline_tree->root);
    // printf("///////////////\n");
    // show_history(list->first, tree->root->discipline_tree->root, 1);
    // deallocate_student_list(list);
    // deallocate_course_tree(tree->root);
    

    /////////// enrollment example //////////
    // Enrollment_Tree *matriculas = create_enrollment_tree();

    // int vet[] = {10, 6, 8, 1, 2, 5, 7};

    // for(int i = 0; i < 7; i++)
    //     register_enrollment(&matriculas->root, vet[i]);
        
    // show(matriculas->root);
    // remove_enrollment(&matriculas->root, 10);
    // show(matriculas->root);
    
    // free(matriculas);

    return 0;
}
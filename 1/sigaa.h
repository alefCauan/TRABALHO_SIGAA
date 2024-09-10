#ifndef SIGAA_H
#define SIGAA_H

/////// STRUCTS //////

// struct de notas
typedef struct Grade {
    int subject_code;
    int semester;
    float final_grade;
    struct Grade *left;
    struct Grade *right;
} Grade;
// struct de matricula
typedef struct Enrollment {
    int subject_code;
    struct Enrollment *left; 
    struct Enrollment *right; 
} Enrollment;
// struct de estudante
typedef struct Student {
    int registration;
    char name[100];
    int course_code;
    Grade *grade_tree;
    Enrollment *enrollment_tree;
    struct Student *next;
} Student;
// raiz de student
typedef struct StudentList {
    Student *first;
} StudentList;
// struct disciplina
typedef struct Subject {
    int subject_code;
    char subject_name[100];
    int period;
    int workload;
    struct Subject *left; 
    struct Subject *right; 
} Subject;
// struct curso
typedef struct Course {
    int course_code;
    char course_name[100];
    int num_periods;
    Subject *subject_tree;
    struct Course *left;
    struct Course *right; 
} Course;
// raiz de Course 
typedef struct CourseTree {
    Course *root;
} CourseTree;

//////////////////// FUNÇÕES PRINCIPAIS  ///////////////////////

////////// ESTUDANTE ////////////
void register_student(StudentList *list, int registration, char name[], int course_code, CourseTree *courses);
void show_students_by_course(StudentList *list, int course_code);

////////// CURSO /////////////
void register_course(CourseTree *tree, int course_code, char name[], int num_periods);
void show_courses(CourseTree *tree);

///////// DISCIPLINA //////////
void register_subject(Course *course, int subject_code, char name[], int period, int workload);
void remove_subject(Course *course, int subject_code);
void show_subjects(Course *course);

///////// MATRICULA //////////
void register_enrollment(Student *student, int subject_code);
void remove_enrollment(Student *student, int subject_code);
void register_grade(Student *student, int subject_code, int semester, float final_grade);


#endif
#ifndef STUDENT_H // Header guard to prevent multiple inclusions
#define STUDENT_H
#define MAX_LENGTH 100

struct student {
  char id[MAX_LENGTH]; 
  char name[MAX_LENGTH];
  char birthdate[MAX_LENGTH];
  float scoreAlgebra;
  float scoreCalculus;
  float scoreProgramming;
  float avg;
};

#endif // STUDENT_H


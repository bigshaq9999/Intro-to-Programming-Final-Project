#include "student.h"

#define MAX_SCORE 1000
#define NUM_SUBJECTS 3

void calculateStudentAverage(struct student *student)
{
	student->avg =
	    (student->scoreAlgebra + student->scoreCalculus +
	     student->scoreProgramming) / NUM_SUBJECTS;
}

float highestGPA(struct student students[], int numStudent)
{
	float max = 0;
	for (int i = 0; i < numStudent; i++) {
		if (students[i].avg > max)
			max = students[i].avg;
	}
	return max;
}

float lowestGPA(struct student students[], int numStudent)
{
	float min = MAX_SCORE;	// MAX_SCORE is a large enough number
	for (int i = 0; i < numStudent; i++) {
		if (students[i].avg < min)
			min = students[i].avg;
	}
	return min;
}

float highestBP(struct student students[], int numStudent)
{
	float max = 0;
	for (int i = 0; i < numStudent; i++) {
		if (students[i].scoreProgramming > max)
			max = students[i].scoreProgramming;
	}
	return max;
}

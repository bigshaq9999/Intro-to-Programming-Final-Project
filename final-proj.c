#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "functions.h"

#define MAX_STUDENTS 1000

void getAndPrintStudentInfo(struct student *students, int numStudent)
{
	getInfo(students, numStudent);
	printInfo(students, numStudent);
}

void calculateAndPrintStats(struct student *students, int numStudent)
{
	float maxAvg = highestGPA(students, numStudent);
	float minAvg = lowestGPA(students, numStudent);
	float maxBP = highestBP(students, numStudent);

	printf("\nThe highest average GPA is: %.2f\n", maxAvg);
	printf("The lowest average GPA is: %.2f\n", minAvg);
	printf("The highest BP GPA is: %.2f\n", maxBP);
}

void printStudentDetails(struct student *students, int numStudent)
{
	printLastName(students, numStudent);
	printOldest(students, numStudent);
	printYoungest(students, numStudent);
}

void sortAndPrint(struct student *students, int numStudent)
{
	printf("\nSorted list of student's GPA in descending order\n");
	sortDescend(students, 0, numStudent - 1);
	printInfo(students, numStudent);
}

int main(void)
{
	int numStudent = 0;
	printf("How many students?\n");
	scanf("%d", &numStudent);
	assert(numStudent <= MAX_STUDENTS);

	struct student students[MAX_STUDENTS];
	getAndPrintStudentInfo(students, numStudent);
	writeInfo(students, numStudent, "./student_list.txt");
	calculateAndPrintStats(students, numStudent);
	printStudentDetails(students, numStudent);
	searchID(students, numStudent);
	sortAndPrint(students, numStudent);

	return 0;
}

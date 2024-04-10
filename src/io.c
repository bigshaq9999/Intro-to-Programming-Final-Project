#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

#include "student.h"
#include "utils.h"

#define MAX_NAME_LENGTH 100
#define LINE_SEPARATOR "|--------------------------------------------------------------------------------------------------|\n"

#define STUDENT_ENTRIES_FORMAT "|%-12s|%-20s|%-12s|%-12s|%-12s|%-12s|%-12s|\n"
#define STUDENT_DATA_FORMAT "|%-12s|%-20s|%-12s|%-12.2f|%-12.2f|%-12.2f|%-12.2f|\n"
#define STUDENT_LIST_FILE "./student_list.txt"


void readStudentID(struct student *student, int index)
{
	char tempID[11];	// Temporary buffer to hold the ID
	while (1) {
		printf("Enter ID for student %d: ", index);
		if (scanf("%10s", tempID) != 1) {
			printf("Error reading student ID. Please try again.\n");
			while (getchar() != '\n') ;	// clear input buffer
			continue;
		}
		if (!isValidID(tempID)) {
			printf("Invalid ID. Please try again.\n");
			continue;
		}
		break;
	}
	strcpy(student->id, tempID);	// Copy the valid ID to the student structure
	getchar();		// Consume newline character
}

void readStudentName(struct student *student, int index)
{
	printf("Enter name for student %d: ", index);
	if (fgets(student->name, MAX_NAME_LENGTH, stdin) == NULL) {
		printf("Error reading student name.\n");
		return;
	}
	student->name[strcspn(student->name, "\n")] = '\0';	// Remove trailing newline
}

void readStudentBirthdate(struct student *student, int index)
{
	int day, month, year;
	while (1) {
		printf("Enter birthdate for student %d (DD/MM/YYYY): ", index);
		if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
			printf
			    ("Error reading student birthdate. Please try again.\n");
			while (getchar() != '\n') ;	// clear input buffer
			continue;
		}
		if (!isValidDate(day, month, year)) {
			printf("Invalid date. Please try again.\n");
			continue;
		}
		break;
	}
	sprintf(student->birthdate, "%02d/%02d/%04d", day, month, year);
}

void readStudentScore(float *score, char *subject, int index)
{
	printf("Enter %s score for student %d: ", subject, index);
	if (scanf("%f", score) != 1) {
		printf("Error reading %s score.\n", subject);
		return;
	}
}

void getInfo(struct student students[], int numStudents)
{
	for (int i = 0; i < numStudents; i++) {
		readStudentID(&students[i], i);
		readStudentName(&students[i], i);
		readStudentBirthdate(&students[i], i);
		readStudentScore(&students[i].scoreAlgebra, "algebra", i);
		readStudentScore(&students[i].scoreCalculus, "calculus", i);
		readStudentScore(&students[i].scoreProgramming, "programming",
				 i);
		calculateStudentAverage(&students[i]);
	}
}

void printInfo(struct student students[], int numStudent)
{
	printf(STUDENT_ENTRIES_FORMAT,
	       "ID",
	       "Name",
	       "Birthdate", "Algebra", "Calculus", "Programming", "Average");
	printf(LINE_SEPARATOR);	// take the sum of the previous formatted line
	for (int i = 0; i < numStudent; i++) {
		printf(STUDENT_DATA_FORMAT,
		       students[i].id,
		       students[i].name,
		       students[i].birthdate,
		       students[i].scoreAlgebra,
		       students[i].scoreCalculus,
		       students[i].scoreProgramming, students[i].avg);
	}
}

void writeInfo(struct student students[], int numStudent, char file[])
{
	FILE *fptr;
	fptr = fopen(STUDENT_LIST_FILE, "w");
	assert(fptr != NULL);

	fprintf(fptr, STUDENT_ENTRIES_FORMAT,
		"ID",
		"Name",
		"Birthdate", "Algebra", "Calculus", "Programming", "Average");
	fprintf(fptr, LINE_SEPARATOR);	// take the sum of the previous formatted line
	for (int i = 0; i < numStudent; i++) {
		fprintf(fptr,
			STUDENT_DATA_FORMAT,
			students[i].id, students[i].name, students[i].birthdate,
			students[i].scoreAlgebra, students[i].scoreCalculus,
			students[i].scoreProgramming, students[i].avg);
	}
	fclose(fptr);
}

void printLastName(struct student students[], int numStudent)
{
	for (int i = 0; i < numStudent; i++) {
		char *p = strrchr(students[i].name, ' ');
		if (p && *(p + 1))
			printf("\nThe last name of student at index %d is %s\n",
			       i, p + 1);
	}
}

void printOldest(struct student students[], int numStudent)
{
	int oldestIndex = 0;

	for (int i = 1; i < numStudent; i++) {
		if (compare_dates
		    (students[i].birthdate,
		     students[oldestIndex].birthdate) < 0) {
			oldestIndex = i;
		}
	}

	printf
	    ("\nThe oldest student's information:\n\tID: %s\n\tFullname: %s\n\tBirthdate: %s\n",
	     students[oldestIndex].id, students[oldestIndex].name,
	     students[oldestIndex].birthdate);
}

void printYoungest(struct student students[], int numStudent)
{
	int youngestIndex = 0;

	for (int i = 1; i < numStudent; i++) {
		if (compare_dates
		    (students[i].birthdate,
		     students[youngestIndex].birthdate) > 0) {
			youngestIndex = i;
		}
	}

	printf
	    ("\nThe youngest student's information:\n\tID: %s\n\tFullname: %s\n\tBirthdate: %s\n",
	     students[youngestIndex].id, students[youngestIndex].name,
	     students[youngestIndex].birthdate);
}


void searchID(struct student students[], int numStudent)
{
	printf("\nEnter the ID of the student you want to search: ");
	char id[100];
	scanf("%s", id);

	for (int i = 0; i <= numStudent; i++) {
		if (i == numStudent) {
			printf("\nStudent of ID %s not found!\n", id);
			break;
		}
		if (strcmp(id, students[i].id) == 0) {
			printf
			    (STUDENT_ENTRIES_FORMAT,
			     "ID", "Name", "Birthdate", "Algebra", "Calculus",
			     "Programming", "Average");
			printf(LINE_SEPARATOR);	// take the sum of the previous formatted line
			printf
			    (STUDENT_DATA_FORMAT,
			     students[i].id, students[i].name,
			     students[i].birthdate, students[i].scoreAlgebra,
			     students[i].scoreCalculus,
			     students[i].scoreProgramming, students[i].avg);
			break;
		}
	}
}

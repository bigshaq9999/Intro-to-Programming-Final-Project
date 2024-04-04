#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "student.h"
#include "functions.h"

#define MAX_NAME_LENGTH 100
#define MAX_SCORE 1000
#define NUM_SUBJECTS 3

#define LINE_SEPARATOR "|--------------------------------------------------------------------------------------------------|\n"

#define STUDENT_INFO_FORMAT "|%-12s|%-20s|%-12s|%-12s|%-12s|%-12s|%-12s|\n"
#define STUDENT_LIST_FILE "./student_list.txt"
#define DATE_FORMAT "%d/%m/%Y"

void getInfo(struct student students[], int numStudents)
{
	for (int i = 0; i < numStudents; i++) {
		printf("Enter ID for student %d: ", i);
		if (scanf("%s", students[i].id) != 1) {
			printf("Error reading student ID.\n");
			return;
		}
		getchar();	// Consume newline character

		printf("Enter name for student %d: ", i);
		if (fgets(students[i].name, MAX_NAME_LENGTH, stdin) == NULL) {
			printf("Error reading student name.\n");
			return;
		}
		students[i].name[strcspn(students[i].name, "\n")] = '\0';	// Remove trailing newline

		printf("Enter birthdate for student %d (DD/MM/YYYY): ", i);
		if (scanf("%s", students[i].birthdate) != 1) {
			printf("Error reading student birthdate.\n");
			return;
		}

		printf("Enter algebra score for student %d: ", i);
		if (scanf("%f", &students[i].scoreAlgebra) != 1) {
			printf("Error reading algebra score.\n");
			return;
		}
		printf("Enter calculus score for student %d: ", i);
		if (scanf("%f", &students[i].scoreCalculus) != 1) {
			printf("Error reading calculus score.\n");
			return;
		}
		printf("Enter programming score for student %d: ", i);
		if (scanf("%f", &students[i].scoreProgramming) != 1) {
			printf("Error reading programming score.\n");
			return;
		}

		students[i].avg =
		    (students[i].scoreAlgebra + students[i].scoreCalculus +
		     students[i].scoreProgramming) / NUM_SUBJECTS;
	}
}

void printInfo(struct student students[], int numStudent)
{
	printf(STUDENT_INFO_FORMAT,
	       "ID",
	       "Name",
	       "Birthdate", "Algebra", "Calculus", "Programming", "Average");
	printf(LINE_SEPARATOR);	// take the sum of the previous formatted line
	for (int i = 0; i < numStudent; i++) {
		printf("|%-12s|%-20s|%-12s|%-12.2f|%-12.2f|%-12.2f|%-12.2f|\n",
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

	fprintf(fptr, STUDENT_INFO_FORMAT,
		"ID",
		"Name",
		"Birthdate", "Algebra", "Calculus", "Programming", "Average");
	fprintf(fptr, LINE_SEPARATOR);	// take the sum of the previous formatted line
	for (int i = 0; i < numStudent; i++) {
		fprintf(fptr,
			"|%-12s|%-20s|%-12s|%-12.2f|%-12.2f|%-12.2f|%-12.2f|\n",
			students[i].id, students[i].name, students[i].birthdate,
			students[i].scoreAlgebra, students[i].scoreCalculus,
			students[i].scoreProgramming, students[i].avg);
	}
	fclose(fptr);
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

void printLastName(struct student students[], int numStudent)
{
	for (int i = 0; i < numStudent; i++) {
		char *p = strrchr(students[i].name, ' ');
		if (p && *(p + 1))
			printf("\nThe last name of student at index %d is %s\n",
			       i, p + 1);
	}
}

int compare_dates(const char *a, const char *b)
{
	struct tm tm_a, tm_b;
	strptime(a, DATE_FORMAT, &tm_a);
	strptime(b, DATE_FORMAT, &tm_b);
	time_t time_a = mktime(&tm_a);
	time_t time_b = mktime(&tm_b);

	return (difftime(time_a, time_b) < 0) ? -1 : 1;
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
			    ("\n|%-12s|%-20s|%-12s|%-12s|%-12s|%-12s|%-12s|\n",
			     "ID", "Name", "Birthdate", "Algebra", "Calculus",
			     "Programming", "Average");
			printf(LINE_SEPARATOR);	// take the sum of the previous formatted line
			printf
			    ("|%-12s|%-20s|%-12s|%-12.2f|%-12.2f|%-12.2f|%-12.2f|\n",
			     students[i].id, students[i].name,
			     students[i].birthdate, students[i].scoreAlgebra,
			     students[i].scoreCalculus,
			     students[i].scoreProgramming, students[i].avg);
			break;
		}
	}
}

int compareStudents(const struct student *a, const struct student *b)
{
	if (a->avg > b->avg) {
		return -1;
	} else if (a->avg < b->avg) {
		return 1;
	} else {
		return strcmp(a->id, b->id);
	}
}

void merge(struct student arr[], int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	struct student left_arr[n1], right_arr[n2];

	for (int i = 0; i < n1; i++) {
		left_arr[i] = arr[left + i];
	}
	for (int j = 0; j < n2; j++) {
		right_arr[j] = arr[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (compareStudents(&left_arr[i], &right_arr[j]) <= 0) {
			arr[k] = left_arr[i];
			i++;
		} else {
			arr[k] = right_arr[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = left_arr[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = right_arr[j];
		j++;
		k++;
	}
}

void sortDescend(struct student arr[], int left, int right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;

		sortDescend(arr, left, mid);
		sortDescend(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

#include <time.h>
#include <string.h>
#include <ctype.h>

#include "student.h"

#define DATE_FORMAT "%d/%m/%Y"

int isValidID(char *id)
{
	int length = strlen(id);
	if (length > 0 && length <= 10) {
		if (id[0] == '-') {
			return 0;	// return false if the number is negative
		}
		for (int i = 0; i < length; i++) {
			if (!(isdigit(id[i]) || isalpha(id[i]))) {
				return 0;
			}
	    }
		return 1;
	}
	return 0;
}

int isValidDate(int day, int month, int year)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int currentYear = tm.tm_year + 1900;

	if (day < 1 || day > 31) {
		return 0;
	}
	if (month < 1 || month > 12) {
		return 0;
	}
	if (year < 1900 || year > currentYear) {
		return 0;
	}
	return 1;
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

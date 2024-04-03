#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "functions.h"

int main(void) {
    int numStudent = 0;
    printf("How many students?\n");
    scanf("%d", &numStudent);
    assert(numStudent <= 1000);

    struct student students[numStudent];
    getInfo(students, numStudent);

    printInfo(students, numStudent);
    
    writeInfo(students, numStudent, "./student_list.txt");

    float maxAvg = highestGPA(students, numStudent);
    float minAvg = lowestGPA(students, numStudent); 
    float maxBP = highestBP(students, numStudent);

    printf("\nThe highest average GPA is: %.2f\n", maxAvg);
    printf("The lowest average GPA is: %.2f\n", minAvg);
    printf("The highest BP GPA is: %.2f\n", maxBP);

    printLastName(students, numStudent);

    printOldest(students, numStudent);

    printYoungest(students, numStudent);

    searchID(students, numStudent);

    printf("\nSorted list of student's GPA in descending order\n");
    sortDescend(students, 0, numStudent-1);

    printInfo(students, numStudent);

    return 0;
}

#pragma once
#include "student.h"

void getInfo(struct student students[], int numStudent);
void printInfo(struct student students[], int numStudent);
void writeInfo(struct student students[], int numStudent, char file[]);
float highestGPA(struct student students[], int numStudent);
float lowestGPA(struct student students[], int numStudent);
float highestBP(struct student students[], int numStudent);
void printLastName(struct student students[], int numStudent);
void printOldest(struct student students[], int numStudent);
void printYoungest(struct student students[], int numStudent);
void searchID(struct student students[], int numStudent);
void sortDescend(struct student students[], int left, int right);

#pragma once
#include "student.h"

void getInfo(struct student students[], int numStudent);
void printInfo(struct student students[], int numStudent);
void writeInfo(struct student students[], int numStudent, char file[]);
void printLastName(struct student students[], int numStudent);
void printOldest(struct student students[], int numStudent);
void printYoungest(struct student students[], int numStudent);
void searchID(struct student students[], int numStudent);

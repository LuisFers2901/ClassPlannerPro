
#ifndef HEADCPP_H
#define HEADCPP_H

#include <iostream>
#include <fstream>
using namespace std;

bool PensumReading(char* &Courses, int* &IDECourses, int* &HRSCourses, int* &IndexCourses, int* &ToolsCourses);
void ViewCourses(char* &Courses, int* &IDECourses, int* &HRSCourses, int* &IndexCourses, int* &ToolsCourses);
void NameCourse(char* &Courses, int* &IndexCourses, int Index);
int* CoursesOptions(char* &Courses, int* &IndexCourses, int* &ToolsCourses, int* &HRSCourses);
void SaveMatrix(int* ScheduleMatrix,  char* outputFilename);
void PrintMatrix(int* ScheduleMatrix);

//void PrintMatrix(int* ScheduleMatrix);
#endif // HEADCPP_H

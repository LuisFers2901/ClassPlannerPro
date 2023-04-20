
#ifndef HEADCPP_H
#define HEADCPP_H

#include <iostream>
#include <fstream>
using namespace std;

bool PensumReading(char* &Courses, int* &IDECourses, int* &HRSCourses, int* &IndexCourses, int* &ToolsCourses);
void ViewCourses(char* &Courses, int* &IDECourses, int* &HRSCourses, int* &IndexCourses, int* &ToolsCourses);
void NameCourse(char* &Courses, int* &IndexCourses, int Index);
int* CoursesOptions(char* &Courses, int* &IndexCourses, int* &ToolsCourses, int* &HRSCourses);
void ClassSchedules(int* &HRS);
bool ScheduleAvailability(int* ScheduleMatrix, int Day, int Hours, int ClassTime);
void UpdateMatrix(int* ScheduleMatrix, int* IDECourses, int ChosenCourses, int Day, int Hours, int ClassTime);
void SaveMatrix(int* ScheduleMatrix, int* HoursStudy);
void PrintMatrix(int* ScheduleMatrix, int* HoursStudy);
int DayInt(char Day);

#endif // HEADCPP_H

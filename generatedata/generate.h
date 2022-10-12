#pragma once
#include<iostream>
using namespace std;
typedef struct Student Student;

string RandStr(int type);//初始化姓名和学号
void BadAbsenceRate(Student *stu);//5-8缺勤人数的选择并生成缺勤记录
void SingleAbsence(Student *stu);//单次课每次0-3人缺勤
Student *AttendanceSheet();//生成考勤表
void WriteFile(string filename);//考勤表读入文件，生成txt文件
int CmpGrade(const void* a, const void* b); 
int CmpString(const void* a, const void* b);

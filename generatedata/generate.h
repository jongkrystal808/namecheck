#pragma once
#include<iostream>
using namespace std;
typedef struct Student Student;

string RandStr(int type);//初始化姓名 
void BadAbsenceRate(Student *stu);//5-8人缺勤人数的确定 
void SingleAbsence(Student *stu);//每次课程0-3人次数随机确定 
Student *AttendanceSheet();//生成考勤表 
void WriteFile(string filename);//将考勤表写入数据中 
int CmpGrade(const void* a, const void* b); 
int CmpString(const void* a, const void* b);

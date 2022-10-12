#pragma once
#include<iostream>
using namespace std;
#ifndef _READFILE_H_
#define _READFILE_H_
extern int TotalRequest;
extern int ValidRequest;
typedef struct Student{
	string name;
	string num;
	double gpa;
    int Attend[20];
    int Absence_Rate;
    int Attend_Rate;
}Student;


Student *ReadFile(string filename); //读入文件的函数
int RandomRollCall2(int i, int Pre_absenceCount,Student *stu,int c[21][91],int a[21][91]); 
void Random_Roll_Call(Student *stu);
int CmpGrade(const void* a, const void* b);
void ReadFiveCourse();
void PrintE();
#endif



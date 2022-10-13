#include<fstream>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "readfile.h"
int TotalRequest=0;
int	ValidRequest=0;
Student *ReadFile(string filename){ 
	ifstream infile;
	string n;
	infile.open(filename.c_str());
	for(int i=0; i<5; i++) infile >> n;
	Student *stu = new Student[90];
	for(int i=0; i<90; i++)
	{
		infile >> stu[i].name;
		infile >> stu[i].num;
		infile >> stu[i].gpa;
		infile >> stu[i].CourseCommitte;
		infile >> stu[i].Trust; 
		for(int j=0; j<20; j++)
		{
			infile >> stu[i].Attend[j];
		}
		stu[i].AbsenceRate = 0;
	}
	infile.close();
	return stu;
}

int RandomRollCall2(int i, int Pre_absenceCount,Student *stu,int c[21][91],int a[21][91])
{
	int absence_count = 0; 
	TotalRequest += Pre_absenceCount; //之前缺勤的那几个这一次一定点
	for(int j=0; j<Pre_absenceCount; j++)
	{
		if(stu[c[i-1][j]].Attend[i-1] == 0)
		{
			c[i][absence_count] = c[i-1][j];
			a[i][c[i-1][j]] = 1;
			stu[c[i-1][j]].Trust -= 0.1;
			stu[c[i-1][j]].AbsenceRate++;
			ValidRequest++;
			absence_count++;
		} 
		else if(stu[c[i-1][j]].Attend[i-1] == 1 && stu[c[i-1][j]].AbsenceRate >= 1) //如果之前缺勤已经超过2次，即使这次到了，下次也点它； 
		{
			c[i][absence_count] = c[i-1][j];
			a[i][c[i-1][j]] = 1;
			absence_count++;
		}
	}
	if(i == 2 && absence_count < 3)
	{
		Student *stu1 = stu;
		qsort(stu1+70,20,sizeof(Student),CmpTrust);
		for(int j=85; j<90; j++)
		{
			if(a[i-1][stu1[j].flag] == 1) continue;//这次已经点过了就不点
			TotalRequest++;
			if(stu1[j].Attend[i-1] == 0)
			{
				c[i][absence_count] = stu1[j].flag;
				a[i][stu1[j].flag] = 1;
				stu[stu1[j].flag].Trust -= 0.1;
				stu[stu1[j].flag].AbsenceRate++;
				ValidRequest++;
				absence_count++;
			 } 
		}
		cout << endl;
	}
	return absence_count;
}

void Random_Roll_Call(Student *stu)
{
	int check[21][91];//缺勤人数号码的 
	int absence[21][91];
	memset(check,0,sizeof(int)*21*91);
	memset(absence,0,sizeof(int)*21*91);
	int radomnum;
	int blacklist[90];
	//第一次抽点 
	qsort(stu+70,20,sizeof(Student),CmpTrust);
	for(int i=0; i<90; i++) stu[i].flag = i;
	TotalRequest += 8;//第一次抽点信任值靠后10名
	int temp = 8;
	int absence_count=0;
	for(int i=89; i>50; i--)
	{
		if(stu[i].CourseCommitte == 1) continue;//如果他被认定为是班委，我们认为他会改过自新不抽点它 
		else{
			//发出抽点请求 
			temp--;
			if(temp < 0) break;
			if(stu[i].Attend[0] == 0 )
			{
				check[1][absence_count] = i;
				absence[1][i] = 1;
				stu[i].Trust -= 0.1;
				stu[i].AbsenceRate++;
				ValidRequest++;
				absence_count++;
			}
		}
	}
	int curr_AbsenceCount = absence_count;
	for(int i=2; i<=20; i++) 
	{
		curr_AbsenceCount = RandomRollCall2(i,curr_AbsenceCount,stu,check,absence);
	}
	
}

int CmpGrade(const void* a, const void* b)
{
	double ret = ((Student*)a)->gpa - ((Student*)b)->gpa;
    if(ret > 0) return -1;
    else if(ret < 0) return 1;
    else return 0;
}
int CmpTrust(const void* a, const void* b)
{
	double ret = ((Student*)a)->Trust - ((Student*)b)->Trust;
    if(ret > 0) return -1;
    else if(ret < 0) return 1;
    else return 0;
}
void ReadFiveCourse()
{
	string filename[5] = {"course1.txt","course2.txt","course3.txt","course4.txt","course5.txt"};
	for(int i=0; i<5; i++)
	{
		Student *stu = new Student[90];
		stu = ReadFile(filename[i]);
		qsort(stu,90,sizeof(Student),CmpGrade);
		int v = ValidRequest;
		int t = TotalRequest;
		Random_Roll_Call(stu);
		cout << "该门课程本学期抽点的总人数为：" << TotalRequest-t <<",有效抽点人数为：" << ValidRequest-v << endl;
	}
}

void PrintE()
{
	double E = (ValidRequest*1.0) / (TotalRequest*1.0) ;
	cout << "本次抽点中E=" << E << endl;
}



#include<fstream>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "readfile.h"
int TotalRequest;
int	ValidRequest;
Student *ReadFile(string filename){ 
	ifstream infile;
	infile.open(filename.c_str());
	Student *stu = new Student[90];
	for(int i=0; i<90; i++)
	{
		infile >> stu[i].name;
		infile >> stu[i].num;
		infile >> stu[i].gpa;
		for(int j=0; j<20; j++)
		{
			infile >> stu[i].Attend[j];
		}
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
			stu[c[i-1][j]].Absence_Rate++;
			ValidRequest++;
			absence_count++;
		} 
		else if(stu[c[i-1][j]].Attend[i-1] == 1 && stu[c[i-1][j]].Attend_Rate <= 4) //如果之前到的次数小于4，我们也要点它。 
		{
			c[i][absence_count] = c[i-1][j];
			a[i][c[i-1][j]] = 1;
			stu[c[i-1][j]].Absence_Rate++;
			absence_count++;
			stu[c[i-1][j]].Attend_Rate++;
		}
		else 
		{
			stu[c[i-1][j]].Attend_Rate++;
		 } 
	}
	if(Pre_absenceCount <= 2)//第一次抽点到的人数较少，为了提高抽点效率，在抽点一次 
	{
		for(int j=85; j<90; j++) 
		{
			if(a[i-1][j] == 1) continue;
			else
			{
				if(stu[c[i-1][j]].Attend[i-1] == 0)
				{
					c[i][absence_count] = c[i-1][j];
					a[i][c[i-1][j]] = 1;
					stu[c[i-1][j]].Absence_Rate++;
					ValidRequest++;
					absence_count++;
				} 
				TotalRequest++;
			}
		}
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
	int absence_count=0;
	int blacklist[90];
	//第一次抽点 
	TotalRequest+=18; //第一次抽点18人，从名单后面抽取 
	for(int i=72; i<90; i++) 
	{
		if(stu[i].Attend[0] == 0) 
		{
			check[1][absence_count] = i; //表示缺勤 
			absence[1][i] = 1;
			absence_count++;
			stu[i].Absence_Rate++;
		}
	}
	ValidRequest += absence_count;
	int curr_AbsenceCount = absence_count;
	for(int i=2; i<=10; i++) 
	{
		curr_AbsenceCount = RandomRollCall2(i,curr_AbsenceCount,stu,check,absence);
	}
	//确定黑名单 
	int black_count = 0;
	for(int i=1; i<=90; i++)
	{
		if(stu[i].Absence_Rate >= 3)
		{
			blacklist[black_count] = i;
			black_count++;
		}
	}
	for(int i=10; i<20; i++)
	{
		for(int j=0; j<black_count; j++)
		{
			TotalRequest++;
			if(stu[blacklist[j]].Attend[i] == 0) 
				ValidRequest ++;
		}
	}
}

int CmpGrade(const void* a, const void* b)
{
	double ret = ((Student*)a)->gpa - ((Student*)b)->gpa;
    if(ret > 0) return -1;
    else if(ret < 0) return 1;
    else return 0;
}
void ReadFiveCourse()
{
	for(int i=0; i<5; i++)
	{
		Student *stu = new Student[90];
		string filename;
		cout << "请输入考勤表文件的路径>";
		cin >> filename;
		stu = ReadFile(filename);
		qsort(stu,90,sizeof(Student),CmpGrade);
		int v = ValidRequest;
		int t = TotalRequest;
		Random_Roll_Call(stu);
		cout << "该门课程本学期抽点的总人数为：" << TotalRequest-t <<",有效抽点人数为：" << ValidRequest-v << endl;
		double E = (ValidRequest*1.0) / (TotalRequest*1.0) ;
		cout << "本次抽点中E=" << E << endl;
	}
}

void PrintE()
{
	cout << "抽点方案为：第1次抽取绩点后18名同学，第2-10次抽点前一次缺勤的同学，如果他之前的签到率少于4次，也要加入下一次的抽点名单."; 
	cout << "在2-10次抽点中如抽到人数小于2，就在绩点后10名在抽一次.如果缺勤次数大于3次就拉入黑名单，后面十次专门点黑名单上的人。" << endl;
	double E = (ValidRequest*1.0) / (TotalRequest*1.0) ;
	cout << "本次抽点中E=" << E << endl;
}



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
	TotalRequest += Pre_absenceCount; //֮ǰȱ�ڵ��Ǽ�����һ��һ����
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
		else if(stu[c[i-1][j]].Attend[i-1] == 1 && stu[c[i-1][j]].Attend_Rate <= 4) //���֮ǰ���Ĵ���С��4������ҲҪ������ 
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
	if(Pre_absenceCount <= 2)//��һ�γ�㵽���������٣�Ϊ����߳��Ч�ʣ��ڳ��һ�� 
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
	int check[21][91];//ȱ����������� 
	int absence[21][91];
	memset(check,0,sizeof(int)*21*91);
	memset(absence,0,sizeof(int)*21*91);
	int radomnum;
	int absence_count=0;
	int blacklist[90];
	//��һ�γ�� 
	TotalRequest+=18; //��һ�γ��18�ˣ������������ȡ 
	for(int i=72; i<90; i++) 
	{
		if(stu[i].Attend[0] == 0) 
		{
			check[1][absence_count] = i; //��ʾȱ�� 
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
	//ȷ�������� 
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
		cout << "�����뿼�ڱ��ļ���·��>";
		cin >> filename;
		stu = ReadFile(filename);
		qsort(stu,90,sizeof(Student),CmpGrade);
		int v = ValidRequest;
		int t = TotalRequest;
		Random_Roll_Call(stu);
		cout << "���ſγ̱�ѧ�ڳ���������Ϊ��" << TotalRequest-t <<",��Ч�������Ϊ��" << ValidRequest-v << endl;
		double E = (ValidRequest*1.0) / (TotalRequest*1.0) ;
		cout << "���γ����E=" << E << endl;
	}
}

void PrintE()
{
	cout << "��㷽��Ϊ����1�γ�ȡ�����18��ͬѧ����2-10�γ��ǰһ��ȱ�ڵ�ͬѧ�������֮ǰ��ǩ��������4�Σ�ҲҪ������һ�εĳ������."; 
	cout << "��2-10�γ������鵽����С��2�����ڼ����10���ڳ�һ��.���ȱ�ڴ�������3�ξ����������������ʮ��ר�ŵ�������ϵ��ˡ�" << endl;
	double E = (ValidRequest*1.0) / (TotalRequest*1.0) ;
	cout << "���γ����E=" << E << endl;
}



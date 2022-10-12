#include<fstream>
#include<stdlib.h>
#include<time.h> 
#include<random>
#include<iomanip>
#include"generate.h"
typedef struct Student{
	string name;
	string num;	//学号
	double gpa; //绩点 
	int Attend[20]; //缺勤 0=缺勤，1=未缺勤 ,初始化为2 
	int flag; //确定5-8后不跟0-3的缺勤重复 
}Student;

string RandStr(int type)  
{
    /*初始化*/
    string str1 = "0320"; 
	string NA1[15] =  { "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋", "沈", "韩"};
	string NA2[40] = { "伟", "刚", "勇", "毅", "俊", "峰", "强", "军", "平", "保", "东", "文", "辉", "力", "明", "永", "健", "世", "广", "志", "瑗", "琰", "韵", "融", "园", "艺", "咏", "卿", "聪", "澜", "纯", "毓", "悦", "昭", "冰", "爽", "琬", "茗", "羽", "希" };
	string name;
	if(type == 1)               
    {
    	char c;                  
		for(int idx = 4;idx < 9;idx ++)
		{
		    c = '0' + rand()%10;
		    str1.push_back(c);       /*push_back()是string类尾插函数。这里插入随机字符c*/
		}
		return str1;                 /*返回生成的随机字符串*/
	}
	else
	{
		name = NA1[rand()%15];
		name += NA2[rand()%40];
		return name;
	}
}
void SingleAbsence(Student *stu)
{
	for(int j=0; j<20; j++) //每一次课的缺勤人数为count 
	{
		srand((unsigned)time(NULL));
		int count = rand() % 4;//[0,3]
		while(count) 
		{
			int Absence_Num = rand() % 90;
			if(stu[Absence_Num].flag == 1)
			{
				continue;
			}
			else
			{
				stu[Absence_Num].Attend[j] = 0;
				count--;
			}
		}
		for(int q=0; q<90; q++)
		{
			if(stu[q].Attend[j] == 0) continue;
			else stu[q].Attend[j] == 1;
		}
	}
}

void BadAbsenceRate(Student *stu)
{
	static normal_distribution<double> normal(85, 5);
   	static default_random_engine e;
   	int Absence_Count = rand()%4 + 5;
	while(Absence_Count)
	{
		int Absence_Num = normal(e);
		if(stu[Absence_Num].flag == 1 || Absence_Num >= 90 || Absence_Num < 0) continue;
		stu[Absence_Num].flag = 1;
		/*���ɲ��ظ����ĸ����ִ���δȱ�ڵ��Ĵ�*/
		int a[20];
		for(int j=0; j<20; j++)
		{
			a[j] = j;
		}
		for(int j=19; j>=1; j--)
		{
			swap(a[j],a[rand()%j]);
		}
		for(int j=0; j<16; j++)
		{
			stu[Absence_Num].Attend[a[j]] = 0;
		}
		for(int j=0; j<20; j++)
		{
			if(stu[Absence_Num].Attend[j] == 0) continue;
			else  stu[Absence_Num].Attend[j] == 1;
		}
		Absence_Count--;
	}
}



Student *AttendanceSheet()
{
	Student *stu = new Student[90];
	for(int i=0; i<90; i++)
	{
		for(int j=0; j<20; j++)
			stu[i].Attend[j] = 1;
			stu[i].num = RandStr(1);
			stu[i].name = RandStr(2);
	}
	static uniform_real_distribution<double> g(1, 4);
    static default_random_engine e;
    for(int i=0; i<90;i++ ) 
	{
		stu[i].gpa = g(e);
	}
	qsort(stu,90,sizeof(Student),CmpGrade);
	BadAbsenceRate(stu);
	SingleAbsence(stu);
	qsort(stu,90,sizeof(Student),CmpString);
	return stu;
}

void WriteFile(string filename)
{
	ofstream dataFile;
	dataFile.open(filename.c_str(), ofstream::app);
	fstream file(filename.c_str(), ios::out);

	Student *stu = new Student[90];
	stu = AttendanceSheet();
	
	for (int i=0; i<90; i++)
	{
		dataFile << stu[i].name <<' '  <<stu[i].num<< ' '<< fixed << setprecision(5)<<stu[i].gpa << ' ' ;     // д������
		for(int j=0; j<20; j++)
			dataFile << stu[i].Attend[j]<< ' ' ; 
		dataFile << endl;
	}
	dataFile << endl;    
	dataFile.close();  // �ر��ĵ�
	cout << filename << "���ɳɹ���" << endl;; 
	
}

int CmpGrade(const void* a, const void* b)
{
	double ret = ((struct Student*)a)->gpa - ((struct Student*)b)->gpa;
    if(ret > 0) return -1;
    else if(ret < 0) return 1;
    else return 0;
}

int CmpString(const void* a, const void* b)
{
	return ((struct Student*)a)->num > ((struct Student*)b)->num;
}

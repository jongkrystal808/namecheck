#include<fstream>
#include<stdlib.h>
#include<time.h> 
#include<random>
#include<iomanip>
#include"generate.h"
typedef struct Student{
	string name;//姓名 
	string num;	//学号 
	double gpa; //绩点
	int Attend[20]; //考勤，1为到，0为缺勤 
	int flag; //存放原先的序号 
	int CourseCommitte;//是否为班委 
	double Trust; //信任分，由过往考勤记录和辅导员评价生成，1-5分 
}Student;

string RandStr(int type)  
{
    /*初始化*/
    string str1 = "0320"; 
	string NA1[20] =  { "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋", "沈", "韩", "杨", "朱", "秦", "尤", "许"};
	string NA2[41] = { "伟", "刚", "勇", "毅", "俊", "峰", "强", "军", "平", "保", "东", "文", "辉", "力", "明", "永", "健", "世", "广", "志", "义", "兴" ,"秀", "娟", "英", "华", "慧", "巧", "美", "娜", "静", "淑", "惠", "珠", "翠", "雅", "芝", "玉", "萍", "红", "娥"}; 
	string name;
	if(type == 1)               
    {
    	char c;                  
		for(int idx = 4;idx < 9;idx ++)
		{
		    c = '0' + rand()%10;
		    str1.push_back(c);       
		}
		return str1;                 
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
	srand((unsigned)time(NULL));
	for(int j=0; j<20; j++) 
	{
		int count = rand() % 4;//[0,3]
		//cout << count << endl;
		while(count) 
		{
			int Absence_Num = rand() % 90;
			if(stu[Absence_Num].flag == 1 )
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
	static normal_distribution<double> normal(85, 3);
   	static default_random_engine e;
   	static uniform_real_distribution<double> t(0, 1);
    static default_random_engine e1;
   	int Absence_Count = rand()%4 + 5;
	while(Absence_Count)
	{
		int Absence_Num = normal(e);
		if(stu[Absence_Num].flag == 1 || Absence_Num >= 90 || Absence_Num < 0 || stu[Absence_Num].CourseCommitte == 1) continue;
		stu[Absence_Num].flag = 1;
		stu[Absence_Num].Trust = t(e1) + 0.5;//如果是本门课程缺勤率80%则认为他以往的信任值不高 
		/*生成不重复的16个数字序列代表缺勤*/
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
		stu[i].CourseCommitte = 0;
		stu[i].flag = 0;
		stu[i].Trust = 0;
	}
	static uniform_real_distribution<double> g(1, 4);
    static default_random_engine e;
    static uniform_real_distribution<double> t1(0, 1);
    static default_random_engine e2;
    for(int i=0; i<90;i++ ) 
	{
		stu[i].gpa = g(e);
	}
	qsort(stu,90,sizeof(Student),CmpGrade);
	int cnum = 5;//每门课5个班委 
	while(cnum >= 3) 
	{
		int num = rand()%30;//前30名选择3个作为班委
		if(stu[num].CourseCommitte == 1) continue;
		stu[num].CourseCommitte = 1;
		cnum--; 
	}
	while(cnum)
	{
		int num = rand()%20+30;//30-49选择2个作为班委
		if(stu[num].CourseCommitte == 1) continue;
		stu[num].CourseCommitte = 1;
		cnum--; 
	}
	BadAbsenceRate(stu);
	SingleAbsence(stu);
	for(int i=0; i<30; i++)
	{
		double trust = t1(e2)+4;
		if(stu[i].Trust != 0) continue;
		stu[i].Trust = trust;
	}
	for(int i=30; i<65; i++)
	{
		double trust = t1(e2)+3;
		if(stu[i].Trust != 0) continue;
		stu[i].Trust = trust;
	}
	for(int i=65; i<75; i++)
	{
		double trust = t1(e2)+2;
		if(stu[i].Trust != 0) continue;
		stu[i].Trust = trust;
	}
	for(int i=75; i<90; i++)
	{
		double trust = t1(e2)+1;
		if(stu[i].Trust != 0) continue;
		stu[i].Trust = trust;
	}
	return stu;
}

void WriteFile(string filename)
{
	ofstream dataFile;
	dataFile.open(filename.c_str(), ofstream::app);
	fstream file(filename.c_str(), ios::out);
	Student *stu = new Student[90];
	stu = AttendanceSheet();
	qsort(stu,90,sizeof(Student),CmpString); 
	dataFile << "姓名      学号          绩点    职位  信任值" <<endl; 
	
	for (int i=0; i<90; i++)
	{
		dataFile << stu[i].name <<"  "  <<stu[i].num<< "  "<< fixed << setprecision(5)<<stu[i].gpa << "   " <<stu[i].CourseCommitte << "   " << stu[i].Trust << "  ";     // 写锟斤拷锟斤拷锟斤拷
		for(int j=0; j<20; j++)
			dataFile << stu[i].Attend[j]<< "  " ; 
		dataFile << endl;
	}
	dataFile << endl;    
	dataFile.close();  
	cout << filename << "生成成功！" << endl; 
	
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

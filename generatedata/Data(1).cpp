#include"generate.h"
int main()
{
	string filenames[5]={"course1.txt","course2.txt","course3.txt","course4.txt","course5.txt"};
	for(int i=0; i<5; i++)
	{
		WriteFile(filenames[i]);
	}
	return 0;
}
	
		


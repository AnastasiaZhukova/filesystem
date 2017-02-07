#include "filelib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>

using namespace std;

const int NumOfCls = 720;
const int SizeOfCls = 512;
const unsigned int DiskSize = NumOfCls*SizeOfCls;


int main()
{
	


	int**Clasters = new int*[NumOfCls+1];
	for (int i = 0; i <= NumOfCls; i++)
	{
		Clasters[i] = new int[3];
	}

	string FAT;
	
	ifstream infat("fat.txt", ios_base::in);
	ifstream incls("clasters.txt", ios_base::in);
	if (!infat.is_open() || !incls.is_open())
	{
		ofstream offat("fat.txt",ios_base::trunc);
		FatForm(FAT, infat);
		ofstream ofcls("clasters.txt", ios_base::trunc);
		NewCls(Clasters,ofcls,NumOfCls);
	
	}

	else
	{
		Cls(Clasters, incls, NumOfCls);	
		FatForm(FAT, infat);
	}
	
	ofstream ofcls("clasters.txt", ios_base::trunc);
	ofstream offat("fat.txt", ios_base::trunc);
	

	char buff[12];
	cout << "Hello! Input command (input 'help' for more information) : ";
	do
	{
		reform(Clasters, FAT, NumOfCls);
		cout <<endl<< "-->"; cin >> buff;
		
		if (!strcmp(buff,"dir"))
		{
			/*reform(Clasters, FAT, NumOfCls, ofcls, offat);*/
			dir(FAT);
		
		}
		else if (!strcmp(buff, "info" ))
		{
			info(Clasters, NumOfCls, SizeOfCls);
			
		}
		else if (!strcmp(buff, "copy"))
		{
			string filename;
			int size;
			cout << "input name : "; cin>>filename;
			cout << "input size : "; cin >> size;
			copy(Clasters,FAT, filename, size);
		/*	reform(Clasters, FAT, NumOfCls, ofcls, offat);*/
			
		}
		else if (!strcmp(buff, "help"))
		{
			help();
		
		}
		else if (!strcmp(buff, "claster"))
		{
			claster(Clasters, NumOfCls);
			
		}
		else if (!strcmp(buff,"fullclaster" ))
		{
			fullclaster(Clasters, NumOfCls);
			
		}
		else if (!strcmp(buff,"del" ))
		{
			string filename;
			cout << "input name of file you want to delete : ";
			cin >> filename;
			del(Clasters, FAT, filename);
		
		}
		else if (!strcmp(buff,"format" ))
		{
			format(Clasters,FAT,NumOfCls);	
			
		}
		else if (!strcmp(buff,"exit" ))
		{
			cout << "Goodbye!" << endl;
			
			break;
		}
		else cout << "Wrong command!";
		
	} while (true);


	reform(Clasters, FAT, NumOfCls/*, ofcls, offat*/);
	return 0;
}

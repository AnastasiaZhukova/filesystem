#define _CRT_SECURE_NO_WARNINGS
#include "filelib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <string.h>

using namespace std;
const int NumOfCls = 720;
const int SizeOfCls = 512;


void ClsForm(int **Clasters, const int NumOfCls)
{
	for (int i = 1; i <= NumOfCls; i++)
	{
		Clasters[i][0] = i;
		Clasters[i][1] = 777;
		Clasters[i][2] = 0;
	}
}
void FatForm(string &FAT, ifstream&infat)
{
	getline(infat, FAT);
	//cout << "FAT " << FAT;

}
void NewCls(int **Clasters,ofstream&ofcls,const int NumOfCls)
{
	ClsForm(Clasters, NumOfCls);
	for (int i = 1; i <= NumOfCls; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ofcls << Clasters[i][j];
			ofcls << " ";
		}
	}
}
void Cls(int **Clasters, ifstream&incls, const int NumOfCls)
{
	for (int i = 1; i <= NumOfCls; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			incls >> Clasters[i][j];
		}
	}
}
int FindFile(string FAT, string filename)
{
	bool bl;
	int i = 0;
	for (i = 0; FAT[i] != '\0'; i++)
	{
		bl = true;

		{
			for (int j = 0; filename[j] != '\0'; j++)
			{
				
				if (FAT[i + j] != filename[j]) { bl = false; break; }
				if (filename[j + 1] == '\0' && (FAT[i + j + 1]) != ' ' || (FAT[i + j + 1]) != '\0') { bl = false; }
				if (filename[j + 1] == '\0' && (FAT[i + j + 1]) == ' ' || (FAT[i + j + 1]) == '\0') { return i; }

			}

			if (bl) return i;
		}
	}
	return -1;

}
int StartCls(string FAT, string filename)
{
	int n=FindFile(FAT, filename);

	if (n != -1)
	{
		int StartCls = 0;
		char fortime[2];
		for (int j=n; /*(*FAT)[j]!='\0'*/; j++)
		{
			if ((FAT)[j] != ' ') continue;
			else
			{
				for (int k = j + 1; FAT[k]!= ' '; k++)
				{
					fortime[0] = FAT[k];
					StartCls = StartCls * 10 + atoi(fortime);
				}
				return StartCls;
			}
		}
	}
	else return -1;

}
int SizeOfFile(string FAT,string filename)
{
	int n = FindFile(FAT, filename);
	if (n != -1)
	{
		int count = 0;
		int size = 0;
		char fortime[1];
		for (int j = n; /*(*FAT)[j]!='\0'*/; j++)
		{
			if (FAT[j] != ' ') continue;
			else count++;
			if (count == 2)
			{
				for (int k = j + 1; (FAT)[k] != ' '; k++)
				{
					fortime[0] = FAT[k];
					size = size * 10 + atoi(fortime);
				}
				return size;
			}

		}
	}
	else return -1;


}
int DiskCheck(int **Clasters, int ClsNeed)
{
	int count = 0;
	for (int i = 1; i <= NumOfCls; i++)
	{
		if (Clasters[i][1] == 777) count++;
		else if(Clasters[i][1] != 777) count = 0;
		if (count == ClsNeed) { return (i - count + 1); }
		else continue;
	}
	return -1;
}
int EmptyClasters(int **Clasters, const int NumOfCls)
{
	int fullcount = 0;
	for (int i = 1; i <= NumOfCls; i++)
	{
		if (Clasters[i][1] == 778) fullcount++;
	}
	return NumOfCls - fullcount;
}
void dir(string FAT)
{
	int count = 0;
	if ((FAT).length() == 0) cout << "Disk is empty!" << endl;
	else
	{
		for (int i = 0; (FAT)[i] != '\0'; i++)
		{
			if ((FAT)[i] != ' ' && count!=1) cout << (FAT)[i];
			if ((FAT)[i] == ' ') count++;
			if (count == 2 && FAT[i] == ' ') cout << " ";
			if (count ==3) {count = 0; cout << endl;}
		}
	}

}

void copy(int **Clasters, string &FAT, string filename, int size)
{
	int ClsNeed = size / SizeOfCls;
	if (size%SizeOfCls != 0) ClsNeed++;
	int StartCls = DiskCheck(Clasters, ClsNeed);
	
	if (StartCls != -1)
	{
		for (int i = 0; i < ClsNeed; i++)
		{
			Clasters[StartCls + i][1] = 778;
			if (i == ClsNeed - 1) Clasters[StartCls + i][2] = 0;
			else Clasters[StartCls + i][2] = StartCls + i + 1;	
		}
		string StartClsStr = to_string(StartCls);
		string SizeStr = to_string(size);
		FAT += filename + " " + StartClsStr + " " + SizeStr + " ";
		cout << "Success!" << endl;
		/*char cls[17]; itoa(StartCls, cls, 10); char si[17]; itoa(size, si, 10);*/
		
		/*FAT += filename;
		FAT+=*/

	}
	else cout << "Not enough space" << endl;
}

void info(int **Clasters, const int NumOfCls, const int SizeOfCls)
{
	int fullcount = 0;
	long int SizeOfDisk = NumOfCls*SizeOfCls;
	cout << "Name of disk : DISK" << endl;
	cout << "Size of disk : " << SizeOfDisk << endl;
	long int EmptySpace = EmptyClasters(Clasters, NumOfCls)*SizeOfCls;
	cout << "Empty space : " << EmptySpace << endl;
	cout << "Size of claster : " << SizeOfCls << endl;
	cout << "Number of clasters : " << NumOfCls << endl;
	int NumOfEmptyCls = EmptyClasters(Clasters, NumOfCls);
	cout << "Number of empt clusters : " << NumOfEmptyCls << endl;
}

void claster(int **Clasters, const int NumOfCls)
{
	setw(10);
	for (int i = 1; i <= NumOfCls; i++)
	{
		if (Clasters[i][1] == 778) cout << "*";
		else cout << "|";
	}
}

void fullclaster(int **Clasters, const int NumOfCls)
{
	char ch;
	setw(10);
	ch = (char)rand() % 15 + 34;
	for (int j = 1; j < NumOfCls; j++)
	{
		if (Clasters[j][1] == 778 && Clasters[j][2] != 0)
		{
			cout << ch;
		}
		else if (Clasters[j][1] == 778 && Clasters[j][2] == 0)
		{
			cout << ch;
			ch = (char)rand() % 15 + 33;
		}
		else cout << "|";
	}
}

void del(int **Clasters, string &FAT, string filename)
{

	int n = StartCls(FAT, filename);
	if (n != -1)
	{
		for (int i = n; ; i++)
		{
			if (Clasters[i][2] != 0)
			{
				Clasters[i][1] = 777;
				Clasters[i][2] = 0;
			}
			else { Clasters[i][1] = 777;  break; }
		}

		int s = FindFile(FAT, filename);
		int len = 0; int count = 0;
		for (int i = s; ; i++)
		{
			if (count < 3) len++;
			if ((FAT)[i] == ' ') count++;
			if (count == 3) break;
		}
		
		FAT.erase(s, len);
		cout << "Deleted" << endl;
	}
	else cout << "File not found" << endl;

}

void format(int **Clasters,string &FAT ,const int NumOfCls)
{
	ClsForm(Clasters, NumOfCls);
	int len = (FAT).length();
	(FAT).erase(0, len);
	cout << "DISK was formated successfully" << endl;
}

void help(void)
{
	cout << "--dir -- list of files \n--info -- information about disk \n--copy -- record a file\n--help -- list of commands\n--claster -- graphic interpretation\n--fullclaster -- full graphic interpretation\n--del -- delete a file\n--format -- format disk\n--exit -- exit\n";
}

void reform(int **Clasters, string &FAT ,const int NumOfCls/*, ofstream&ofcls, ofstream&offat*/)
{
	/*cout << "FAT " << FAT << endl;*/
	ofstream offat("fat.txt", ios_base::trunc);
	ofstream ofcls("clasters.txt", ios_base::trunc);
	for (int i = 1; i <= NumOfCls; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ofcls << Clasters[i][j];
			ofcls << " ";
		}
	}

	offat << FAT;
}


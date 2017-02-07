#include <iostream>
#ifndef filelib_pp7
#define filelib_pp7

using namespace std;
void ClsForm(int **, const int );
void FatForm(string&, ifstream& );
void NewCls(int**, ofstream&,const int);
void Cls(int **, ifstream&, const int);
int FindFile(string , string );
int EmptyClasters(int **, const int );
void dir(string);
void info(int **, const int , const int );
void copy(int **, string& , string , int);
void del(int **, string& , string );
void claster(int **, const int);
void fullclaster(int **, const int);
void format(int **, string& ,const int);
void help(void);
void reform(int**, string& ,const int/*, ofstream&, ofstream&*/);
#endif 

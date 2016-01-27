// fileTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
//#include <cmath>
#include <sstream>
#include <string>
using namespace std;

const char * file = "planets.data";
const int Name_Limit = 20;
struct planet
{
	char name[20];
	double population;
	double gravity;
};

inline void eatline(){while(cin.get()!='\n') continue;}

int fileFunc(int Mode)
{
	cout<<fixed<<right;
	planet pl;
	
	switch(Mode)
	{
		case 1:
		{
			ifstream fin(file,ios_base::in | ios_base::binary);
			if(fin.is_open())
			{
				cout<<"here is content of the "<<file<<endl;
				while(fin.read((char *)&pl,sizeof(pl)))
				{
					cout<<setw(12)<<pl.name<<": "
						<<setprecision(0)<<setw(12)<<pl.population
						<<setprecision(2)<<setw(6)<<pl.gravity<<endl;
				}
				fin.close();
			}
			ofstream fout(file,ios::out | ios::binary | ios_base::app);
			if(!fout.is_open())
			{
				cerr<<"can't open"<<file<<endl;
				exit(EXIT_FAILURE);
			}

			cout<<"Enter planet name : ";
			cin.get(pl.name,Name_Limit);
			while(pl.name[0]!='\0')
			{
				eatline();
				cout<<"Enter the population of this planet: ";
				cin>>pl.population;
				cout<<"Enter the gravity of this planet: ";
				cin>>pl.gravity;
				eatline();

				fout.write((char *)&pl,sizeof(pl));
				cout<<"Enter next planet name (blank to quit)"<<endl;
				cin.get(pl.name,Name_Limit);
			}
			fout.close();

			fin.clear();
			fin.open(file,ios_base::in | ios_base::binary);
			if(fin.is_open())
			{
				cout<<"Here is new content of the "<<file<<endl;
				while(fin.read((char *)&pl,sizeof pl))
				{
					cout<<setw(12)<<pl.name<<": "
						<<setprecision(0)<<setw(12)<<pl.population
						<<setprecision(2)<<setw(6)<<pl.gravity<<endl;
				}
				fin.close();
			}
			break;
		}
		case 2:
		{
			fstream fio;
			fio.open(file,ios_base::in | ios_base::out | ios_base::binary);
			if(fio.is_open())
			{
				int totalRec = 0;
				fio.seekg(0);
				cout<<"Here are the content of the "<<file<<endl;
				while(fio.read((char *)&pl,sizeof pl))
				{
					cout<<setw(12)<<pl.name<<": "
						<<setprecision(0)<<setw(12)<<pl.population
						<<setprecision(2)<<setw(6)<<pl.gravity<<endl;
					totalRec = totalRec + 1;
				}
				if(fio.eof()) fio.clear();
				else {cerr<<"Error in reading";exit(EXIT_FAILURE);}

				int rec;
				cout<<"Enter the recorde you want to modify.\n";
				cin>>rec;

				rec = min(totalRec,max(1,rec)) -1;
				streampos sps = rec*sizeof(pl);
				fio.seekg(sps);

				fio.read((char *)&pl,sizeof pl);
				cout<<"your selection is: \n";
				cout<<setw(12)<<pl.name<<": "
					<<setprecision(0)<<setw(12)<<pl.population
					<<setprecision(2)<<setw(6)<<pl.gravity<<endl;

				if (fio.eof()) fio.clear();
				eatline();
				cout<<"Enter planet name : ";
				cin.get(pl.name,Name_Limit);
			
				eatline();
				cout<<"Enter the population of this planet: ";
				cin>>pl.population;
				cout<<"Enter the gravity of this planet: ";
				cin>>pl.gravity;
			
				fio.seekp(sps);
				fio.write((char *)&pl,sizeof pl)<<flush;

				if(fio.fail()){cerr<<"fail in write";exit(EXIT_FAILURE);}

				fio.seekg(0);
				cout<<"Here is content after you modify.\n";
				while(fio.read((char *)&pl,sizeof pl))
				{
					cout<<setw(12)<<pl.name<<": "
						<<setprecision(0)<<setw(12)<<pl.population
						<<setprecision(2)<<setw(6)<<pl.gravity<<endl;
				}

				fio.close();
			}
			break;
		}
		case 3:
		{
			cout<<"this system can generate up to "<<TMP_MAX
				<<"temporary name of up to"<<L_tmpnam<<"characters.\n";
			char pszName[L_tmpnam]={'\0'};
			cout<<"Here are ten names :\n";
			for (int i=0;i<10;++i)
			{
				tmpnam(pszName);
				cout<<pszName<<endl;
			}
			break;
		}
		case 4://incore formatting
		{
			ostringstream outstr;

			string hdisk;
			cout<<"what's the name of your hard disk?";
			getline(cin,hdisk);

			int cap;
			cout<<"waht's its capacity in GB?";
			cin>>cap;

			outstr<<"The hard disk "<<hdisk<<" has capacity of "<<cap<<" gigabytes.\n";
			string result = outstr.str();//save result
			cout<<result;
			break;
		}
		case 5:
		{
			string lit = "It was a dark_ and stormy day,and the full moon glowed brilliantly. ";
			istringstream instr(lit);
			string word;
			while(instr>>word) cout<<word<<endl;
			break;
		}
		case 6:
		{
			int a = 13;
			cout<<(a>>1)<<"  "<<a;
			break;
		}
		case 7:
		{
			class Example
			{
				public:
					int feet;
					int inches;
					Example(int a)
						:inches(a)
					{

					}
					Example()
						:inches(0)
					{

					}
					void sayHello(){cout<<"Hello~~~";}
			};

			int Example::*pt = &Example::inches;
			Example ob1(111);
			Example ob2(222);
			Example *pq = new Example(333);
			cout<<ob1.*pt<<endl;
			cout<<ob2.*pt<<endl;
			cout<<pq->*pt<<endl;

			void (Example::*ptr)();
			ptr = &Example::sayHello;

			(Example(444).*ptr)();
			break;
		}
		case 8:
		{
			string word;
			cin>>word;
			reverse(word.begin(),word.end());
			cout<<word.c_str()[0]<<endl;
			cout<<word.data()<<"  "<<word.size()<<endl;;
			cout<<word.at(100)<<endl;
			break;
		}
		case 9:
			{
				auto a = 100;
				cout<<a<<endl;
				break;
			}
		default:
			break;
	}
	return 0;
}


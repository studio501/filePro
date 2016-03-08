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

#include "sstringTest.h"
using namespace std;



void toolMain(int argc, char* argv[])
{
	if(argc != 2)
	{
		return;
	}

	//_TCHAR haha = *argv[1];
	
	/*char filename[256];
	int i=1;
	while(argv[1][i]) 
	{
		cout<<argv[1][i];
		filename[i-1]=argv[1][i];
		++i;
	}*/
	char *filename = argv[1];
	//cout<<filename<<endl;
	//cout<<argv[1][1]<<endl;
		//argv[1];
	//cout<<argv[1][6]<<endl;
	ifstream fin(filename,ios_base::in);
	char temp[MAX_STR_LEN];

	string checkname = string("check_")+string(filename);
	ofstream fout(checkname.c_str(),ios_base::out);

	//逗号
	SString comma;
	strAssign(comma,",");
	//冒号
	SString colon;
	strAssign(colon,":");
	//右扩弧
	SString rightArc;
	strAssign(rightArc,"}");

	//
	SString updatePlayerInfoStr;
	strAssign(updatePlayerInfoStr,"updatePlayerInfo");
	int *p_updatePlayerInfo = (int*)malloc((strLength(updatePlayerInfoStr)+1)*sizeof(int));
	get_nextval(updatePlayerInfoStr,p_updatePlayerInfo);

	SString moneyStr;
	strAssign(moneyStr,"\"money\"");
	int *p_money = (int*)malloc((strLength(moneyStr)+1)*sizeof(int));
	get_nextval(moneyStr,p_money);

	SString ctype2Str;
	strAssign(ctype2Str,"\"cType\":2");
	int *p_ctype2 = (int*)malloc((strLength(ctype2Str)+1)*sizeof(int));
	get_nextval(ctype2Str,p_ctype2);

	SString valStr;
	strAssign(valStr,"\"val\"");
	int *p_val = (int*)malloc((strLength(valStr)+1)*sizeof(int));
	get_nextval(valStr,p_val);

	SString lvlStr;
	strAssign(lvlStr,"\"lvl\"");
	int *p_lvl = (int*)malloc((strLength(lvlStr)+1)*sizeof(int));
	get_nextval(lvlStr,p_lvl);

	SString spinProStr;
	strAssign(spinProStr,"route = logic.slotsHandler.spin");
	int *p_spinPro = (int*)malloc((strLength(spinProStr)+1)*sizeof(int));
	get_nextval(spinProStr,p_spinPro);

	SString totalMoneyStr;
	strAssign(totalMoneyStr,"\"winMoney\"");
	int *p_totalMoney = (int*)malloc((strLength(totalMoneyStr)+1)*sizeof(int));
	get_nextval(totalMoneyStr,p_totalMoney);

	SString connectStr;
	strAssign(connectStr,"request connector.entryHandler.entry");
	int *p_connect = (int*)malloc((strLength(connectStr)+1)*sizeof(int));
	get_nextval(connectStr,p_connect);

	SString condStr;
	strAssign(condStr,"\"condId\"");
	int *p_cond = (int*)malloc((strLength(condStr)+1)*sizeof(int));
	get_nextval(condStr,p_cond);

	SString timeAwardStr;
	strAssign(timeAwardStr,"route = logic.timingHandler.gain");
	int *p_timeAward = (int*)malloc((strLength(timeAwardStr)+1)*sizeof(int));
	get_nextval(timeAwardStr,p_timeAward);

	bool isFirstShowMoney = false;
	if(fin.is_open()&&fout.is_open())
	{
		SString T;
		int lineNum = 0;
		int k = 0;
		int turnCount = 0;
		long long preMoney=0,betMoney=0,winMoney=0,curMoney=0;
		bool intoGame = false;
		while(fin.getline(temp,MAX_STR_LEN))
		{
			++lineNum;
			if (lineNum==1385)
			{
				int aa=100;
			}
			strAssign(T,temp);
			if(index_KMP(T,connectStr,1,p_connect))
			{
				preMoney=betMoney=winMoney=curMoney=0;
				isFirstShowMoney=false;
				turnCount=0;
				if(!intoGame)
				{
					fout<<"start game."<<endl;
					intoGame=true;
				}
				else
				{
					fout<<"\noff line reconnect game."<<endl;
				}
				
			}
			else if(index_KMP(T,timeAwardStr,1,p_timeAward))
			{
				k=index_KMP(T,moneyStr,1,p_money);
				int cp=indexInMainStr(T,rightArc,k);
				int lp=indexInMainStr(T,colon,k);
				SString numStr;
				subString(numStr,T,lp+1,cp-lp-1);
				long long t=ssToNumber(numStr);
				curMoney+=t;
				fout<<"\nin lobby gain money :"<<t<<" by collect time award. after collect money is"<<curMoney<<endl;
			}
			else
			{
				if(!isFirstShowMoney)
				{
					if(index_KMP(T,updatePlayerInfoStr,1,p_updatePlayerInfo))
					{

						k=index_KMP(T,moneyStr,1,p_money);
						int cp=indexInMainStr(T,comma,k);
						int lp=indexInMainStr(T,colon,k);
						SString numStr;
						subString(numStr,T,lp+1,cp-lp-1);
						preMoney=ssToNumber(numStr);
						curMoney=preMoney;
						fout<<"init money is:"<<preMoney<<endl;
						isFirstShowMoney=true;
					}
				}
				else
				{
					if(turnCount==0)
					{
						if(index_KMP(T,ctype2Str,1,p_ctype2))
						{
							k=index_KMP(T,valStr,1,p_val);
							int cp=indexInMainStr(T,comma,k);
							int lp=indexInMainStr(T,colon,k);
							SString numStr;
							subString(numStr,T,lp+1,cp-lp-1);
							betMoney=ssToNumber(numStr);
							fout<<"betmoney:"<<betMoney<<" line:"<<lineNum<<"   ";
							//fout<<"betmoney:"<<betMoney<<endl;
							++turnCount;
							//turnCount=0;
						}
					}
					else if(turnCount==1)
					{
						if(index_KMP(T,updatePlayerInfoStr,1,p_updatePlayerInfo))
						{

							k=index_KMP(T,moneyStr,1,p_money);
							int cp=indexInMainStr(T,comma,k);
							int lp=indexInMainStr(T,colon,k);
							SString numStr;
							subString(numStr,T,lp+1,cp-lp-1);
							preMoney=curMoney;
							curMoney=ssToNumber(numStr);
							++turnCount;
							fout<<"after bet:"<<curMoney<<" line:"<<lineNum<<"   ";
							if(index_KMP(T,lvlStr,1,p_lvl))
							{
								fout<<"level up    ";
							}
						}
					}
					else if(turnCount==2)
					{
						if(index_KMP(T,spinProStr,1,p_spinPro))
						{
							//strPrint(T);
							k=index_KMP(T,totalMoneyStr,1,p_totalMoney);
							int cp=indexInMainStr(T,comma,k);
							int lp=indexInMainStr(T,colon,k);
							SString numStr;
							subString(numStr,T,lp+1,cp-lp-1);
							winMoney=ssToNumber(numStr);
							fout<<"winmoney:"<<winMoney<<"   ";
							//++turnCount;
							if(preMoney+betMoney+winMoney==curMoney) fout<<"true"<<"   ";
							else fout<<"false"<<"   ";
							fout<<endl;
							if(index_KMP(T,condStr,1,p_cond))
							{
								fout<<"into freegame or bonus..."<<endl;
							}
							turnCount=0;
						}
					}
				}
			}
				
			
			
			/*if(!isFirstShowMoney)
			{
				if(index_KMP(T,updatePlayerInfoStr,1,p_updatePlayerInfo))
				{

				}
			}*/
			//strPrint(T);
			//if(index_KMP(T,updatePlayerInfoStr,1,p_updatePlayerInfo)) strPrint(T);
		}	
		fin.close();
		fout.close();
	}
	else
	{
		cout<<"can't open "<<filename<<endl;
		system("pause");
	}
}


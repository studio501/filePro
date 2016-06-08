
#pragma once

class ReUse1
{
	int number;
public:
	__declspec(dllexport) ReUse1();
	__declspec(dllexport) void Effect();
};

class ReUse2
{
	char Name[10];
public:
	__declspec(dllexport) ReUse2();
	__declspec(dllexport) void Output(char *);
};

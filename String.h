

#pragma once


class String
{
	static int nCharArry;
	char * str;
	size_t _len;
	int _ref;
public:
	String();
	String(char *p);
	String(const String &s);
	char & operator[](unsigned int idx);
	String & operator =(const String &s);
	~String();
	const char * c_str();
};
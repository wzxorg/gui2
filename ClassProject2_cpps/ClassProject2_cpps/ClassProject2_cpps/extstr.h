#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

typedef string String;
/*
Ϊ��c++�ַ������
��ͷ�ļ��ṩextstr����
(c)321FreeWeb @321.vipgz1.idcfengye.com 2020
*/
class extstr
{
public:
	string value;
	long int length() {
		return value.size();
	}
	long int to_int() {
		stringstream sst;
		int int_val;
		sst << value;
		sst >> int_val;
		return int_val;
	}
	long double to_double() {
		stringstream sst;
		int double_val;
		sst << value;
		sst >> double_val;
		return double_val;

	}
	void replace(string before, string after) {
		int pos;
		pos = value.find(before);
		while (pos != -1) {
			// str.length()���ַ��ĳ��ȣ�ע��str������string����
			value.replace(pos, string(before).length(), after);
			pos = value.find(before);
		}

	}
	int sub_str(string str) {

		int sub = 0;
		for (size_t i = 0; (i = value.find(str, i)) != string::npos; sub++, i++);
		return sub;

	}
	void clear() {
		value = "";

	}
	bool empty() {
		if (value.empty()) {
			return true;
		}
		return false;
	}


private:

};
/*
string int_str(long int );
string double_str(long double );
string float_str(float );
string str_replace(string, string, string);
int sub_str(string, string);
*/

inline string intTOstr(long int m) {
	stringstream s1;
	string s2;
	s1 << m;
	s1 >> s2;
	return s2;
}
inline string doubleTOstr(long double m) {
	stringstream s1;
	string s2;
	s1 << m;
	s1 >> s2;
	return s2;
}
inline string floatTOstr(float m) {
	stringstream s1;
	string s2;
	s1 << m;
	s1 >> s2;
	return s2;
}
static int strTOint(string str) {
	stringstream sst;
	int int_val;
	sst << str;
	sst >> int_val;
	return int_val;
}
inline string str_replace(string str, string s1, string s2) {
	int pos;
	pos = str.find(s1);
	while (pos != -1) {
		// str.length()���ַ��ĳ��ȣ�ע��str������string����
		str.replace(pos, string(s1).length(), s2);
		pos = str.find(s1);
	}

	return str;
}
inline int sub_str(string mixture, string str) {
	int sub = 0;
	for (size_t i = 0; (i = mixture.find(str, i)) != string::npos; sub++, i++);
	return sub;
}
/*
static char* stringToChar(string str) {
	char *p = (char*)str.data();
	char *p1 = new char[strlen(p)];
	strcpy(p1,p);
	return p;
}*/

/*
extstr�÷������ʾ��

1.����
1.1����
extstr a;

1.2����
value

����
extstr a;
a.value="Hello World";

1.3����
1.3.1  length()
����value�ĳ���
��:
extstr a;
a.value="Hello World";
int b;
b=a.length();

1.3.2  to_int()
��valueת��Ϊint���Ͳ�����
��:
extstr a;
a.value="2";
int b;
b= a.to_int();

1.3.3  to_double()
��valueת��Ϊdouble���Ͳ�����
����
extstr a;
a.value="1.3";
double b;
b=a.to_double();

1.3.4 replace()
�滻
��:
extstr a;
a.value="Hello World";
a.replace("World","Kitty");
cout <<a.value;

�����Ľ�����Ϊ
Hello Kitty
1.3.5 sub_str()
����ĳ���ַ�����value�г��ֵĴ���
����
extstr a;
a.value="Hello World";
int b=a.sub_str("l");

1.3.6 clear()
��value��ֵ����Ϊ""
����
extstr a;
a.value="Hello World";
a.clear();

1.3.7 empty()
�ж�value��ֵ�Ƿ�Ϊ��,������true��false��
����
extstr a;
a.value="Hello World";
a.clear();
bool b=a.empty();
��ʱbΪfalse��

��������Ӧ�þ�����
int_str(1);//����"1"
double_str(1.1);//����"1.1"
//...�Դ�����
str_replace("aabbb","a","b");//����"bbbbb"
sub_str("aabbb","b");//����3
*/

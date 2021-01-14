#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

typedef string String;
/*
为简化c++字符串编程
此头文件提供extstr对象
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
			// str.length()求字符的长度，注意str必须是string类型
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
		// str.length()求字符的长度，注意str必须是string类型
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
extstr用法与代码示例

1.基本
1.1定义
extstr a;

1.2属性
value

例：
extstr a;
a.value="Hello World";

1.3方法
1.3.1  length()
返回value的长度
例:
extstr a;
a.value="Hello World";
int b;
b=a.length();

1.3.2  to_int()
将value转换为int类型并返回
例:
extstr a;
a.value="2";
int b;
b= a.to_int();

1.3.3  to_double()
将value转换为double类型并返回
例：
extstr a;
a.value="1.3";
double b;
b=a.to_double();

1.3.4 replace()
替换
例:
extstr a;
a.value="Hello World";
a.replace("World","Kitty");
cout <<a.value;

此例的结果输出为
Hello Kitty
1.3.5 sub_str()
返回某个字符串在value中出现的次数
例：
extstr a;
a.value="Hello World";
int b=a.sub_str("l");

1.3.6 clear()
将value的值设置为""
例：
extstr a;
a.value="Hello World";
a.clear();

1.3.7 empty()
判断value的值是否为空,并返回true或false。
例：
extstr a;
a.value="Hello World";
a.clear();
bool b=a.empty();
此时b为false。

其他函数应用举例：
int_str(1);//返回"1"
double_str(1.1);//返回"1.1"
//...以此类推
str_replace("aabbb","a","b");//返回"bbbbb"
sub_str("aabbb","b");//返回3
*/

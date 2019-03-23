#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

class BigInteger
{
private:
	string str_data;
public:
	friend ostream& operator << (ostream&, BigInteger &);//重载<<，可以对BigInteger使用cout操作
	friend ostream& operator >> (ostream&, BigInteger &);//重载>>，可以对BigInteger使用cin操作
	BigInteger();//字符串的初始化为空串
	BigInteger(const string &str_data);//可以调用这个函数给BigInteger赋值
	string Multiple_(string str_left, string str_right);//乘法运算函数
	string Add(string str_left, string str_right);//加法运算函数
	string Sub(string str_left, string str_right);//减法运算函数
	//string Equal(string &x, string &y);
	BigInteger operator = (BigInteger x);//不能采用引用的方式,否则不能接受x+y的值，惨痛教训
	BigInteger operator + (const BigInteger &x);//重载+运算符
	BigInteger operator - (const BigInteger &x);//重载-运算符
	BigInteger operator * (const BigInteger &x);//重载*运算符
	bool operator > (const BigInteger &x)const;//重载>运算符
	bool operator < (const BigInteger &x)const;//重载<运算符
	bool operator >= (const BigInteger &x)const;
	bool operator <= (const BigInteger &x)const;
	bool operator != (const BigInteger &x)const;
	friend istream& operator >> (istream &in, BigInteger &x)//>>运算符的定义
	{
		in >> x.str_data;
		return cin;
	}
	friend ostream& operator << (ostream &out, BigInteger &x)//<<运算符的定义
	{
		out << x.str_data;
		return out;
	}
};

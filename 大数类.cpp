#include "大数类.h"
#include <cstring>

bool BigInteger::operator > (const BigInteger &x)const
{
	int len1 = str_data.length();
	int len2 = x.str_data.length();
	if (len1 > len2)return true;
	if (len1 < len2)return false;
	return str_data > x.str_data;
}
bool BigInteger::operator < (const BigInteger &x)const
{
	int len1 = str_data.length();
	int len2 = x.str_data.length();
	if (len1 < len2)return true;
	if (len1 > len2)return false;
	return str_data < x.str_data;
}
bool BigInteger::operator >= (const BigInteger &x)const
{
	int len1 = str_data.length();
	int len2 = x.str_data.length();
	if (len1 > len2)return true;
	if (len1 < len2)return false;
	return str_data >= x.str_data;
}
bool BigInteger::operator <= (const BigInteger &x)const
{
	int len1 = str_data.length();
	int len2 = x.str_data.length();
	if (len1 < len2)return true;
	if (len1 > len2)return false;
	return str_data <= x.str_data;
}
bool BigInteger::operator != (const BigInteger &x)const
{
	return str_data != x.str_data;
}

BigInteger::BigInteger() :str_data("")//BigInteger类型数值的初始化,字符串初始化为空串
{}

BigInteger::BigInteger(const std::string &str) : str_data(str)
{}

BigInteger BigInteger::operator = (BigInteger x)//重载等于运算符
{
	//BigInteger res;
	str_data = x.str_data;
	return *this;
}

BigInteger BigInteger::operator -(const BigInteger &x)//重载-运算符
{
	BigInteger tmp;
	tmp.str_data = Sub(this->str_data, x.str_data);//调用sub函数
	return tmp;
}
BigInteger BigInteger::operator +(const BigInteger &x)//重载+运算符
{
	BigInteger res;
	res.str_data = Add(this->str_data, x.str_data);//调用Add函数
	return res;
}

string BigInteger::Add(string str_left, string str_right)//两个正整数相加
{
	int size1 = str_left.size();
	int size2 = str_right.size();
	//下面保证str_left的长度不小于str_right的长度
	if (size1 < size2)
	{
		swap(str_left, str_right);
		swap(size1, size2);
	}

	//相加结果的最大长度是size1+1,初始化为0
	string res(size1 + 1, '0');//留下一位进位
	int cha = size1 - size2;//差

	//下面具体计算
	for (int i = size1 - 1; i >= 0; i--)
	{
		if (i - cha >= 0)//保证较短的字符串不越界
		{
			res[i + 1] += ((str_left[i] - '0') + (str_right[i - cha] - '0'));
			if ((res[i + 1] - '0') >= 10)//处理进位
			{
				res[i + 1] -= 10;
				res[i] += 1;
			}
		}//将str_left的比str_right长的部分加下去
		else
		{
			res[i + 1] += str_left[i] - '0';
			if ((res[i + 1] - '0') >= 10)
			{
				res[i + 1] -= 10;
				res[i] += 1;
			}
		}
	}
	//去除前缀0
	if (res[0] == '0')
	{
		for (int i = 0; i < size1; i++)
		{
			res[i] = res[i + 1];
		}
		res.pop_back();
	}
	return res;
}

string BigInteger::Sub(string str_left, string str_right)//减法函数
{
	int size1 = str_left.size();
	int size2 = str_right.size();
	if (size1 < size2 || ((size1 == size2) && str_left < str_right)) //保证被减数大于减数
	{
		swap(str_left, str_right);
		swap(size1, size2);
	}

	string res(size1, '0');//结果最大位数和被减数相同
	int cha = size1 - size2;//差
	//下面计算
	for (int i = size1 - 1; i >= 0; i--)
	{
		if (i - cha >= 0)//保证较短的数字不越界访问
		{
			res[i] += str_left[i] - str_right[i - cha];
			if (res[i] < '0')//处理进位
			{
				res[i] += 10;
				res[i - 1] -= 1;
			}
		}
		else//剩下的数字拉下去
		{
			res[i] += str_left[i] - '0';
			if (res[i] < '0')
			{
				res[i] += 10;
				res[i - 1] -= 1;
			}
		}
	}
	//去除前导0
	int i = 0;
	while (res[i] == '0')i++;
	if (i == size1)return "0";//如果全部为0，那么结果为0
	for (int j = i; j < size1; j++)//去除前置0
	{
		res[j - i] = res[j];
	}
	res.resize(res.size() - i);
	return res;
}


BigInteger BigInteger::operator *(const BigInteger &x)//重载*运算符
{
	BigInteger res;
	res.str_data = Multiple_(this->str_data, x.str_data);//调用函数
	return res;
}

string BigInteger::Multiple_(string str_left, string str_right)
{
	int size1 = str_left.size();
	int size2 = str_right.size();
	if (size1 < size2)//保证第一个数字不短于第二个数字
	{
		swap(str_left, str_right);
		swap(size1, size2);
	}
	string res = "";//初始化结果为空串
	int cha = size1 - size2;


	//主要是模拟手算
	//由于乘法的运算可能超过ASCII码的表示范围，采用int型数组计算
	int *a = (int *)malloc(sizeof(int) * (2 * size1 + 10));//乘法的位数不会超过这个
	memset(a, 0, sizeof(int) * (2 * size1 + 10));
	int k = 0;//移位
	int sit = 2 * size1 + 9;//每次乘法存储的位置sit
	for (int i = size2 - 1; i >= 0; i--)//size2次运算
	{
		for (int j = size1 - 1; j >= 0; j--)//size1次运算
		{
			a[sit--] += (str_left[j] - '0') * (str_right[i] - '0');
		}
		sit = 2 * size1 + 9 - (++k);//处理移位
	}
	for (int i = 2 * size1 + 9; i >= 0; i--)//处理进位
	{
		if (a[i] >= 10)
		{
			//给出的位数大于乘法的最大位数，下面这样写不会报错
			a[i - 1] += a[i] / 10;
			a[i] = a[i] % 10;
		}
	}
	//去掉前缀0
	int i = 0;
	while (a[i] == 0)i++;
	if (i == 2 * size1 + 10)return "0";//结果为0，返回0
	for (int j = i; j < 2 * size1 + 10; j++)
	{
		res += (char)(a[j] + '0');
	}
	free(a);//释放内存
	return res;
}

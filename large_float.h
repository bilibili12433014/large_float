#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class large_float
{
	//a是分子
	//b是分母
	//sign是符号，0是正数，1是负数
	//已经定义+-*/%运算
	//add是两个字符串相加
	//div是除法
	//sub是减法
	//mul是乘法
	//is_int()返回是否是整数
	//out()用来输出数据
	//yue_fen()是约分
	//默认构造函数构造数据0
	//另外两种构造函数分别支持输入string或int作为数据输入
	//可自动识别构造数据正负或手动通过sign控制
public:
	string a = "0";
	string b = "1";
	bool sign = 0;
	large_float()
	{
		this->a = "0";
		this->b = "1";
		this->sign = 0;
	}
	large_float(string a, string b = "1", bool sign = 0)
	{
		if (a[0]=='-')
		{
			a = a.substr(1);
			this->sign = 1;
		}
		else
		{
			this->sign = sign;
		}
		this->a = a;
		this->b = b;
	}
	large_float(int a, int b = 1, bool sign = 0)
	{
		stringstream aa, bb;
		if (a < 0)
		{
			a = -a;
			this->sign = 1;
		}
		else
		{
			this->sign = sign;
		}
		aa << a;
		bb << b;
		aa >> this->a;
		bb >> this->b;
	}
	large_float operator%(large_float b)
	{
		large_float r;
		if (this->b != "1" or b.b != "1")
		{
			cout << "error: % need 2 int type!";
			exit(-1);
		}
		r.a = mod(this->a, b.a);
		if (r.a[0] == '-') r.a = r.a.substr(1);
		r.sign = this->sign;
		return r;
	}///*/
	large_float operator+(large_float b)
	{
		large_float r;
		if (this->sign + b.sign == 0)
		{
			r.sign = 0;
		}
		else if (this->sign + b.sign == 2)
		{
			r.sign = 1;
		}
		else if (this->sign)
		{
			return b - *this;
		}
		else
		{
			return *this - b;
		}
		r.sign = 0;
		r.a = r.add(r.mul(this->a, b.b), r.mul(this->b, b.a));
		r.b = r.mul(this->b, b.b);
		r.yue_fen();
		return r;
	}
	large_float operator-(large_float b)
	{
		large_float r;
		if (this->sign == 0 && b.sign == 1)
		{
			b.sign = 0;
			return *this + b;
		}
		else if (this->sign == 1 && b.sign == 0)
		{
			r = *this + b;
			r.sign = 1;
			return r;
		}
		else if (this->sign == 1 && b.sign == 1)
		{
			b.sign = 0;
			return b - *this;
		}
		else
		{
			r.a = r.sub(r.mul(this->a, b.b), r.mul(this->b, b.a));
			r.b = r.mul(this->b, b.b);
			if (r.a[0] == '-')
			{
				r.a = r.a.substr(1);
				r.sign = 1;
			}
			else
			{
				r.sign = 0;
			}
		}
		r.yue_fen();
		return r;
	}
	large_float operator*(large_float b)
	{
		large_float r;
		if (this->sign != b.sign) r.sign = 1;
		r.a = r.mul(this->a, b.a);
		r.b = r.mul(this->b, b.b);
		r.yue_fen();
		return r;
	}
	large_float operator/(large_float b)
	{
		large_float r;
		if (this->sign != b.sign) r.sign = 1;
		r.a = r.mul(this->a, b.b);
		r.b = r.mul(this->b, b.a);
		r.yue_fen();
		return r;
	}
	bool operator<(large_float b)
	{
		if (this->sign == 1 && b.sign == 0) return true;
		else if (this->sign == 0 && b.sign == 1) return false;
		else if (this->sign == 0 && b.sign == 0)
		{
			this->a = this->mul(this->a, b.b);
			b.a = b.mul(this->b, b.a);
			if (this->a.length() < b.a.length()) return true;
			else if (this->a.length() > b.a.length()) return false;
			else
			{
				if (this->a < b.a) return true;
				else return false;
			}
		}
		else
		{
			this->a = this->mul(this->a, b.b);
			b.a = b.mul(this->b, b.a);
			if (this->a.length() < b.a.length()) return false;
			else if (this->a.length() > b.a.length()) return true;
			else
			{
				if (this->a < b.a) return false;
				else return true;
			}
		}
	}
	bool operator==(large_float b)
	{
		if (this->a == b.a && this->b == b.b && this->sign == b.sign) return true;
		else return false;
	}
	bool operator>(large_float b)
	{
		if (*this == b || *this < b) return false;
		else return true;
	}
	bool operator!=(large_float b)
	{
		return !(*this == b);
	}
	bool operator>=(large_float b)
	{
		if (*this < b) return false;
		else return true;
	}
	bool operator<=(large_float b)
	{
		if (*this == b || *this < b) return true;
		else return false;
	}

	void out()
	{
		if (sign) cout << "-";
		if (b == "1") cout << a << endl;
		else cout << a << "/" << b << endl;
	}
	void yue_fen()
	{
		if (a == "0")
		{
			b = "1";
			return;
		}
		string m = b, n = a;
		string m0 = m, n0 = n;
		//r.a = sub(a, mul(div(a, b), b));
		while (mod(m, n) != "0")
		{
			string temp = m;
			m = n;
			n = mod(temp, n);
		}
		a = div(n0, n);
		b = div(m0, n);
	}
	bool is_int()
	{
		if (mod(a, b) == "0")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string mod(string a, string b)
	{
		return sub(a, mul(div(a, b), b));
	}
	string div(string a, string b)
	{
		if (a.length() < b.length()) return "0";
		else if (a.length() == b.length())
		{
			if (a[0] < b[0])
			{
				return "0";
			}
		}
		string c = "";
		int length;
		length = b.length();
		string cc;
		cc = a.substr(0, b.length());
		while (length <= a.length())
		{
			for (int i = 0; i <= 10; i++)
			{
				string str;
				stringstream cccc;
				cccc << i;
				cccc >> str;
				if (large_float(cc) < large_float(mul(b, str)))
				{
					if (i == 0)
					{
						c += "0";
					}
					else
					{
						stringstream ccccc;
						ccccc << i - 1;
						ccccc >> str;
						c += str;
						cc = sub(cc, mul(b, str));
					}
					if (length < a.length())
					{
						cc += a.substr(length, 1);
					}
					length++;
					break;
				}
			}
		}
		while (c.length() != 1 && c[0] == '0')
		{
			c = c.substr(1);
		}
		return c;
	}
	string sub(string a, string b)
	{
		string c = "";
		bool j = false;
		int aa, bb;
		char cc;
		if (a == "0") return b;
		if (b == "0") return a;
		bool fu = false;
		if (a.length() < b.length())
		{
			c = a;
			a = b;
			b = c;
			c = "";
			fu = true;
		}
		if (a.length() == b.length())
		{
			if (a[0] < b[0])
			{
				c = a;
				a = b;
				b = c;
				c = "";
				fu = true;
			}
		}
		for (size_t i = 1; i <= b.length(); i++)
		{
			aa = a[a.length() - i] - '0';
			bb = b[b.length() - i] - '0';
			if (j)
			{
				aa--;
				j = false;
			}
			if (aa - bb < 0)
			{
				cc = aa - bb + 10 + '0';
				j = true;
			}
			else
			{
				cc = aa - bb + '0';
			}
			c = cc + c;
		}
		for (size_t i = b.length() + 1; i <= a.length(); i++)
		{
			aa = a[a.length() - i] - '0';
			if (j)
			{
				aa--;
				j = false;
			}
			if (aa < 0)
			{
				cc = aa + 10 + '0';
				j = true;
			}
			else
			{
				cc = aa + '0';
			}
			c = cc + c;
		}
		if (fu)
		{
			c = "-" + c;
		}
		while (c.length() != 1 && c[0] == '0')
		{
			c = c.substr(1);
		}
		return c;
	}
	string add(string a, string b)
	{
		string c = "";
		bool j = false;
		int aa, bb;
		char cc;
		if (a == "0") return b;
		if (b == "0") return a;
		if (a.length() < b.length())
		{
			c = a;
			a = b;
			b = c;
			c = "";
		}
		for (size_t i = 1; i <= b.length(); i++)
		{
			aa = a[a.length() - i] - '0';
			bb = b[b.length() - i] - '0';
			if (j)
			{
				aa++;
				j = false;
			}
			if (aa + bb >= 10)
			{
				cc = aa + bb - 10 + '0';
				j = true;
			}
			else
			{
				cc = aa + bb + '0';
			}
			c = cc + c;
		}
		for (size_t i = b.length() + 1; i <= a.length(); i++)
		{
			aa = a[a.length() - i] - '0';
			if (j)
			{
				aa++;
				j = false;
			}
			if (aa >= 10)
			{
				cc = aa - 10 + '0';
				j = true;
			}
			else
			{
				cc = aa + '0';
			}
			c = cc + c;
		}
		if (j)
		{
			c = "1" + c;
		}
		return c;
	}
	string mul(string a, string b)
	{
		if (a == "0" || b == "0") return "0";
		string c = "0";
		string aa;
		int  bb;
		char cc;
		if (a.length() < b.length())
		{
			c = a;
			a = b;
			b = c;
			c = "";
		}
		for (size_t i = 1; i <= b.length(); i++)
		{
			aa = a;
			bb = b[b.length() - i] - '0';
			for (int j = 1; j < bb; j++)
			{
				aa = add(aa, a);
			}
			for (int j = 1; j < i; j++)
			{
				aa = aa + "0";
			}
			c = add(c, aa);
		}
		return c;
	}
};
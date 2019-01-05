/*
题目描述

学习KMP算法，给出主串和模式串，求模式串在主串的位置
算法框架如下，仅供参考


输入

第一个输入t，表示有t个实例

第二行输入第1个实例的主串，第三行输入第1个实例的模式串

以此类推

输出

第一行输出第1个实例的模式串的next值

第二行输出第1个实例的匹配位置，位置从1开始计算，如果匹配成功输出位置，匹配失败输出0

以此类推

样例输入

3
qwertyuiop
tyu
aabbccdd
ccc
aaaabababac
abac
样例输出

0 1 1 
5
0 1 2 
0
0 1 1 2 
8
*/
#include <iostream>
#include <string>

using namespace std;

class myString
{
  private:
	string mainstr;
	int size;
	void GetNext(string p, int next[]);
	int KMPFind(string p, int pos, int next[]);

  public:
	myString();
	~myString();
	void SetVal(string sp);
	int KMPFindSubsstr(string p, int pos);
};

myString::myString()
{
	size = 0;
	mainstr = "";
}
myString::~myString()
{
	size = 0;
	mainstr = "";
}

void myString::SetVal(string sp)
{
	mainstr = "";
	mainstr.assign(sp);
	size = mainstr.length();
}

int myString::KMPFindSubsstr(string p, int pos)
{
	int i;
	int L = p.length();
	int *next = new int[L + 1];
	next[0] = 0;
	GetNext(p, next);
	for (i = 1; i <= L; i++)
	{
		cout << next[i] << ' ';
	}
	cout << endl;
	int v = -1;
	v = KMPFind(p, pos, next);
	delete next;
	return v;
}

void myString::GetNext(string p, int next[])
{
	int i, j;
	i = 1;
	next[1] = 0;
	j = 0;
	while (i < p.length())
	{
		if (j == 0 || p[i - 1] == p[j - 1])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

int myString::KMPFind(string p, int pos, int next[])
{
	int i, j;
	i = pos;
	j = 1;
	while (i <= mainstr.length() && j <= p.length())
	{
		if (j == 0 || mainstr[i - 1] == p[j - 1])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}

	if (j > p.length())
	{
		return i - p.length();
	}
	else
	{
		return 0;
	}
}

int main()
{
	int num;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		string main, pattern;
		cin >> main;
		myString myNewString;
		myNewString.SetVal(main);
		cin >> pattern;
		cout << myNewString.KMPFindSubsstr(pattern, 1) << endl;
	}
	return 0;
}

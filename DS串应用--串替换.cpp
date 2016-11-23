/*
题目描述

给出主串、模式串、替换串，用KMP算法找出模式串在主串的位置，然后用替换串的字符替换掉模式串

本题只考虑一处替换的情况，如果你想做的完美一些，能够实现多处替换那

可能需要考虑模式串和替换串长度不一致的情况

输入

第一个输入t，表示有t个实例

第二行输入第1个实例的主串，第三行输入第1个实例的模式串，第四行输入第1个实例的替换串

以此类推

输出

第一行输出第1个实例的主串

第二行输出第1个实例的主串替换后结果，如果没有发生替换就输出主串原来的内容。

以此类推

样例输入

3
aabbccdd
bb
ff
aaabbbccc
ddd
eee
abcdef
abc
ccccc
样例输出

aabbccdd
aaffccdd
aaabbbccc
aaabbbccc
abcdef
cccccdef
*/
#include <iostream>
#include <string>

using namespace std;

class myString{
private:	
	string mainstr;
	int size;
	void GetNext(string p,int next[]);
	int KMPFind(string p,int pos,int next[]);
	
public:
	myString();
	~myString();
	void SetVal(string sp);
	int KMPFindSubsstr(string p,int pos);
	int Replace(string p,string pattern,int index);
};

myString::myString(){
	size = 0;
	mainstr = "";
}
myString::~myString(){
	size = 0;
	mainstr = "";
}

void myString::SetVal(string sp){
	mainstr = "";
	mainstr.assign(sp);
	size = mainstr.length();
}

int myString::KMPFindSubsstr(string p,int pos){
	int i;
	int L = p.length();
	int *next = new int[L+1];
	next[0] = 0;
	GetNext(p,next);
	int v = -1;
	v = KMPFind(p,pos,next);
	delete next;
	return v;
}

void myString::GetNext(string p,int next[]){
	int i,j;
	i=1;
	next[1]=0;
	j=0;
	while(i<p.length()){
		if(j==0||p[i-1]==p[j-1]){
			++i;
			++j;
			next[i] = j;
		}
		else{
			j = next[j];
		}
	}
}

int myString::KMPFind(string p,int pos,int next[]){
	int i,j;
	i=pos;
	j=1;
	while(i<=mainstr.length()&&j<=p.length()){
		if(j==0||mainstr[i-1]==p[j-1]){++i;++j;}
		else j=next[j];
	}
	
	if(j>p.length()){
		return i-p.length();
	}
	else{
		return 0;
	}
}
int myString::Replace(string p,string pattern,int index){
	int pal=pattern.length();
	int pl=p.length();
	int ml=mainstr.length();
	if(!index==0){
		if(pal<pl){
			for(int i=ml;i>index;i--){
				mainstr[i+pl-pal-1] = mainstr[i-1];
			}
			size=size+pl-pal;
		}
		if(pal>pl){
			for(int i=index+pl;i<ml;i++){
				mainstr[i-1] = mainstr[i+pal-pl-1];
			}
			size = size-pal+pl;
		}
		for(int i=0;i<pl;i++){
			mainstr[index-1+i] = p[i];
		}	
	}
	for(int j=0;j<size;j++){
		cout<<mainstr[j];
	}
}

int main(){
	int num;
	string str,re;
	cin>>num;
	for(int i=1;i<=num;i++){
		int index = 0;
		string main,pattern;
		cin>>main;
		myString myNewString;
		myNewString.SetVal(main);
		cin>>pattern;
		index = myNewString.KMPFindSubsstr(pattern,1);	
		cin>>re;
		cout<<main<<endl;
		myNewString.Replace(re,pattern,index);
		cout<<endl;
	}
	return 0;
}

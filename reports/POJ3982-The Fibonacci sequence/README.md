## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3982] [[The Fibonacci sequence](http://poj.org/problem?id=3982)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 高精度算法]

------

## 问题描述

变种的**大数斐波那契数列**


## 解题思路

水题，直接加就可以了，循环使用4个大数数组a,b,c,ans存放最新的和值，循环25次后的ans就是A99的值


## AC 源码


```c
//Memory Time
//216K   32MS 

#include<iostream>
#include<string>
using namespace std;

const int size=1000;   //大数位数

void add(char* aa,char* bb,char* cc,char* ans)
{
	int a[size+1]={0};
	int b[size+1]={0};
	int c[size+1]={0};
	int pa=0,pb=0,pc=0;

	int lena=strlen(aa);
	int lenb=strlen(bb);
	int lenc=strlen(cc);

	/*倒序*/

	for(int i=lena-1;i>=0;i--)
		a[pa++]=aa[i]-'0';
	for(int j=lenb-1;j>=0;j--)
		b[pb++]=bb[j]-'0';
	for(int k=lenc-1;k>=0;k--)
		c[pc++]=cc[k]-'0';

	int len=lena>lenb?lena:lenb;
	len=len>lenc?len:lenc;
	char* d=new char[len+2];  //倒序的ans

	int w=0;  //低位到高位的进位
	for(int x=0;x<=len;x++)  //'='为了处理最高位的进位
	{
		int temp=a[x]+b[x]+c[x]+w;
		d[x]=temp%10+'0';
		w=temp/10;
	}

	bool flag=false;
	bool sign=false;  //标记ans是否为全0
	for(w=0;len>=0;len--)  //w和len均作指针使用，已无意义
	{
		if(!flag && d[len]=='0')   //删除数字开头的0
			continue;
		else
			flag=true;

		sign=true;
		ans[w++]=d[len];
	}
	if(sign)
		ans[w]='\0';
	else
	{
		ans[0]='0';
		ans[1]='\0';
	}

	delete d;
	return;
}

char a[size+1];
char b[size+1];
char c[size+1];
char ans[size+1];
int main(void)
{
	while(cin>>a>>b>>c)
	{
		for(int i=1;i<=25;i++)
		{
			add(a,b,c,ans);
			add(b,c,ans,a);
			add(c,ans,a,b);
			add(ans,a,b,c);
		}
		cout<<ans<<endl;   //循环25次后，ans刚好是第99个数的值
	}
	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2389] [[Bull Math](http://poj.org/problem?id=2389)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 高精度算法]

------

## 问题描述

无。


## 解题思路

**大数**相乘，水题一道，直接**模拟**笔算竖式即可，没技巧没算法。


## AC 源码


```c
//Memory Time
//216K  16MS 

#include<iostream>
#include<string>
using namespace std;

const int size=1000;  //大数位数

void mult(char* A,char* B,char* ans)
{
	int a[size+1]={0};
	int b[size+1]={0};
	int pa=0,pb=0;
	int c[2*size+1]={0};

	int lena=strlen(A);
	int lenb=strlen(B);

	for(int i=lena-1;i>=0;i--)
		a[pa++]=A[i]-'0';
	for(int j=lenb-1;j>=0;j--)
		b[pb++]=B[j]-'0';

	for(pb=0;pb<lenb;pb++)
	{
		int w=0;  //低位到高位的进位
		for(pa=0;pa<=lena;pa++)
		{
			int temp=a[pa]*b[pb]+w;
			w=temp/10;
			temp=(c[pa+pb]+=temp%10);
			c[pa+pb]=temp%10;
			w+=temp/10;
		}
	}
	bool flag=false;
	bool sign=false;  //标记ans是否为全0
	for(pa=0,pb=lena+lenb-1;pb>=0;pb--)
	{
		if(!flag && c[pb]==0)  //删除ans开头的0
			continue;
		else
			flag=true;

		sign=true;
		ans[pa++]=c[pb]+'0';
	}
	if(sign)
		ans[pa]='\0';
	else
	{
		ans[0]='0';
		ans[1]='\0';
	}

	return;
}

int main(void)
{
	char a[size+1];
	char b[size+1];
	char ans[2*size+1];
	while(cin>>a>>b)
	{
		mult(a,b,ans);
		cout<<ans<<endl;
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

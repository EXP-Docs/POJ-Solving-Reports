## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2602] [[Superlong sums](http://poj.org/problem?id=2602)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 高精度算法]

------

## 问题描述

无。


## 解题思路


非常恶心的**大数相加**

首先输入就够恶心了...哪有人逐位还要间断输入两个数的...


**注意**：

- 如果用 `char[]` 保存加数和被加数，要用 `getchar()` 输入，
- 如果用 `int[]` 保存加数和被加数，要用 `scanf()`输入。
- 用cin会超时，`cin` 是重载函数，没有指定格式，输入时比较浪费时间
- 100W 的空间不能局部静态申请，单可以全局静态申请，也可以局部动态申请(用 `new`)


最恶心得是，我把结果开头的0（如果有的话）删去，竟然WA...！

Output file should contain exactly N digits in a single linerepresenting the sum of these two integers.

这是输出要求的格式，竟然要求 `被加数、加数、和` 的位数一致！！

按这样理解，这题是不允许最高位出现进位的...！！


## AC 源码

### 方法一：使用 char[] 存储数字

```c
//Memory  Time 
//11972K 1594MS 

#include<iostream>
#include<string>
using namespace std;

const int size=1000000;  //大数位数上限
int n;  //大数位数

int a[size+1];
int b[size+1];

void add(char* A,char* B,char* ans)
{
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	int pa=0,pb=0;

	int lena=strlen(A);
	int lenb=strlen(B);

	/*倒序*/

	for(int i=lena-1;i>=0;i--)
		a[pa++]=A[i]-'0';
	for(int j=lenb-1;j>=0;j--)
		b[pb++]=B[j]-'0';

	int len=lena>lenb?lena:lenb;
	char* c=new char[len+1];  //倒序的ans

	int w=0;  //低位到高位的进位
	for(int k=0;k<len;k++)
	{
		int temp=a[k]+b[k]+w;
		c[k]=temp%10+'0';
		w=temp/10;
	}
	len--;

	for(w=0;len>=0;len--)  //w和len均作指针使用，已无意义
		ans[w++]=c[len];
	ans[w]='\0';

	delete c;
	return;
}

char A[size+1];
char B[size+1];
char ans[size+1];

int main(int i)
{
	while(cin>>n)
	{
		getchar();
		for(i=0;i<n;i++)
		{
			A[i]=getchar();
			getchar();  //空格
			B[i]=getchar();
			getchar();  //回车
		}
		A[i]=B[i]='\0';

		add(A,B,ans);
		cout<<ans<<endl;
	}
	return 0;
}
```

### 方法一：使用 int[] 存储数字

```c
//Memory  Time 
//17868K 1625MS

#include<iostream>
using namespace std;

int n;  //大数位数

void add(int* a,int* b,char* ans)
{
	char* c=new char[n+1];  //倒序的ans

	int w=0;  //低位到高位的进位
	for(int k=0;k<n;k++)
	{
		int temp=a[k]+b[k]+w;
		c[k]=temp%10+'0';
		w=temp/10;
	}

	n--;
	for(w=0;n>=0;n--)  //w和n均作指针使用，已无意义
		ans[w++]=c[n];
	ans[w]='\0';

	delete c;
	return;
}

int main(int i)
{
	while(cin>>n)
	{
		int* a=new int[n+1];
		int* b=new int[n+1];
		int* ta=new int[n+1];
		int* tb=new int[n+1];
		char* ans=new char[n+1];

		for(i=0;i<n;i++)
			scanf("%d %d",&ta[i],&tb[i]);

		/*倒序*/

		int pa=0,pb=0;
		for(i=n-1;i>=0;i--)
		{
			a[pa++]=ta[i];
			b[pb++]=tb[i];
		}

		add(a,b,ans);
		cout<<ans<<endl;

		delete a;
		delete b;
		delete ta;
		delete tb;
		delete ans;
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

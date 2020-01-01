## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1002] [[487-3279](http://poj.org/problem?id=1002)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 高效查找法]

------

## 问题描述

无。


## 解题思路

**有两种处理方法**：

**1、Hash+qsort法**

- 在输入时把字符号码转换为7位数字，用int保存，然后开两个8位数组vist和time，分别记录该号码是否出现过；若出现过，出现的次数是多少。
- 把出现过2次或以上的号码先逐一存放到待输出数组sort_out
- 输入完毕后，对数组sort_out快排，逐一输出这些号码及其出现次数即可。

 

**2、qsort法**

- 在输入时先把字符号码全部转换为7位数字，然后全部存入数组sort_out
- 用qsort对数组sort_out排序，然后顺次读取每一个数组sort_out中的号码，相同的号码必然是连续存放的，只需把连续出现2次以上的号码输出即可。



**注意**：

- 本题输入必须使用字符串输入，若逐字输入，无论用何种算法都会超时。
- `sort()` 与 `qsort()` 都是C++的快排函数，本题的排序机制很简单，不想写比较函数的同学可以用 `sort()`



## AC 源码


### 解题思路一：Hash+Qsort

```c
//Memory Time
//49324K 907MS 

/*Hash+Qsort*/

#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

int ctoi(char ch)  //把字符ch转换为其在手机上对应的数字键
{
	if(ch=='A' || ch=='B' || ch=='C')
		return 2;
	if(ch=='D' || ch=='E' || ch=='F')
		return 3;
	if(ch=='G' || ch=='H' || ch=='I')
		return 4;
	if(ch=='J' || ch=='K' || ch=='L')
		return 5;
	if(ch=='M' || ch=='N' || ch=='O')
		return 6;
	if(ch=='P' || ch=='R' || ch=='S')
		return 7;
	if(ch=='T' || ch=='U' || ch=='V')
		return 8;
	if(ch=='W' || ch=='X' || ch=='Y')
		return 9;
}

int time[10000000];  //各个号码出现的次数
bool vist[10000000];  //各个号码出现的次数
int sort_out[100000];  //按字典序存放待输出的电话号码

int main(void)
{
	int n;  //号码数
	while(cin>>n)
	{
		/*Initial*/

		memset(time,0,sizeof(time));
		memset(vist,false,sizeof(vist));
		int ps=0;  //sort_out指针
		bool flag=false;  //标记是否出现过重复号码

		/*Input*/

		for(int i=1;i<=n;i++)
		{
			int x=0;
			char s[20];
			cin>>s;
			for(int j=0;s[j]!='\0';j++)
			{
				if(s[j]=='-' || s[j]=='Q' || s[j]=='Z')
					continue;
				else if(s[j]<='9')
					x=x*10+s[j]-'0';
				else if(s[j]<='Z')
					x=x*10+ctoi(s[j]);
			}

			time[x]++;

			if(!vist[x] && time[x]>=2)  //电话号码x重复出现2次以上，则等待输出
			{
				flag=true;
				vist[x]=true;
				sort_out[ps++]=x;
			}
		}

		/*Sort & Output*/

		if(!flag)
			cout<<"No duplicates."<<endl;
		else
		{
			sort(sort_out,sort_out+ps);  //把待输出按字典序排序

			for(int i=0;i<ps;i++)
			{
				cout<<setfill('0')<<setw(3)<<sort_out[i]/10000;
				cout<<'-';
				cout<<setfill('0')<<setw(4)<<sort_out[i]%10000;
				cout<<' '<<time[ sort_out[i] ]<<endl;
			}
		}
	}
	return 0;
}
```

### 解题思路一：Qsort

```c
//Memory Time
//644K  672MS 

/*Qsort*/

#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

void initial(int* ctoi)  //把字符ch转换为其在手机上对应的数字键
{
	for(int i=0;i<=9;i++)
		ctoi[i+'0']=i;

	ctoi['A'] = ctoi['B'] = ctoi['C'] = 2;
	ctoi['D'] = ctoi['E'] = ctoi['F'] = 3;
	ctoi['G'] = ctoi['H'] = ctoi['I'] = 4;
	ctoi['J'] = ctoi['K'] = ctoi['L'] = 5;
	ctoi['M'] = ctoi['N'] = ctoi['O'] = 6;
	ctoi['P'] = ctoi['R'] = ctoi['S'] = 7;
	ctoi['T'] = ctoi['U'] = ctoi['V'] = 8;
	ctoi['W'] = ctoi['X'] = ctoi['Y'] = 9;
	return;
}

int main(int i)
{
	int ctoi['Z'+1];
	initial(ctoi);

	int n;  //号码数
	while(cin>>n)
	{
		/*Initial*/

		int* sort_out=new int[n];  //按字典序存放待输出的电话号码

		/*Input*/

		for(i=0;i<n;i++)
		{
			int x=0;
			char s[20];
			cin>>s;

			for(int j=0;s[j]!='\0';j++)
			{
				if(s[j]=='-' || s[j]=='Q' || s[j]=='Z')
					continue;
				x=x*10+ctoi[ s[j] ];
			}
			sort_out[i]=x;
		}

		/*Sort & Output*/

		sort(sort_out,sort_out+n);

		bool flag=true;  //标记是否所有号码都是唯一的
		for(i=0;i<n;)
		{
			int time=0;  //ort_out[i]出现的次数
			int k=sort_out[i];
			bool sign=false;  //标记k出现次数是否大于2

			while(k==sort_out[i] && i<n)
			{
				time++;
				i++;

				if(time==2)
				{
					flag=false;
					sign=true;
				}
			}

			if(sign)
			{
				cout<<setfill('0')<<setw(3)<<k/10000;
				cout<<'-';
				cout<<setfill('0')<<setw(4)<<k%10000;
				cout<<' '<<time<<endl;
			}
		}
		if(flag)
			cout<<"No duplicates."<<endl;

		delete sort_out;
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

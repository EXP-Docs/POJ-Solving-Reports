## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3292] [[Semi-prime H-numbers](http://poj.org/problem?id=3292)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 同余模]

------

## 问题描述

一个H-number是所有的模四余一的数。

如果一个H-number是H-primes 当且仅当它的因数只有1和它本身（除1外）。

一个H-number是H-semi-prime当且仅当它只由两个H-primes的乘积表示。

H-number剩下其他的数均为H-composite。

给你一个数h,问1到h有多少个H-semi-prime数。


## 解题思路

感觉跟**同余模**扯不上关系。

**筛法**打表，再直接输出。

水题。


## AC 源码


```c
//Memory Time 
//4172K  63MS 

#include<iostream>
using namespace std;

const int size=1000001;

int H_Number[size+1];

/*筛法打表*/
void Table(void)
{
	memset(H_Number,0,sizeof(H_Number));  //H_Number[i]=0 表示 i为H-prime

	for(int i=5;i<=size;i+=4)
	{
		for(int j=5;j<=size;j+=4)
		{
			int multiply=i*j;
			if(multiply>size)
				break;

			if(H_Number[i]==0 && H_Number[j]==0)  //i与j均为H-prime
				H_Number[multiply]=1;  //multiply为H-semi-primes
			else
				H_Number[multiply]=-1; //multiply为H-composite
		}
	}

	int Pcount=0; //H-prime计数器
	for(int k=1;k<=size;k++)
	{
		if(H_Number[k]==1)
			Pcount++;
		H_Number[k]=Pcount;   //从1到k有Pcount个H-semi-primes
	}
	return;
}

int main(void)
{
	Table();
	int h;
	while(cin>>h && h)
		cout<<h<<' '<<H_Number[h]<<endl;

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

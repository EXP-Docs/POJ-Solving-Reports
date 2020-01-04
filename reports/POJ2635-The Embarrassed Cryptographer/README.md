## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2635] [[The Embarrassed Cryptographer](http://poj.org/problem?id=2635)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 同余模]

------

## 问题描述

给定一个大数K，K是两个大素数的乘积的值。

再给定一个int内的数L

问这两个大素数中最小的一个是否小于L，如果小于则输出这个素数。


## 解题思路

首先对题目的插图表示无语。。。

**高精度求模+同余模定理**，解题步骤：

1、 **Char格式读入K**。把K转成千进制Kt，同时变为int型。

把数字往大进制转换能够加快运算效率。若用十进制则耗费很多时间，会TLE。

千进制的性质与十进制相似。

例如，把 `K=1234567890` 转成千进制，就变成了： `Kt=[  1][234][567][890]` 。

为了方便处理，我的程序是按“局部有序，全局倒序”模式存放 Kt

即 `Kt=[890][567][234][1  ]`  (一个中括号代表一个数组元素)

2、 **素数打表**，把10^6内的素数全部预打表，在求模时则枚举到小于L为止。

注意打表不能只打到100W，要保证素数表中最大的素数必须大于 `10^6`，否则当 `L=100W` 且K为 GOOD 时，会因为数组越界而RE，这是因为越界后prime都是负无穷的数，枚举的 `while(prime[pMin]<L)` 循环会陷入死循环

3、 **高精度求模**。

主要利用Kt数组和同余模定理。

例如要验证123是否被3整除，只需求模 `124%3`

但当123是一个大数时，就不能直接求，只能通过同余模定理对大数“分块”间接求模

具体做法是：

- 先求 `1%3 = 1`
- 再求 `(1*10+2)%3 = 0`
- 再求 `(0*10+4)%3 = 1`

那么就间接得到 `124%3=1`，这是显然正确的

而且不难发现， `(1*10+2)*10+4 = 124`

这是在10进制下的做法，千进制也同理，`*10` 改为 `*1000` 就可以了


## 测试数据

- 来源：[Nordic 2005（问题C）](http://ncpc.idi.ntnu.no/)
- 下载：[download](/testdata.zip)
- 输入：[input](/testdata/input.dat)
- 输出：[output](/testdata/output.dat)


## AC 源码


```c
//Memory Time
//624K  1235MS 

#include<iostream>
#include<string.h>
using namespace std;

const int Range=1000100;  //打表不能只打到100W，素数表中最大的素数必须大于10^6

int Kt[10000];  //千进制的K
int L;
int prime[Range+1];

/*素数组打表*/
void PrimeTable(void)
{
	int pNum=0;
	prime[pNum++]=2;

	for(int i=3;i<=Range;i+=2)  //奇偶法
	{
		bool flag=true;
		for(int j=0;prime[j]*prime[j]<=i;j++)  //根号法+递归法
			if(!(i%prime[j]))
			{
				flag=false;
				break;
			}
		if(flag)
			prime[pNum++]=i;
	}
	return;
}

/*高精度K对p求模，因数检查(整除)*/
bool mod(const int* K,const int p,const int len)
{
	int sq=0;
	for(int i=len-1;i>=0;i--)  //千进制K是逆序存放
		sq=(sq*1000+K[i])%p;  //同余模定理

	if(!sq)   //K被整除
		return false;
	return true;
}

int main(void)
{
	PrimeTable();

	char K[10000];
	while(cin>>K>>L && L)
	{
		memset(Kt,0,sizeof(Kt));
		int lenK=strlen(K);
		for(int i=0;i<lenK;i++)  //把K转换为千进制Kt，其中Kt局部顺序，全局倒序
		{                      //如K=1234567=[  1][234][567] ，则Kt=[567][234][1  ]
			int pKt=(lenK+2-i)/3-1;
			Kt[pKt]=Kt[pKt]*10+(K[i]-'0');
		}
		int lenKt=(lenK+2)/3;

		bool flag=true;
		int pMin=0;  //能整除K且比L小的在prime中的最小素数下标
		while(prime[pMin]<L)  //枚举prime中比L小的素数
		{
			if(!mod(Kt,prime[pMin],lenKt))
			{
				flag=false;
				cout<<"BAD "<<prime[pMin]<<endl;
				break;
			}
			pMin++;
		}
		if(flag)
			cout<<"GOOD"<<endl;
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

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2305] [[Basic remains](http://poj.org/problem?id=2305)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 同余模]

------

## 问题描述

在b进制下，求 `p%m`

其中p为b进制大数1000位以内，m为b进制数9位以内

## 解题思路

以字符串形式保存p，m

利用**进制转换公式**先把m逐位转换为10进制，由于m只有9位，因此直接转换用int保存即可。

再利用进制转换公式把p逐位转换为10进制，为了避免处理大数，转换过程中，若出现比m大的时候，则对m取模，继续转换。根据**同余模公式**知，这是允许的。


此时得到的p值就是 `（10进制p）%（10进制m）`

当 `p==0` 时，直接输出，否则把p逐位转换回去n进制再输出。

n进制的p必须用数组保存，因为10进制的p虽然不是大数，但n进制就不一定。


> **不要用大数去做**，当 `p>>m` 时，会超时的。


## AC 源码


```c
//Memory Time 
//256K   32MS 

#include<iostream>
#include<string.h>
using namespace std;

const int size=1000;   //大数位数

int main(void)
{
	int n; //进制数
	while(cin>>n && n)
	{
		char* Stra=new char[size+1];  //字符串n进制被减数
		char* Strb=new char[size+1];  //字符串n进制减数
		int pa=0;  //Stra[]指针
		int Diga=0,Digb=0;  //数字10进制被减数、减数

		cin>>Stra>>Strb;

		for(int j=0;Strb[j];j++)  //把n进制字符串减数 转换为 10进制数字减数
		{
			Digb*=n;
			Digb+=Strb[j]-'0';
		}
		for(int i=0;Stra[i];i++)  //把n进制字符串被减数 转换为 10进制数字被减数
		{
			Diga*=n;
			Diga+=Stra[i]-'0';

			if(Diga>=Digb) //同余模公式，为避免大数计算，进制转化时顺便求模
				Diga%=Digb;
		}
		if(!Diga)
			cout<<0<<endl;
		else
		{
			while(Diga)  //把10进制数字模 转换为 n进制字符串模
			{
				Stra[pa++]=Diga%n+'0';
				Diga/=n;
			}
			for(pa--;pa>=0;pa--)
				cout<<Stra[pa];
			cout<<endl;
		}

		delete Stra;
		delete Strb;
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

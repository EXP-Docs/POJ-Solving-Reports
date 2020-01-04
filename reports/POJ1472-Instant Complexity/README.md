## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1472] [[Instant Complexity](http://poj.org/problem?id=1472)]

> [Time: 1000MS] [Memory: 10000K] [难度: 中级] [分类: 模拟法]

------

## 问题描述

给出一段Pascial程序，计算其时间复杂度（能计算的项则计算，不能计算则化到最简的关于n的表达式O(n)，并把各项根据n的指数从高到低排列），输出时，系数为0的项不输出，系数为1的项不输出系数，指数为1的项不输出指数。

一段程序只有唯一一个BEGIN，代表程序的开始。与其对应的为最后的END，代表程序的结束。

一段程序最多只有10层循环嵌套，循环的入口为LOOP，一个LOOP对应一个END，代表该层循环的结束。

一段程序中OP的个数不限。

LOOP是循环的入口，其后面的数据可能是常量（非负整数），也可能是变量n，代表循环体执行的次数。

OP是语句，其后面的数据只能为常量（非负整数），代表该语句执行的次数。


## 解题思路

此题就是一条**表达式化简的模拟题**，用递归直接模拟（也可用**状态机**做）。

以第一个样例说明处理方法：

```delphi
BEGIN
  LOOP n
    OP 4
    LOOP 3
      LOOP n
        OP 1
      END
      OP 2
    END
    OP 1
  END
  OP 17
END
```

从该例子我们可以得到一条关于n的最初表达式： `n*(4+3*(n*1+2)+1)+17`

稍微化简一下，合并同一层的OP值，得到了： `n*(3*(n*1+2)+5)+17`

**不难看出每一个循环体都能写成 `k*n+i` 形式的子表达式，其中loop是 `*` 关系，op是 `+` 关系**


由于最大循环次数为10，那么我们用 `exp[11]` 存储多项式的每一项的指数i和系数 `k=exp[i]`，其中 `exp[0]` 其实就是常数项，由OP语句产生

**注意**LOOP后面可能输入字符n，也可能输入数字

处理方法：

- 用字符串输入s
- 若为 `s[0]==n`，则直接作字符处理
- 若 `s[0]!=n`，则认为是数字串，把它转换为int再处理


## 测试数据

- 来源：[Southwestern European Regional Contest 1997](http://www.informatik.uni-ulm.de/acm/Regionals/1997/)
- 下载：[download](/testdata.zip)
- 输入：[input](/testdata/input.dat)
- 输出：[output](/testdata/output.dat)


## AC 源码


```c
//Memory Time 
//264K   0MS 

#include<iostream>
using namespace std;

/*字符串转数字*/
int StrToNum(char* s)
{
	int digit=0;
	for(int i=0;s[i];i++)
		digit=digit*10+(s[i]-'0');

	return digit;
}

bool solve(int* exp)
{
	char s[30];
	cin>>s;

	if(s[0]=='E')    //END
		return false;
	else if(s[0]=='B')  //BEGIN
		while(solve(exp));   //若因为OP返回，则继续；若因为END返回，则结束
	else if(s[0]=='O')  //0P
	{
		cin>>s;
		exp[0]+=StrToNum(s);
		return solve(exp);
	}
	else     //LOOP
	{
		int TempExp[11]={0};  //临时exp[]
		cin>>s;
		while(solve(TempExp));

		if(s[0]=='n')   //LOOP n
		{
			for(int i=10;i>0;i--)
				TempExp[i]=TempExp[i-1];  //表达式乘以n，则所有项的次数+1
			TempExp[0]=0;
		}
		else  //LOOP Num
		{
			int x=StrToNum(s);
			for(int i=0;i<11;i++)
				TempExp[i]*=x; //表达式乘以const，则所有项的系数*const
		}
		for(int i=0;i<11;i++)
			exp[i]+=TempExp[i];
	}
	return true;
}

int main(void)
{
	int test;
	cin>>test;
	for(int t=1;t<=test;t++)
	{
		char s[6];
		int exp[11]={0};  //指数为i的项，其系数为exp[i]

		solve(exp);

		cout<<"Program #"<<t<<endl;
		cout<<"Runtime = ";

		bool flag=false;
		bool before=false;  //标记输出当前项之前，是否输出过前面的项
		for(int i=10;i>=0;i--)
			if(exp[i])   //当系数不为0时，才输出该项
			{
				flag=true;

				if(before)
				{
					cout<<'+';
					before=false;
				}

				if(!i)  //当指数为0时，直接输出系数
				{
					cout<<exp[i];
					before=false;
				}
				else
				{
					bool sign=false;  //标记系数是否为1
					if(i && exp[i]!=1)
					{
						sign=true;
						cout<<exp[i];
						before=true;
					}
					if(i)  //当指数不为0时
					{
						if(sign)
							cout<<'*';
						cout<<'n';
						if(i!=1)
							cout<<'^'<<i;
						before=true;
					}
				}
			}
		if(!flag)
			cout<<0<<endl<<endl;
		else
			cout<<endl<<endl;
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

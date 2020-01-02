## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3126] [[Prime Path](http://poj.org/problem?id=3126)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: BFS]

------

## 问题描述

给定两个四位素数a  b，要求把a变换到b

变换的过程要保证  每次变换出来的数都是一个 四位素数，而且当前这步的变换所得的素数  与  前一步得到的素数  只能有一个位不同，而且每步得到的素数都不能重复。

求从a到b最少需要的变换次数。无法变换则输出Impossible


## 解题思路

超级水题，40入口的**BFS + 素数判定**

不过剪枝之后就没有40入口了，入口数远小于40

无论是判定素数还是搜索素数，首先排除偶数，这样就剪掉一半枝叶了

判断素数用根号法判断，

如果一个数X不能被 `[2,√X]` 内的所有素数整除，那么它就是素数

可以判断的复杂度降到 logn

**注意**：

- 千位的变换要保证千位不为0
- 其实**素数也是用来辅助搜索剪枝**的


## AC 源码


```c
//Memory Time 
//212K   16MS 

#include<iostream>
using namespace std;

typedef class
{
	public:
		int prime;
		int step;
}number;

bool JudgePrime(int digit)
{
	if(digit==2 || digit==3)
		return true;
	else if(digit<=1 || digit%2==0)
		return false;
	else if(digit>3)
	{
		for(int i=3;i*i<=digit;i+=2)
			if(digit%i==0)
				return false;
		return true;
	}
}

int a,b;
bool vist[15000];
number queue[15000];

void BFS(void)
{
	int i;  //temporary
	int head,tail;
	queue[head=tail=0].prime=a;
	queue[tail++].step=0;
	vist[a]=true;

	while(head<tail)
	{
		number x=queue[head++];
		if(x.prime==b)
		{
			cout<<x.step<<endl;
			return;
		}

		int unit=x.prime%10;       //获取x的个位
		int deca=(x.prime/10)%10;  //获取x的十位

		for(i=1;i<=9;i+=2)     //枚举x的个位，保证四位数为奇数（偶数必不是素数）
		{
			int y=(x.prime/10)*10+i;
			if(y!=x.prime && !vist[y] && JudgePrime(y))
			{
				vist[y]=true;
				queue[tail].prime=y;
				queue[tail++].step=x.step+1;
			}
		}
		for(i=0;i<=9;i++)     //枚举x的十位
		{
			int y=(x.prime/100)*100+i*10+unit;
			if(y!=x.prime && !vist[y] && JudgePrime(y))
			{
				vist[y]=true;
				queue[tail].prime=y;
				queue[tail++].step=x.step+1;
			}
		}
		for(i=0;i<=9;i++)     //枚举x的百位
		{
			int y=(x.prime/1000)*1000+i*100+deca*10+unit;
			if(y!=x.prime && !vist[y] && JudgePrime(y))
			{
				vist[y]=true;
				queue[tail].prime=y;
				queue[tail++].step=x.step+1;
			}
		}
		for(i=1;i<=9;i++)     //枚举x的千位,保证四位数，千位最少为1
		{
			int y=x.prime%1000+i*1000;
			if(y!=x.prime && !vist[y] && JudgePrime(y))
			{
				vist[y]=true;
				queue[tail].prime=y;
				queue[tail++].step=x.step+1;
			}
		}

	}

	cout<<"Impossible"<<endl;
	return;
}

int main(void)
{
	int test;
	cin>>test;
	while(test--)
	{
		cin>>a>>b;
		memset(vist,false,sizeof(vist));
		BFS();
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

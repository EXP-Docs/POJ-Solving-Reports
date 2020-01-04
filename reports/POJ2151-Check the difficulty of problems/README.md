## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2151] [[Check the difficulty of problems](http://poj.org/problem?id=2151)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 概率]

------

## 问题描述

ACM比赛中，共M道题，T个队，pij表示第i队解出第j题的概率

问 每队至少解出一题且冠军队至少解出N道题的概率。


## 解题思路

**概率+DP**  ，概率不好真的拿不下这题

这题难点不在编程，在于问题的转化和理解

只要能用笔算出答案，离AC也就不远了。。。



**要求**：

- 每队至少解出一题 且 冠军队至少解出N道题的概率
- 由于冠军队可以不止一队，即允许存在并列冠军


则原来的所求的概率可以转化为：**每队均至少做一题的概率P1 减去 每队做题数均在1到N-1之间的概率P2**

![](/reports/POJ2151-Check%20the%20difficulty%20of%20problems/img/01.png)



## AC 源码


```c
//Memory Time
//8272K  110MS 

#include<iostream>
#include<iomanip>
using namespace std;

int M,T,N;   //M:题数  T:队数   N:冠军队至少做题数
double dp[1001][31][31];   //状态方程: dp[i][j][k]为第i队PASS前j题中的k题的概率

double p[1001][31];  //p[i][j]为第i队通过第j题的概率
double s[1001][31];  //s[i][j]为第i队在M题中至少PASS j题的概率

void ProTable(void)  //概率打表
{
	memset(dp,0.0,sizeof(dp));
	memset(s,0.0,sizeof(s));

	int i,j,k;
	for(i=1;i<=T;i++)  //逐队枚举
	{
		/*Initial*/

		dp[i][0][0]=1.0;

		for(j=1;j<=M;j++)
			dp[i][j][0]=dp[i][j-1][0]*(1-p[i][j]);

		/*Dp*/

		for(j=1;j<=M;j++)
			for(k=1;k<=j;k++)
				dp[i][j][k] = dp[i][j-1][k-1]*p[i][j] + dp[i][j-1][k]*(1-p[i][j]);

		s[i][0]=dp[i][M][0];
	    for(k=1;k<=M;k++)
			s[i][k]=s[i][k-1]+dp[i][M][k];
	}
	return;
}

int main(int i,int j)
{
	while(cin>>M>>T>>N)
	{
		if(!M && !T && !N)
			break;

		/*Input*/

		for(i=1;i<=T;i++)
			for(j=1;j<=M;j++)
				cin>>p[i][j];

		/*Compute the Probability*/

		ProTable();

		double p1=1.0;
		for(i=1;i<=T;i++)
			p1*=(s[i][M]-s[i][0]);   //所有队至少做1题的概率

		double p2=1.0;
		for(i=1;i<=T;i++)
			p2*=(s[i][N-1]-s[i][0]); //所有队做的题数均在1~N-1之间的概率

		/*Output*/

		cout<<fixed<<setprecision(3)<<p1-p2<<endl;
		//每队至少解出一题 且 至少有一队(冠军队)能至少解出N道题的概率
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

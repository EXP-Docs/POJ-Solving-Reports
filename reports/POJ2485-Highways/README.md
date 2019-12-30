## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2485] [[Highways](http://poj.org/problem?id=2485)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 最小生成树算法]

------

## 问题描述

无。


## 解题思路

题意很简单，就是求**最小生成树**的最大边。

思路、解法都和 [POJ1789](/reports/POJ1789-Truck%20History) 基本一致，只是多了一个判定条件

## AC 源码


```c
//Memory Time 
//656K  766MS 

#include<iostream>
using namespace std;

const int inf=65540;      //无限大
int dist[501][501];
int n;         //村落数量

int prim(void)
{
	int s=1;
	int m=1;
	bool u[501]={false};
	u[s]=true;

	int min_w;
	int point;
	int max_in_min=0;

	int low_dis[501];
	memset(low_dis,inf,sizeof(low_dis));

	while(true)
	{
		if(m==n)
			break;

		min_w=inf;
		for(int i=2;i<=n;i++)
		{
			if(!u[i] && low_dis[i]>dist[s][i])
				low_dis[i] = dist[s][i];
			if(!u[i] && min_w>low_dis[i])
			{
				min_w = low_dis[i];
				point=i;
				
			}
		}
		if(max_in_min<min_w)           //寻找最小生成树中的最长路径
			max_in_min = min_w;
		s=point;
		u[s]=true;
		m++;
	}
	return max_in_min;
}

int main(void)
{
	int test;
	cin>>test;
	while(test--)
	{
		/*Input*/

		cin>>n;

		int w;        //两点间边权（临时变量）
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cin>>dist[i][j];

		/*Prim Algorithm & Output*/

		cout<<prim()<<endl;

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

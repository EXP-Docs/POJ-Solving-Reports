## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1258] [[Agri-Net](http://poj.org/problem?id=1258)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 最小生成树算法]

------

## 问题描述

无。


## 解题思路

求**最小生成树**的总权值


## AC 源码


```c
//Memory Time 
//300K   32MS 

#include<iostream>
using namespace std;

const int inf=100001;      //无限大

int n;   //农场数量
int dist[101][101];

int prim(void)
{
	int s=1;
	int m=1;
	bool u[101]={false};
	u[s]=true;

	int min_w;
	int prim_w=0;
	int point;
	int low_dis[101];

	/*Initial*/

	for(int i=1;i<=n;i++)
		low_dis[i]=inf;

	/*Prim Algorithm*/

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
		s=point;
		u[s]=true;
		prim_w+=min_w;
		m++;
	}
	return prim_w;
}

int main(void)
{
	while(cin>>n)
	{
		/*Input*/

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

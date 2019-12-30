## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2240] [[Arbitrage](http://poj.org/problem?id=2240)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 最短路径算法]

------

## 问题描述

求自身到自身的最大转换率。


## 解题思路

最简单的方法就是***floryd算法变形***，求最大路径后，求最大环，看它是否满足条件。

每一个结点都必须有到自身的环(不甚清楚原因)。

**注意**：

- 本题需要建立容器，建立字符串到int的映射（一一对应）关系，把然后字符串作为数组下标，***模拟数组***
- 切记该double的地方一定不能为int


## AC 源码


```c
//Memory Time 
//276K   79MS 

#include <iostream>
#include<map>
#include<string>
using namespace std;

const int inf=10000;      //无限大
int n;      //货币种类
int m;      //兑换方式

map<string,int>STL;     //建立一个 使字符串与整数有一一对应关系 的容器STL,以便利用邻接矩阵存储数据

double rate;
char str[50],str1[50],str2[50];
double dist[31][31];

int i,j,k;

void floyd(void)
{
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(dist[i][j] < dist[i][k] * dist[k][j])       //变形的最大路径，变"+"为"*"
					dist[i][j] = dist[i][k] * dist[k][j];
	return;
}

int main(void)
{
	int cases=1;
	while(cases)
	{
		/*Initial*/

		memset(dist,inf,sizeof(dist));

		/*Input*/

		cin>>n;
		if(!n)break;

		for(i=1;i<=n;i++)
		{
			cin>>str;
			STL[str]=i;          //将输入的货币从1到n依次编号
			dist[i][i]=1;        //到自身的转换率默认为1，但通过floyd可能会被改变
			                     //有向图的顶点（一般）存在环
		}

		cin>>m;
		for(i=1;i<=m;i++)
		{
			cin>>str1>>rate>>str2;
			dist[STL[str1]][STL[str2]]=rate;      //构造图
		}

		/*Floyd Algorithm*/

		floyd();

		/*Output*/

		int flag=false;
		for(i=1;i<=n;i++)
			if(dist[i][i]>1)
			{
				flag=true;
				break;
			}
	 	if(flag)
			cout<<"Case "<<cases++<<": Yes"<<endl;
		else
			cout<<"Case "<<cases++<<": No"<<endl;
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

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1125] [[Stockbroker Grapevine](http://poj.org/problem?id=1125)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 最短路径算法]

------

## 问题描述

众所周知，证券经纪业依靠的就是过度的传言。您需要想出股票经纪人中传播假情报的方法，让您的雇主在股票市场的占据优势。为了获得最大的效果，你必须蔓延最快的方式谣言。

不幸的是你，股票经纪人信息只信任他们的“可靠来源”，这意味着你在你传播谣言之前必须考虑到他们的接触结构。它需要特定股票经纪人和一定的时间把谣言传递给他的每一位同事。你的任务将是写一个程序，告诉您选择哪一个股票经纪人作为谣言的出发点和所花费多少时间将谣言扩散到整个社会的股票经纪人。这一期限是衡量过去的人收到信息所需的时间。

**输入**：

你的程序包含多组股票经纪人的输入数据。每组以股票经纪人的人数开始。接下来的几行是每个经纪人与其他人接触的一些信息，包括这些人都是谁，以及将讯息传达到他们所需的时间。每个经纪人与其他人接触信息的格式如下：开头的第一个数表示共有n个联系人，接下来就有n对整数。每对整数列出的第一个数字指的是一个联系人（例如，一个'1'是指编号1的人），其次是在传递一个信息给那个人时所采取分钟的时间。没有特殊的标点符号或空格规则。

每个人的编号为1至经纪人数目。所花费的传递时间是从1到10分钟（含10分种）。股票经纪的人数范围是从1到100。当输入股票经纪人的人数为0时，程序终止。 

**输出**：

在对于每一组数据，你的程序必须输出一行，包括的信息有传输速度最快的人，以及在最后一个人收到消息后，所总共使用的时间（整数分钟计算）。 

你的程序可能会收到的一些关系会排除一些人，也就是有些人可能无法访问。如果你的程序检测到这样一个破碎的网络，只需输出消息“disjoint”。请注意，所花费的时间是从A传递消息到B，B传递信息到A不一定是花费同样的传递时间，但此类传播也是可能的。


## 解题思路

**最短路问题**，**Floyd算法**。相比于Bellman和Dijkstra，我认为是最接近人类自然思维的算法，说真的，我第一次做Floyd的题目时，我没有看过Floyd算法，我自己把Floyd推导出来了。。。

至于数据的存储，就用邻接矩阵，只要对矩阵上的时间进行修改就行了，相对比较方便。


## AC 源码


```c
//Memory Time 
//304K   0MS 

#include<iostream>
using namespace std;

const int inf=20;       //每条边的权值1~10，因此20就足以看做无限大了
int dist[101][101];

int i,j,k;
int n;   //经纪人个数

void floyd()
{
	/*Floyd Algorithm*/

	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)                                                  //for(i=1;i<=n-1;i++)
			for(j=1;j<=n;j++)      //注意，只有无向图（双向边权相等）才可以使用for(j=i+1;j<=n;j++)，这是因为无向图的邻接矩阵有对称性
				if(i!=j && dist[i][j] > dist[i][k] + dist[k][j])  //i!=j是因为无向图的顶点(一般)不存在环
					dist[i][j] = dist[i][k] + dist[k][j];

	int maxlength;
	int min_in_max=inf;
	int flag_source;

	for(i=1;i<=n;i++)                     //以i点作为各通路源点
	{
		maxlength=0;
		for(j=1;j<=n;j++)
			if(i!=j && maxlength<dist[i][j])   //寻找i到j的最长路径
				maxlength=dist[i][j];
		if(min_in_max>maxlength)
		{
			min_in_max=maxlength;       //寻找最长路径中的最短路
			flag_source=i;              //该短路所在路径的源点记录
		}
	}

	/*Output*/

	if(min_in_max<inf)
		cout<<flag_source<<' '<<min_in_max<<endl;
	else
		cout<<"disjoint"<<endl;

	return;
}

int main(void)
{
	while(1)
	{
		/*Initial*/

		memset(dist,inf,sizeof(dist));

		/*Input*/

		cin>>n;     
		if(!n)break;

		for(i=1;i<=n;i++)
		{
			int pair;
			cin>>pair;
			for(j=1;j<=pair;j++)
			{
				int cat,time;      //i的接触人，接触时间(边权)
				cin>>cat>>time;
				dist[i][cat]=time;
			}
		}

		/*Floyd Algorithm & Output*/

		floyd();
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

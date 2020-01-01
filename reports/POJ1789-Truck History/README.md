## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1789] [[Truck History](http://poj.org/problem?id=1789)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 最小生成树算法]

------

## 问题描述

用一个7位的string代表一个编号，两个编号之间的distance代表这两个编号之间不同字母的个数。一个编号只能由另一个编号“衍生”出来，代价是这两个编号之间相应的distance，现在要找出一个“衍生”方案，使得总代价最小，也就是distance之和最小。

例如有如下4个编号：

```
aaaaaaa
baaaaaa
abaaaaa
aabaaaa
```

显然的，第二，第三和第四编号分别从第一编号衍生出来的代价最小，因为第二，第三和第四编号分别与第一编号只有一个字母是不同的，相应的distance都是1，加起来是3。也就是最小代价为3。



## 解题思路

此题的关键是将问题转化为**最小生成树**的问题。因为每两个节点之间都有路径，所以是完全图。每一个编号为图的一个顶点，顶点与顶点间的编号差即为这条边的权值，题目所要的就是我们求出最小生成树来。这里我用**prim算法**来求最小生成树。


## AC 源码


```c
//Memory Time 
//15688K 344MS 

#include<iostream>
#include<string>
using namespace std;

const int inf=10;          //无穷大（两点间边权最大为7）
const int large=2001;

int n;  //truck types
char str[large][8];
int dist[large][large]={0};

/*Compute Weight*/

int weight(int i,int j)     //返回两个字符串中不同字符的个数（返回边权）
{
	int w=0;
	for(int k=0;k<7;k++)
		if(str[i][k]!=str[j][k])
			w++;
	return w;
}

/*Prim Algorithm*/

int prim(void)
{
	int s=1;       //源点（最初的源点为1）
	int m=1;       //记录最小生成树的顶点数
	bool u[large]; //记录某顶点是否属于最小生成树
	int prim_w=0;  //最小生成树的总权值
	int min_w;     //每个新源点到其它点的最短路
	int flag_point;
	int low_dis[large];  //各个源点到其它点的最短路

	memset(low_dis,inf,sizeof(low_dis));
	memset(u,false,sizeof(u));
	u[s]=true;

	while(1)
	{
		if(m==n)      //当最小生成树的顶点数等于原图的顶点数时，说明最小生成树查找完毕
			break;

		min_w=inf;
		for(int j=2;j<=n;j++)
		{
			if(!u[j] && low_dis[j]>dist[s][j])
				low_dis[j] = dist[s][j];
			if(!u[j] && min_w>low_dis[j])
			{
				min_w=low_dis[j];
				flag_point=j;      //记录最小权边中不属于最小生成树的点j
			}
		}
		s=flag_point;       //顶点j与旧源点合并
		u[s]=true;          //j点并入最小生成树（相当于从图上删除j点，让新源点接替所有j点具备的特征）
		prim_w+=min_w;      //当前最小生成树的总权值
		m++;                
	}
	return prim_w;
}

int main(void)
{
	int i,j;

	while(cin>>n && n)
	{
		/*Input*/
		
		for(i=1;i<=n;i++)
			cin>>str[i];

		/*Structure Maps*/

		for(i=1;i<=n-1;i++)
			for(j=i+1;j<=n;j++)
				dist[i][j]=dist[j][i]=weight(i,j);

		/*Prim Algorithm & Output*/

		cout<<"The highest possible quality is 1/"<<prim()<<'.'<<endl;

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

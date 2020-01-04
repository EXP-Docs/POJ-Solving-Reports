## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2031] [[Building a Space Station](http://poj.org/problem?id=2031)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 计算几何]

------

## 问题描述

就是给出三维坐标系上的一些球的球心坐标和其半径，搭建通路，使得他们能够相互连通。如果两个球有重叠的部分则算为已连通，无需再搭桥。求搭建通路的最小费用（费用就是边权，就是两个球面之间的距离）。


## 解题思路

不要被三维吓到了，其实就是图论的**最小生成树**问题

球心坐标和半径是用来求 两点之间的边权 的，求出边权后，把球看做点，用邻接矩阵存储这个无向图，再求最小生成树，非常简单的水题。

 
把球A和球B看做无向图图的两个结点，那么

**边权 = AB球面距离 = A球心到B球心的距离 –  A球半径 – B球半径**


边权直接用上面的公式求，接下来再用**Prim**就能完美AC了

> **注意**若边权 `<=0`，说明两球接触，即已连通，此时边权为0


## AC 源码


```c
//Memory Time 
//316K   16MS 

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

const double inf=1000.0;
const double eps=1e-10;

typedef class
{
	public:
		double x,y,z;
		double r;
}point;

/*Discuss Precision*/

int EPS(double k)
{
	if(fabs(k)<eps)
		return 0;
	return k>0?1:-1;
}

/*AB之间的距离（权值）*/

double dist(point A,point B)
{
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)+(A.z-B.z)*(A.z-B.z))-A.r-B.r;
}                        //AB距离是以球面为基准，而不是球心，因此要减去A球和B球的半径

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		if(n<=0)
			break;

		/*Initial*/

		point* node=new point[n+1];

		double w[101][101];
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				w[i][j]=inf;

		/*Input*/

		for(i=1;i<=n;i++)
			cin>>node[i].x>>node[i].y>>node[i].z>>node[i].r;

		for(i=1;i<=n-1;i++)
			for(j=i+1;j<=n;j++)
			{
				double temp=dist(node[i],node[j]);
				if(EPS(temp)<=0)
					w[i][j]=w[j][i]=0;  //两个球接触(相交)，则距离(权值)为0
				else
					w[i][j]=w[j][i]=temp;
			}

		/*Prim Algorithm*/

		bool vist[101]={false};
		int s=1;
		vist[s]=true;
		int fi;
		double sum_w=0.0;
		for(int count=1;count<n;count++)
		{
			double min=inf;

			for(i=2;i<=n;i++)
				if(!vist[i])
					if(min>w[s][i])
					{
						min=w[s][i];
						fi=i;
					}

			sum_w+=w[s][fi];
			vist[fi]=true;

			for(i=2;i<=n;i++)   //新源点s'继承最新合并进来的fi的性质
				if(!vist[i])    //以fi到其他点的更短路 取代旧源点s到其他点的权值
					if(w[s][i]>w[fi][i])
						w[s][i]=w[fi][i];
		}

		cout<<fixed<<setprecision(3)<<sum_w<<endl;

		/*Relax*/

		delete node;
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

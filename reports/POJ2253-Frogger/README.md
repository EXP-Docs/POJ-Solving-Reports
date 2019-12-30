## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2253] [[Frogger](http://poj.org/problem?id=2253)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 最短路径算法]

------

## 问题描述

给出两只青蛙的坐标A、B，和其他的n-2个坐标，任一两个坐标点间都是双向连通的。显然从A到B存在至少一条的通路，每一条通路的元素都是这条通路中前后两个点的距离，这些距离中又有一个最大距离。

现在要求求出所有通路的最大距离，并把这些最大距离作比较，把最小的一个最大距离作为青蛙的最小跳远距离。


## 解题思路

用Floyd算法求出两两最短路，再求出从每个点开始的最长路，最后从这n个最长路中求出最小的那个即为所求。

注意精度。


## AC 源码


```c
//Memory Time 
//584K   63MS 

#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

class coordinate
{
public:
	double x,y;
}point[201];

double path[201][201];   //两点间的权值

int main(void)
{
	int i,j,k;

	int cases=1;
	while(cases)
	{
		/*Read in*/

		int n;   //numbers of stones;
		cin>>n;
		if(!n)break;

		for(i=1;i<=n;i++)
			cin>>point[i].x>>point[i].y;

		/*Compute the weights of any two points*/

		for(i=1;i<=n-1;i++)
			for(j=i+1;j<=n;j++)
			{
				double x2=point[i].x-point[j].x;
				double y2=point[i].y-point[j].y;
				path[i][j]=path[j][i]=sqrt(x2*x2+y2*y2);  //双向性
			}

		/*Floyd Algorithm*/

		for(k=1;k<=n;k++)    //k点是第3点
			for(i=1;i<=n-1;i++)    //主要针对由i到j的松弛,最终任意两点间的权值都会被分别松弛为最大跳的最小（但每个两点的最小不一定相同）
				for(j=i+1;j<=n;j++)
					if(path[i][k]<path[i][j] && path[k][j]<path[i][j])    //当边ik,kj的权值都小于ij时，则走i->k->j路线，否则走i->j路线
						if(path[i][k]<path[k][j])               //当走i->k->j路线时，选择max{ik,kj},只有选择最大跳才能保证连通
							path[i][j]=path[j][i]=path[k][j];
						else
							path[i][j]=path[j][i]=path[i][k];

		cout<<"Scenario #"<<cases++<<endl;
		cout<<fixed<<setprecision(3)<<"Frog Distance = "<<path[1][2]<<endl;
		//fixed用固定的小数点位数来显示浮点数（包括小数位全为0)
		//setprecision(3)设置小数位数为3
		cout<<endl;
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

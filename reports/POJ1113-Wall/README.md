## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1113] [[Wall](http://poj.org/problem?id=1113)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 凸包]

------

## 问题描述

给定多边形城堡的n个顶点，绕城堡外面建一个围墙，围住所有点，并且墙与所有点的距离至少为L，求这个墙最小的长度。

## 解题思路

**推导公式（1）**：**城堡围墙长度最小值 = 城堡顶点坐标构成的散点集的凸包总边长 + 半径为L的圆周长**


由于数据规模较大，必须用**GrahamScan Algorithm构造凸包**（详细的算法可以参考我的 [POJ2187](/reports/POJ2187-Beauty%20Contest)，这里就不再啰嗦了），然后顺序枚举凸包相邻的两点并计算其距离，得到凸包的总边长，最后加上圆周长 `2πL`。

根据圆形的性质,其实就相当于多加了一个 `r=L` 的圆，把该圆根据凸包的边数（假设有k条）划分为k段弧，分别用来连接凸包上所有边。这样做的目的就是为了在保证围墙距离城堡至少为L的同时，使得转角处为圆角而不是直角，减少建造围城所需的资源。


------

**附**：

针对上面的**公式（1）**的**证明**：

证明如下：假如顺时针给出四个点A、B、C、D。组成了凸四边形ABCD。我们不妨过A点作AE垂直于AB，同时过A点再作AF垂直于AD，过B点作BG、BH分别垂直于AB、BC。连结EG，垂线段的长度为L，过A点以AE为半径作一段弧连到AF，同理，使GH成为一段弧。此时EG=AB（边），AB段城墙的最小值为EF+弧EF+弧GH=AB+弧EF+弧GH。对所有点进行同样的操作后，可知城墙的最小值=四边形的周长+相应顶点的弧长（半径都为L）之和。

下面证明这些顶点弧长组成一个圆。依然以前面的四边形为例。A、B、C、D四顶点各成周角，总和为 `360*4=1440` 度，四边形内角和为360度，每个顶点作两条垂线，总角度为 `4*2*90=720` 度，所以总圆周角为 `1440-360-720=360` 度，刚好组成圆。

所以**四边形ABCD的围墙最短= 四边形的周长+圆周长**。


推广到任意多边形，用同样的方法，城墙最短=凸包的周长 + 以L为半径的圆的周长。

首先，我们得出城墙最短 = 凸包的周长 + 相应顶点的弧长（半径都为L）之和。

再证明 相应顶点的弧长（半径都为L）之和=以L为半径的圆的周长。

事实上，设凸包顶点为n,n个顶点组成n个周角，角度为 `360*n=2*180*n`，凸包的内角和为 `180*(n-2)`，作了 `2*n` 条垂线，和为 `2*n*90=180*n` ,所以总圆周角为 `2*180*n-180*(n-2)-180*n=360`，组成圆。


## AC 源码


```c
//Memory Time 
//244K   63MS 

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

const int inf=10001;
const double pi=3.141592654;

typedef class
{
	public:
		int x,y;
}point;

/*AB距离平方*/

int distsquare(point A,point B)
{
	return (B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y);
}

/*AB距离*/

double distant(point A,point B)
{
	return sqrt((double)((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y)));
}

/*叉积计算*/

int det(int x1,int y1,int x2,int y2)
{
	return x1*y2-x2*y1;
}

int cross(point A,point B,point C,point D)
{
	return det(B.x-A.x,B.y-A.y,D.x-C.x,D.y-C.y);
}

/*快排判断规则*/

point* s;
int cmp(const void* pa,const void* pb)
{
	point* a=(point*)pa;
	point* b=(point*)pb;

	int temp=cross(*s,*a,*s,*b);
	if(temp>0)
		return -1;
	else if(temp==0)
		return distsquare(*s,*b)-distsquare(*s,*a);
	else
		return 1;
}

int main(int i,int j)
{
	int N,L;
	while(cin>>N>>L)
	{
		/*Input*/

		point* node=new point[N+1];

		int min_x=inf;
		int fi;
		for(i=1;i<=N;i++)
		{
			cin>>node[i].x>>node[i].y;

			if(min_x > node[i].x)
			{
				min_x = node[i].x;
				fi=i;
			}
			else if(min_x == node[i].x)
				if(node[fi].y > node[i].y)
					fi=i;
		}

		/*Quicksort the Vertex*/

		node[0]=node[N];
		node[N]=node[fi];
		node[fi]=node[0];

		s=&node[N];
		qsort(node+1,N,sizeof(point),cmp);

		/*Structure Con-bag*/

		int* bag=new int[N+2];
		bag[1]=N;
		bag[2]=1;
		int pb=2;
		for(i=2;i<=N;)
			if(cross(node[ bag[pb-1] ],node[ bag[pb] ],node[ bag[pb] ],node[i]) >= 0)
				bag[++pb]=i++;
			else
				pb--;

		/*Compute Min-length*/

		double minlen=0;
		for(i=1;i<pb;i++)
			minlen+=distant(node[ bag[i] ],node[ bag[i+1] ]);

		minlen+=2*pi*L;

		cout<<fixed<<setprecision(0)<<minlen<<endl;

		delete node;
		delete bag;
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

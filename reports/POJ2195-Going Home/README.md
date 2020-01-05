## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2195] [[Going Home](http://poj.org/problem?id=2195)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 费用流]

------

## 问题描述

给定一个 `N*M` 的地图，地图上有若干个man和house，且man与house的数量一致。man每移动一格需花费 `$1`（即单位费用=单位距离），一间house只能入住一个man。现在要求所有的man都入住house，求最小费用。


## 解题思路

**费用流问题**。

------

**构图**：

把man作为一个顶点集合U，house作为另一个顶点集合V，把U中所有点到V中所有点连线，费用 `cost[u][v]为abs(△x)+abs(△y)`，反向弧费用 `cost[v][u]= -cost[u][v]`，容量 `cap[u][v]=1`，构成一个多源多汇的二分图。

由于每一个多源多汇的网络流都必有一个与之对应的单源单汇的网络流，为了便于解题，由此构造一个超级源s和超级汇t，超级源s与U中所有点相连，费用 `cost[s][u]=0`（这是显然的），容量 `cap[s][u]=1`；V中所有点与超级汇t相连，费用 `cost[v][t]=0`（这是显然的），容量 `cap[t][v]=1`。

至于其他不连通的点，费用与容量均为0。容量为0的边，可以理解为饱和边，不再连通。而上述的所有边之所以容量初始化为1，是因为每间house只允许入住1个man。而与超级源（汇）相连的边的费用之所以为0，是为了现在所构造的**单源单汇网络流**最终所求的最小费用等于原来的**多源多汇网络流**的最小费用。


------


**求解**：

接下来的解题方法有关“**最小费用最大流**”，请未知的同学先去看看相关文献。

其实题目所求的**最小费用，就是最短距离**。用**spfa算法**求上述二分图G的最短路径，该最短路径就是图G的所有**增广链**中费用最小的一条。比较该增广链上所有边的容量，最小的容量就是“可分配的最大流MaxFlow”。

再者就是利用MaxFlow对增广链上的各条边的容量进行调整，正向弧容量减去MaxFlow，反向弧容量加上MaxFlow。然后该条增广链上各条边的费用分别乘以MaxFlow之和，就是第一个man到达合适的house所花费的最小费用。而图G经过调整，变成图G1。

针对图G1再次使用spfa算法，找到第二条增广链.....重复上述算法，直到无法找到增广链为止，则得到的费用和就是所求。

此种解题方法是**先计算最小费用，然后再在保证费用最小的情况下，增大流量**，最终达到求解目的。理论上，对于有n个man的图，可以找到n条增广链，即重复迭代spfa算法n次。若超过n次，则说明该图存在负权环，无解。但本题并无输出“无解”的要求，故可认为测试数据中不存在此类数据，因此在循环spfa算法时，不必计算次数，用 `while()` 足矣。

------


**最后要注意的是**：

Discuss上很多人说用了栈空间定义的数组，提交会RE或TLE，数组开大之后才能AC，因此便怪罪于测试数据有误。

其实不然。真正的原因是，题目所提及的N与M纯粹是地图的行数和列数，与man或house的个数无关，而我看了他们的代码，有部分同学却误以为N就是man的个数，导致出现RE。

因此在此强调一下，题目的N不等于man的个数，建议大家先对地图的man个数进行数数，得到man的个数，然后再开堆空间（new函数）；而非要开栈空间的同学也未尝不可，由于N与M的值均 `<=100`，且man与house的个数一致，则认为man的个数上限为 `100*100/2=5000` 。


## 测试数据

- 输入：[input](/reports/POJ2195-Going%20Home/testdata/input.dat)
- 输出：[output](/reports/POJ2195-Going%20Home/testdata/output.dat)


## AC 源码


```c
//Memory Time 
//612K   63MS 

#include<iostream>
#include<memory.h>
#include<cmath>
#include<queue>
using namespace std;

struct coordinate
{
	int x,y;
};

class solve
{
public:
	solve(int row,int col):R(row),C(col)
	{
		MinCost=0;
		n=0;

		Input();
		StructureBinaryMap();

		pre=new int[2*n+2];
		memset(pre,0,sizeof(int)*(2*n+2));
		dist=new int[2*n+2];
		vist=new bool[2*n+2];

		while(spfa())
			AddMaxFlow();
	}
	~solve()
	{
		cout<<MinCost<<endl;

		delete[] m;
		delete[] H;
		delete[] dist;
		delete[] vist;

		for(int i=0;i<R;i++)
			delete[] InMap[i];

		for(int j=0;j<2*n+2;j++)
		{
			delete[] cost[j];
			delete[] cap[j];
		}
	}

	int inf() const{return 0x7FFFFFFF;}
	int min(int a,int b) {return a<b?a:b;}

	void Input(void);
	void StructureBinaryMap(void);   //构造二分图
	bool spfa(void);				 //搜索从超级源到超级汇的最短路(即最小费用)的增广链
	void AddMaxFlow(void);			 //增广链调整(曾流)，计算最小费用

protected:
	int R,C;		//地图尺寸R*C ，
	int n;          //the number of man or Houses
	int s,t;		//s:超级源编号，t:超级汇编号
	int MinCost;    //最小花费

	char** InMap;   //输入的地图
	coordinate* m;	//记录所有man的坐标
	coordinate* H;	//记录所有House的坐标
	int* pre;		//最小费用流路径上，结点i的前驱结点为pre[i]
		
	int** cost;		//两点间费用,其中超级源为0，1~n为man，n+1~2n为house,2n+1为超级汇
	int** cap;		//两点间容量,其中超级源为0，1~n为man，n+1~2n为house,2n+1为超级汇
	int* dist;		//超级源到各点的最短距离
	bool* vist;		//标记各点是否在队列
};

void solve::Input(void)
{
	int i,j;
	
	InMap=new char*[R];
	for(i=0;i<R;i++)
	{
		InMap[i]=new char[C];
		for(j=0;j<C;j++)
		{
			cin>>InMap[i][j];

			if(InMap[i][j]=='m')	//检查'm'
				n++;				//得到man or house的数量
		}
	}
	return;
}

void solve::StructureBinaryMap(void)
{
	int i,j;
	int pm=0,pH=0;

	m=new coordinate[n+1];
	H=new coordinate[n+1];	

	/*记录各个man与house的坐标*/

	for(i=0;i<R;i++)
		for(j=0;j<C;j++)
			if(InMap[i][j]=='m')
			{
				m[++pm].x=i;
				m[pm].y=j;
			}
			else if(InMap[i][j]=='H')
			{
				H[++pH].x=i;
				H[pH].y=j;
			}

	/*建立存储空间*/

	cost=new int*[2*n+2];
	cap=new int*[2*n+2];
	for(i=0;i<2*n+2;i++)
	{
		cost[i]=new int[2*n+2];
		cap[i]=new int[2*n+2];

		memset(cost[i],0,sizeof(int)*(2*n+2));  //所有路径费用默认为0
		memset(cap[i],0,sizeof(int)*(2*n+2));   //所有路径容量默认为0(饱和，不连通)
	}

	/*初始化超级源s到各个man的容量*/

	s=0;
	for(i=1;i<=n;i++)
		cap[s][i]=1;	//容量默认为1

	/*初始化各个man到house的距离(费用)及容量*/

	for(i=1;i<=n;i++)
		for(j=n+1;j<=2*n;j++)
		{
			cost[i][j]=abs(m[i].x-H[j-n].x)+abs(m[i].y-H[j-n].y);   //man到house的费用为abs(△x)+abs(△y)
			cost[j][i]=-cost[i][j];		//注意顺便构造负权边
			cap[i][j]=1;
		}

	/*初始化各个house到超级汇t的容量*/

	t=2*n+1;
	for(j=n+1;j<t;j++)
		cap[j][t]=1;	//容量默认为1

	return;
}

bool solve::spfa(void)
{
	dist[s]=0;
	for(int i=1;i<2*n+2;i++)   //注意这里不能用memset(),memset是对字节为单位进行赋值
		dist[i]=inf();	//若非置0，memset对char、bool以外的类型都会赋一个与期望完全不同的数值
	
	memset(vist,false,sizeof(bool)*(2*n+2));
	vist[s]=true;

	queue<int>q;
	q.push(s);

	while(!q.empty())
	{
		int u=q.front();	//获取队头元素
		for(int v=0;v<=t;v++)
		{
			if(cap[u][v] && dist[v]>dist[u]+cost[u][v])  //u->v容量未饱和，且能够松弛
			{
				dist[v]=dist[u]+cost[u][v];
				pre[v]=u;		//记录u的前驱结点

				if(!vist[v])
				{
					q.push(v);
					vist[v]=true;
				}
			}
		}
		q.pop();	 //队头元素出队
		vist[u]=false;
	}

	if(dist[t]==inf())  //dist[t]没有被调整，说明已不存在增广链
		return false;

	return true;	//找到一条当前费用和最小的增广链
}

void solve::AddMaxFlow(void)
{
	int MaxFlow=inf();  //可分配最大流
	int i;

	for(i=t;i!=s;i=pre[i])  //可分配最大流 为增广链上的最小容量边的容量
		MaxFlow=min(MaxFlow,cap[pre[i]][i]);

	for(i=t;i!=s;i=pre[i])	//增广链上流量调整(增流)
	{
		cap[pre[i]][i]-=MaxFlow;	//正向弧容量减去可分配最大流
		cap[i][pre[i]]+=MaxFlow;	//反向弧容量加上可分配最大流
		MinCost+=cost[pre[i]][i]*MaxFlow;  //最小费用=单位费用*流量
	}

	return;
}

int main(void)
{
	int row,col;
	while(cin>>row>>col && (row+col))
		solve poj2195(row,col);

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

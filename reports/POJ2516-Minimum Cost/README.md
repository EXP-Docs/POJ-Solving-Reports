## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2516] [[Minimum Cost](http://poj.org/problem?id=2516)]

> [Time: 4000MS] [Memory: 65536K] [难度: 中级] [分类: 费用流]

------

## 问题描述

有N个供应商，M个店主，K种物品。每个供应商对每种物品的的供应量已知，每个店主对每种物品的需求量的已知，从不同的供应商运送不同的货物到不同的店主手上需要不同的花费，又已知从供应商Mj送第kind种货物的单位数量到店主Ni手上所需的单位花费。

问：供应是否满足需求？如果满足，最小运费是多少？


## 解题思路

**费用流问题**。


**（1）输入格式：**

在说解题思路之前，首先说说输入格式，因为本题的输入格式和解题时所构造的图的方向不一致，必须要提及注意。以样例1为例：

![](/reports/POJ2516-Minimum%20Cost/img/01.png)


**（2）题目分析和拆解：**

**A、首先处理“供应是否满足需求”的问题**。

要总供应满足总需求，就必须有 每种物品的供应总量都分别满足其需求总量，只要有其中一种物品不满足，则说明供不应求，本组数据无解，应该输出-1。但是要注意这里判断无解后，只能做一个标记，但还要继续输入，不然一旦中断输入，后面的几组数据结果就全错了。

而要知道“每种物品的供应总量都分别满足其需求总量”，对所有供应商第kind种物品的供应量求和 `ksupp[kind]`，对所有店主第kind种物品的需求量求和 `kneed[kind]`，然后比较 `ksupp[kind]` 与 `kneed[kind]` 就可以了。

**而最小费用流的计算是建立在“供等于求”或“供过于求”的基础上的**。


------

**B、最小费用问题：**

要直接求出“把所有物品从所有供应商运送到所有店主的最小费用MinTotalCost”是不容易的。但是求出“把第kind种物品从所有供应商运送到所有店主的最小费用 `MinCost[kind]`”却简单得多，这就转化为经典的多源多汇的费用流问题，而最后只需要把K种物品的最小费用求和 `MinCost[kind]`，就能得到运送所有物品的最小费用MinTotalCost。

其实题目的输入方式最后要输入K个矩阵已经暗示了我们要拆解处理。

------

**C、构图：**

那么对于第kind种物品如何构图呢？

解决多源多汇网络问题，必须先构造与其等价的单源单汇网络。构造超级源s和超级汇t，定义各点编号如下：

超级源s编号为0，供应商编号从1到M，店主编号从 `M+1` 到 `M+N`，超级汇t编号为 `M+N+1`。

令总结点数 `Nump=M+N+2`，申请每条边的“花费”空间 `cost[Nump][Nump]`和“容量”空间 `cap[Nump][Nump]`，并初始化为全0。

超级源s向所有供应商M建边，费用为0，容量为供应商j的供应量。

每个供应商都向每个店主建边，正向弧费用为输入数据的第kind个矩阵（注意方向不同），容量为供应商j的供应量；反向弧费用为正向弧费用的负数，容量为0。

所有店主向超级汇t建边，费用为0，容量为店主i的需求量。


**注意：**

- 1、其他没有提及的边，费用和容量均为0，容量为0表示饱和边或不连通。
- 2、计算每种物品的最小费用都要重复上述工作重新构图，不过存储空间cost和cap不必释放，可重新赋值再次利用。

------

**D、求解**

对于第kind种物品的图，都用**spfa算法**求解**最小费用路径**（**增广链**），再利用可分配最大流调MaxFlow整增广链上的容量，正向弧容量减去MaxFlow，反向弧容量减去MaxFlow，费用为单位花费乘以MaxFlow。

具体的算法流程可参考我 [POJ2195](/reports/POJ2195-Going%20Home) 的解题报告，基本一样。但注意的导致本题无可行解的原因只有“供不应求”，由输入数据知显然各边的容量均>=0，因此并不会出现负权环，spfa仍然用while循环直至无增广链为止足矣。



## AC 源码


```c
//Memory Time 
//596K  1188MS 

#include<iostream>
#include<queue>
using namespace std;

class solve
{
public:
	solve(int n,int m,int k):N(n),M(m),K(k)
	{
		MinTotalCost=0;
		Nump=N+M+2;
		s=0;
		t=N+M+1;
		Err=false;

		AppRoom();
		Input();
		Compute();
	}
	~solve()
	{
		if(Err)
			cout<<-1<<endl;
		else
			cout<<MinTotalCost<<endl;

		Relax();
	}

	int inf() const{return 0x7FFFFFFF;}
	int min(int a,int b) {return a<b?a:b;}
	bool check(int kind) const{return ksupp[kind]>=kneed[kind];}

	void AppRoom(void);			//申请存储空间
	void Input(void);			//输入
	void Compute(void);			//计算MinTotalCost
	void Initial(int kind);		//初始化数据，重新构造第kind种物品的流量图
	bool spfa(void);			//对当前图求最小费用流(增广链)
	void AddFlow(int kind);		//对最小费用流增流，调整增广链上的流量和费用，并累计第kind种物品的费用MinCost[kind]
	void Relax(void);			//释放空间

protected:
	int N;				//店主数
	int M;				//供货商数
	int K;				//商品种数
	int s,t;			//超级源s 与 超级汇t 的编号
	int Nump;			//N+M+超级源s+超级汇t (即总结点数量)
	int** supply;		//supply[j][k]:供货商j对第k种物品的供货量
	int** need;			//need[i][k]: 店主i对第k种物品的需求量
	int*** InputCost;	//InputCost[kind][N][M] 对应输入的K的花费矩阵
	int* MinCost;		//所有供货商运送第k种货物给所有店主的最小花费
	int MinTotalCost;	//所有供货商运送所有物品给所有店主的最小总花费

	/*构图时各点编号-- 超级源s:0 , 供应商M:1~M , 店主N:M+1~M+N , 超级汇t:N+M+1*/
	int** cost;			//任意两点之间的花费
	int** cap;			//任意两点之间的容量
	int* dist;			//超级源到各点的距离
	int* vist;			//判断某点是否在队列中

	int* pre;			//记录前驱. u->v，pre[v]=u
	bool Err;			//标记供不应求
	int* ksupp;			//第k种物品的总供应量
	int* kneed;			//第k种物品的总需求量
};

void solve::AppRoom(void)
{
	int i,k;

	/*申请构图与解题必要空间*/

	MinCost=new int[K+1];
	ksupp=new int[K+1];
	kneed=new int[K+1];
	dist=new int[Nump];
	vist=new int[Nump];
	pre=new int[Nump];

	cost=new int*[Nump];
	cap=new int*[Nump];
	for(i=0;i<Nump;i++)
	{
		cost[i]=new int[Nump];
		cap[i]=new int[Nump];
	}

	/*申请输入空间*/

	supply=new int*[M+1];
	for(i=1;i<=M;i++)
		supply[i]=new int[K+1];

	need=new int*[N+1];
	for(i=1;i<=N;i++)
		need[i]=new int[K+1];

	InputCost=new int**[K+1];	//K个矩阵
	for(k=1;k<=K;k++)
	{
		InputCost[k]=new int*[N+1];
		for(i=1;i<=N;i++)
			InputCost[k][i]=new int[M+1];
	}


	return;
}

void solve::Input(void)
{
	int i,j,k;

	for(i=1;i<=N;i++)
		for(k=1;k<=K;k++)
			cin>>need[i][k];

	for(j=1;j<=M;j++)
		for(k=1;k<=K;k++)
			cin>>supply[j][k];
	
	for(k=1;k<=K;k++)
		for(i=1;i<=N;i++)
			for(j=1;j<=M;j++)
				cin>>InputCost[k][i][j];

	/*计算第k种物品的供应总量和需求总量*/

	for(k=1;k<=K;k++)
	{
		ksupp[k]=0;
		for(j=1;j<=M;j++)
			ksupp[k]+=supply[j][k];

		kneed[k]=0;
		for(i=1;i<=N;i++)
			kneed[k]+=need[i][k];
	}

	return;
}

void solve::Compute(void)
{
	for(int kind=1;kind<=K;kind++)
	{
		Initial(kind);
		if(!check(kind))	//检查第k种物品的供求情况
		{
			Err=true;
			return;
		}

		while(spfa())
			AddFlow(kind);

		MinTotalCost+=MinCost[kind];
	}

	return;
}

void solve::Initial(int kind)
{
	int i,j;

	MinCost[kind]=0;
	memset(pre,0,sizeof(int)*Nump);

	for(i=0;i<Nump;i++)		//目的是处理不属于当前所构造的图的边
	{
		memset(cap[i],0,sizeof(int)*Nump);
		memset(cost[i],0,sizeof(int)*Nump);
	}

	/*初始化超级源s到各个供货商的容量*/

	for(j=1;j<=M;j++)
		cap[s][j]=supply[j][kind];	//s到供货商j的容量为供货商j的供应量
		

	/*初始化各个店主到超级汇t的容量*/

	for(i=M+1;i<t;i++)
		cap[i][t]=need[i-M][kind];	//店主i到t的容量为店主i的需求量

	/*初始化各个供应商到各个店主的容量和费用*/

	for(i=M+1;i<t;i++)
		for(j=1;j<=M;j++)
		{
			cost[j][i]=InputCost[kind][i-M][j];	//注意这里的费用存储方式与输入的存储方式相反
			cost[i][j]=-cost[j][i];				//反向弧费用
			cap[j][i]=supply[j][kind];			//供应商j到店主i的容量为供货商j的供应量
		}

	return;
}

bool solve::spfa(void)
{
	for(int i=s;i<=t;i++)
	{
		dist[i]=inf();
		vist[i]=false;
	}
	dist[s]=0;

	queue<int>q;
	q.push(s);
	vist[s]=true;

	while(!q.empty())
	{
		int u=q.front();
		for(int v=s;v<=t;v++)
		{
			if(cap[u][v] && dist[v]>dist[u]+cost[u][v])
			{
				dist[v]=dist[u]+cost[u][v];
				pre[v]=u;

				if(!vist[v])
				{
					q.push(v);
					vist[v]=true;
				}
			}
		}

		q.pop();
		vist[u]=false;
	}

	if(dist[t]<inf())
		return true;		//dist[t]被修正，说明找到增广链

	return false;	//已无增广链，spfa结束
}

void solve::AddFlow(int kind)
{
	int MaxFlow=inf();		//可分配最大流
	int i;
	for(i=t;i!=s;i=pre[i])
		MaxFlow=min(MaxFlow,cap[pre[i]][i]);	//可分配最大流=增广链上的最小容量

	for(i=t;i!=s;i=pre[i])
	{
		cap[pre[i]][i]-=MaxFlow;	//正向弧容量调整
		cap[i][pre[i]]+=MaxFlow;	//反向弧容量调整
		MinCost[kind]+=cost[pre[i]][i]*MaxFlow;		//最小费用=单位费用*可分配最大流
	}

	return;
}

void solve::Relax(void)
{
	int i,k;

	delete[] MinCost;
	delete[] dist;
	delete[] vist;
	delete[] pre;
	delete[] ksupp;
	delete[] kneed;

	for(i=0;i<Nump;i++)
	{
		delete[] cost[i];
		delete[] cap[i];
	}

	for(i=1;i<=M;i++)
		delete[] supply[i];

	for(i=1;i<=N;i++)
		delete[] need[i];

	for(k=1;k<=K;k++)
	{
		for(i=1;i<=N;i++)
			delete[] InputCost[k][i];

		delete[] InputCost[k];
	}

	return;
}

int main(void)
{
	int n,m,k;
	while(cin>>n>>m>>k && (n+m+k))
		solve poj2516(n,m,k);

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

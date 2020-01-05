## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3308] [[Paratroopers](http://poj.org/problem?id=3308)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 最小割/网络流]

------

## 问题描述

火星人侵略地球，他们意图登陆破坏某个地区的兵器工厂。据探子回报，火星人登陆的地区为 `n*m` 大小的地域，而且每一个火星人的着陆点坐标已知。

火星人很强悍，只要有一个火星人着陆后能够幸存，他必定能毁坏这片区域的全部兵工厂。为了防止这种情况发生，必须保证在火星人着陆的一瞬间把他们全部同时杀死。

现在防卫队有一个激光枪，开一枪就能把 在同一行（或同一列）着陆的火星人全部杀死。但是这种激光枪的使用是有代价的，把这种激光枪安装到不同行的行首、或者不同列的列首，费用都不同。现在已知把激光枪安装到任意位置的费用，总的花费为这些安装了激光枪的行列花费的乘积。

问怎样安装激光枪才能在杀死所有火星人的前提下费用最少？


## 解题思路

**Dinic算法**求解**最大流问题**。


这题和 [POJ3041](/reports/POJ3041-Asteroids) 非常相似，但却并不是一回事。[POJ3041](/reports/POJ3041-Asteroids) 是要求开枪的次数最少破坏全部陨石，而本题是要求开枪的花费最少杀死全部火星人，由于在不同位置开枪的代价不同，因此“花费最小不一定就是开枪次数最少”，这个要注意。

------


本题的模型是显然是一个**二分图**，并且是二分图中直观的**顶点覆盖问题**。


首先说说“**覆盖**”的大致概念：图G的一个顶点覆盖是由一些顶点构成的集合 `Q∈V(G)`, 又G中有若干条边的集合 `P∈E(G)`，这些边均至少有一个端点在Q内，则P被Q顶点覆盖。

二分图中的顶点覆盖问题是，如果覆盖每个顶点需要付出不同的代价，也可以说是不同的花费，或称为点权（或为容量），那么问题可以描述成，在保证覆盖所有边的情况下，如何使得权和最小。


**求二分图顶点覆盖问题，都是转化为最小割问题去求解**，转化方法如下：

建超级源S 和超级汇 T，假设二分图两个点集分别为 X 和 Y。X和Y原来的边容量设为INF，将S到X里每个点x连一条边，边权为x的点权，也可以看做覆盖点x的所有出边的花费 `(W-)`，将Y里每个点y到T连一条边，边权为y的点权，也可以看做覆盖点y的所有入边的花费 `(W+)`。这样求得最小割容量，即为原问题的解。


**这是对这个转化方法的解释和证明：**

X到Y的边权为INF，自然不会成为最小割中的边，那就只有可能是S到X和Y到T中的边，而：S到X中点x的边e1, 权为点x的点权，点x和Y中的所有临边e2，都需要受到e1的流量的限制，同样，X到Y中点y的所有边也会受到点y到T的容量限制。这样求得割就能保证覆盖掉所有的边。

我们可以用反证法证明一下：假设有边 `<x, y>` 没有被覆盖掉，则边 `<S, x>` 流量为0且边 `<y, T>` 流量为0，而 `<x, y>` 流量为INF，自然可以找到一条S到T的增流路径 `<S, x, y, T>`，与以求得流为最大流相矛盾，则可以说明，在最大流的情况下，所有的边都已经被覆盖掉。

而**最小割问题可以用最大流来解决**，问题就变得简单了。


而我们又知道，图G的最小割的容量，等于其最大流的流量，因此**本题最终是转化为最大流问题**求解。（**据我所知，还没有直接求最小割的算法**）


------



下面说说本题的详细解题过程：

**1、 构造二分图**

构造方法按照上述把“顶点覆盖问题转化为最小割问题”的方法去处理：

显然取行坐标为二分图的X集合，编号为 `1~N`，点权就是激光炮在第i行射一炮的费用ri；列坐标为二分图的Y集合，编号为 `N+1~N+M`，点权就是激光炮在第j列射一炮的费用cj。

然后建立超级源S，编号为0，超级汇T，编号为 `N+M+1`。S向X集合每个点都连一条正向弧，边容量为第i点的点权；Y集合每个点都向T连一条正向弧，边容量为第j点的点权。而落有伞兵火星人的区域，表示该位置的x与y是连通的，则从X集合取该点与Y集合的对应点连一条正向弧，边容量为无限大inf。

X集合每个点到S的反向弧、T到Y集合每个点的反向弧，落有火星人区域的y 到x的反向弧，也都要连上边（这是为了后续的Dinic算法在增广链上调整流量之用），但边容量默认为0，表示不连通。


**2、 此时问题转化为最小割问题，因为图G的最小割的容量，等于其最大流的流量，因此用求最大流的方法去求解。**

但本题数据比较BT，常规求最大流的方法（压入重标法）会TLE，因此只能用相对更高效的Dinic算法。

循环：一次BFS对残余图分层，一次DFS在层次图上求一条增广链，调整最大流。


------


**注意**：

**1、 double精度的问题**

本题有一句这样的话：the total cost of constructing a system firing all guns simultaneously is equal to the product of their costs.

其中product不是“产品”的意思，而是“乘积”的意思，英语差的同学建议查字典。

因此为了方便求最大流，应该首先对所有费用（点权）求一次自然对数，把乘法转变为加法。最后再对累加的最小费用求一次exp，就是答案。

而自然对数log是double型的， double精度在15～16位左右，那么本题的无限大inf和最小精度eps的差距就不能超过15位，否则精度问题会把你WA成sb。

而又由于，eps要开到输出小数位数两倍的原则（本题要求取到4位小数），那么eps在本题中开到 `1e-8` 就是很有必要的一件事情，所以相应的inf最多只能开到 `1e8`。（但其实呢，2倍原则一般针对带有乘除法的浮点型问题，所以本题只开到 `1e-5` 或者 `1e-6` 亦可）

但注意本题中的另一个性质，取对数，任何数字取对数log之后就会变得很小（别告诉我你不知道O(logN)的算法有多么快），所以这题的inf开的很小就好。（inf开到 `1e2` 都能过，说明poj还比较仁慈，没有添加什么超 `2^100` 的数据。）

 

**2、 存储问题**

本题推荐用**邻接链表**存储，邻接矩阵不可能不超时的。还有，上面构图时已经提及过了，在把二分图构造为单源单汇网络流时，看似都是只有一个方向的有向边（正向弧），但其实反向弧也要用到的（Dinic算法），因此往链表添加边 `a->b` 时，若不顺便添加边 `b->a` ，必然会WA。

 

**3、poj的 C++ 和 G++的问题**

对于双精度输出，G++上面要用 `%f`，C++则用 `%lf`，否则WA。


## AC 源码


```c
//Memory Time 
// 796K  47MS 

#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

class Node
{
public:
	int id;
	class Node* next;
	Node():id(-1),next(0){}
};

class solve
{
public:
	solve(int n,int m,int l):N(n),M(m),L(l)
	{
		Initial();
		Input_Creat();
		Dinic();
		printf("%.4lf\n",exp(MinCost));
	}
	~solve()
	{
		delete[] level;

		for(int i=0;i<=T;i++)
			delete[] cap[i];

		EmptyList();
	}

	double min(double a,double b) const{return a<b?a:b;}
	double inf() const{return 1e8;}
	double eps() const{return 1e-8;}
	double precision(double x) const{return fabs(x)<eps()?0:x;}

	void Initial(void);					//申请存储空间并初始化
	void Input_Creat(void);				//输入并创建单源单汇网络

	void Dinic(void);					//Dinic算法寻找最大流
	bool BFS(void);						//对剩余图标号分层
	double DFS(int str,double flow);	//搜索增广链，修正最大流
										//str:搜索起点; flow:“关口点str”允许通过的最大流

	void AddEdge(int a,int b);			//向邻接链表加入双向弧a<->b (反向弧b->a容量默认为0)
	void DelLink(Node* p);				//释放以p为表头的整条链
	void EmptyList(void);				//释放邻接链表

protected:

	int N;				//行数(X点集)
	int M;				//列数(Y点集)
	int L;				//伞兵数量
	int S;				//超级源
	int T;				//超级汇
	Node** LinkHead;	//邻接链表表头

	double** cap;		//容量，在本题“费用”即“容量”
	int* level;			//层次图上各顶点的标号
	double MinCost;		//最小总费用

};

void solve::Initial(void)
{
	MinCost=0;
	S=0;
	T=N+M+1;

	LinkHead=new Node*[T+1];
	for(int i=0;i<=T;i++)
		LinkHead[i]=0;

	cap=new double*[T+1];
	for(int j=0;j<=T;j++)
	{
		cap[j]=new double[T+1];
		memset(cap[j],0,sizeof(double)*(T+1));	//初始化所有弧的容量为0（不连通）
	}

	level=new int[T+1];

	return;
}

void solve::Input_Creat(void)
{
	/*Temporary*/

	int i,j,k;
	double R_cost,C_cost;
	int x,y;

	/*输入行费用，构造超级源S到X点集的边*/

	for(i=1;i<=N;i++)
	{
		scanf("%lf",&R_cost);
		cap[S][i]=log(R_cost);	//正向弧容量，取对数，化乘为加
		AddEdge(S,i);
	}

	/*输入列费用，构造Y点集到超级汇T的边*/

	for(j=N+1;j<T;j++)
	{
		scanf("%lf",&C_cost);
		cap[j][T]=log(C_cost);	//正向弧容量，取对数，化乘为加
		AddEdge(j,T);
	}

	/*输入伞兵的坐标，构造X点集到Y点集的边*/

	for(k=1;k<=L;k++)
	{
		scanf("%d %d",&x,&y);
		cap[x][y+N]=inf();		//正向弧容量
		AddEdge(x,y+N);
	}

	return;
}

void solve::AddEdge(int a,int b)
{
	/*正向弧部分*/

	if(!LinkHead[a])
		LinkHead[a]=new Node;

	Node* p1=LinkHead[a]->next;
	Node* pa=new Node;
	pa->id=b;
	pa->next=p1;
	LinkHead[a]->next=pa;

	/*反向弧部分*/

	if(!LinkHead[b])
		LinkHead[b]=new Node;

	Node* p2=LinkHead[b]->next;
	Node* pb=new Node;
	pb->id=a;
	pb->next=p2;
	LinkHead[b]->next=pb;

	return;
}

void solve::Dinic(void)
{
	while(BFS())
		MinCost+=DFS(S,inf());

	return;
}

bool solve::BFS(void)
{
	for(int i=S;i<=T;i++)
		level[i]=-1;

	queue<int>q;
	q.push(S);
	level[S]=0;

	while(!q.empty())
	{
		int a=q.front();
		if(LinkHead[a])
		{
			for(Node* p=LinkHead[a]->next;p;p=p->next)
			{
				int b=p->id;
				if(level[b]==-1 && precision(cap[a][b])>0)
				{
					q.push(b);
					level[b]=level[a]+1;
				}
			}
		}
		q.pop();
	}
	return level[T]!=-1;
}

double solve::DFS(int str,double flow)
{
	if(str==T)
		return flow;
						//假设关口点str有多个分支
	double SubFlow=0;	//则SubFlow为前k个分支允许通过的最大流之和
						//flow-SubFlow即为str能够给余下的分支所提供的最大流量之和

	if(LinkHead[str])
	{
		for(Node* p=LinkHead[str]->next;p;p=p->next)
		{
			int end=p->id;
			/*注意不能“跨层”搜索*/
			if(level[end]==level[str]+1 && precision(cap[str][end])>0)
			{
				double AdjustFlow=DFS(end,min(flow-SubFlow,cap[str][end]));
				SubFlow+=AdjustFlow;

				cap[str][end]-=AdjustFlow;	//正向弧容量修正
				cap[end][str]+=AdjustFlow;	//反向弧容量修正
			}
		}
	}

	return SubFlow;
}

void solve::DelLink(Node* p)
{
	if(p->next)
		p=p->next;
	delete[] p;
	return;
}

void solve::EmptyList(void)
{
	for(int i=1;i<=N;i++)
		if(LinkHead[i])
			DelLink(LinkHead[i]);
	return;
}

int main(void)
{
	int test;
	scanf("%d",&test);
	for(int t=1;t<=test;t++)
	{
		int n,m,l;
		scanf("%d %d %d",&n,&m,&l);
		solve poj3308(n,m,l);
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

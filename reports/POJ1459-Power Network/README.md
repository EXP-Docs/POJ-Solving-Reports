## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1459] [[Power Network](http://poj.org/problem?id=1459)]

> [Time: 1000MS] [Memory: 32768K] [难度: 初级] [分类: 最大流]

------

## 问题描述

无。


## 解题思路

多源多汇**最大流问题**。

> **提示：** BFS找增广链 + 压入重标法 

题目给出很多都是废话，特别是符号 `s(u)`， `d(u)`， `Con` 还有那条公式都别管，混淆视听。

**难点在于构图**：

- 电站p(u)均为源点
- 用户c(u)均为汇点
- 中转站当普通点处理

------

**第一个误区是例图**， 节点 和 边 都有 `x/y` （流量和容量），这个很容易使人产生矛盾（因为学习最大流问题是，只有 边 才有流量和容量）。

但是不难发现，题目所给的例图中有多个源点，多个汇点，多个普通点，只有源点和汇点才标有 `x/y`，普通点没有标 `x/y`，而且所给出的所有边都有 `x/y`。 

这无疑在促使我们对图做一个变形： 构造一个超级源s，一个超级汇t，使s指向所有源点，并把源点的 容量y 分别作为这些边的 容量，使所有汇点指向t，并把汇点的容量y分别作为这些边的 容量，然后本来是源点和汇点的点，全部变为普通点。

**这样就把“多源多汇最大流”变形为“单源单汇最大流”问题**。

------

**第二个误区就是流量值**。 学习最大流问题时，会发现边上的流量值是给定初始值的，但是这题的输入只有容量，没有流量，很多人马上感觉到无从入手。其实边上的流量初始值为多少都没有所谓，解最大流需要用到的只有容量。但是一般为了方便起见， 会把所有边的流量初始化为0。这样做有一个最大的好处，就是可以回避 反向弧 的存在，这个下面详细叙述。


------


本题中要**注意**的是：

- 如果输入中，某一点上有环，就无视掉。环是否存在不影响最终结果。
- 一般两点之间都是单边，一旦存在双边也没有问题，因为由定义知两个方向的容量一定相等（其实不相等也无妨，因为其中有一条为 反向弧，前面已经提到 反向弧 是可以直接回避、无视的，因此反向弧上的容量为多少就不重要了），而且在寻找增广路的标号过程中，搜索的是未标号的点，就是说 `(u,v)` 这条弧即使是双向的，但一旦从u到达v后，就不能回头了，因为两者都被标记了，即另外一条弧就不起任何作用了。


**下面详细说说为什么能够回避反向弧**。

首先需要明确，任意一个点j上记录的信息有：

- 寻找增广路时，除超级源s外，增广路上任一点j都有一个唯一的前驱i（i被记录在j）
- min{从i到j的容流差,l(vi)}
- 构图时，除超级汇t外，图上任一点j都会直接指向一些点(这些点作为后继点，同在记录在j)

从这个特点可以知道，从超级源开始寻找增广路时，万一遇到双向边，正向弧，反向弧自动被回避。万一遇到单向边，如果是非饱和正向弧，就会继续走下去；如果是反向弧，这条弧必然是 零弧（每条边初始化流量均为0），从定义知如果增广路有反向弧，它必须要是 非零弧，而且由于反向弧每次都不会经过，所以在改进增广路时反向弧上的流量也不会被改变，永远为0，也就与最终结果无关了。

最后当无法寻找增广路时，最大流就是与超级源s直接关联的边上的 流量之和。


## AC 源码


```c
/*BFS+压入重标法*/

//Memory  Time 
//384K    860MS  

#include<iostream>
using namespace std;

const int inf=10001;

int n;  //总节点数
int np; //电站数
int nc; //用户数
int line;  //线路数
int cap[102][102];  //弧(u,v)的容量
int flow[102][102];  //弧(u,v)的流量
bool vist[102];   //标记点v是否已标号
int s,t;  //超级源，超级汇

class info   //当前点v的标记信息
{
public:
	int pre;  //当前点v的前驱u
	int lv;  //l(v)
	int nei[101];  //当前节点直接指向的邻居节点
	int pn;  //邻居节点的指针
}node[102];

int min(int a,int b)
{
	return a<b?a:b;
}

void back(void)
{
	int x=t;
	while(x!=s)
	{
		flow[ node[x].pre ][x] += node[t].lv;  //改进增广路
		x=node[x].pre;

	}
	return;
}

bool bfs(void)
{
	memset(vist,false,sizeof(vist));
	node[s].pre=-1;
	node[s].lv=inf;
	vist[s]=true;

	int queue[102];
	int head=0;
	int tail=0;
	queue[tail++]=s;

	while(head<=tail-1)  //注意，这是再也找不到增广路的结束条件
	{
		int x=queue[head];
		int y;
		for(int i=0;i<node[x].pn;i++)
		{
			y=node[x].nei[i];
			if(!vist[y] && flow[x][y]<cap[x][y])   //搜索的目标要求是 未标记 & 非饱和弧
			{
				queue[tail++]=y;

				vist[y]=true;
				node[y].pre=x;
				node[y].lv=min( node[x].lv , cap[x][y]-flow[x][y] );
			}
			if(vist[t])  //当超级汇被标记
				break;
		}
		if(!vist[t])
			head++;
		else
			return true;  //搜索到一条增广路
	}
	return false;
}

int main(int i,int j,int u,int v,int z,char temp)
{
	while(cin>>n>>np>>nc>>line)
	{
		/*Initial*/

		s=n;
		t=n+1;
		for(i=0;i<n+1;i++)
			node[i].pn=0;

		/*Input & Structure Maps*/

		for(i=1;i<=line;i++)
		{
			cin>>temp>>u>>temp>>v>>temp>>z;
			if(u==v)
				continue;   //不需要环
			cap[u][v]=z;
			flow[u][v]=0;   //每条边的流量都初始化为0
			node[u].nei[ node[u].pn++ ]=v;
		}
		for(i=1;i<=np;i++)
		{
			cin>>temp>>v>>temp>>z;
			cap[s][v]=z;     //建立超级源，指向所有电站
			flow[s][v]=0;
			node[s].nei[ node[s].pn++ ]=v;
		}
		for(i=1;i<=nc;i++)
		{
			cin>>temp>>u>>temp>>z;
			cap[u][t]=z;     //建立超级汇，被所有用户指向
			flow[u][t]=0;
			node[u].nei[ node[u].pn++ ]=t;
		}

		/*标号法找增广轨*/

		while(true)
		{
			if(bfs())  //如果能搜到到增广路
				back();  //从超级汇开始回溯,改进增广路
			else
			{
				int max=0;        //输出最大流
				for(i=0;i<node[s].pn;i++)
					max+=flow[s][ node[s].nei[i] ];
				cout<<max<<endl;
				break;
			}
		}
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

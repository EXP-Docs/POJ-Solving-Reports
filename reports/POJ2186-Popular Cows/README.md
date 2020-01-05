## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2186] [[Popular Cows](http://poj.org/problem?id=2186)]

> [Time: 2000MS] [Memory: 65536K] [难度: 中级] [分类: 强连通分量/缩点]

------

## 问题描述

有N只奶牛，其中奶牛A认为奶牛B备受注目，而奶牛B也可能认为奶牛C备受注目。奶牛们的这种“认为”是单向可传递的，就是说若奶牛A认为奶牛B备受注目，但奶牛B不一定会认为奶牛A备受注目。而当A认为B备受注目，且B认为C备受注目时，A一定也认为C备受注目。

现在给出M对这样的“认为...备受注目”的关系对，问有多少只奶牛被除其本身以外的所有奶牛关注。


## 解题思路

**极大强连通分量**+**缩点**。


发现自从用**Tarjan算法**做了 [POJ2942](/reports/POJ2942-Knights%20of%20the%20Round%20Table) 之后，这些利用Tarjan算法的题目都是水题。


**构造模型**：

N个顶点的有向图G，有M条边。求一共有多少个点，满足这样的条件：所有其它的点都可以到达这个点。


首先，这个题的N和M都非常大，暴搜肯定TLE。

考虑一下，如果图G是一棵有向树，那么问题就变的很简单了，因为当且仅当这棵树只有一个叶子结点（出度为0的点）时，树上的其他所有结点都能到达这个点。而当有向树上有1个以上的叶子时，都是无解的。

由于树是无环的，下面称这样的一棵有向树为 **有向无环树DAG**


------


那么我们**能否把图转化为树去求解呢**？

首先可以想到的是，如果图G中包含有环，那么就可以把这个环缩成一个点，因为环中的任意两个点可以到达，环中所有的点具有相同的性质，即它们分别能到达的点集都是相同的，能够到达它们的点集也是相同的。

那么是否只有环中的点才具有相同的性质呢？进一步的考虑，图中的每一个极大强连通分量中的点都具有相同的性质。所以，如果把图中的所有极大强连通分量求出后，对每个极大强连通分量缩点，就可以把图收缩成一棵有向无环树DAG，那么只要判断出度为0的缩点是否只有1个，若DAG中有且仅有1个这样的缩点，则输出缩点（图G的极大强连通分量）内所包含的图G的结点个数，问题就解决。


------


预备知识：**Tarjan算法求有向图的极大强连通分量**。

补充一个小内容：

用Tarjan算法求极大强连通分量时，对于有向边 `s->t`

- 1、 若 `DFN[t]==0`，则 `s->t` 是一条树边，t尚未入栈；
- 2、 若 `DFN[t]<DFN[s]`，当t在栈中，`s->t` 为一条后向边；当t已经出栈，`s->t` 为一条横叉边。

注意只有有向图有横叉边，无向图不存在横叉边的概念。

对横叉边的处理：无视掉。


## 测试数据

- 来源（已失效）：[USACO 2003 Fall](http://www.4ucode.com/Study/Topic/1377469) 


## AC 源码


```c
//Memory Time 
//2116K  266MS 

#include<iostream>
#include<stack>
using namespace std;

/*图G的结点的存储结构*/
class Node
{
public:
	int id;
	class Node* next;
	Node():id(0),next(0){}
};

/*缩点(极大强连通分量)的存储结构*/
class Shrink_point
{
public:
	int in;		//缩点入度
	int out;	//缩点出度
	int num;	//缩点内含有图G的结点的个数
	Shrink_point():in(0),out(0),num(0){}
};

/*******************************************************/

class solve
{
public:
	solve(int n,int m):N(n),M(m)
	{
		Initial();
		Input_Creat();

		/*注意:有向图G不一定从任何位置开始搜索都能遍历所有点*/
		for(int i=1;i<=N;i++)
			if(DFN[i]==0)
			{
				stack_Node.push(i);		//搜索起点入栈
				Status[i]=1;
				Tarjan(i);
			}

		printf("%d\n",solution());

	}
	~solve()
	{
		delete[] DFN;
		delete[] Low;
		delete[] Status;
		delete[] SCC;
		delete[] sp;

		EmptyList();

		while(!stack_Node.empty())
			stack_Node.pop();
	}

	int min(int a,int b) const{return a<b?a:b;}

	void Initial(void);		//申请存储空间并初始化
	void Input_Creat(void);	//输入并构造有向图G
	void Tarjan(int s);		//寻找图G的所有极大强连通分量
	int solution(void);		//若缩点图只有1个出度为0的缩点，返回缩点内包含的结点数。否则无解,返回0

	void DelLink(Node* p);	//释放以p为表头的整条链
	void EmptyList(void);	//释放邻接链表

protected:
	int N;					//the number of cows
	int M;					//the number of popular pairs
	Node** LinkHead;		//邻接链表表头

	int TimeStamp;			//(外部)时间戳
	int* DFN;				//DFN[u]: 结点u的搜索次序(时间戳)
	int* Low;				//Low[u]: 结点u或u的子树能够追溯到的最早的栈中结点的次序号

	stack<int>stack_Node;	//辅助栈，用于寻找极大强连通分量
	int* Status;			//Status[i]-> 0:i未入栈  1:i在栈中  2:i已出栈
	int* SCC;				
	int SCC_id;				//SCC[i]=SCC_id  图G中结点i所属的极大强连通分量(缩点)的编号为SCC_id
	Shrink_point* sp;		//存储每个缩点(极大强连通分量)的信息
};

void solve::Initial(void)
{
	LinkHead=new Node*[N+1];
	for(int i=1;i<=N;i++)
		LinkHead[i]=0;

	TimeStamp=0;
	DFN=new int[N+1];
	Low=new int[N+1];
	memset(DFN,0,sizeof(int)*(N+1));
	memset(Low,0,sizeof(int)*(N+1));

	SCC_id=0;
	SCC=new int[N+1];
	Status=new int[N+1];
	memset(Status,0,sizeof(int)*(N+1));

	sp=new Shrink_point[N+1];

	return;
}

void solve::Input_Creat(void)
{
	int a,b;
	for(int j=1;j<=M;j++)
	{
		scanf("%d %d",&a,&b);

		if(!LinkHead[a])
			LinkHead[a]=new Node;

		Node* tmp=LinkHead[a]->next;
		LinkHead[a]->next=new Node;
		LinkHead[a]->next->id=b;
		LinkHead[a]->next->next=tmp;
	}
	return;
}

void solve::Tarjan(int s)
{
	DFN[s]=Low[s]=++TimeStamp;
	if(LinkHead[s])
	{
		for(Node* p=LinkHead[s]->next;p;p=p->next)
		{
			int t=p->id;
			if(DFN[t]<DFN[s])
			{
				if(DFN[t]==0)			//s->t为树枝边
				{
					stack_Node.push(t);
					Status[t]=1;

					Tarjan(t);
					Low[s]=min(Low[s],Low[t]);
				}
				else if(DFN[t]!=0 && Status[t]==1)	//s->t为后向边
				{
					Low[s]=min(Low[s],DFN[t]);
				}
			}
		}
	}
	if(DFN[s]==Low[s])	//找到极大强连通分量
	{
		SCC_id++;
		for(int node=stack_Node.top();;node=stack_Node.top())
		{
			stack_Node.pop();
			Status[node]=2;
			SCC[node]=SCC_id;
			sp[ SCC_id ].num++;

			if(node==s || stack_Node.empty())
				break;
		}
	}
	return;
}

int solve::solution(void)
{
	/*计算所有缩点的入度和出度*/

	for(int i=1;i<=N;i++)
		if(LinkHead[i])
		{
			for(Node* p=LinkHead[i]->next;p;p=p->next)
			{
				int j=p->id;
				if(SCC[i]!=SCC[j])
				{
					sp[ SCC[i] ].out++;
					sp[ SCC[j] ].in++;
				}
			}
		}

	/*寻找出度为0的缩点*/

	int cnt=0;		//记录出度为0的缩点个数
	int pk;			//记录出度为0的缩点编号

	for(int k=1;k<=SCC_id;k++)
		if(sp[k].out==0)
		{
			cnt++;
			pk=k;
		}
	if(cnt!=1)			//出度为0的缩点的个数不为1，本题无解
		return 0;
	
	return sp[pk].num;	//返回出度为0的缩点所包含图G中的结点个数
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
	int n,m;
	while(scanf("%d %d",&n,&m)!=EOF)
		solve poj2186(n,m);

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

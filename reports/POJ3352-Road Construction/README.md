## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3352] [[Road Construction](http://poj.org/problem?id=3352)]

> [Time: 2000MS] [Memory: 65536K] [难度: 中级] [分类: 连通分量/割边/割点]

------

## 问题描述

某个企业想把一个热带天堂岛变成旅游胜地，岛上有N个旅游景点，任意2个旅游景点之间有路径连通（注意不一定是直接连通）。而为了给游客提供更方便的服务，该企业要求道路部门在某些道路增加一些设施。

道路部门每次只会选择一条道路施工，在该条道路施工完毕前，其他道路依然可以通行。然而有道路部门正在施工的道路，在施工完毕前是禁止游客通行的。这就导致了在施工期间游客可能无法到达一些景点。

为了在施工期间所有旅游景点依然能够正常对游客开放，该企业决定搭建一些临时桥梁，使得不管道路部门选在哪条路进行施工，游客都能够到达所有旅游景点。给出当下允许通行的R条道路，问该企业至少再搭建几条临时桥梁，才能使得游客无视道路部门的存在到达所有旅游景点？


## 解题思路

做过 [POJ2942](/reports/POJ2942-Knights%20of%20the%20Round%20Table) 后，这题根本就是水题嘛。


首先**建立模型**：

给定一个连通的无向图G，至少要添加几条边，才能使其变为**双连通图**。

模型很简单，正在施工的道路我们可以认为那条边被删除了。那么一个图G能够在删除任意一条边后，仍然是连通的，当且仅当图G至少为双连通的。

> 不要问我为什么不是3-连通、4-连通...人家题目问“至少添加几条边”好不...

显然，当图G存在桥（割边）的时候，它必定不是双连通的。桥的两个端点必定分别属于图G的两个【边双连通分量】（注意不是点双连通分量），一旦删除了桥，这两个【边双连通分量】必定断开，图G就不连通了。但是如果在两个【边双连通分量】之间再添加一条边，桥就不再是桥了，这两个【边双连通分量】之间也就是双连通了。

那么如果图G有多个【边双连通分量】呢？至少应该添加多少条边，才能使得任意两个【边双连通分量】之间都是双连通（也就是图G是双连通的）？


------


 这个问题就是本题的问题。要解决这个问题：

**1、 首先要找出图G的所有【边双连通分量】**。

Tarjan算法用来寻找图G的所有【边双连通分量】是最简单有效的方法，因为Tarjan算法在DFS过程中会对图G所有的结点都生成一个Low值，而由于题目已表明任意两个结点之间不会出现重边，因此Low值相同的两个结点必定在同一个【边双连通分量】中！  （如果是有重边的话，那么不同的low值是可能是属于同一个边双连通分量的，这个时候就要通过其他方法去求解边双连通分量。不过这不是本题要讨论的）


**2、 把每一个【边双连通分量】都看做一个点（即【缩点】）**

也有人称【缩点】为【块】，都是一样的。其实缩点不是真的缩点，只要利用Low值对图G的点分类处理，就已经缩点了。

![](/img/01.png)

以样例1为例，样例1得到的图G为上左图，其中：

- `Low[4]=Low[9]=Low[10]`
- `Low[3]=Low[7]=Low[8]`
- `Low[2]=Low[5]=Low[6]`
- `Low[1]独自为政....`

把Low值相同的点划分为一类，每一类就是一个【边双连通分量】，也就是【缩点】了，不难发现，连接【缩点】之间的边，都是图G的桥，那么我们就得到了上右图以缩点为结点，已桥为树边所构造成的树。


**3、 问题再次被转化为“至少在缩点树上增加多少条树边，使得这棵树变为一个双连通图”**。

首先知道一条**等式**：

若要使得任意一棵树，在增加若干条边后，变成一个双连通图，那么

**至少增加的边数 =（ 这棵树总度数为1的结点数 + 1 ）/ 2**

（证明就不证明了，自己画几棵树比划一下就知道了）

那么我们只需求缩点树中总度数为1的结点数（即叶子数）有多少就可以了。换而言之，我们只需求出所有缩点的度数，然后判断度数为1的缩点有几个，问题就解决了。


**4、 求出所有缩点的度数的方法**

两两枚举图G的直接连通的点，只要这两个点不在同一个【缩点】中，那么它们各自所在的【缩点】的度数都+1。注意由于图G时无向图，这样做会使得所有【缩点】的度数都是真实度数的2倍，必须除2后再判断叶子。


## AC 源码


```c
//Memory Time 
//340K   32MS  

#include<iostream>
using namespace std;

class Node
{
public:
	int id;
	class Node* next;
	Node():id(0),next(0){}
};

class solve
{
public:
	solve(int n,int r):N(n),R(r)
	{
		Initial();			
		Input_Creat();
		Tarjan(1,-1);		//本题给定的图G为连通的，因此从任意节点开始搜索均可
		printf("%d\n",BCC_SP_D_E());
	}
	~solve()
	{
		delete[] DFN;
		delete[] Low;
		delete[] degree;

		EmptyList();
	}

	int min(int a,int b) const{return a<b?a:b;}

	void Initial(void);				//申请存储空间并初始化
	void Input_Creat(void);			//输入并创建图G

	void Tarjan(int s,int father);	//计算Low[]数组，用于寻找所有边双连通分量
	int BCC_SP_D_E(void);			//把每个边双连通分量(BCC)构造为缩点(SP)，并计算每个缩点的度数(D)
									//返回值为使得图G为双连通所需添加的最少的边(E)的数量

	void DelLink(Node* p);			//释放以p为表头的整条链
	void EmptyList(void);			//释放邻接链表

protected:

	int N;					//the number of islands
	int R;					//the number of roads
	Node** LinkHead;		//邻接链表表头

	int TimeStamp;			//(外部)时间戳
	int* DFN;				//DFN[u]: 结点u的搜索次序(时间戳)
	int* Low;				//Low[u]: 结点u或u的子树能够追溯到的最早的栈中结点的次序号

	int* degree;			//记录每个缩点的总度数
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

	degree=new int[N+1];
	memset(degree,0,sizeof(int)*(N+1));

	return;
}

void solve::Input_Creat(void)
{
	int a,b;
	Node* tmp;
	for(int j=1;j<=R;j++)
	{
		scanf("%d %d",&a,&b);

		if(!LinkHead[a])
			LinkHead[a]=new Node;
		if(!LinkHead[b])
			LinkHead[b]=new Node;

		tmp=LinkHead[a]->next;
		LinkHead[a]->next=new Node;
		LinkHead[a]->next->id=b;
		LinkHead[a]->next->next=tmp;

		tmp=LinkHead[b]->next;
		LinkHead[b]->next=new Node;
		LinkHead[b]->next->id=a;
		LinkHead[b]->next->next=tmp;
	}
	return;
}

void solve::Tarjan(int s,int father)
{
	DFN[s]=Low[s]=++TimeStamp;
	for(Node* p=LinkHead[s]->next;p;p=p->next)
	{
		int t=p->id;
		if(t!=father && DFN[t]<DFN[s])
		{
			if(DFN[t]==0)			//s->t为树枝边
			{
				Tarjan(t,s);
				Low[s]=min(Low[s],Low[t]);
			}
			else					//s->t为后向边
			{
				Low[s]=min(Low[s],DFN[t]);
			}
		}
	}
	return;
}

int solve::BCC_SP_D_E(void)
{
	for(int i=1;i<=N;i++)
		if(LinkHead[i])
		{
			for(Node* p=LinkHead[i]->next;p;p=p->next)	//枚举图G中每两个连通的点i<->j
			{											//由于图G为无向图，则连通是双向的
				int j=p->id;
				if(Low[i]!=Low[j])		//图G中Low值相同的两个点必定在同一个边双连通分量(即同一个缩点)中
				{						//检查i、j是否不在同一个缩点中

					degree[Low[i]]++;	//结点i所在的缩点的度+1
					degree[Low[j]]++;	//结点j所在的缩点的度+1
				}
			}
		}
	
	int leave=0;			//记录总度数=1（叶子）的缩点
	for(int k=1;k<=N;k++)	//枚举各个缩点的度数D
		if(degree[k]/2==1)	//由于是无向图，因此每个缩点的度都重复计算了2次，除2后才是真实的度数
			leave++;

	return (leave+1)/2;		//将一棵树连成一个边双连通分量至少需要添加的边数=(叶子节点数+1)/2
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
	int n,r;
	while(scanf("%d %d",&n,&r)!=EOF)
		solve poj3352(n,r);

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

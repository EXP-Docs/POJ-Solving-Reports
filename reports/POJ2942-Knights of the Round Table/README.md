## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2942] [[Knights of the Round Table](http://poj.org/problem?id=2942)]

> [Time: 7000MS] [Memory: 65536K] [难度: 中级] [分类: 双连通分量]

------

## 问题描述

亚瑟王要在圆桌上召开骑士会议，为了不引发骑士之间的冲突，并且能够让会议的议题有令人满意的结果，每次开会前都必须对出席会议的骑士有如下要求：

- 1、 相互憎恨的两个骑士不能坐在直接相邻的2个位置；
- 2、 出席会议的骑士数必须是奇数，这是为了让投票表决议题时都能有结果。

如果出现有某些骑士无法出席所有会议（例如这个骑士憎恨所有的其他骑士），则亚瑟王为了世界和平会强制把他剔除出骑士团。

现在给定准备去开会的骑士数n，再给出m对憎恨对（表示某2个骑士之间使互相憎恨的），问亚瑟王至少要剔除多少个骑士才能顺利召开会议？



**注意**：

- 1、所给出的憎恨关系一定是双向的，不存在单向憎恨关系。
- 2、由于是圆桌会议，则每个出席的骑士身边必定刚好有2个骑士。即每个骑士的座位两边都必定各有一个骑士。
- 3、一个骑士无法开会，就是说至少有3个骑士才可能开会。


## 解题思路

**综合性非常强的图论题**，在说解题报告之前，我建议大家先对以下内容有所认识，否则本题是很难做下去的：

- 1、**补图** 的定义
- 2、**双连通分量** 的定义
- 3、**二分图** 的定义
- 4、**奇圈** 的定义
- 5、判定一个图是否为二分图的方法：**交叉染色法**
- 6、**Tarjan算法**

上述知识点用于解决本题的重要性与其编号呈正相关。

给个有关图论的知识点的传送门：[http://www.byvoid.com/blog/biconnect/](http://www.byvoid.com/blog/biconnect/)

最后要说一下的是，或者大家在看我这篇解题报告之前，已经看过其他解题报告，都不谋而合地给出了求割点的方法。

这里我声明一下：**本题不需要求割点**，我们**仅仅是利用了Tarjan算法判定出现割点的过程以及条件**而已，但我不建议用Tarjan算法去求无向图的割点，Tarjan算法只适用于求有向图的割点，直接套Tarjan模板用来求无向图割点会出错的。要求无向图的割点建议去看看刘汝佳的《算法艺术与信息学竞赛》，那里有详细方法。这些话与本题无关，我就不多说了。


------


为了方便大家做题，我这里**大概说一下上述的6个知识点**，注意下述是我通俗的理解，不是标准定义：

**1、 补图**

图G的补图`~G`就是把图G原有的边全部删去，原本不存在的边全部连上。


**2、双连通分量**

简单来说，无向图G如果是双连通的，那么至少要删除图G的2个结点才能使得图G不连通。换而言之，就是图G任意2个结点之间都存在两条以上的路径连接（注意：路径不是指直接相连的边），那么双连通分量就是指无向图G的子图`G'`是双连通了。


**3、二分图**

二分图又叫二部图，这个百度百科有定义，了解一下二分图是什么样子的可以了，无需深入去了解。不懂得同学等到做二分图的题目时再认真学吧。


**4、 奇圈**

用一条线把奇数个点串连起来，所得到的闭合的圈就是奇圈了。其实奇圈就是有奇数个顶点的环。


**5、交叉染色法判定二分图**

初始化所有结点为无色（颜色0）状态，用DFS遍历一个图G的同时，顺便对结点染色（只染1、2色），注意遍历过的结点还可以再遍历重新上色。让遍历到某个时候在对结点t染色时，发现边 `s->t` 的另一个结点s已染色，且s的颜色与当前正在对t染的颜色相同，那么图G必定不是二分图。

这是因为想象一下二分图就像是河的两岸有两排结点，每染色一次则过河一次，那么相同颜色的结点必定在同一侧。一旦出现异侧有相同颜色的结点，就可以说明图G不是二分图了。


**6、Tarjan算法**

我希望大家主要去学习一下这个算法的基本原理，尤其是DFN数组和Low数组，还有什么是深搜树，什么是树枝边，什么是后向边。

学习一下Tarjan算法求割点的过程（注意我上文是建议大家不要用Tarjan算法去求解割点的题，但不是让大家不要看它求割点的过程），因为这个过程是求双连通分量的关键。

 而如果想很好地了解Tarjan算法求割点的过程，还是建议先去看刘汝佳的《算法艺术与信息学竞赛》 P285 页，然后去做一下 [POJ1523](/reports/POJ1523-SPF) （纯粹求割点的题）找点感觉。

只要弄懂了刘汝佳的方法，再看Tarjan算法就非常容易理解了。

------


有了上述知识支撑，可以开始解题了：

1、 利用m对憎恨对构造图G，则图G中有边相连的两个点表示这2个骑士互相憎恨。

2、 构造图G的补图`~G`，则图`~G`中有边相连的两个点表示这2个骑士可以坐在相邻位置。

3、 在图`~G`中，可能存在某些点的度数 `<=1`，就是说这些骑士旁边最多只能坐另一个骑士，根据圆桌的座位要求每个骑士k的座位两边都必定各有一个骑士（k度数==2），那么我们认为这些度数 `<=1` 的点是孤立的或者是单连通的，也就是说他们不在圆桌的“环”内。

![](/img/01.png)

例如上图，我们利用图G构造补图`~G`后，显然骑士1的度=0，他是孤立的、不连通的；骑士5的度=1，他是单连通的；骑士 `{2,3,4}` 则构成一个双连通分量，他们正在圆桌“环”内开会。显然度数 `<=1` 的骑士1和骑士5都在环外，不满足出席会议的条件，亚瑟王为了维护世界和平自然会把这2人驱逐出骑士团。


4、 现在问题是，我们怎么才能知道哪些骑士在环外？

我们可以把问题转化为，我们怎么才能知道哪些骑士在环内？显然在环内的所有结点都是双连通的，我们可以通过Tarjan算法求双连通分量。注意，补图`~G`可能有几个双连通子图，即它可能有不止一组双连通分量，而Tarjan算法是一组一组双连通分量求出来的，因此每求出一组双连通分量我们就要马上处理一组。

**下面都是针对某一组双连通分量的处理**。


5、 骑士在双连通分量内（在环内），并不能就此就说明它可以出席会议了，因为假如这个骑士所在的双连通分量，不是一个奇数顶点的环（奇圈），而是一个偶数顶点的环，那么这个双连通分量内的全部骑士都要被亚瑟王开除。


6、 那么怎样判断一个双连通分量是奇圈呢？

首先我们要接受两条定理，想知道证明过程的可以上网找，这里不证明：

- （1）如果一个双连通分量内的某些顶点在一个奇圈中（即双连通分量含有奇圈），那么这个双连通分量的其他顶点也在某个奇圈中；
- （2）如果一个双连通分量含有奇圈，则他必定不是一个二分图。反过来也成立，这是一个充要条件。

由于双连通分量也是一个图，那么要判断双连通分量是否为奇圈，只需判断这个双连通分量是否为一个二分图，而要判断一个图是否为二分图，就用交叉染色法！


7、 显然所有在奇圈中的骑士，都是允许出席会议的，而由于可能有部分骑士允许出席一个以上的会议（即他们是2个以上的奇圈的公共点），那么为了避免重复统计人数，当我们判断出哪些骑士允许出席会议时，就把他们做一个标记（相同的骑士只做一个标记）。最后当Tarjan算法结束后，我们统计一下被标记的人数有多少，再用总人数减去这部分人，剩下的就是被亚瑟王剔除的人数了。


------


说到这里，本题就已经解出来了，所有知识点都被联系起来了。老实说做完这题还很有成就感的哈！

**几点小建议**：

- 1、 为方便输入，图G用邻接矩阵存储，但为了后期处理数据方便，补图`~G`则最好改用邻接链表，图G唯一的作用就只有生成补图`~G`而已。
- 2、 给结点和边都独立开辟一个存储结构。结点是为了链表处理，边是为了Tarjan求双连通分量时的压栈。
- 3、 在弄清楚知识点之前不要盲目做这题，最好先找相关知识点的简单一点的题目做一下练笔。我在Disscuss上发现有同学做这题用了4个月，而我算上做练笔题的时间，前后只用了2天。


## AC 源码


```c
//Memory  Time
//632K	 2469MS  

#include<iostream>
#include<stack>
using namespace std;

/*结点存储结构*/
class Node
{
public:
	int id;
	class Node* next;
	Node():id(0),next(0){}
};

/*边存储结构*/
class Edge
{
public:
	Edge(int x=0,int y=0):s(x),t(y){}	//初始化
	Edge(const Edge& c):s(c.s),t(c.t){}	//复制
	
	int u(void) const{return s;}
	int v(void) const{return t;}

protected:
	int s,t;	//边s->t
};

bool operator==(Edge a,Edge b)	//协助函数:==运算符重载
{
	return a.u()==b.u() && a.v()==b.v();
}

/*********************************************************/
class solve
{
public:
	solve(int n=0,int m=0):N(n),M(m)
	{
		Initial();
		Input();
		Struct_G();

		for(int i=1;i<=N;i++)	//图G的补图可能不连通
			if(!DFN[i])
				Tarjan(i,-1);

		/*统计留席的骑士数*/
		int NotFireNum=0;
		for(int j=1;j<=N;j++)
			if(NotFire[j])
				NotFireNum++;
		printf("%d\n",N-NotFireNum); //总数减去留席骑士数，就是被剔除的骑士数
	}
	~solve()
	{
		for(int i=1;i<=N;i++)
			delete[] G[i];

		delete[] Dcc;
		delete[] DFN;
		delete[] Low;
		delete[] NotFire;
		delete[] flag;
		delete[] color;

		EmptyList();

		while(!stack_Edge.empty())
			stack_Edge.pop();
	}

	int min(int a,int b) const{return a<b?a:b;}

	void Initial(void);				//申请存储空间并初始化
	void Input(void);				//输入图G
	void Struct_G(void);			//构造图G的补图
	void Tarjan(int s,int father);	//Tarjan算法。s:当前搜索位置, father:s的父亲结点
	bool IsBinary(int s,int col);	//交叉染色判断s所在的双连通分量是否为二分图(s为搜索起点)

	void DelLink(Node* p);			//删除以结点p为表头的整条链
	void EmptyList(void);			//清空邻接链表

protected:

	int N;					//the number of Kinghts
	int M;					//the pairs of hate
	bool** G;				//邻接矩阵 记录图G
	Node** LinkHead;		//图G的补图的邻接链表表头

	int TimeStamp;			//（外部）时间戳
	int* DFN;				//DFN[u]: 结点u的搜索次序（时间戳）
	int* Low;				//Low[u]: 结点u或u的子树能够追溯到的最早的栈中结点的次序号

	stack<Edge>stack_Edge;	//边栈
	int* Dcc;				//存储点的双连通分量
	bool* flag;				//标记处于同一个双联通分量的所有顶点
	int dNum;				//双连通分量的顶点个数
	int* color;				//记录结点所染的颜色
	bool* NotFire;			//标记留席的骑士（即没有被剔除的骑士）
};

void solve::Initial(void)
{
	/*申请图G的存储空间并初始化*/

	G=new bool*[N+1];
	for(int i=1;i<=N;i++)
	{
		G[i]=new bool[N+1];
		memset(G[i],false,sizeof(bool)*(N+1));
		G[i][i]=true;
	}

	/*申请图G的补图~G的存储空间并初始化*/

	LinkHead=new Node*[N+1];
	for(int j=0;j<=N;j++)
		LinkHead[j]=0;

	/*申请执行Tarjan算法所需的存储空间并初始化*/

	TimeStamp=0;
	DFN=new int[N+1];
	Low=new int[N+1];
	memset(DFN,0,sizeof(int)*(N+1));
	memset(Low,0,sizeof(int)*(N+1));

	/*申请用于判定二分图所需的存储空间并初始化*/

	Dcc=new int[2*N+1];		//由于是按边压栈，则同一个点可能最多2次入栈
	flag=new bool[N+1];
	color=new int[N+1];
	NotFire=new bool[N+1];
	memset(NotFire,false,sizeof(bool)*(N+1));

	return;
}

void solve::Input(void)
{
	int x,y;		//temporary
	for(int j=1;j<=M;j++)
	{
		scanf("%d %d",&x,&y);
		G[x][y]=G[y][x]=true;
	}
	return;
}

void solve::Struct_G(void)
{
	for(int i=1;i<=N;i++)
	{
		LinkHead[i]=new Node;
		for(int j=1;j<=N;j++)
		{
			if(!G[i][j])
			{
				Node* tmp=LinkHead[i]->next;
				LinkHead[i]->next=new Node;
				LinkHead[i]->next->id=j;
				LinkHead[i]->next->next=tmp;
			}
		}
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
			if(!DFN[t])	//s->t为树枝边
			{
				Edge tagE(s,t);
				stack_Edge.push(tagE);	//树枝边压栈

				Tarjan(t,s);
				Low[s]=min(Low[s],Low[t]);

				if(DFN[s]<=Low[t])		//此时s为割点
				{
					/*寻找双连通分量，找到一组则马上处理一组*/
					dNum=0;
					memset(flag,false,sizeof(bool)*(N+1));
					memset(color,0,sizeof(int)*(N+1));
					for(Edge e=stack_Edge.top();;e=stack_Edge.top())
					{
						stack_Edge.pop();
						Dcc[dNum++]=e.u();
						Dcc[dNum++]=e.v();
						flag[e.u()]=true;		//标记处于同一个双连通分量的所有点
						flag[e.v()]=true;
						
						if(e==tagE || stack_Edge.empty())
							break;
					}
					if(!IsBinary(Dcc[0],1))		//当前的双连通分量不是二分图，则说明双连通分量内有奇圈
					{
						for(int i=0;i<dNum;i++)	//奇圈内的所有骑士均留席
							NotFire[Dcc[i]]=true;
					}
				}
				
			}
			else		//s->t为后向边
			{
				Low[s]=min(Low[s],DFN[t]);
			}
		}
	}
	return;
}

bool solve::IsBinary(int s,int col)
{
	color[s]=col;	//对s染色
	for(Node* p=LinkHead[s]->next;p;p=p->next)
	{
		int t=p->id;
		if(flag[t])			//检查t是否与s在同一个双连通分量
		{
			if(color[t]==0)	//t未染色
			{
				return IsBinary(t,3-col);	//3-col,目的是轮番用“1、2”交替染色
			}
			else			//t已染色
			{
				if(color[s]==color[t])		//若同一条边的两个端点同色
					return false;			//说明双连通分量不是二分图
			}								//即双连通分量内有奇圈
		}
	}
	return true;
}

void solve::DelLink(Node* p)
{
	if(p->next)
		DelLink(p->next);
	delete p;
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
	while(scanf("%d %d",&n,&m) && (n+m))
		solve poj2942(n,m);

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

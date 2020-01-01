## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3436] [[ACM Computer Factory](http://poj.org/problem?id=3436)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 最大流]

------

## 问题描述

老实说，我完全看不懂题目在说什么。。。

不过还是简单概括下：

有N台机器，每台机器有P部分，每部分都有各自的输入、输出规格，因此一台机器有P个输入规格，P个输出规格。每台机器有 `2\*P+1` 种参数去描述：

- 第一个参数Q： 该机器的容量
- 接下来P个参数S： 该机器各部分的输入规格
- 接下来P个参数D： 该机器各部分的输出规格

其中输入规格有三种情况：0, 1, 2

- 0：该部分不能存在
- 1：该部分必须保留
- 2：该部分可有可无

输出规格有2种情况：0, 1

- 0：该部分不存在
- 1：该部分存在


至于这条题要我做什么，我完全不理解。。。不过通过对样例的输入输出的剖析，再加之前人总结出来的一些不清不楚的见解，我还是勉强能够详尽地分析这题的模型。

------

> **注意**：本题只可以有一次输入，一次输出，还有 Sample I/O 这段英文不用输入输出

**Sample input:**

P  N （N台机器，每台机器有P部分）

接着输入N行，其实每行都是一个节点的信息

每一行的格式为 一个Q  P个S  P个D

其中Q为当前节点的容量，S都是当前节点的输入规格，D都是输出规格

**Sample output:**

第一行的两个数字分别表示：最大流的值，流量发生变化的边数M（和s还有t关联的边不在其内，那些不属于原有的边，是附加边）

接下来有M行，每一行都有三个数字，A B W

A B为流量发生变化的边的端点，W为流量的变化值（每条边初始流量为0，最终流量就是找到最大流时的流量）

若图不连通，则输出0 0


## 解题思路

**最大流问题**。

首先**构造图**：

添加两个超级源s, 超级汇t

- ① 如果某个节点(i)的输入部分不含1，则添加一条s->i路径，容量为Qi;
- ② 如果某个节点(j)输出全为1，则添加一条j->t路径，容量为Qj;
- ③ 如果节点i的输出与j的输入不存在冲突(输出与输入对应位置的和不能为1)，则添加一条i->j的路径，容量为min(Qi, Qj).

> 输出与输入对应位置的和不能为1，就是说组合为可以为00，11， 21或20，但不能是01


------

这题折磨了我3天，网上的前辈都推荐拆点做，但是我没有用拆点（感觉拆点很麻烦）。

这道题我用了三种方法去做，但是结果却差强人意：

- **① 【BFS+标号法+不拆点】 成功AC**
- ② 【BFS+压入重标法+不拆点】(WA，不知道错哪里了，找不到反例) 
- ③ 【BFS+压入重标法+模拟拆点】(WA，不知道错哪里了，找不到反例)     

AC的程序我贴下面，后两个WA的代码也贴在AC代码下面，希望有人帮我查出哪里出错了。。。


## AC 源码

```c
/* 【BFS+标号法+不拆点】 -> 成功AC*/

//Memory Time 
//292K   0MS 

#include<iostream>
using namespace std;

const int inf=10001;
int s; //超级源
int t;   //超级汇

int n;  //总节点数（包括超级源、超级汇）
int p;  //每台机器的部分数
int cap[52][52];// 边容量


int min(int a,int b)
{
	return a<b?a:b;
}

/*利用BFS找增广链求网络最大流*/

int maxflow(void)  
{
	int queue[52];
	int head,tail;
	int pre[52]; //节点i的前驱
    
	int minflow;
	int flow = 0;
    int x,y;

    while(true)
    {
        memset(pre, -1, sizeof(pre));

        for(queue[head=tail=0]=s;head<=tail;head++)
        {
            x=queue[head];
            for(int i=0;(i<n) && (pre[t]==-1);i++)//当汇点还没有被标记时
               if (cap[x][i]>0 && pre[i]==-1)  //当节点u指向i的边存在，且i还没有标记前驱时
               {
                    pre[i]=x;//记录节点i的前驱为u
                    queue[++tail]=i;
               }
        }

        if(pre[t]==-1)
			break;//BFS后汇点没有被标记，则跳出while，已经不存在增广链

        minflow=inf;//初始化
        for(x=pre[y=t];y!=s;)//回溯
		{
			if(cap[x][y] < minflow)
				minflow=cap[x][y];//寻找当前增广链中最小容量的边，记录其边权（容量）
			y=x;
			x=pre[y];
		}

        for(x=pre[y=t];y!=s;) //当前增广链 流量调整
		{
			cap[x][y] -= minflow;  //正向弧容量减少
			cap[y][x] += minflow;  //反向弧容量增加
			y=x;
			x=pre[y];
		}

        flow += minflow;  //最大流=每次寻得的增广链的调整量之和
    }
    return flow;//返回最大流
}

int main(int i,int j,int k)
{
	int in[52][21];
	int out[52][3];
	int backup[52][52];//备份图
    int N;  //除超级源、超级汇以外的总节点数
	int line;  //生产线数（容量发生变化的边数）
	int flow;  //最大流

    while (cin>>p>>N)
    {
		/*Initial*/

        memset(cap,0,sizeof(cap)); //所有正向弧和反向弧的容量都初始化为0

        s=0;//超级源
		t=N+1; //超级汇
        n=N+2; //总节点数+2
		line=0;  //记录变化的边的数量(生产线数量)

		/*Input*/

        for(i=1;i<=N;i++)
            for(j=0;j<2*p+1;j++)
                cin>>in[i][j];    //用一个数列存储第i个节点的信息 in[i][0] 为节点i的容量
        
		bool flag_s, flag_t;
        for(i=1;i<=N;i++)
        {
            flag_s=flag_t=true;
            for(k=0;k<p;k++)
            {
                if(in[i][1+k]==1)
					flag_s=false;  //检查第i个节点的输入序列信息，当输入列不含1时
                if(in[i][p+1+k]==0)
					flag_t=false;//检查第i个节点的输出序列信息，当输出列全为1时
            }
            if(flag_s)
				cap[s][i]=in[i][0];  //当输入列不含1时,S->i，边容量为i的容量
            if(flag_t)
				cap[i][t]=in[i][0]; //当输出列全为1时,i->t，边容量为i的容量

            bool flag=true;
            for(j=1;j<=N;j++)
				if(i!=j)
                {
                    flag=true;
                    for(k=0;(k<p) && flag;k++)
						if(in[i][p+1+k]+in[j][1+k]==1)  //当第i个节点的第k个输出位，对应第j个节点的第k个输入位之和全不为0时
                            flag=false;

                    if(flag)
						cap[i][j] = min(in[i][0], in[j][0]);  //i->j,边容量为i的容量和j的容量的最小值
                }
        }

		/*利用BFS找增广链求网络最大流*/

        memcpy(backup, cap, sizeof(cap));  //把寻找增广链前的图的容量信息复制
        flow=maxflow();  //返回最大流
        
		/*Output*/

        for(i=1;i<=N;i++)   //注意范围，排除了含超级源和超级汇的边
			for(j=1;j<=N;j++)
                if (cap[i][j] < backup[i][j])//比较调整前后的边权，若容量减少了，则输出这条边的信息
                {
                    out[line][0]=i;     //i,j为生产线的两端点
                    out[line][1]=j;
                    out[line][2]=backup[i][j] - cap[i][j];//变化的流量值（该生产线的最大生产量）
                    line++;
                }

        cout<<flow<<' '<<line<<endl;
        for(i=0;i<line;i++)
            cout<<out[i][0]<<' '<<out[i][1]<<' '<<out[i][2]<<endl;
    }
    return 0;
}
```

## WA 源码

```c
/*【BFS+压入重标法+不拆点】-> WA */

#include<iostream>
using namespace std;

const int inf=10001;
int s=0; //超级源
int t;   //超级汇

int n;  //机器数
int p;  //每台机器的部分数
int cap[52][52];  //弧(i,j)的容量
int flow[52][52];  //弧(i,j)的流量
bool mark[52][52]={false};  
int sum=0;
bool vist[52];   //标记点i是否已标号

class info   //当前点j的标记信息
{
public:
	int pre;  //当前点j的前驱i
	int lv;  //l(v)
	int q;  //机器（节点i）的生产量（容量）
	int in[10];  //输入规格
	int out[10]; //输出规格
	int nei[51];  //当前节点直接指向的邻居节点
	int pn;  //邻居节点的指针
}node[52];

int min(int a,int b)
{
	return a<b?a:b;
}

void back(void)
{
	int x=t;
	while(x!=s)
	{
		if(x!=t && node[x].pre!=s)
		{
			if(!mark[ node[x].pre ][x])
				sum++;           //记录流量发生变化的弧数（含s、t的弧除外）
			mark[ node[x].pre ][x]=true;  //标记弧(i,j)的流量是否发生了变化（含s、t的弧除外）
		}
		flow[ node[x].pre ][x] += node[t].lv;  //改进增广路
		x=node[x].pre;

	}
	return;
}

bool bfs(void)
{
	memset(vist,false,sizeof(vist));
	vist[s]=true;

	int queue[52];
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

int main(int i,int j,int k)
{
	/*Input*/

	cin>>p>>n;

	/*Initial*/

	node[s].pre=-1;
	node[s].lv=inf;
	t=n+1;
	for(i=0;i<t;i++)
		node[i].pn=0;

	/*Input & Structure Graphs*/

	bool sign;
	for(i=1;i<=n;i++)
	{
		sign=false;
		cin>>node[i].q;

		for(j=0;j<p;j++)
		{
			cin>>node[i].in[j];
			if(node[i].in[j]==1)  //如果某个节点(i)的输入部分不含1
				sign=true;
		}
		if(!sign)   //则添加一条s->i路径，容量为Qi
		{
			node[s].nei[ node[s].pn++ ]=i;
			cap[s][i]=node[i].q;
			flow[s][i]=0;
		}

		sign=false;
		for(j=0;j<p;j++)
		{
			cin>>node[i].out[j];
			if(node[i].out[j]==0)  //如果某个节点(j)输出全为1
				sign=true;
		}
		if(!sign)  //则添加一条j->t路径，容量为Qj
		{
			node[i].nei[ node[i].pn++ ]=t;
			cap[i][t]=node[i].q;
			flow[i][t]=0;
		}
	}

	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			sign=false;
			if(i!=j)
			{
				for(k=0;k<p;k++)
					if((node[i].out[k] + node[j].in[k])==1)  //如果节点i的输出与j的输入不存在冲突
					{                                      //即输出与输入对应位置的和不为1
						sign=true;
						break;
					}

				if(!sign)        //则添加一条i->j的路径，容量为min(Qi, Qj).
				{
					node[i].nei[ node[i].pn++ ]=j;
					cap[i][j]=min(node[i].q,node[j].q);
					flow[i][j]=0;
				}
			}
		}

	/*压入重标法找增广轨*/

	while(true)
	{
		if(bfs())  //如果能搜到到增广路
			back();  //从超级汇开始回溯,改进增广路
		else
		{
			int max=0;
			for(i=0;i<node[s].pn;i++)
				max+=flow[s][ node[s].nei[i] ];
			cout<<max<<' '<<sum<<endl;
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					if(i!=j && mark[i][j])
						cout<<i<<' '<<j<<' '<<flow[i][j]<<endl;
			break;
		}
	}
	return 0;
}
```

```c
/*【BFS+压入重标法+模拟拆点】-> WA */


#include<iostream>
using namespace std;

const int inf=10001;
int s=0; //超级源
int t;   //超级汇

int n;  //机器数
int p;  //每台机器的部分数
int cap[52][52];  //弧(i,j)的容量
int flow[52][52];  //弧(i,j)的流量
bool mark[52][52]={false};  
int sum=0;
bool vist[52];   //标记点i是否已标号

class info   //当前点j的标记信息
{
public:
	int pre;  //当前点j的前驱i
	int lv;  //l(v)
	int q;  //机器（节点j）的总生产量（容量）
	int f;  //机器（节点j）的当前生产量（流量）
	int in[10];  //输入规格
	int out[10]; //输出规格
	int nei[51];  //当前节点直接指向的邻居节点
	int pn;  //邻居节点的指针
}node[52];

int min(int a,int b)
{
	return a<b?a:b;
}

void back(void)
{
	int x=t;
	while(x!=s)
	{
		if(x!=t && node[x].pre!=s)
		{
			if(!mark[ node[x].pre ][x])
				sum++;           //记录流量发生变化的弧数（含s、t的弧除外）
			mark[ node[x].pre ][x]=true;  //标记弧(i,j)的流量是否发生了变化（含s、t的弧除外）
		}
		flow[ node[x].pre ][x] += node[t].lv;  //改进增广路
		node[x].f += node[t].lv;        //改进增广路上的顶点
		x=node[x].pre;

	}
	return;
}

bool bfs(void)
{
	memset(vist,false,sizeof(vist));
	vist[s]=true;

	int queue[52];
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
			if(!vist[y] && flow[x][y]<cap[x][y] && node[y].f<node[y].q)   //搜索的目标要求是 未标记 & 非饱和弧 & 非饱和点（模拟拆点）
			{                                                             //当某一顶点满流后，该顶点不能再生产更多的机器
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

int main(int i,int j,int k)
{
	freopen("in.txt","r",stdin);

	/*Input*/

	cin>>p>>n;

	/*Initial*/
 
	t=n+1;
	node[s].pre=-1;
	node[s].lv=inf;
	node[t].q=inf;
	for(i=0;i<=t;i++)
	{
		node[i].pn=0;
		node[i].f=0;
	}

	/*Input & Structure Graphs*/

	bool sign;
	for(i=1;i<=n;i++)
	{
		sign=false;
		cin>>node[i].q;

		for(j=0;j<p;j++)
		{
			cin>>node[i].in[j];
			if(node[i].in[j]==1)  //如果某个节点(i)的输入部分不含1
				sign=true;
		}
		if(!sign)   //则添加一条s->i路径，容量为Qi
		{
			node[s].nei[ node[s].pn++ ]=i;
			cap[s][i]=node[i].q;
			flow[s][i]=0;
		}

		sign=false;
		for(j=0;j<p;j++)
		{
			cin>>node[i].out[j];
			if(node[i].out[j]==0)  //如果某个节点(j)输出全为1
				sign=true;
		}
		if(!sign)  //则添加一条j->t路径，容量为Qj
		{
			node[i].nei[ node[i].pn++ ]=t;
			cap[i][t]=node[i].q;
			flow[i][t]=0;
		}
	}

	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			sign=false;
			if(i!=j)
			{
				for(k=0;k<p;k++)
					if((node[i].out[k] + node[j].in[k])==1)  //如果节点i的输出与j的输入不存在冲突
					{                                      //即输出与输入对应位置的和不为1
						sign=true;
						break;
					}

				if(!sign)        //则添加一条i->j的路径，容量为min(Qi, Qj).
				{
					node[i].nei[ node[i].pn++ ]=j;
					cap[i][j]=min(node[i].q,node[j].q);
					flow[i][j]=0;
				}
			}
		}

	/*压入重标法找增广轨*/

	while(true)
	{
		if(bfs())  //如果能搜到到增广路
			back();  //从超级汇开始回溯,改进增广路
		else
		{
			int max=0;
			for(i=0;i<node[s].pn;i++)
				max+=flow[s][ node[s].nei[i] ];
			cout<<max<<' '<<sum<<endl;
			for(i=1;i<=n;i++)
				for(j=1;j<=n;j++)
					if(i!=j && mark[i][j])
						cout<<i<<' '<<j<<' '<<flow[i][j]<<endl;
			break;
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

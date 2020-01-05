## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1724] [[ROADS](http://poj.org/problem?id=1724)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 搜索]

------

## 问题描述

给定一个图，图中每条路都有 路长Length 和 过路费Toll 两个参数，一条路连接两个城市，任意两个城市之间有且仅有一条路。

现在只有 K 块钱，要求从起点City1出发，到达终点CityN的最短路，也就是说在 K 花费内的最短路。


## 解题思路

这个题其实有很多种解法的，只不过是题目描述用的模型是最短路的模型，其实方法多种多样，Discuss里有同学用**dijkstra+`A*`算法**，也有人用**BFS+优先队列**，也有人用直接用**STL的priotrity_queue+剪枝**.....


我用了**DFS+剪枝**去做：

每个城市只能到达1次，每次找满足 Toll<RestMoney 的城市；当NowLen>MinLen就回溯，无需往下搜索了；递归出口是遍历所有允许的情况。

其实这题难度不大，关键是建立 **邻接链表** 去存储相同Source的路径去提高搜索效率。

因为Bob每进入一个Cityk，他就只能选择以k为源点的路径走向下一个城市，此时应该直接枚举所有以k为源点的路径。若使用了其他存储方式，则必然每次都要在所有路径中重新寻找以k为源点的路径，再枚举，这相当浪费时间。

## 测试数据

- 来源：[CEOI 1998](http://www.hsin.hr/ceoi98/)
- 下载：[download](/testdata.zip)
- 输入1：[input](/testdata/input-1.dat)
- 输出1：[output](/testdata/output-1.dat)
- 输入2：[input](/testdata/input-2.dat)
- 输出2：[output](/testdata/output-2.dat)
- 输入3：[input](/testdata/input-3.dat)
- 输出3：[output](/testdata/output-3.dat)



## AC 源码

### 解题风格一： C++

```c
//Memory Time 
//440K   250MS 

/*--- C++ Class ---*/

#include<iostream>
using namespace std;

class Road
{
	public:
		int S,D,L,T;  //Source,Destination,Length,Toll
		int next;     //指向相同Source的下一条边
};

class info
{
	public:
		info(int N,int R)
		{
			road=new Road[R+1];
			vist=new bool[N+1];
			ListTable_Head=new int[N+1];

			memset(vist,false,sizeof(bool)*(N+1));
			memset(ListTable_Head,-1,sizeof(int)*(N+1));
			MinLen=1e7;
			pr=0;
		}
		~info()
		{
			delete[] road;
			delete[] vist;
			delete[] ListTable_Head;
		}

		void input(int R);
		void output(void);
		void DFS(int NowCity,int NowLen,int RestMoney,int N);

	protected:
		Road* road;
		bool* vist;
		int* ListTable_Head;  //邻接链表头指针数组
		int MinLen;
		int pr;   //road[]指针
};

void info::input(int R)
{
	for(int i=1;i<=R;i++)
	{
		int s,d,l,t;
		cin>>s>>d>>l>>t;

		road[pr].S=s;
		road[pr].D=d;
		road[pr].L=l;
		road[pr].T=t;
		road[pr].next=ListTable_Head[s];
		ListTable_Head[s]=pr++;
	}
	return;
}

void info::output()
{
	cout<<(MinLen<1e7?MinLen:-1)<<endl;
	return;
}

void info::DFS(int NowCity,int NowLen,int RestMoney,int N)
{
	if(NowLen>MinLen)
		return;

	if(NowCity==N && RestMoney>=0 && NowLen<MinLen)
	{
		MinLen=NowLen;
		return;
	}

	for(int i=ListTable_Head[NowCity];i!=-1;i=road[i].next)
	{
		int tD=road[i].D;
		int tL=road[i].L;
		int tT=road[i].T;

		if(!vist[tD] && RestMoney>=tT)
		{
			vist[tD]=true;
			DFS(tD,NowLen+tL,RestMoney-tT,N);
			vist[tD]=false;
		}
	}
	return;
}

int main(void)
{
	int K,N,R;  //Money,CityNum,RoadNum
	while(cin>>K>>N>>R)
	{
		info poj1724(N,R);
		poj1724.input(R);
		poj1724.DFS(1,0,K,N);
		poj1724.output();
	}
	return 0;
}
```

### 解题风格二： C

```c
//Memory Time 
//444K   235MS 

/*--- C Style ---*/

#include<iostream>
using namespace std;

const int inf=1e7;
const int CitySize=101;
const int RoadSize=10001;

struct
{
	int S,D,L,T;  //Source,Destination,Length,Toll
	int next;     //指向相同Source的下一条边
}road[RoadSize];

int pr;   //road[]指针
int K,N,R;  //Money,CityNum,RoadNum
int MinLen;
bool vist[CitySize];
int ListTable_Head[CitySize];  //邻接链表头指针数组

void DFS(int NowCity,int NowLen,int RestMoney)
{
	if(NowLen>MinLen)
		return;

	if(NowCity==N && RestMoney>=0 && NowLen<MinLen)
	{
		MinLen=NowLen;
		return;
	}

	for(int i=ListTable_Head[NowCity];i!=-1;i=road[i].next)
	{
		int tD=road[i].D;
		int tL=road[i].L;
		int tT=road[i].T;

		if(!vist[tD] && RestMoney>=tT)
		{
			vist[tD]=true;
			DFS(tD,NowLen+tL,RestMoney-tT);
			vist[tD]=false;
		}
	}
	return;
}

int main(void)
{
	while(cin>>K>>N>>R)
	{
		memset(ListTable_Head,-1,sizeof(ListTable_Head));
		memset(vist,false,sizeof(vist));
		pr=0;
		MinLen=inf;

		for(int i=1;i<=R;i++)
		{
			int s,d,l,t;
			cin>>s>>d>>l>>t;
			road[pr].S=s;
			road[pr].D=d;
			road[pr].L=l;
			road[pr].T=t;
			road[pr].next=ListTable_Head[s];
			ListTable_Head[s]=pr++;
		}

		DFS(1,0,K);

		cout<<(MinLen<inf?MinLen:-1)<<endl;
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

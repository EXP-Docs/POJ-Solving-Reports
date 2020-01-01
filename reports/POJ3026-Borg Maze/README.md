## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3026] [[Borg Maze](http://poj.org/problem?id=3026)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 最小生成树算法]

------

## 问题描述

在一个 y行 x列 的迷宫中，有可行走的通路空格 `　`，不可行走的墙 `#`，还有两种英文字母 `A` 和 `S` ，现在从 `S` 出发，要求用最短的路径 `L` 连接所有字母，输出这条路径 `L` 的总长度。


## 解题思路

**BFS + Prim**

一格的长度为1，而且移动的方法只有上、下、左、右，

所以在无任何墙的情况下（但“墙#”是必须考虑的，这里只是为了说明）

**任意两个字母之间的距离就是直接把 横坐标之差 加上 纵坐标之差**

**注意**的是：

- ① 可行的路为 字母 和 空格
- ② 不可行的路为 # 和 矩阵范围之外


根据题意的**“分离”规则**，重复走过的路不再计算

因此当使用prim算法求L的长度时，根据算法的特征恰好不用考虑这个问题（源点合并很好地解决了这个问题），L就是最少生成树的总权值W

由于使用prim算法求在最小生成树，因此无论哪个点做起点都是一样的，（通常选取第一个点），因此起点不是S也没有关系

所以所有的A和S都可以一视同仁，看成一模一样的顶点就可以了

最后要注意的就是 **字符的输入**：

- cin不读入空字符（包括 空格，换行等）
- gets读入空格，但不读入换行符）

 
剩下的问题关键就是处理 **任意两字母间的最短距离**，由于存在了“墙#” ，这个距离不可能单纯地利用坐标加减去计算，必须额外考虑，推荐用BFS（广搜、宽搜），这是本题的唯一难点，因为prim根本直接套用就可以了。


另外注意在求 **任意两字母间的最短距离** 时 **不能直接** 用 BFS：

- (1) 必须先把矩阵中每一个允许通行的格看做一个节点（就是在矩阵内所有非#的格都作为图M的一个顶点），对每一个节点i，分别用BFS求出它到其他所有节点的权值（包括其本身，为0），构造节点图M；
- (2) 然后再加一个判断条件，从图M中抽取以字母为顶点的图，进而构造字母图N。这个判定条件就是当节点图M中的某点j为字母时，把i到j的权值再复制（不是抽离）出来，记录到字母图N的邻接矩阵中
- (3) 剩下的就是对字母图N求最小生成树了


## AC 源码


```c
/*BFS+Prim*/

//Memory Time 
//368K   0MS 

#include<iostream>
#include<string>
using namespace std;

const int inf=2501;      //无限大,最大迷宫的总长也就2500

char map[51][51];  //迷宫原图
int node[51][51];   //记录当前格是否为字母，是第几个字母
int col,row;      //当前迷宫的行列数
int num;         //字母顶点数数目
int dist[102][102];      //构造节点图的两节点间权值，理论节点数最多为2500个（每一个允许通行的格为一个节点）
                         //但是POJ的数据库允许压缩到101个，哈哈，这样时间和空间复杂度都减少很多
int edge[102][102];      //构造字母图的两个字母间的边权，字母数最多为101

class move
{
 public:
	int row,col;
}mov[4]={{0,-1},{0,1},{-1,0},{1,0}}; //分别对应 上 下 左 右

void bfs(int i,int j)
{
	bool vist[51][51];  //标记当前迷宫某一格是否已被访问
	int que_x[2500],que_y[2500];  //坐标队列
	int head=0,tail=0;  //队列指针

	/*Initial*/

	memset(dist,0,sizeof(dist));
	memset(vist,false,sizeof(vist));
	vist[i][j]=true;
	que_x[tail]=i;
	que_y[tail++]=j;

	while(head<tail)
	{
		int x=que_x[head];
		int y=que_y[head++];
		if(node[x][y])
			edge[ node[i][j] ][ node[x][y] ] = dist[x][y];   //抽取字母到字母的边权
		for(int k=0;k<4;k++)
		{
			int mx=x+mov[k].row;
			int my=y+mov[k].col;
			if(mx>=1 && mx<= row && my>=1 && my<=col)
				if(!vist[mx][my] && map[mx][my]!='#')
				{
					que_x[tail]=mx;
					que_y[tail++]=my;
					vist[mx][my]=true;
					dist[mx][my]=dist[x][y]+1;
				}
		}
	}
	return;
}

int prim(void)
{
	int s=1;
	int m=1;
	bool u[102];
	u[s]=true;

	int min_w;
	int prim_w=0;
	int point;
	int low_dis[102];

	for(int i=1;i<=num;i++)
	{
		low_dis[i]=inf;
		u[i]=false;
	}

	while(true)
	{
		if(m==num)
			break;

		min_w=inf;
		for(int i=2;i<=num;i++)
		{
			if(!u[i] && low_dis[i]>edge[s][i])
				low_dis[i] = edge[s][i];
			if(!u[i] && min_w>low_dis[i])
			{
				min_w=low_dis[i];
				point=i;
			}
		}
		s=point;
		u[s]=true;
		prim_w+=min_w;
		m++;
	}
	return prim_w;
}

int main(int i,int j)
{
	int test;
	cin>>test;
	while(test--)
	{
		/*Initial*/

		memset(node,0,sizeof(node));
		num=0;

		/*Input*/

		cin>>col>>row;
		char temp[51];
		gets(temp);  //吃掉cin遗留下来的换行符,我不知道为什么getchar()会AW
		for(i=1;i<=row;i++)
		{
			gets(map[i]);
			for(j=1;j<=col;j++)
				if(map[i][j]=='A'||map[i][j]=='S')
					node[i][j]=++num;
		}

		/*BFS-> Structure Maps*/

		for(i=1;i<=row;i++)
			for(j=1;j<=col;j++)
				if(node[i][j])
					bfs(i,j);   //构造节点i,j到其他所有节点的边权（非#的格子就是一个节点）

		/*Prim Algorithm & Output*/

		cout<<prim()<<endl;
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

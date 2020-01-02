## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2251] [[Dungeon Master](http://poj.org/problem?id=2251)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: BFS]

------

## 问题描述

给出一三维空间的地牢,要求求出由字符'S'到字符'E'的最短路径

移动方向可以是上，下，左，右，前，后，六个方向

每移动一次就耗费一分钟，要求输出最快的走出时间。
不同L层的地图，相同RC坐标处是连通的


## 解题思路

我越看这题就越觉得是  XX地下城 ......

水题一道，求最短路问题，直接**BFS**

开三维数组，每次搜索方向由二维的4个方向增加到6个，但是方法还是那个方法，没难度

> 注意：如果三维数组恰好开到极限的 `30*30*30` 是会RE的，别替人家电脑省空间，想AC就开大点。


值得一提的是, 发现有些同学郁闷地用 DFS 解半天解不出来。。。。

这里就提示一下大家，**凡是看到求最短路，用DFS一定很难做出来，一定要BFS**


## AC 源码


```c
//Memory Time 
// 784K  32MS 

#include<iostream>
using namespace std;

typedef class
{
	public:
		int l,r,c;
		int depth;  //树深（分钟）
}SE;

SE s,e;
bool maze[40][40][40];
int shortminute;

bool BFS(int k,int i,int j)
{
	bool vist[40][40][40]={false};

	SE queue[30000];
	int head,tail;
	queue[head=0].l=k;
	queue[tail=0].r=i;
	queue[0].c=j;
	queue[tail++].depth=1;

	vist[k][i][j]=true;

	while(head<tail)
	{
		SE x=queue[head++];

		if(x.l==e.l && x.r==e.r && x.c==e.c)
		{
			shortminute=x.depth;
			return true;
		}

		if(maze[x.l][x.r][x.c-1] && !vist[x.l][x.r][x.c-1])  //West
		{
			vist[x.l][x.r][x.c-1]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r;
			queue[tail].c=x.c-1;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l][x.r-1][x.c] && !vist[x.l][x.r-1][x.c])  //North
		{
			vist[x.l][x.r-1][x.c]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r-1;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l][x.r][x.c+1] && !vist[x.l][x.r][x.c+1])  //East
		{
			vist[x.l][x.r][x.c+1]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r;
			queue[tail].c=x.c+1;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l][x.r+1][x.c] && !vist[x.l][x.r+1][x.c])  //South
		{
			vist[x.l][x.r+1][x.c]=true;
			queue[tail].l=x.l;
			queue[tail].r=x.r+1;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l-1][x.r][x.c] && !vist[x.l-1][x.r][x.c])  //Up
		{
			vist[x.l-1][x.r][x.c]=true;
			queue[tail].l=x.l-1;
			queue[tail].r=x.r;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
		if(maze[x.l+1][x.r][x.c] && !vist[x.l+1][x.r][x.c])  //Down
		{
			vist[x.l+1][x.r][x.c]=true;
			queue[tail].l=x.l+1;
			queue[tail].r=x.r;
			queue[tail].c=x.c;
			queue[tail++].depth=x.depth+1;
		}
	}
	return false;
}

int main(int i,int j,int k)
{
	int L,R,C;
	while(cin>>L>>R>>C)
	{
		if(!L && !R && !C)
			break;

		/*Initial*/

		memset(maze,false,sizeof(maze));
		
		/*Structure the Maze*/

		for(k=1;k<=L;k++)
			for(i=1;i<=R;i++)
				for(j=1;j<=C;j++)
				{
					char temp;
					cin>>temp;
					if(temp=='.')
						maze[k][i][j]=true;
					if(temp=='S')
					{
						maze[k][i][j]=true;
						s.l=k;
						s.r=i;
						s.c=j;
					}
					if(temp=='E')
					{
						maze[k][i][j]=true;
						e.l=k;
						e.r=i;
						e.c=j;
					}
				}

		/*Search the min Minute*/

		if(BFS(s.l,s.r,s.c))
			cout<<"Escaped in "<<shortminute-1<<" minute(s)."<<endl;
		else
			cout<<"Trapped!"<<endl;

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

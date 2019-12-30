## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3259] [[Wormholes](http://poj.org/problem?id=3259)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 最短路径算法]

------

## 问题描述

无。


## 解题思路

利用虫洞的时光旅行，很有趣的一道题。涉及到图论的知识，**关键是构造图**，用**Bellman-Ford算法**找出负权环

Bellman-Ford算法核心在于松弛，具体算法可以百度。

**需要注意的就是输入说明Input这部分，很多人读不懂这段题意**：

**正权（双向）边部分**：

```
Line 1 of each farm: Three space-separated integers respectively: N, M, and W
Lines 2~M+1 of each farm: Three space-separated numbers (S, E, T) that describe, respectively: a bidirectional path between S and E that requires T seconds to traverse.
Two fields might be connected by more than one path.
```

**负权(单向)边部分**：

```
Lines M+2~M+W+1 of each farm: Three space-separated numbers (S,E, T) that describe, respectively: A one way path from S toE that also moves the traveler back T seconds.
```

## AC 源码


```c
//Memory Time 
//308K   204MS 

#include<iostream>
using namespace std;

int dis[1001];      //源点到各点权值
const int max_w=10001;      //无穷远

class weight
{
public:
    int s;
	int e;
	int t;
}edge[5200];

int N,M,W_h; //N (1≤N≤500)fields 顶点数
             //M (1≤M≤2500)paths 正权双向边
             //W_h (1≤W≤200) wormholes 虫洞（回溯），负权单向边
int all_e;   //边集（边总数）

bool bellman(void)
{
    bool flag;

	/*relax*/

    for(int i=0;i<N-1;i++)
    {
        flag=false;
        for(int j=0;j<all_e;j++)
            if(dis[edge[j].e] > dis[edge[j].s] + edge[j].t)
			{
                dis[edge[j].e] = dis[edge[j].s] + edge[j].t;
                flag=true;         //relax对路径有更新
			}
        if(!flag)   
            break;  //只要某一次relax没有更新，说明最短路径已经查找完毕，或者部分点不可达，可以跳出relax
    }

	/*Search Negative Circle*/

    for(int k=0;k<all_e;k++)
        if( dis[edge[k].e] > dis[edge[k].s] + edge[k].t)
            return true;

    return false;
}
int main(void)
{
    int u,v,w;

	int F;
    cin>>F;
    while(F--)
    {
		memset(dis,max_w,sizeof(dis));    //源点到各点的初始值为无穷，即默认不连通

        cin>>N>>M>>W_h;

        all_e=0;      //初始化指针

		/*read in Positive Paths*/

        for(int i=1;i<=M;i++)
        {
            cin>>u>>v>>w;
            edge[all_e].s=edge[all_e+1].e=u;
            edge[all_e].e=edge[all_e+1].s=v;
            edge[all_e++].t=w;
            edge[all_e++].t=w;               //由于paths的双向性，两个方向权值相等，注意指针的移动
        }

		/*read in Negative Wormholds*/

        for(int j=1;j<=W_h;j++)
        {
            cin>>u>>v>>w;
            edge[all_e].s=u;
            edge[all_e].e=v;
            edge[all_e++].t=-w;     //注意权值为负
        }

		/*Bellman-Ford Algorithm*/

        if(bellman())
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
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

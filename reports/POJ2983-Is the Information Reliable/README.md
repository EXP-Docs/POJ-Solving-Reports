## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2983] [[Is the Information Reliable?](http://poj.org/problem?id=2983)]

> [Time: 3000MS] [Memory: 131072K] [难度: 中级] [分类: 差分约束]

------

## 问题描述

给出M个表达式，判断这些信息是否可靠。


## 解题思路

**差分约束**+Bellman-Ford（建议用**优化的Bellman-Ford**）

设 `dist[i]` 为超级源点到i点的距离，则

建立 `<=` 的差分系统：

由于 P  A  B  X 指“确定A到B的距离（边权）为X”

从 P  A  B  X 得到的差分系统为

`dist[A] - dist[B] >= X  &&  dist[A] - dist[B] <= X`

等价于

`dist[B] <= dist[A] - X  &&  dist[A] <= dist[B] + X`

则 `if(dist[B] > dist[A]-X)` 松弛：`dist[B] = dist[A]-X`

由于 V  A  B 指“只知道A到B的距离（边权）至少为1”

从 V  A  B 得到的差分系统为

`dist[A] >= dist[B] +1`

等价于

`dist[B] <= dist[A] -1 `

则 `if(dist[B] > dist[A] -1)` 松弛：`dist[B] = dist[A] -1`

------

**注意**：

- （1）建立 `<=` 的差分系统，就必须求最短路（Bellman-Ford算法）。而信息是否可靠，就是判断图中是否存在负权回路（也是利用 Bellman-Ford判断）
- （2）由于最坏有10W组不等式，经实测用 `scanf` 输入比 `cin` 要节省1500ms
- （3）经实测用优化Bellman-Ford算法比普通Bellman-Ford算法快2000ms


## AC 源码

### 解题方法一：差分约束+优化Bellman

```c
/*差分约束+优化Bellman*/

//Memory Time 
//2596K  485MS 

#include <iostream>
using namespace std;

const int inf=1000000000;

class
{
public:
	int s,e;
}edge[200001];

int N; //太空站数目
int M; //tips数

int dist[1001];  //源点到各点的距离
int w[200001];  //边权

int main(int i,int j)
{
    while(cin>>N>>M)
    {
		memset(dist,0,sizeof(dist));  //初始化源点到各点的距离
		int pe=0;

		for(i=0;i<M;i++)
		{
			char pv;
			int a,b,x;

			getchar();   //吃掉回车
			scanf("%c",&pv);   //由于要频繁输入，用scanf比cin要快1500ms

			if(pv=='P')  //清晰边权，即A、B间距离确定，建立双向边
			{
				scanf("%d%d%d",&a,&b,&x);
				edge[pe].s=a;
				edge[pe].e=b;
				w[pe++]=x;
				edge[pe].s=b;
				edge[pe].e=a;
				w[pe++]=-x;
			}
			else if(pv=='V')  //模糊边权，即A、B间距离不确定，建立单向边
			{
				scanf("%d%d",&a,&b);
				edge[pe].s=a;
				edge[pe].e=b;
				w[pe++]=1;
			}
		}

		/*Bellman-Ford*/

		bool sign;  //用于Bellman-Ford算法优化
		for(j=0;j<N;j++)
		{
			sign=false;
			for(i=0;i<pe;i++)
				if(dist[ edge[i].e ] > dist[ edge[i].s ] - w[i])
				{
					dist[ edge[i].e ] = dist[ edge[i].s ] - w[i];
					sign=true;
				}  
			if(!sign)//若dist没有任何改变，则以后也不会改变，可以直接退出循环
				break;
		}//循环n次后若flag == false 说明有负权回路，或者权值矛盾

		if(sign)
			cout<<"Unreliable"<<endl; //存在负权环
		else
			cout<<"Reliable"<<endl;   //不存在负权环
  
    }
    return 0;
}
```

### 解题方法二：差分约束+无优化Bellman

```c
/*差分约束+无优化Bellman*/


//Memory Time 
//2596K 2438MS

#include<iostream>
using namespace std;

const int inf=1000000000;

class
{
public:
	int s,e;
}edge[200001];

int N; //太空站数目
int M; //tips数

int dist[1001];  //源点到各点的距离
int w[200001];  //边权

int main(int i,int j)
{
	while(cin>>N>>M)
	{
		memset(dist,0,sizeof(dist));  //初始化源点到各点的距离
		int pe=0;

		for(i=0;i<M;i++)
		{
			char pv;
			int a,b,x;

			getchar();   //吃掉回车
			scanf("%c",&pv);  
			if(pv=='P')    //清晰边权，即A、B间距离确定，建立双向边
			{
				scanf("%d%d%d",&a,&b,&x);
				edge[pe].s=a;
				edge[pe].e=b;
				w[pe++]=x;
				edge[pe].s=b;
				edge[pe].e=a;
				w[pe++]=-x;
			}
			else if(pv=='V')  //模糊边权，即A、B间距离不确定，建立单向边
			{
				scanf("%d%d",&a,&b);
				edge[pe].s=a;
				edge[pe].e=b;
				w[pe++]=1;
			}
		}

	/*Bellman-Ford*/

		/*Relax*/

		for(j=0;j<N;j++)
			for(i=0;i<pe;i++)
				if(dist[ edge[i].e ] > dist[ edge[i].s ] - w[i])
					dist[ edge[i].e ] = dist[ edge[i].s ] - w[i];

		/*Judge the Negative Circle*/

		bool sign=false;
		for(i=0;i<pe;i++)
			if(dist[ edge[i].e ] > dist[ edge[i].s ] - w[i])
			{
				sign=true;
				break;
			}
				
		if(sign)
			cout<<"Unreliable"<<endl; //存在负权环
		else
			cout<<"Reliable"<<endl;   //不存在负权环
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

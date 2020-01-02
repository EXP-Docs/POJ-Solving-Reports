## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1129] [[Channel Allocation](http://poj.org/problem?id=1129)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 搜索]

------

## 问题描述

当一个广播电台在一个非常大的地区，广播站会用中继器来转播信号以使得每一个接收器都能接收到一个强烈的信号。然而，每个中继器必须慎重选择使用，使相邻的中继器不互相干扰。如果相邻的中继器使用不同的频道，那么就不会相互干扰。

由于无线电频道是一有限的，一个给定的网络所需的中继频道数目应减至最低。编写一个程序，读取一个中继网络，然后求出需要的最低的不同频道数。


**建模**：

一个有N个节点的**无向图**，要求对每个节点进行染色，使得相邻两个节点颜色都不同，问最少需要多少种颜色？

那么题目就变成了一个经典的**图的染色**问题。


## 解题思路

对于这题数据范围很小（节点最多26个），所以使用普通的**暴力搜索法**即可。

对点i的染色操作：从最小的颜色开始搜索，当i的直接相邻（直接后继）结点已经染过该种颜色时，搜索下一种颜色。

就是说i的染色，当且仅当i的临近结点都没有染过该种颜色，且该种颜色要尽可能小。


要注意题中的一句话：

```
since the repeaters lie in a plane, the graph formed byconnecting adjacent repeaters does not have any line segments that cross.
```

大致意思就是 “**城市所在的世界是一个平面世界，当把城市看做点，相邻城市用边连接时，这些边不能相交**”


> 在网上很多同学都说用“**四色定理**”解决这题， 其实不是，四色定理在本题单纯是用来**剪枝**的，而且由于结点数较少（只有26），剪枝与否对时间影响不大，普通的爆搜也是0ms AC的，不过有兴趣的同学可以看看“四色定理”。

因为**当结点数很多时，四色定理的剪枝优势就会体现出来了**


我把 **暴力搜索** 和 **经过四色定理剪枝的搜索** 两个程序都都贴出来，大家比较一下就知道四色定理怎么用了。


## 提示

四色定理的“相邻”是指两块多边形地区“至少一条边重合”才为之相邻。

“至少一条边重合”同时也隐含了“任意边（线段）不正规相交。

如：

![](/img/01.png)


再反观本题的模型，本题的相邻是“两点有边连接，但任意两边不交叉（正规相交）”，这种“相邻”其实就是四色定理的“相邻”。

我举一个例子就一目了然了：

```
N=7

A:BCDEFG

B:ACDEFG

C:ABD

D:ABCE

E:ABDF

F:ABEG

G:ABF
```

画成图就是：


![](/img/02.png)

> 由于边不允许相交，这已经是7个点的最大连接数


**四色定理的原始理论依据**：

对于一个散点集，若要求尽可能连接任意两个点，但任意一条边边不允许与其他边相交，

那么当散点集的元素个数<=4时，连接所得的图必为一个一个 无向完全图

当散点集的元素个数>4时，连接所得的图必不是一个完全图

> 完全图：任意两点均相邻


最后千万要注意输出，当频道数大于1时，`channel` 为复数 `channels`


## AC 源码

### 解题方法一：四色定理剪枝的搜索

```c
/*四色定理*/

//Memory Time 
//184K   0MS 

#include<iostream>
using namespace std;

typedef class
{
	public:
		int next[27];  //直接后继
		int pn;   //next[]指针（后继个数）
}point;

int main(int i,int j,int k)
{
	int n;
	while(cin>>n)
	{
		if(!n)
			break;

		getchar();  //n的换行符

		point* node=new point[n+1];  //结点

		/*Structure the Map*/

		for(i=1;i<=n;i++)
		{
			getchar();  //结点序号
			getchar();  //冒号

			if(node[i].pn<0)   //初始化指针
				node[i].pn=0;

			char ch;
			while((ch=getchar())!='\n')
			{
				j=ch%('A'-1);   //把结点字母转换为相应的数字，如A->1  C->3
				node[i].next[ ++node[i].pn ]=j;
			}
		}

		int color[27]={0};  //color[i]为第i个结点当前染的颜色，0为无色（无染色）
		color[1]=1;  //结点A初始化染第1种色
		int maxcolor=1;  //当前已使用不同颜色的种数

		for(i=1;i<=n;i++)  //枚举每个顶点
		{
			color[i]=n+1;  //先假设结点i染最大的颜色
			bool vist[27]={false};  //标记第i种颜色是否在当前结点的相邻结点染过
			for(j=1;j<=node[i].pn;j++) //枚举顶点i的所有后继
			{
				int k=node[i].next[j];
				if(color[k])  //顶点i的第j个直接后继已染色
					vist[ color[k] ]=true;  //标记该种颜色
			}
			for(j=1;i<=n;j++)  //从最小的颜色开始，枚举每种颜色
				if(!vist[j] && color[i]>j) //注意染色的过程是一个不断调整的过程，可能会暂时出现大于4的颜色
				{                          //因此不能单纯枚举4种色，不然会WA
					color[i]=j;
					break;
				}

			if(maxcolor<color[i])
			{
				maxcolor=color[i];
				if(maxcolor==4)   //由四色定理知，最终完成染色后，图上最多只有四种颜色
					break;        //因此当染色过程出现结点的颜色为4时，就可以断定最少要用4种颜色染色
			}
		}

		if(maxcolor==1)
			cout<<1<<" channel needed."<<endl;
		else
			cout<<maxcolor<<" channels needed."<<endl;

		delete node;
	}
	return 0;
}
```

### 解题方法二：暴力搜索

```c
/*暴力搜索*/

//Memory Time 
//184K   0MS 

#include<iostream>
using namespace std;

typedef class
{
	public:
		int next[27];  //直接后继
		int pn;   //next[]指针（后继个数）
}point;

int main(int i,int j,int k)
{
	int n;
	while(cin>>n)
	{
		if(!n)
			break;

		getchar();  //n的换行符

		point* node=new point[n+1];  //结点

		/*Structure the Map*/

		for(i=1;i<=n;i++)
		{
			getchar();  //结点序号
			getchar();  //冒号

			if(node[i].pn<0)   //初始化指针
				node[i].pn=0;

			char ch;
			while((ch=getchar())!='\n')
			{
				j=ch%('A'-1);   //把结点字母转换为相应的数字，如A->1  C->3
				node[i].next[ ++node[i].pn ]=j;
			}
		}

		int color[27]={0};  //color[i]为第i个结点当前染的颜色，0为无色（无染色）
		color[1]=1;  //结点A初始化染第1种色
		int maxcolor=1;  //当前已使用不同颜色的种数

		for(i=1;i<=n;i++)  //枚举每个顶点
		{
			color[i]=n+1;  //先假设结点i染最大的颜色
			bool vist[27]={false};  //标记第i种颜色是否在当前结点的相邻结点染过
			for(j=1;j<=node[i].pn;j++) //枚举顶点i的所有后继
			{
				int k=node[i].next[j];
				if(color[k])  //顶点i的第j个直接后继已染色
					vist[ color[k] ]=true;  //标记该种颜色
			}
			for(j=1;i<=n;j++)  //从最小的颜色开始，枚举每种颜色，最终确定结点i的染色
				if(!vist[j] && color[i]>j)
				{
					color[i]=j;
					break;
				}

			if(maxcolor<color[i])
				maxcolor=color[i];
		}

		if(maxcolor==1)
			cout<<1<<" channel needed."<<endl;
		else
			cout<<maxcolor<<" channels needed."<<endl;

		delete node;
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

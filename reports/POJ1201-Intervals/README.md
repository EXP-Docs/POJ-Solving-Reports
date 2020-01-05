## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1201] [[Intervals](http://poj.org/problem?id=1201)]

> [Time: 2000MS] [Memory: 65536K] [难度: 中级] [分类: 差分约束]

------

## 问题描述

给出数轴上的n个区间 `[ai，bi]`，每个区间都是连续的int区间。

现在要在数轴上任意取一堆元素，构成一个元素集合V

要求每个区间 `[ai，bi]` 和元素集合V的交集至少有ci不同的元素

求集合V最小的元素个数。


## 解题思路

[POJ1716](/reports/POJ1716-Integer%20Intervals) 的升级版，只是边权不是固定，而是变化的而已

其实只要把 [POJ1716](/reports/POJ1716-Integer%20Intervals) 的 范围 和“固定边权2”改为ci 就能直接AC了

> 注意**本题只能用差分约束+Relax解决**，不能像 [POJ1716](/reports/POJ1716-Integer%20Intervals) 那样用贪心。


建议先去把我做 [POJ1716](/reports/POJ1716-Integer%20Intervals) 的方法看懂了，再来做这题，不过我还是**重述一下思路**：


设 `s[x] = 从0到x` 的所有在集合中的数的个数

则ai到bi的个数即 `S[bi] - S[ai-1]` 。

因此有

(1) `S[bi] - S[ai-1] >= ci`。

又根据s[x]本身的性质，后面的一定不比前面的小，后面的最多比前面多一，有：

(2)  `s[i + 1] - s[i] >= 0`

(3)  `s[i + 1] - s[i] <= 1`

故建图,使图中每一组边，均满足（**注意三条式子的不等号方向要一致，这个很重要**）:

- `S[ai - 1] <= S[bi] - ci` 
- `S[i] <= S[i - 1] + 1` 
- `S[i - 1] <= S[i]`

上面三式，可把 `s[x]` 看作源点（假设存在）到各点的最短距离，初始化为0；

常数为边 `(ai – 1，bi)`的边权

当存在不满足这三条式子的边时，对这条边进行Relax操作，**更新不等号左边的变量**。

其实就是**Bellman-Ford**算法的核心部分

- `if( S[ai - 1] > S[bi] – 2 )   S[ai - 1] = S[bi] – ci;`
- `if( S[i] > S[i - 1] + 1 )   S[i] > S[i - 1] + 1;`
- `if( S[i - 1] > S[i] )   S[i - 1] = S[i];`


最后源点到最大顶点的距离减去源点到最小顶点的距离就是所求（其实一个单位距离就代表V中的一个元素；最小顶点到最大顶点其实就是所有输入的区间中，最小的左端点到最大的右端点这个范围）。

> 注意，经过我测试，像POJ1716一样，本题变量的定义均要从全局定义，否则WA，什么原因我也不清楚（变量和数组的大小都只有50000，真是神了）



## AC 源码


```c
//Memory Time 
//996K  1141MS 

#include<iostream>
using namespace std;

const int inf=60000;

class
{
	public:
		int s,e;
}inter[50001];

int n; //区间数
int upli;
int doli; // UpLimit , Downlimit 上下限
int dist[50001];  //源点到各点的距离
int c[50001];  //边权

int main(int i,int j,int k)
{
	while(cin>>n)
	{
		upli=0;
		doli=inf;

		/*Input*/

		for(k=0;k<n;k++)
		{
			int a,b;
			cin>>a>>b>>c[k];
			inter[k].s=a;
			inter[k].e=b+1;

			if(doli>inter[k].s)  //寻找最小的顶点
				doli=inter[k].s;
			if(upli<inter[k].e)  //寻找最大的顶点，inter[k].e必大于inter[k].s，因此无需再与inter[k].s比较
				upli=inter[k].e;

			dist[k]=0; //初始化源点到各点的距离
		}

		/*Bellman-Ford:Relax*/

		bool flag=true;
		while(flag)
		{
			flag=false;
			for(i=0;i<n;i++)
				if(dist[ inter[i].s ]>dist[ inter[i].e ]-c[i])
				{
					dist[ inter[i].s ]=dist[ inter[i].e ]-c[i];
					flag=true;
				}

			for(j=doli;j<upli;j++)
				if(dist[j+1]>dist[j]+1)
				{
					dist[j+1]=dist[j]+1;
					flag=true;
				}

			for(j=upli-1;j>=doli;j--)
				if(dist[j]>dist[j+1])
				{
					dist[j]=dist[j+1];
					flag=true;
				}
		}
		cout<<dist[upli]-dist[doli]<<endl;
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

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1716] [[Integer Intervals](http://poj.org/problem?id=1716)]

> [Time: 1000MS] [Memory: 10000K] [难度: 中级] [分类: 差分约束]

------

## 问题描述

给出数轴上的n个区间，每个区间都是连续的int区间。

现在要在数轴上任意取一堆元素，构成一个元素集合V

要求每个区间和元素集合V的交集至少有两个不同的元素

求集合V最小的元素个数。


## 解题思路

**本题有两种解法**： 贪心算法  或  差分约束

------


**一、贪心算法**

先对所有区间按末端点排序

取第i个区间的最后两个元素Selem和Eelem

若第i+1个区间包含了这两个元素，则跳到下一个区间所取的元素个数+0

若第i+1个区间只包含了这两个元素中的一个（由于有序，所以必定是包含Eelem），则取第i+1个区间的最后一个元素，所取的元素个数+1。为了方便下一区间的比较，更新Selem和Eelem的值，使他们为当前V集合中最后的两个元素。

若第i+1个区间没有包含这两个元素，则第i+1个区间的最后两个元素，所取的元素个数+2。为了方便下一区间的比较，更新Selem和Eelem的值，使他们为当前V集合中最后的两个元素。


Selem初始化为第一个区间的最后倒数第2个元素

Eelem初始化为第一个区间的最后的元素

所取的元素个数初始化为2 (就是Selem和Eelem)


------



**二、差分约束+Relax**

设 `s[x] = 从0到x` 的所有在集合中的数的个数

则ai到bi的个数即 `S[bi] - S[ai-1]`。

因此有

(1) `S[bi] - S[ai-1] >= 2`。

又根据s[x]本身的性质，后面的一定不比前面的小，后面的最多比前面多一，有：

(2)  `s[i + 1] - s[i] >= 0`

(3)  `s[i + 1] - s[i] <= 1`

故建图,使图中每一组边，均满足（**注意三条式子的不等号方向要一致，这个很重要**）:

- `S[ai - 1] <= S[bi] - 2`
- `S[i] <= S[i - 1] + 1`
- `S[i - 1] <= S[i]`

上面三式，可把 `s[x]` 看作源点（假设存在）到各点的最短距离，初始化为0；

常数为边 `(ai – 1，bi)` 的边权

当存在不满足这三条式子的边时，对这条边进行Relax操作，**更新不等号左边的变量**。

其实就是**Bellman-Ford**算法的核心部分

- `if( S[ai - 1] > S[bi] – 2 )   S[ai - 1] = S[bi] – 2;`
- `if( S[i] > S[i - 1] + 1 )   S[i] > S[i - 1] + 1;`
- `if( S[i - 1] > S[i] )   S[i - 1] = S[i];`


最后源点到最大顶点的距离减去源点到最小顶点的距离就是所求（其实一个单位距离就代表V中的一个元素；最小顶点到最大顶点其实就是所有输入的区间中，最小的左端点到最大的右端点这个范围）。

 
> 注意，经过我测试，本题变量的定义均要从全局定义，否则WA，什么原因我也不清楚（变量和数组的大小都只有10000，真是神了），只能说POJ太虐人了，白白耗了我一堆时间。


## AC 源码

### 解题方法一： 贪心算法

```c
//Memory Time 
//284K   94MS

/*Greed*/

#include<iostream>
#include<algorithm>
using namespace std;

typedef class
{
public:
	int s,e;
}interval;      //间隔（区间）

int cmp(const void* a,const void* b)
{
	interval* x=(interval*)a;
	interval* y=(interval*)b;
	return (x->e) - (y->e);  //对区间按末端点排序
}

int main(void)
{
	int n; //区间数
	while(cin>>n)
	{
		interval* inter=new interval[n];

		for(int i=0;i<n;i++)
			cin>>inter[i].s>>inter[i].e;

		qsort(inter,n,sizeof(interval),cmp);  //对区间按末端点排序

		int Selem=inter[0].e-1 , Eelem=inter[0].e;  //当前区间所取的两个元素，初始化为第0个区间最后两个元素
		int sum=2;  //至少取sum个元素才能保证每个区间至少含有其中的2个元素
		for(int k=1;k<n;k++)
			if(inter[k].s<=Selem)  //前一个区间所取的两个元素都在当前区间内
				continue;  //则当前区间无需取任何元素
			else if(inter[k].s<=Eelem)  //前一个区间所取的只有一个元素在当前区间内
			{
				Selem=Eelem;
				Eelem=inter[k].e;  //按序更新当前区间所取的两个元素：Selem与Eelem
				sum++;  //Eelem是新取的一个元素
			}
			else  //前一个区间所取的没有一个元素在当前区间内
			{
				Selem=inter[k].e-1;
				Eelem=inter[k].e;  //按序更新当前区间所取的两个元素：Selem与Eelem
				sum+=2;  //Selem与Eelem是新取的两个元素
			}
		cout<<sum<<endl;

		delete inter;
	}
	return 0;
}
```

### 解题方法二： 差分约束+Relax

```c
//Memory Time 
//296K  282MS 

/*Difference Constraints*/

#include<iostream>
using namespace std;

const int inf=20000;

class
{
	public:
		int s,e;
}inter[10001];

int dist[10001];  //源点到各点的距离
int n; //区间数
int upli;
int doli; // UpLimit , Downlimit 上下限

int main(int i)
{	
	while(cin>>n)
	{
		upli=0;
		doli=inf;

		/*Input*/

		for(i=0;i<n;i++)
		{
			int a,b;
			cin>>a>>b;
			inter[i].s=a;
			inter[i].e=b+1;

			if(doli>inter[i].s)  //寻找最小的顶点
				doli=inter[i].s;
			if(upli<inter[i].e)  //寻找最大的顶点，inter[k].e必大于inter[k].s，因此无需再与inter[k].s比较
				upli=inter[i].e;

			dist[i]=0; //初始化源点到各点的距离
		}

		/*Bellman-Ford:Relax*/

		bool flag=true;
		while(flag)  //只要某一次Relax没有更新，说明最短路径已经查找完毕，或者部分点不可达，可以跳出relax
		{
			flag=false;
			for(i=0;i<n;i++)
				if(dist[ inter[i].s ]>dist[ inter[i].e ]-2)
				{
					dist[ inter[i].s ]=dist[ inter[i].e ]-2;
					flag=true;  //Relax对路径有更新
				}

			for(i=doli;i<upli;i++)
				if(dist[i+1]>dist[i]+1)
				{
					dist[i+1]=dist[i]+1;
					flag=true;
				}

			for(i=upli-1;i>=doli;i--)   //这里逆向松弛(从upli到doli)比正向松弛(从doli到upli)快了500ms
				if(dist[i] > dist[i+1])
				{
					dist[i] = dist[i+1];
					flag = true;
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

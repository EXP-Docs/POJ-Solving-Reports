## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3020] [[Antenna Placement](http://poj.org/problem?id=3020)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 二分图]

------

## 问题描述

一个矩形中，有N个城市 `*`，现在这n个城市都要覆盖无线，若放置一个基站，那么它至多可以覆盖相邻的两个城市。

问至少放置多少个基站才能使得所有的城市都覆盖无线？


## 解题思路

**提示：**

- 别被图片的圈圈误导了，看清楚题目
- `*` 是城市， `o` 是空地
- 椭圆的天线覆盖范围要覆盖的是城市 `*` , 而不是覆盖空地

思前想后，依稀可以认为是一道求二分图的**最小路径覆盖**问题（注意不是最小点覆盖）

那么接下来需要确认的是，究竟是求 *有向二分图的最小路覆盖*，还是求 *无向二分图的最小路覆盖* ？

因为有向和无向是截然不同的计算方法。

要确认是构造有向图，还是构造无向图，那么就需要先根据题意，看看构造二分图时所使用的方式，更适合构造哪一种二分图。

然后就进入了 **本题难点：如何构造二分图**

------

**构图**：

首先要明确的是，输入的一堆“圈圈星星”可以看做是一张大地图，地图上有所有城市的坐标，但是这里有一个**误区**：不能简单地把城市的两个x、y坐标作为准备构造的二分图的两个顶点集。

**城市才是要构造的二分图的顶点！**

构造方法如下：

例如输入：

```
\*oo
\*\*\*
o\*o
```

可以抽象为一个数字地图：

```
100
234
050
```

数字就是根据输入的城市次序作为该城市的编号，0代表该位置没有城市。

然后根据题目的“范围”规则，**从第一个城市开始，以自身作为中心城市，向四个方向的城市进行连线（覆盖）**

因此就能够得到**边集**：

```
e12
e21　e23
e32　e34　e35
e43
e53
```

可以看到，这些边都是有向边，但是每一条边都有与其对应的一条相反边。

即任意两个城市（顶点）之间的边是成对出现的

那么我们就可以确定下来，应该 **构造无向二分图（其实无向=双向）**

因为若要构造有向的二分图时，需要判断已出现的边，是很麻烦的工作


------


为了**把有向图G构造为无向二分图**，这里需要引入一个新名词“**拆点**”

其实就是把原有向图G的每一个顶点都”拆分”（我认为复制更准确）为2个点，分别属于所要构造的二分图的两个顶点集。


例如在刚才的例子中抽出一条有向边e12举例说明：

复制顶点1和顶点2，使得：

- `1，2∈V1`
- `1', 2'∈V2`
- 不难发现 `|V1|=|V2|`

根据边e12和e21，得到无向二分图：

![](/reports/POJ3020-Antenna%20Placement/img/01.png)

那么同理就可以得到刚才的例子的 无向二分图为：

![](/reports/POJ3020-Antenna%20Placement/img/02.png)


再继而通过无向二分图，以V1的元素作为row，V2的元素作为col，构造 **可达矩阵** 存储到计算机：

| - | 1’| 2’|  3’|  4’|  5’|
|:---:|:---:|:---:|:---:|:---:|:---:|
| 1 |  F |  T |   F |   F |   F |
| 2 |  T |  F |   T |   F |   F |
| 3|   F |  T |   F |   T |   T |
| 4 |  F |  F |   T |   F |   F |
| 5 |  F |  F |   T |   F |   F |



接下来就是要**求这个 无向二分图的最小路径覆盖** 了

利用**公式**： `无向二分图的最小路径覆盖 = 顶点数 – 最大二分匹配数/2`


**顶点数**：就是用于构造无向二分图的城市数，即进行“拆点”操作前的顶点数量

最大二分匹配书数所以要除以2，是因为进行了“拆点”操作，使得匹配总数多了一倍，因此除以2得到原图的真正的匹配数。


最后剩下的问题就是**求最大二分匹配数**了，用**匈牙利算法**，这就不多说了，参考 [POJ3041](/reports/POJ3041-Asteroids) 的做法，基本一摸一样。


从这道题得出了一个结论：

当二分图的两个顶点子集基数相等时，该二分图所有顶点的匹配数 等于 任意一个顶点子集匹配数的2倍 

其实匈牙利算法解题是极为简单的，但是**图论的难并不是难在解答，而是建图的过程**，也难怪会有牛曰：用匈牙利算法，建图是痛苦的，最后是快乐的。


## AC 源码


```c
//Memory Time 
//420K   16MS 

#include<iostream>
using namespace std;

int ipmap[41][11];   //标记存在城市'*'的位置，并依次记录城市的编号
int ip;     //城市编号（最终是城市数量）
int V1,V2;  //二分图的两个顶点集
int M;      //最大二分匹配

bool city[401][401];   //标记两个城市之间是否能连通
                      //通过“拆点”操作，把每一个城市拆分为2个，分别属于所构造的二分图的两个点集
bool vist[401];
int link[401];

int dire_r[4]={-1,1,0,0};
int dire_c[4]={0,0,-1,1};   //分别对应四个方位 上 下 左 右


/*Hungary Algorithm*/

bool dfs(int x)
{
	for(int y=1;y<=V2;y++)
		if(city[x][y] && !vist[y])
		{
			vist[y]=true;
			if(link[y]==0 || dfs(link[y]))
			{
				link[y]=x;
				return true;
			}
		}
	return false;
}

void search(void)
{
	for(int x=1;x<=V1;x++)
	{
		memset(vist,false,sizeof(vist));
		if(dfs(x))
			M++;
	}
	return;
}

int main(void)
{
	int test,h,w;
	cin>>test;
	while(test--)
	{
		/*Initial*/

		memset(ipmap,0,sizeof(ipmap));
		memset(city,false,sizeof(city));
		memset(link,0,sizeof(link));
		ip=0;
		M=0;

		/*Read in the maps*/

		cin>>h>>w;

		int i,j;
		char temp;
		for(i=1;i<=h;i++)
			for(j=1;j<=w;j++)
			{
				cin>>temp;
				if(temp=='*')
					ipmap[i][j]=++ip;
			}

		/*Structure the Bipartite Graphs*/

		for(i=1;i<=h;i++)
			for(j=1;j<=w;j++)
				if(ipmap[i][j])
					for(int k=0;k<4;k++)
					{
						int x=i+dire_r[k];
						int y=j+dire_c[k];
						if(ipmap[x][y])
							city[ ipmap[i][j] ][ ipmap[x][y] ]=true;      //"拆点"操作是"顺便"被完成的
					}                                                    //二分图构造完毕后，之后的问题就和POJ3041一样处理了

		V1=V2=ip;

		/*增广轨搜索*/

		search();

		/*Output*/

		cout<<ip-M/2<<endl;   //无向二分图：最小路径覆盖数 = "拆点"前原图的顶点数 - 最大匹配数/2
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

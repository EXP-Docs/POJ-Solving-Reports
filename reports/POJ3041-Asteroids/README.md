## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3041] [[Asteroids](http://poj.org/problem?id=3041)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 二分图]

------

## 问题描述

无。


## 解题思路

把方阵看做一个特殊的二分图（以行列分别作为两个顶点集V1、V2，其中 `|V1|=|V2|`）

然后把每行x或者每列y看成一个点，而障碍物(x,y)可以看做连接x和y的边。

按照这种思路构图后，问题就转化成为选择最少的一些点(x或y)，使得从这些点与所有的边相邻，其实这就是**最小点覆盖问题**。

再利用 二分图最大匹配的Konig定理：**最小点覆盖数 = 最大匹配数**

> 最小点覆盖：假如选了一个点就相当于覆盖了以它为端点的所有边，那么需要选择最少的点来覆盖图的所有的边。）

因此**本题自然转化为求 二分图的最大匹配 问题**。

求最大匹配的一种显而易见的算法是：先找出全部匹配，然后保留匹配数最多的。但是这个算法的时间复杂度为边数的指数级函数，所以需要寻求一种更加高效的算法——用**增广路求最大匹配的方法（匈牙利算法）**


**增广路的定义**(也称增广轨或交错轨)：

若P是图G中一条连通两个未匹配顶点的路径，并且属于M的边和不属于M的边(即已匹配和待匹配的边)在P上交替出现，则称P为相对于M的一条增广路径。

由增广路的定义可以**推出下述三个结论**：

- P的路径个数必定为奇数，第一条边和最后一条边都不属于M。
- 将M和P进行取反操作可以得到一个更大的匹配M （反操作：把P中的 匹配边 与 非匹配边 互换）
- M为G的最大匹配当且仅当不存在M的增广路径P

**匈牙利算法步骤**：

- 置M为空
- 找出一条增广路径P，通过异或操作获得更大的匹配M’代替M
- 重复(2)操作直到找不出增广路径为止


## AC 源码


```c
//Memory Time 
//464K   47MS 

#include<iostream>
using namespace std;

int n,k;  //n矩阵规格，k星体数量
int V1,V2;       //二分图顶点集
 /*矩阵的行列分别属于二分图的两个顶点集V1、V2，其中行x∈V1，列y∈V2*/
bool grid[501][501];  //存储数据方式：可达矩阵
bool vis[501];     //记录V2的点每个点是否已被搜索过
int link[501];     //记录 V2中的点y 在 V1中 所匹配的点x的编号
int m;  //最大匹配数

/*Hungary Algorithm*/

bool dfs(int x)
{
	for(int y=1;y<=V2;y++)
		if(grid[x][y] && !vis[y])  //x到y相邻(有边) 且 节点y未被搜索
		{
			vis[y]=true;   //标记节点y已被搜索
			if(link[y]==0 || dfs(link[y])) //link[y]==0 : 如果y不属于前一个匹配M
			{                               //find(link[y] : 如果被y匹配到的节点可以寻找到增广路
				link[y]=x; //那么可以更新匹配M'(用M替代M')
				return true;  //返回匹配成功的标志
			}
		}
	return false;  //继续查找V1下一个x的邻接节点
}

void search(void)
{
	for(int x=1;x<=V1;x++)
	{
		memset(vis,false,sizeof(vis)); //清空上次搜索时的标记
		if(dfs(x))  //从V1中的节点x开始寻找增广路
			m++;
	}
	return;
}

int main(void)
{
	cin>>n>>k;
	V1=V2=n;

	int x,y;         //坐标(临时变量)
	for(int i=1;i<=k;i++)
	{
		cin>>x>>y;
		grid[x][y]=true;   //相邻节点标记
	}

	/*增广轨搜索*/

	search();

	/*Output*/

	cout<<m<<endl;

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

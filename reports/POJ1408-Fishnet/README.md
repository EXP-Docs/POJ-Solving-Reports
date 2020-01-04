## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1408] [[Fishnet](http://poj.org/problem?id=1408)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 多边形算法]

------

## 问题描述

一个1X1的正方形，每条边上有n个不同的点（不包括顶点），并给出它们的坐标。现在把对边相对应的点相连，将正方形分割成 `(n+1)*(n+1)` 个小四边形。问最大的四边形的面积是多少。


## 解题思路

计算几何**求面积**的题，算半条水题吧。。

**基本思路**：构造所有的线段，然后枚举每对水平－竖直线段，求交点，然后计算四边形面积，求最大值。

**应用知识**：

- ① 叉积（规范相交）
- ② 多边形分解
- ③ 三角形基于计算几何的面积公式（注意正负）


我先建立一个**数学模型**说明问题：

以 `n=3` 为例画图 （当然实际上内部的线不一定是正交的，这里只是为了简单说明）

![](/img/01.png)


第一步建立一个大小为 `(n+2)*(n+2)` 的二维交点矩阵node，每个元素存储一个交点坐标 `(x,y)`

由于四角交点为定点，每条边上的交点又是输入值，那么外围一圈的交点都是已知了

由于对边的点是对应相连的，因此要求的就是内部 `n*n` 个交点

显然地，所求的所有交点都是某两条直线规范相交所得，因此就可以直接使用**求规范相交的交点的公式**，而不需要套用模板了

**交点公式 (及推导过程) 请参看  刘汝佳《算法艺术与信息学竞赛》P357** 这里不再说明


通过两两枚举所有内部直线，就能得到 交点矩阵 `node[][]`

------


那么剩下的问题就是求出所有 **简单四边形（不包含其他四边形）** 的面积，输出最大的一个。**那么问题就是：已知一个不规则四边形四个角的坐标，求它的面积**

![](/img/02.png)

由于四边形是不规则的，直接求解其面积是非常困难的，唯有将其划分为两个三角形，分别求出两个三角形的面积，再相加。


如图，我求解所有四边形时都是采用如图的划分方法

那么**问题进一步转化为“已知不规则三角形三个角的坐标，如何求其面积”**



不用比较都看得出，**计算几何的方法远远优于解析几何**，不但省去计算一堆长度的麻烦（避免了精度误差），而且还能利用计算交点时 计算叉积的功能函数 `cross()`

使用计算几何，不但运算量大大减少了，代码也写少了，结果还更精确


不过有一点要注意的是，**计算几何计算的面积是有方向的，即面积可能为负，所以绝对值必不可少**，这点千万注意


## AC 源码


```c
//Memory Time 
//544K   16MS 

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

typedef class Node
{
	public:
		double x,y;
}location;

double det(double x1,double y1,double x2,double y2)
{
	return x1*y2-x2*y1;
}

double cross(location A,location B,location C,location D)       //计算 AB x CD
{
	return det(B.x-A.x , B.y-A.y , D.x-C.x , D.y-C.y);
}

/*Compute Intersection*/

double xx,yy;  //坐标返回值
void intersection(location A,location B,location C,location D)
{
	double area1=cross(A,B,A,C);
	double area2=cross(A,B,A,D);

	xx=(area2*C.x - area1*D.x)/(area2-area1);    //本题所求的交点一定是规范相交所得，因此无需判断是否规范相交
	yy=(area2*C.y - area1*D.y)/(area2-area1); 
	return;
}

/*Compute Area*/

double area(location A,location B,location C,location D)
{
	double triangle1=fabs(0.5*cross(A,B,A,C));    //用计算几何的方法计算的面积是有向面积
	double triangle2=fabs(0.5*cross(A,B,A,D));    //即算出来的面积可能为负数，因此必须用绝对值
                                                  // fabs() 为取double的绝对值函数
	return triangle1+triangle2;
}

int main(int i,int j,int k)
{
	int n;
	while(cin>>n)
	{
		if(!n)
			break;

		/*Initial*/

		location** node=new location*[n+2];
		node[0]=new location[n+2];   //下边
		node[n+1]=new location[n+2]; //上边

		/*Input Down-edge*/

		node[0][0].x = node[0][0].y =0.0;
		for(i=1;i<=n;i++)
		{
			cin>>node[0][i].x;
			node[0][i].y=0.0;
		}
		node[0][n+1].x=1.0;
		node[0][n+1].y=0.0;

		/*Input Up-edge*/

		node[n+1][0].x=0.0;
		node[n+1][0].y=1.0;
		for(i=1;i<=n;i++)
		{
			cin>>node[n+1][i].x;
			node[n+1][i].y=1.0;
		}
		node[n+1][n+1].x=1.0;
		node[n+1][n+1].y=1.0;

		/*Input Left-edge*/

		for(i=1;i<=n;i++)
		{
			node[i]=new location[n+2];
			cin>>node[i][0].y;
			node[i][0].x=0.0;
		}

		/*Input right-edge*/

		for(i=1;i<=n;i++)
		{
			cin>>node[i][n+1].y;
			node[i][n+1].x=1.0;
		}

		/*Compute Intersection*/

		for(j=1;j<=n;j++)
			for(i=1;i<=n;i++)
			{
				intersection(node[0][j],node[n+1][j],node[i][0],node[i][n+1]);
				node[i][j].x=xx;
				node[i][j].y=yy;
			}

		/*Compute Area*/

		double max_area=0.0;

		for(i=1;i<=n+1;i++)
			for(j=1;j<=n+1;j++)
			{
				double temp=area(node[i-1][j-1],node[i][j],node[i][j-1],node[i-1][j]);
				if(max_area < temp)
					max_area = temp;
			}


		/*Output*/

		cout<<fixed<<setprecision(6)<<max_area<<endl;

		/*Realx Room*/

		delete[] node;
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

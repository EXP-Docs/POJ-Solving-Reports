## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2187] [[Beauty Contest](http://poj.org/problem?id=2187)]

> [Time: 3000MS] [Memory: 65536K] [难度: 初级] [分类: 凸包]

------

## 问题描述

给定平面上的一些散点集，求最远两点距离的平方值。


## 解题思路

别想着暴力枚举任意亮点距离找最大，行不通，想想**三点共线**吧！


**平面上的散点集的最远的两点距离必然在这个散点集的凸包的某两个顶点上出现**。

那么**先求凸包，再枚举顶点距离**就OK了。

别看是3000ms就想用简单的卷包裹，这题数据规模极大，**卷包裹**铁超（我一开始就是这么做的。。。） 万般无奈不得不用**Graham Scan Algorithm**。。。。O(nlogn)用来做这题还是相当可观的。

GrahamScan理解是不困难的，同学们百度搜搜就知道基本思想了：数据结构：栈。 而且每个点最多入栈出栈一次。


问题是用栈构造凸包之前要对散点集进行排序，水平序我不说了，我没看懂，听说很简单。我用的是**极坐标排序**。

利用**叉积的旋向** 配合 **比较排序** （如插入排序，冒泡，快排等）可以对极坐标排序，推荐用 `qsort()`，不要用冒泡之类的，太慢了，用Graham都是想快而已。



`qsort()` 难点在于 比较规则，（我的程序为cmp函数），必须把“qsort对cmp返回值的处理、cmp返回值、叉积旋向返回值”三者有机结合，否则一定排序出错，详见我的程序，有详细解释。

Cmp比较规则为“按极角大小逆时针排序，极角相等则近极坐标的点优先”。在网上看到有些童鞋在“极角相同”的情况下，利用第二关键字“距离”计算排序时，是通过计算两点的横坐标到 原点横坐标之差 作为判断“距离”依据。乍一看好像没错，也能AC，其实那是POJ数据库不强大，试试多点与原点的连线垂直于x轴的情况吧！


最后注意的：在使用 `qsort()` 之前，必须先找到 散点集中 最左下角的点，把它放在散点集数组的最后一个元素位，作为 极坐标原点（快排的参考点），否则排序也会出错。

 
其实只要 `qsort()` 的cmp函数能处理好了，基本这题就过了，难度不大。


## AC 源码


```c
//Memory Time 
//812K   469MS 

#include<iostream>
using namespace std;

const int inf=10001;

typedef class location
{
	public:
		int x,y;
}node;

/*点A到点B的距离的平方*/

int distsquare(node A,node B)
{
	return (B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y);
}

/*计算叉积*/

int det(int x1,int y1,int x2,int y2)
{
	return x1*y2-x2*y1;
}

int cross(node A,node B,node C,node D)
{
	return det(B.x-A.x , B.y-A.y , D.x-C.x , D.y-C.y);
}

/*qsort比较规则*/

node* p;  //极坐标原点
int cmp(const void* a,const void* b)
{
	node* s=(node*)a;
	node* t=(node*)b;

	int temp=cross(*p,*s,*p,*t);  //叉乘ps X pt 
	if(temp>0)    //说明pt向量的极角 小于 ps向量的极角
		return -1;  //从逆时针排序角度，t点位置在s点前面，即t<s ，根据qsort规则返回-1

	else if(temp==0) //说明pt向量的极角 等于 ps向量的极角
		return distsquare(*p,*t)-distsquare(*p,*s);  //距离原点近的点优先排序，用减法能够实现3出口：- 0 +
	                    //注意，网上有些程序在这里不是比较 距离之差，而是比较 横坐标绝对值 之差
	                    //这是欠缺考虑  多点与原点连线 垂直于x轴，不完善，之所以能AC是因为POJ的数据库不足够大而已
	else
		return 1; //pt向量的极角 大于 ps向量的极角
}

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		node* farm=new node[n+1];
		int* conbag=new int[n+2];  //conbag[]顺序记录输入的点中构造成凸包的顶点集的各点在farm[]中的下标

		/*Input & search the first vertex*/

		int min_x=inf;
		int fi=0;
		for(i=1;i<=n;i++)
		{
			cin>>farm[i].x>>farm[i].y;

			if(min_x > farm[i].x)
			{
				min_x = farm[i].x;   //先以横坐标为第一关键字搜索最左下角的点
				fi=i;
			}
			else if(min_x == farm[i].x)
			{
				if(farm[fi].y > farm[i].y)   //若第一关键字相同，则以纵坐标作为第二关键搜索
					fi=i;
			}
		}

		/*Quicksort Point Sets*/

		farm[0]=farm[n];   //这三步非常关键，是使用qsort前的准备工作
		farm[n]=farm[fi];  //目的是把前面找到的最左下角的点作为 极坐标原点
		farm[fi]=farm[0];  //即把第fi个点移到farm[]最后的位置,qsort则会把它作为排序的参考点

		p=&farm[n]; //极坐标原点传参

		qsort(farm+1,n,sizeof(node),cmp);  //farm[]散点集排序

		/*Graham Scan Algorithm*/

		int pc=1;  //conbag[]指针
		conbag[1]=n;  //(约定)极坐标原点 为凸包第1个顶点
		conbag[++pc]=1; //(在前面基础上,)有序点集farm[]的第一个点 (必)为凸包第2个顶点
		conbag[0]=2;   //凸包顶点计数器

		for(i=2;i<=n;)
			if(cross(farm[ conbag[pc-1] ],farm[ conbag[pc] ],farm[ conbag[pc] ],farm[i]) >= 0)
			{   //检查向量(前一点pc-1,当前点pc) 与 向量(当前点pc,待入栈点i) 的旋转关系
				conbag[++pc]=i++;  //入栈
				conbag[0]++;
			}
			else
			{
				pc--;         //当前点pc出栈
				conbag[0]--;
			}

		/*Search The Max distant*/

		int maxdist=0;
		for(i=1;i<=conbag[0]-2;i++)          //散点集的两点最大距离必定出现在该散点集的凸包的某两个顶点之间
			for(j=i+1;j<=conbag[0]-1;j++)
			{
				int temp=distsquare(farm[ conbag[i] ],farm[ conbag[j] ]);
				if(maxdist < temp)
					maxdist = temp;
			}

		/*Output*/

		cout<<maxdist<<endl;


		delete farm;
		delete conbag;
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

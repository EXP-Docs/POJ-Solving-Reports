## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1039] [[Pipe](http://poj.org/problem?id=1039)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 叉积/点积]

------

## 问题描述

有一宽度为1的折线管道,上面顶点为 `(xi,yi)`,所对应的下面顶点为 `(xi,yi-1)`,假设管道都是不透明的,不反射的,光线从左边入口处的 `(x1,y1)`, `(x1,y1-1)` 之间射入,向四面八方传播,求解光线最远能传播到哪里(取x坐标)或者是否能穿透整个管道。


## 解题思路

刘汝佳《**算法艺术与信息学艺术**》第三章 计算几何初步 的例2  P359 一模一样的题

(别人叫它**黑书**，小菜们看不懂什么意思，我稍微解释了，确实这书表面内里一般黑。。。)

把那本书3.1节读透了，就能理解这题了，但理解不一定会做

![](/reports/POJ1039-Pipe/img/01.png)


我第一次做计算几何的题，不看着模板根本做不下去，惭愧。。。。

纠结多天了，现在还对模板**利用叉积计算交点**的算法存在一个疑问。。。

要点难点我都注释在我的程序里了，程序模块分得很多，看着就习惯了


## AC 源码


```c
//Memory  Time 
//456K    63MS 

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

const double precision=1e-3;   //精度限制
const double inf=99999.0;   //正无穷，注意下面使用的是负无穷

typedef class Node    //折点坐标
{
public:
	double x;
	double y;
}point;

int max(int a,int b)
{
	return a>b?a:b;
}

/*把浮点p的值转化为0,1或-1  (精度讨论)*/

int dblcmp(double p)
{
	if(fabs(p)<precision)    // fabs()  浮点数的绝对值
		return 0;       //只要是在0的邻域，就认为是0

	return p>0?1:-1;
}

/*叉积运算*/

double det(double x1,double y1,double x2,double y2)
{
	return x1*y2-x2*y1;
}

/*计算P点在AB的左侧还是右侧（AC与AB的螺旋关系）*/

double cross(point A,point B,point P)
{
	return det(B.x-A.x , B.y-A.y , P.x-A.x , P.y-A.y);
}

/*判断直线AB、CD是否相交*/

bool check(point A,point B,point C,point D)
{
	return (dblcmp(cross(A,B,C)) * dblcmp(cross(A,B,D)) <= 0);
	//这里对黑书P353所述模板的相交约束条件做了修改
	//目的是允许 入射光线L 与 折点处垂线 不规范相交(即垂线的端点可以落在L上 或者 允许延长线相交)
}

/*计算直线AB、CD的交点横坐标*/
//本题这里传参是有讲究的，AB是代表光线L与管道的交点，CD是代表上管壁或者下管壁的端点
//之所以这样做，是因为AB与CD实质上是不相交的，是AB的延长线与CD相交
//按照上述传参顺序，根据修改后的模板，那么仅仅判断C、D是否在AB的两侧，就能计算 AB延长线与CD的交点
//倘若传参顺序错了，就会判断A、B是否在CD的两侧，但是AB一定是在CD同侧的，也就不能求交点了

double intersection(point A,point B,point C,point D)
{
	double area1=cross(A,B,C);
	double area2=cross(A,B,D);
	int c=dblcmp(area1);
	int d=dblcmp(area2);

	if(c*d<0) //CD在AB的两侧，规范相交
		return (area2*C.x - area1*D.x)/(area2-area1);  //黑书P357交点计算公式

	if(c*d==0)   //CD的其中一个端点在AB上，不规范相交
		if(c==0)
			return C.x;//C在AB上,返回AB与CD非规范相交时的交点C的横坐标
		else
			return D.x;//D在AB上,返回AB与CD非规范相交时的交点D的横坐标

	return -inf;  //CD在AB同侧，无交点,返回 负无穷
}

int main(int i,int j,int k)
{
	int n;    //折点数
	while(cin>>n)
	{
		if(!n)
			break;

		point* up=new point[n+1];         //上折点
		point* down=new point[n+1];       //下折点

		double max_x=-inf;  //最大可见度(管中最远可见点的横坐标)
		/*Input*/

		for(i=1;i<=n;i++)
		{
			cin>>up[i].x>>up[i].y;
			down[i].x=up[i].x;
			down[i].y=up[i].y-1;
		}

		bool flag=false;  //标记当前光线L(直线up[i]->down[j])能否贯通全管
		for(i=1;i<=n;i++) //枚举所有通过一个上折点、一个下折点的直线
		{
			for(j=1;j<=n;j++)
				if(i!=j)
				{
					for(k=1;k<=n;k++)     //直线L最大延伸到第k-1节管子
						if(!check(up[i],down[j],up[k],down[k]))   //up[k]->down[k]为折点处垂直x轴的直线
							break;

					if(k>n)
					{
						flag=true;
						break;
					}
					else if(k>max(i,j))  //由于不清楚L究竟是与第k-1节管子的上管壁还是下管壁相交，因此都计算交点，取最优
					{                   //举例：若实际L是与上管壁相交，当计算下管壁时，得到的是第k-1个下折点，并不会是最优
						                //反之亦同理 
						double temp=intersection(up[i],down[j],up[k],up[k-1]);
						if(max_x < temp)  //L与第k-1节管子的上管壁相交
							max_x=temp;

						temp=intersection(up[i],down[j],down[k],down[k-1]);
						if(max_x < temp)  //L与第k-1节管子的上管壁相交
							max_x=temp;
					}
				}

			if(flag)
				break;
		}

		if(flag)
			cout<<"Through all the pipe."<<endl;
		else
			cout<<fixed<<setprecision(2)<<max_x<<endl;

		/*Relax Room*/

		delete up,down;
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

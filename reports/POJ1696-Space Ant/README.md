## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1696] [[Space Ant](http://poj.org/problem?id=1696)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 凸包]

------

## 问题描述

一只蚂蚁,只会向左转,现在给出平面上很多个点,求解一种走法,

能使得蚂蚁能经过的点最多,每个顶点该蚂蚁只能经过一次,且所行走的路线不能发生交叉。


## 解题思路

**凸包**的入门水题，是凸包的一个变形

网上看到很多人copy别人的，说什么“**极坐标排序**”，那是Graham Scan Algorithm的做法！虽然**Graham**只有O(nlogn) ，但是这题完全没必要用它，因为题目的规模很小，我用卷包裹算法照样0 ms 一次AC 。确实理论上**卷包裹**的O(n^2)不如Graham快，但是规模这么小的题目是反映不出来的。

Graham能不用就不用，一代码超长超烦，特别是散点集排序。看过算法理论的同学，一般都宁愿用极坐标而不用水平序，但是极坐标排序的比较规则特容易出错。水平排序我没看懂，估计其他菜鸟们也差不多。


![](/img/01.jpg)

解题的例图题目已经给出，最终的路线就是螺旋形的。要求从 纵坐标 最小的点作为出发点，这个在输入时顺便找出来，可以节省一点点时间。

其实无论输入什么样的点集，一定可以走完全部n个点的，这是凸包的性质决定，所以就放手去做了，不用担心走不完的情况。
 

唯一注意的是，前面提到过时凸包的变形，是因为螺旋线是不封闭的，凸包是封闭的。要想不封闭很简单，做一个标记就可以了，每构造一个凸包顶点，就标记该点，不再与其连线

当连线完前面n-1个点后，第n个点（最后没被标记的点）就不用再做了，一定是最后一点，输出它就可以了

 
其他细节参见我的程序， **卷包裹算法** 百度就有了，这里我就不多说了


## AC 源码


```c
//Memory Time 
//228K   0MS 

#include<iostream>
using namespace std;

const int inf=101;

typedef class
{
	public:
		int x,y;
}point;

/*AB距离平方*/

int distsquare(point A,point B)
{
	return (B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y);
}

/*叉积计算*/

int det(int x1,int y1,int x2,int y2)
{
	return x1*y2-x2*y1;
}

int cross(point A,point B,point C,point D)
{
	return det(B.x-A.x , B.y-A.y , D.x-C.x , D.y-C.y);
}

int main(int i)
{
	int test;
	cin>>test;
	while(test--)
	{
		int n;   //n个点
		cin>>n;
		point* node=new point[n+1];  //n个点坐标
		int* conbag=new int[n+1];    //凸包顶点（根据顶点构造顺序，依次记录node[]下标）
		bool* vist=new bool[n+1];    //标记已作为凸包顶点的点

		/*Input*/

		int min_y=inf;    //最小纵坐标值
		int fi=0;
		for(i=1;i<=n;i++)
		{
			int num;
			cin>>num>>node[i].x>>node[i].y;
			vist[i]=false;

			if(min_y > node[i].y)
			{
				min_y = node[i].y;
				fi=i;
			}
		}
		conbag[1]=fi;  //起点
		conbag[0]=1;  //凸包顶点计数器
		vist[fi]=true;

		/*Structure Convex bag*/

		int pc=1;   //conbag[]指针
		while(true)
		{
			int s=conbag[pc];  //最新的凸包顶点
			int k;    //当前待加入的凸包顶点
			for(i=1;i<=n;i++)   //寻找当前基准向量sk,k取任意没标记的点就可以了
				if(!vist[i])
				{
					k=i;
					break;
				}

			for(i=1;i<=n;i++)   //枚举没标记的点i，计算sk X si的值，寻找最优（最外面的）k点作为凸包顶点
				if(i!=k && !vist[i])
				{
					int temp=cross(node[s],node[k],node[s],node[i]);

					if(temp<0)
						k=i;
					else if(temp==0)
						if(distsquare(node[s],node[k]) > distsquare(node[s],node[i]))  //当k i共线时，距离s近的点优先选取
							k=i;
				}

			conbag[++pc]=k;   //更新凸包顶点
			conbag[0]++;
			vist[k]=true;

			if(n-conbag[0]==1)   //处理完前面n-1个点后 第n个点不再处理
				break;
		}

		cout<<conbag[0]+1<<' ';  //这里输出n也可以的

		fi=0;
		for(i=1;i<=conbag[0];i++)
		{
			cout<<conbag[i]<<' ';   //输出前面n-1个点的同时寻找第n个没标记的点
			if(!vist[i])
				fi=i;
		}
		if(fi)
			cout<<fi<<endl;
		else
			cout<<n<<endl;

		delete node;
		delete conbag;
		delete vist;

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

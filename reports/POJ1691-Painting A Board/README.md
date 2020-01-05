## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1691] [[Painting A Board](http://poj.org/problem?id=1691)]

> [Time: 1000MS] [Memory: 10000K] [难度: 中级] [分类: 记忆化搜索]

------

## 问题描述

墙上有一面黑板，现划分为多个矩形，每个矩形都要涂上一种预设颜色C。

由于涂色时，颜料会向下流，为了避免处于下方的矩形的颜色与上方流下来的颜料发生混合，要求在对矩形i着色时，处于矩形i上方直接相邻位置的全部矩形都必须已填涂颜色。

在填涂颜色a时，若预设颜色为a的矩形均已着色，或暂时不符合着色要求，则更换新刷子，填涂颜色b。



**注意**：

- 1、 当对矩形i涂色后，发现矩形i下方的矩形j的预设颜色与矩形i一致，且矩形j上方的全部矩形均已涂色，那么j符合填涂条件，可以用 填涂i的刷子对j填涂，而不必更换新刷子。
- 2、 若颜色a在之前填涂过，后来填涂了颜色b，现在要重新填涂颜色a，还是要启用新刷子，不能使用之前用于填涂颜色a的刷子。
- 3、 若颜色a在刚才填涂过，现在要继续填涂颜色a，则无需更换新刷子。
- 4、 矩形着色不能只着色一部分，当确认对矩形i着色后，矩形i的整个区域将被着色。

首先要注意输入数据，每个矩形信息的输入顺序是 y x y x c，而不是 x y x y c

若弄反了x y坐标怎样也不会AC的.....


## 解题思路

**拓扑思想+DFS**

方法还是很直观的，把每个矩形看作一个点，处于黑板最上方的矩形i入度为0，然后从矩形i出发，与其下方直接相邻的矩形连线，这些矩形的入度+1。换而言之，矩形a上方直接相邻的矩形数upNum，就是矩形a（点a）的入度数upNum。

　当矩形i被涂色后，矩形i下方直接相邻的所有矩形的入度数-1。

　那么若一个矩形的入度数为0时，它就是待涂色状态；入度不为0则不允许涂色。

　然后就是按照题目要求的涂色限制条件，DFS涂色方案了，数据量较少，无需剪枝也能AC。


------


最后说说**怎样判定矩形a在矩形b的上方**。

矩形a与矩形b的基本位置关系共有3种，如下图：

![](/reports/POJ1691-Painting%20A%20Board/img/01.png)

设矩形左上角的坐标为 `(Lx，Ly)` 右下角的坐标为 `(Rx，Ry)`

则先判断 `Rect[a].Ry==Rect[b].Ly`，确定矩形a的底部和矩形b的顶部是否可能重合（直接相邻）


然后再判断3种情况：

- 情况1： `Rect[a].Lx>=Rect[b].Lx  &&  Rect[a].Lx<Rect[b].Rx`
- 情况2： `Rect[a].Lx<=Rect[b].Lx  &&  Rect[a].Rx>=Rect[b].Rx`
- 情况3： `Rect[a].Rx>Rect[b].Lx  &&  Rect[a].Rx<=Rect[b].Rx`

> 注意必须左右方向都要限制，其他特殊情况已由这3种关系所囊括。


## 测试数据

- 来源：[Tehran 1999 （问题B）](https://code.google.com/archive/p/djudge-core/downloads?page=4)
- 下载：[download](/reports/POJ1691-Painting%20A%20Board/testdata.zip)
- 输入：[input](/reports/POJ1691-Painting%20A%20Board/testdata/input.dat)
- 输出：[output](/reports/POJ1691-Painting%20A%20Board/testdata/output.dat)

## AC 源码


```c
//Memory Time 
//260K  0MS 

#include<iostream>
using namespace std;

struct rectangle
{
	int Lx,Ly;		 //左上角坐标 
	int Rx,Ry;		 //右下角坐标
	int SetColor;    //预设着色
	bool flag;		 //标记当前矩形是否已着色
	int UpNum;		 //该矩形上方的矩形数  (UpNum=0表示该矩形上方的矩形已全部被着色，该矩形为待着色状态)
	int low[16];     //指向该矩形下方的矩形
	int pl;          //low[]指针
};

class info
{
public:
	info(int n=0):N(n)
	{
		memset(color,false,sizeof(color));
		Rect=new rectangle[N+1];
		initial();

		MinBrushNum=20;   //最多只有15个矩形
		DFS(0,0,1);   //c==0表示当下对填涂的颜色暂无要求
	}
	~info()
	{
		cout<<MinBrushNum<<endl;
		delete[] Rect;
	}
	void initial(void);
	bool Judge_Upper(int a,int b);  //判断矩形a是否在矩形b上方
	void DFS(int n,int c,int b);   //n:当前已着色的矩形数，c:当前着色, b:当前正在用第b把刷子

protected:
	int N;			  //矩形数量
	rectangle* Rect;  //N个矩形的信息
	bool color[21];   //标记出现过的颜色
	int MinBrushNum;  //最少刷子数
};

void info::initial(void)
{
	for(int k=1;k<=N;k++)
	{
		cin>>Rect[k].Ly>>Rect[k].Lx;
		cin>>Rect[k].Ry>>Rect[k].Rx;
		cin>>Rect[k].SetColor;

		Rect[k].flag=false;
		Rect[k].UpNum=0;
		Rect[k].pl=0;

		color[ Rect[k].SetColor ]=true;
	}
	for(int i=1;i<N;i++)
		for(int j=i+1;j<=N;j++)
		{
			if(!Judge_Upper(i,j))  //若矩形i不在矩形j上方
				Judge_Upper(j,i);  //则判断矩形j是否在矩形i上方
		}
	return;
}

bool info::Judge_Upper(int a,int b)
{
	if(Rect[a].Ry==Rect[b].Ly)
	{
		if((Rect[a].Lx>=Rect[b].Lx && Rect[a].Lx<Rect[b].Rx) ||    //情况1
		   (Rect[a].Lx<=Rect[b].Lx && Rect[a].Rx>=Rect[b].Rx) ||   //情况2
		   (Rect[a].Rx>Rect[b].Lx && Rect[a].Rx<=Rect[b].Rx))	   //情况3
		{
			Rect[b].UpNum++;
			Rect[a].low[ Rect[a].pl++ ]=b;
			return true;
		}
	}
	return false;
}

void info::DFS(int n,int c,int b)
{
	if(n==N)
	{
		if(MinBrushNum > b)
			MinBrushNum = b;
		return;
	}

	if(c==0)  //填涂颜色为随意时，枚举上方矩形均已被涂色的未涂色矩形
	{
		for(int i=1;i<=N;i++)
		{
			if(!Rect[i].flag && Rect[i].UpNum==0)
			{
				int j;

				Rect[i].flag=true;
				for(j=0;j<Rect[i].pl;j++)   //第i个矩形下方的矩形的UpNum均-1
					Rect[ Rect[i].low[j] ].UpNum--;

				DFS(n+1,Rect[i].SetColor,b);  //下一次填涂的颜色与当次一样，则用同一把刷子

				Rect[i].flag=false;
				for(j=0;j<Rect[i].pl;j++)
					Rect[ Rect[i].low[j] ].UpNum++;
			}
		}
	}
	else  //填涂颜色为上次填涂的颜色
	{
		bool tag=false;
		for(int i=1;i<=N;i++)
		{
			if(Rect[i].SetColor==c && !Rect[i].flag && Rect[i].UpNum==0)
			{
				int j;
				tag=true;

				Rect[i].flag=true;
				for(j=0;j<Rect[i].pl;j++)   //第i个矩形下方的矩形的UpNum均-1
					Rect[ Rect[i].low[j] ].UpNum--;

				DFS(n+1,c,b);  //下一次填涂的颜色与当次一样，则用同一把刷子

				Rect[i].flag=false;
				for(j=0;j<Rect[i].pl;j++)
					Rect[ Rect[i].low[j] ].UpNum++;
			}
		}

		if(!tag)
			DFS(n,0,b+1);  //颜色为c的矩形均已补满足填涂条件，启用新刷子填涂其他颜色
	}
	return;
}

int main(void)
{
	int Case;
	cin>>Case;
	for(int c=1;c<=Case;c++)
	{
		int N;
		cin>>N;
		info POJ1691(N);
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

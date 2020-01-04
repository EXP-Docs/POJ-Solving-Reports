## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1027] [[The Same Game](http://poj.org/problem?id=1027)]

> [Time: 1000MS] [Memory: 10000K] [难度: 中级] [分类: 模拟法]

------

## 问题描述

在一个固定大小为10x15的矩形区域A内被RGB三种颜色的小球填满

现在按如下步骤操作：

- 1、 删除区域A内最大的一片区域M（任意颜色都可以，只要其占有区域最大）
- 2、 删除M后，自然会出现空的位置，在M区域上方的小球自然下落；
<br/>　当删除M后出现空列时，右边的列往左填充。
<br/>　注意是以“列”为单位填充，非空列只能整列往空列移动。
<br/>　移动后，各个小球之间的相对顺序 与 移动前一样。
- 3、 当区域A剩余小球数为0，或A内的最大区域为1时，游戏结束。否则返回1。

输出每一步的得分，最后输出总得分。


## 解题思路

没难度的**模拟题**，直接模拟就可以了，1次AC。

**关键**在于删除矩形区域M后的刷新地图操作。

寻找最大区域M，和删除M区域都是用**BFS**执行。


**题目要求**： 区域Z的坐标 = 在区域Z左下角的小球的坐标

因此为了对应坐标：

- 输入map时，行从 `9~0` 输入，列从 `0~14` 输入
- 搜索最大区域时，列从 `0~14` 优先搜索，行再从 `0~9` 搜索
- 输出坐标时记得行列+1


## AC 源码


```c
//Memory Time 
//264K   407MS 

#include<iostream>
using namespace std;

char map[10][16];
bool vist[10][15];
int MaxSize=-1;
char MaxColor;
int MaxR,MaxC;

void SearchMaxArea(void); //搜索当前地图的最大区域
int BFSArea(int i,int j);  //同色区域搜索，返回该区域的大小
void DelMaxArea(void); //删除最大区域
void RefreshMap(void);  //刷新地图

int main(void)
{
	int Game;
	cin>>Game;
	for(int g=1;g<=Game;g++)
	{
		for(int k=9;k>=0;k--)
			cin>>map[k];
		cout<<"Game "<<g<<':'<<endl<<endl;

		int step=0;
		int RemainBalls=150;
		int SumScore=0;
		while(true)
		{
			MaxSize=-1;
			SearchMaxArea();

			if(MaxSize==0 || MaxSize==1)
				break;

			DelMaxArea();
			RefreshMap();
			
			int score=(MaxSize-2)*(MaxSize-2);
			cout<<"Move "<<++step<<" at ("<<MaxR+1<<','<<MaxC+1<<"): ";
			cout<<"removed "<<MaxSize<<" balls of color "<<MaxColor<<", got "<<score<<" points."<<endl;

			RemainBalls-=MaxSize;
			SumScore+=score;
		}
		if(RemainBalls==0)
			SumScore+=1000;
		cout<<"Final score: "<<SumScore<<", with "<<RemainBalls<<" balls remaining."<<endl<<endl;
	}
	return 0;
}

/*搜索当前地图的最大区域*/
void SearchMaxArea(void)
{
	memset(vist,false,sizeof(vist));
	MaxSize=0;

	for(int j=0;j<15;j++)   //从左下角开始搜索
		for(int i=0;i<10;i++)
		{
			int size=0;
			if(!vist[i][j] && map[i][j])
			{
				size=BFSArea(i,j);
				if(MaxSize<size)      //记录最大区域的左下角坐标
				{
					MaxSize=size;
					MaxR=i;
					MaxC=j;
				}
			}
		}
	return;
}

/*同色区域搜索*/
int BFSArea(int i,int j)
{
	class
	{
	public:
		int x,y;
	}queue[151];

	int head,tail;
	queue[head=tail=0].x=i;
	queue[tail++].y=j;
	vist[i][j]=true;

	int size=0;
	char color=map[i][j];
	while(head<tail)
	{
		int x=queue[head].x;
		int y=queue[head++].y;
		size++;

		if(x+1<10 && !vist[x+1][y] && map[x+1][y]==color)  //上
		{
			vist[x+1][y]=true;
			queue[tail].x=x+1;
			queue[tail++].y=y;
		}
		if(x-1>=0 && !vist[x-1][y] && map[x-1][y]==color)  //下
		{
			vist[x-1][y]=true;
			queue[tail].x=x-1;
			queue[tail++].y=y;
		}
		if(y-1>=0 && !vist[x][y-1] && map[x][y-1]==color)  //左
		{
			vist[x][y-1]=true;
			queue[tail].x=x;
			queue[tail++].y=y-1;
		}
		if(y+1<15 && !vist[x][y+1] && map[x][y+1]==color)  //右
		{
			vist[x][y+1]=true;
			queue[tail].x=x;
			queue[tail++].y=y+1;
		}
	}
	return size;
}

/*删除最大区域*/
void DelMaxArea(void)
{
	class
	{
	public:
		int x,y;
	}queue[151];

	int head,tail;
	queue[head=tail=0].x=MaxR;
	queue[tail++].y=MaxC;

	MaxColor=map[MaxR][MaxC];
	map[MaxR][MaxC]=0;  //删除该格上的球

	while(head<tail)
	{
		int x=queue[head].x;
		int y=queue[head++].y;
		map[x][y]=0;

		if(x+1<10 && map[x+1][y]==MaxColor)  //上
		{
			map[x+1][y]=0;
			queue[tail].x=x+1;
			queue[tail++].y=y;
		}
		if(x-1>=0 && map[x-1][y]==MaxColor)  //下
		{
			map[x-1][y]=0;
			queue[tail].x=x-1;
			queue[tail++].y=y;
		}
		if(y-1>=0 && map[x][y-1]==MaxColor)  //左
		{
			map[x][y-1]=0;
			queue[tail].x=x;
			queue[tail++].y=y-1;
		}
		if(y+1<15 && map[x][y+1]==MaxColor)  //右
		{
			map[x][y+1]=0;
			queue[tail].x=x;
			queue[tail++].y=y+1;
		}
	}
	return;
}

/*刷新地图*/
void RefreshMap(void)
{
	bool empty[15]={false};
	int i,j;

	/*处理从上到下的移动*/
	for(j=0;j<15;j++)
	{
		bool flag=false;  //标记第j列是否全列为空
		int pi=-1;
		for(i=0;i<10;i++)
		{
			if(map[i][j])
			{
				flag=true;
				if(pi!=-1)
				{
					map[pi][j]=map[i][j];
					map[i][j]=0;
					i=pi;
					pi=-1;
				}
			}
			else
			{
				pi=i;
				while(i+1<10 && !map[i+1][j])
					i++;
			}
		}
		if(!flag)
			empty[j]=true;  //第j列为空
	}

	/*处理从右到左的移动*/
	int k=-1;
	for(j=0;j<15;j++)
	{
		if(!empty[j])
		{
			if(k!=-1)
			{
				for(int x=0;x<10;x++)
				{
					map[x][k]=map[x][j];
					map[x][j]=0;
				}
				empty[j]=true;
				j=k;
				k=-1;
			}
		}
		else
		{
			k=j;
			while(j+1<15 && empty[j+1])
				j++;
		}
	}

	return;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

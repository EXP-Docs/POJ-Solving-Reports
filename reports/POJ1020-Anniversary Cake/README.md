## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1020] [[Anniversary Cake](http://poj.org/problem?id=1020)]

> [Time: 1000MS] [Memory: 10000K] [难度: 中级] [分类: 搜索]

------

## 问题描述

有一块边长为BoxSize的正方形的大蛋糕，现在给出n块不同尺寸的正方形的小蛋糕的边长，问是否能把大蛋糕按恰好切割为这n块小蛋糕，要求每块小蛋糕必须为整块。


## 解题思路

**有技巧的DFS**。


可以把大蛋糕想象为一个蛋糕盒子，然后往里面装小蛋糕。

装蛋糕时遵循以下原则：

- 自下而上，自左至右：即先装好盒子底部，再继续往上层装，且装每一层时都靠左边放蛋糕；
- 大蛋糕优先装，因为小蛋糕灵活度比较高。

只要把问题变换为上述问题，我想对深搜比较熟悉的同学也会马上得到思路了，这个只是很简单的DFS思路。

------


但是**本题的难点不在于怎样去DFS，而是每放入一个蛋糕后，怎样去标记盒子已经放有蛋糕的位置**？

我初始的做这题时，因为看到数据规模不大（`Max_n=16`，`Max_size=10`，那么大蛋糕最大也就 `40*40` ），于是我把尺寸为BoxSize的盒子划分为 `BoxSize*BoxSize` 个 `1*1` 的格子，每放入一个大小为size的蛋糕，就用一个二重循环去标记 `size*size` 的格子。

最后是毫无悬念地TLE了。

看了别人的方法，发现或分格子的思路是正确的，但应该“按列标记”。不但把盒子看做多个 `1*1` 个格子，也把小蛋糕看做多个 `1*1` 的单位，建立一个一维数组 `col[ BoxSize ]` ，每放入一个蛋糕，则去记录每列的格子被填充的数目。

例如在第 `2~4` 列放入了一个 `size=3` 的小蛋糕，那么 `col[2]+=3`, `col[3]+=3`, `col[4]+=3`。

有同学会问，为什么行不用计数？要是放入蛋糕后，该蛋糕底部出现部分悬空怎么处理？这个情况是不会出现的，因为当前DFS遵循先把底部放满原则，要是出现悬空，则会回溯。

更具体的处理方法请看程序注释。


## 测试数据

- 来源（已失效）：[Tehran 2002, First Iran Nationwide Internet Programming Contest（问题E）](http://sina.sharif.edu/~acmicpc/acmicpc02/inipc/inipcprobs.html)
- 输入：[input](/reports/POJ1020-Anniversary%20Cake/testdata/input.dat)
- 输出：[output](/reports/POJ1020-Anniversary%20Cake/testdata/output.dat)



## AC 源码


```c
//Memory Time 
//208K  32MS 

#include<iostream>
using namespace std;

int BoxSize;      //盒子尺寸
int n;            //蛋糕的总个数
int SizeNum[11];  //各种尺寸的蛋糕个数
int col[41];      //把盒子纵行分割成BoxSize*BoxSize个1*1大小的小格子
                  //col[i]记录第i列被填充了的格子数

bool DFS(int FillNum)   //FillNum:已放入盒子的蛋糕数
{
	if(FillNum==n)
		return true;

	/*寻找格子数被填充最少的列，靠左优先*/
	int min=50;
	int prow;
	for(int i=1;i<=BoxSize;i++)
		if(min>col[i])
		{
			min=col[i];
			prow=i;
		}

	/*枚举各种尺寸的蛋糕自下而上地放入盒子*/
    for(int size=10;size>=1;size--)
	{
		if(!SizeNum[size])
			continue;

		//检查尺寸为size的蛋糕放入盒子时在纵向和横向是否越界
		if(BoxSize-col[prow]>=size && BoxSize-prow+1>=size)
        {
			//检查盒子从第prow列到第prow+size-1列，共size列的宽度wide中
			//是否每列剩余的空间都足够放入高度为size的蛋糕
            int wide=0;
            for(int r=prow;r<=prow+size-1;r++)
			{
				if(col[r]<=col[prow])  //比较各列的"填充数"
				{    //注意，这里若比较"未填充数"BoxSize-col[r]<size会TLE
					wide++;       //虽然两个条件等价，但确实计算了3秒左右，不知何故
					continue;
				}
				break;
			}

            if(wide>=size)
            {
				int r;
                //放入尺寸为size的蛋糕
				SizeNum[size]--;
				for(r=prow;r<=prow+size-1;r++)
					col[r]+=size;
			
				if(DFS(FillNum+1))
					return true;
 
				//回溯
				SizeNum[size]++;
				for(r=prow;r<=prow+size-1;r++)
					col[r]-=size;
            }
        }
	}
    return false;
}

int main(void)
{
	int test;
	cin>>test;
	for(int t=1;t<=test;t++)
	{
		memset(SizeNum,0,sizeof(SizeNum));
		memset(col,0,sizeof(col));

		cin>>BoxSize>>n;

		int cnt=0;   //记录size>(BoxSize/2)的蛋糕个数
		int area=0;  //计算所有蛋糕的面积之和
		for(int i=1;i<=n;i++)
		{
			int size;
			cin>>size;
			area+=size*size;
			SizeNum[size]++;

			if(size>BoxSize/2)
				cnt++;
		}

		if(cnt>1 || area!=BoxSize*BoxSize)
		{
			cout<<"HUTUTU!"<<endl;
			continue;
		}

		if(DFS(0))
			cout<<"KHOOOOB!"<<endl;
		else
			cout<<"HUTUTU!"<<endl;
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

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2676] [[Sudoku](http://poj.org/problem?id=2676)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 搜索]

------

## 问题描述

**九宫格问题**，也有人叫**数独问题**

把一个9行9列的网格，再细分为9个 `3*3` 的子网格，要求每行、每列、每个子网格内都只能使用一次 `1~9` 中的一个数字，即每行、每列、每个子网格内都不允许出现相同的数字。


0是待填位置，其他均为已填入的数字。

要求填完九宫格并输出（如果有多种结果，则只需输出其中一种）

如果给定的九宫格无法按要求填出来，则输出原来所输入的未填的九宫格。


## 解题思路

**DFS试探**，失败则回溯


用三个数组进行标记每行、每列、每个子网格已用的数字，用于剪枝：

```
bool row[10][10];    //row[i][x]  标记在第i行中数字x是否出现了
bool col[10][10];    //col[j][y]  标记在第j列中数字y是否出现了
bool grid[10][10];   //grid[k][x] 标记在第k个3\*3子格中数字z是否出现了
```

row 和 col的标记比较好处理，关键是找出grid子网格的序号与 行i列j的关系，

即要知道第i行j列的数字是属于哪个子网格的。


首先我们假设子网格的序号如下编排：

![](/reports/POJ2676-Sudoku/img/01.png)


由于 `1<=i`、 `j<=9`，我们有： （其中 `/` 是C++中对整数的除法）

![](/reports/POJ2676-Sudoku/img/02.png)


令 `a= i/3` , `b= j/3`  ，根据九宫格的 行列 与 子网格 的 关系，我们有:

![](/reports/POJ2676-Sudoku/img/03.png)



不难发现 `3a+b=k` 即 `3*(i/3)+j/3=k`

又我在程序中使用的数组下标为 `1~9`，grid编号也为 `1~9`

因此上面的关系式可变形为 `3*((i-1)/3)+(j-1)/3+1=k`

有了这个推导的关系式，问题的处理就变得非常简单了，直接DFS即可


## AC 源码


```c
//Memory Time 
//184K  422MS 

#include<iostream>
using namespace std;

int map[10][10]; //九宫格

bool row[10][10];    //row[i][x]  标记在第i行中数字x是否出现了
bool col[10][10];    //col[j][y]  标记在第j列中数字y是否出现了
bool grid[10][10];   //grid[k][x] 标记在第k个3*3子格中数字z是否出现了

                     //(这里说明的字母不代表下面程序中的变量)

bool DFS(int x,int y)
{
	if(x==10)
		return true;

	bool flag=false;

	if(map[x][y])
	{
		if(y==9)
			flag=DFS(x+1,1);
		else
			flag=DFS(x,y+1);

		if(flag)  //回溯
			return true;
		else
			return false;
	}
	else
	{
		
		int k=3*((x-1)/3)+(y-1)/3+1;

		for(int i=1;i<=9;i++)   //枚举数字1~9填空
			if(!row[x][i] && !col[y][i] && !grid[k][i])
			{
				map[x][y]=i;

				row[x][i]=true;
				col[y][i]=true;
				grid[k][i]=true;

				if(y==9)
					flag=DFS(x+1,1);
				else
					flag=DFS(x,y+1);

				if(!flag)   //回溯，继续枚举
				{
					map[x][y]=0;
					
					row[x][i]=false;
					col[y][i]=false;
					grid[k][i]=false;
				}
				else
					return true;
			}
	}
	return false;
}

int main(int i,int j)
{
	int test;
	cin>>test;
	while(test--)
	{
		/*Initial*/

		memset(row,false,sizeof(row));
		memset(col,false,sizeof(col));
		memset(grid,false,sizeof(grid));

		/*Input*/

		char MAP[10][10];
		for(i=1;i<=9;i++)
			for(j=1;j<=9;j++)
			{
				cin>>MAP[i][j];
				map[i][j]=MAP[i][j]-'0';

				if(map[i][j])
				{
					int k=3*((i-1)/3)+(j-1)/3+1;
					row[i][ map[i][j] ]=true;
					col[j][ map[i][j] ]=true;
					grid[k][ map[i][j] ]=true;
				}
			}

		/*Fill the Sudoku*/

		DFS(1,1);
		
		for(i=1;i<=9;i++)
		{
			for(j=1;j<=9;j++)
				cout<<map[i][j];
			cout<<endl;
		}
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

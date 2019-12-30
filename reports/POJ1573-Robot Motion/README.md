## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1573] [[Robot Motion](http://poj.org/problem?id=1573)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 模拟法]

------

## 问题描述

无。


## 解题思路

是模拟题，读懂题意直接模拟就可以了，没有算法，没有技术含量。


## AC 源码


```c
//Memory Time 
//256K   0MS 


#include<iostream>
using namespace std;

int main(void)
{
	int row,col,entry;
	char grid[12][12];     //在规定大小的grid外部至少再定义一圈"门槛"以判断Robot是否离开了grid  (最大grid为10x10)

	for(;;)
	{
		memset(grid,'O',sizeof(grid));     // 'O' 为大写字母O,意为 Out

		/*Input*/

		int i,j;

		cin>>row>>col>>entry;
		if(!(row && col && entry))break;

		for(i=1;i<=row;i++)
			for(j=1;j<=col;j++)
				cin>>grid[i][j];

			/*Judge Robot get out of the grid or starts a loop in the grid*/

			int flag[12][12]={0};   //标记Robot经过某点的次数，当有一点为2则说明Robot陷入了以该点为loop起始点的循环
			int count;
			int r=1;
			int c=entry;
			for(count=0;;count++)
			{
				flag[r][c]++;  //注意顺序，先标记，再位移
				if(grid[r][c]=='N')        // ↑
					r--;
				else if(grid[r][c]=='S')   // ↓
					r++;
				else if(grid[r][c]=='W')   // ←
					c--;
				else if(grid[r][c]=='E')   // →
					c++;
				else if(grid[r][c]=='O')        // Out
				{
					cout<<count<<" step(s) to exit"<<endl;
					break;
				}

				if(flag[r][c]==2)         //loop
				{
					row=r;           //标记Robot循环起止点
					col=c;
					int flg=1;
					for(r=1,c=entry,count=0;;count++)
					{
						if(r==row && c==col && flg==1)  //注意顺序，先寻找循环点再位移（避免Robot刚进入grid就陷入了循环的情况）
						{
							cout<<count<<" step(s) before a loop of ";        //输出进入循环前的步数
							count=0;
							flg++;
						}
						if(r==row && c==col && count!=0 && flg==2)
						{
							cout<<count<<" step(s)"<<endl;              //输出循环步数
							break;
						}
						if(grid[r][c]=='N')        // ↑
							r--;
				        else if(grid[r][c]=='S')   // ↓
							r++;
						else if(grid[r][c]=='W')   // ←
							c--;
						else if(grid[r][c]=='E')   // →
							c++;
					}
					break;    //跳出count的for循环
				}
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

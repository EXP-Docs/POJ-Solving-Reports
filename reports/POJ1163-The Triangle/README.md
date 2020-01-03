## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1163] [[The Triangle](http://poj.org/problem?id=1163)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

无。


## 解题思路

和 [POJ3176](/reports/POJ3176-Cow%20Bowling) 一模一样，不懂做这题的去看看我对 [POJ3176](/reports/POJ3176-Cow%20Bowling)  的解释。

不骗人，确实是一模一样的代码


## AC 源码


```c
//Memory Time 
//232K    0MS 

#include<iostream>
using namespace std;

int max(int a,int b)
{
	return a>b?a:b;
}

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		int **way=new int*[n+1];   //动态申请二维数组的第一维，每个元素都是一个一维数组的指针

		/*Input & Initial*/

		for(i=0;i<=n;i++)
		{
			way[i]=new int[i+2]; //动态申请二维数组的第二维，每一行的空间
			for(j=0;j<=i+1;j++)
				way[i][j]=0;   //不能用memset初始化

			if(i!=0)
				for(j=1;j<=i;j++)
					cin>>way[i][j];
		}

		/*Dp*/

		int max_weight=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=i;j++)
			{
				way[i][j] += max(way[i-1][j-1],way[i-1][j]);

				if(i==n && max_weight<way[i][j])
					max_weight=way[i][j];
			}

		cout<<max_weight<<endl;

		delete[] way;
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

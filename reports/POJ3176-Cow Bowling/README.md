## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3176] [[Cow Bowling](http://poj.org/problem?id=3176)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

输入一个n层的三角形，第i层有i个数，求从第1层到第n层的所有路线中，权值之和最大的路线。

规定：第i层的某个数只能连线走到第i+1层中与它位置相邻的两个数中的一个。


## 提示

用二维数组 `way[][]` 靠左存储三角形内的数据，那么连线规则变更为

`way[i][j] → Way[i+1][j]`

或 

`Way[i][j] → Way[i+1][j+1]`

**注意**： `way[][]` 初始化为输入时的三角形数值，此时 `way[i][j]` 表示该点位置上的权值，没输入的位置初始化为0。


## 解题思路

**动态规划**。

**`way[i][j]` 表示以第i行j列的位置作为终点的路线的最大权值**。 （注意区分初始化时的意义）

那么 `way[i][j]` 的最大值取决于 `way[i-1][j-1]` 和 `way[i-1][j]`，从这两者之间筛选出最大值，加到 `way[i][j]` 上，即为 `way[i][j]` 的最大权值。

最后只要比较第n行中所有位置的权值 `way[n][j]` ,最大的一个即为所求。



顺带一提，[POJ1163](/reports/POJ1163-The%20Triangle) 和这题是双子题，两道题基本一模一样，区别仅仅在于n的取值范围。所以说如果是用动态申请二维数组的同学，就可以直接把代码复制到POJ1163提交AC了。


------



再**顺便说一下动态申请二维数组的方法**。

C++的new函数是无法直接申请二维空间的，但是可以间接申请。

以我的程序为例，先申请一个“指向一维指针数组”的二维指针

`int **way=new int*[n+1];`

这个数组 `way[]` 的每一个元素都是一个指针

再利用for循环，逐行申请空间，使每一个元素（指针）指向一个“一维数组”

`Way[i]=new int[i+2];`   //这个大小是根据本题而决定的一个小优化，不同的题具体申请大小


这两次操作相当于先申请了二维数组way的行数，再逐行申请列数，这就相当于间接申请了一个二维数组，而且每行的列数还可以不同，优化了空间使用率。


## AC 源码


```c
//Memory Time 
//468K   172MS 

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

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3258] [[River Hopscotch](http://poj.org/problem?id=3258)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 二分法]

------

## 问题描述

一条河长度为 L，河的起点(Start)和终点(End)分别有2块石头，S到E的距离就是L。

河中有n块石头，每块石头到S都有唯一的距离

问现在要移除m块石头（S和E除外），每次移除的是与当前最短距离相关联的石头，要求移除m块石头后，使得那时的最短距离尽可能大，输出那个最短距离。


## 解题思路

**经典的二分**，理解题意就不怎么难了 （其实编程不难，要理解就非常难。。。。）

详细的解释看我的程序，实在看不懂就参考一下我 [POJ3273](/reports/POJ3273-Monthly%20Expense) 的做法，看上去不同，其实思路是差不多的，数学题都很难理解的，耐心吧。。。。

我感觉说了好像没说的感觉， 总之看程序吧


## AC 源码


```c
//Memory Time 
//420K   391MS 

#include<iostream>
#include<algorithm>
using namespace std;

int main(void)
{
	int L;  //河总长
	int n;  //河中石头数（除起点S和终点外E）
	int m;  //移除石头数

	while(cin>>L>>n>>m)
	{
		/*Input & Initial*/

		int* dist=new int[n+2];  //第i块石头到起点石头的距离为dist[i]
		dist[0]=0;    //起点S
		dist[n+1]=L;  //终点E

		int low=L;   //上界(一次跳跃的最短距离)
		int high=L;   //下界(一次跳跃的最大距离)
		for(int i=1;i<=n+1;i++)
		{
			if(i<=n)   //仅输入1~n，当i=n+1时仅用于寻找low
				cin>>dist[i];

			if(low > dist[i]-dist[i-1])
				low=dist[i]-dist[i-1];
		}

		sort(dist,dist+(n+2));   //根据石头到S的距离升序排列

		/*Binary-Search*/
		
		while(low<=high)
		{
			int mid=(low+high)/2;  //对最大跳和最小跳的距离折中，二分查找mid相对于最优解是偏大还是偏小
			                       //假设mid是移除m个石头后的最短距离

			int delrock=0;    //利用当前的mid值能移除的石头数
			int sum=0;   //类比POJ 3273, 这里是 连续距离的累加值
			             //当在第i个距离累加后sum

			for(int i=1;i<=n+1;)
			{
				if( (sum+=dist[i]-dist[i-1]) <= mid)
				{
					i++;
					delrock++;
				}
				else   //当从第i个距离累加到i+k个距离后，若sum>mid，则k个距离作为一段
				{
					i++;
					sum=0;  //sum置0，从第i+k+1个距离重新累加
				}
			}

			if(delrock<=m)   //本题难点之一：即使delrock==m也不一定找到了最优解
				low=mid+1;   //用当前mid值移除的石头数小于规定数，说明mid偏小
			else             
				high=mid-1;  //反之mid偏大
		}

		/*Output & Relax*/

		cout<<low<<endl;

		delete dist;
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

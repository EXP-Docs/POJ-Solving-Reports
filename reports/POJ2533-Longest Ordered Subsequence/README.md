## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2533] [[Longest Ordered Subsequence](http://poj.org/problem?id=2533)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 最长公共子序列]

------

## 问题描述

无。


## 解题思路

**动态规划**，求**LIS最大不下降子序列**

O(n^2)和O(n\*logn)算法都能完美AC

不懂的就去看看LIS的概念就会做了


## AC 源码

### 解题方法一：LIS - O(n^2)算法

```c
//Memory Time 
//228K   16MS 

//O(n^2)算法
#include<iostream>
using namespace std;

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		int* sq=new int[n];
		int* dp=new int[n];  //dp[i]表示以第i个位置为终点的最长不下降序列的长度

		for(i=0;i<n;i++)
			cin>>sq[i];

		int max_length=0;
		for(i=0;i<n;i++)
		{
			dp[i]=1;  //初始化dp[0]=1,其他最小值为1
			for(j=0;j<i;j++)
				if(sq[j]<sq[i] && dp[i]<dp[j]+1)
					dp[i]=dp[j]+1;

			if(max_length<dp[i])
				max_length=dp[i];
		}
		cout<<max_length<<endl;

		delete sq,dp;
	}
	return 0;
}
```

### 解题方法二：LIS - O(n^2)算法

```c
//Memory Time 
//224K   0MS 

//O(n*logn)算法
#include<iostream>
using namespace std;
const int inf=10001;

int binary_search(int ord[],int digit,int length)   //二分法搜索digit，若str中存在digit，返回其下标
{                                                   //若不存在，返回str中比digit小的最大那个数的（下标+1）
	int left=0,right=length;
	int mid;
	while(right!=left)
	{
		mid=(left+right)/2;
		if(digit==ord[mid])
			return mid;
		else if(digit<ord[mid])
			right=mid;
		else
			left=mid+1;
	}
	return left;
}

int main(int i,int j)
{
	int n;
	while(cin>>n)
	{
		int* sq=new int[n+1];
		int* ord=new int[n+1];  //对于dp[]的每一个取值k，ord[k]记录满足dp[i]=k的所有sq[i]中的最小值，即ord[k]=min{sq[i]} (dp[i]=k)

		for(i=1;i<=n;i++)
			cin>>sq[i];

		int max_length=0;
		ord[0]=-1;  //下界无穷小
		int len=1;  //ord的长度
		for(i=1;i<=n;i++)
		{
			ord[len]=inf;  //上界无穷大,指针len总是指向ord最后一个元素的后一位
			j=binary_search(ord,sq[i],len);
			if(j==len)  //sq[i]大于ord最大（最后）的元素
				len++;
			ord[j]=sq[i];
		}
		cout<<len-1<<endl; //len要减去ord[0]的长度1

		delete sq,ord;
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

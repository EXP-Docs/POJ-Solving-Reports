## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1159] [[Palindrome](http://poj.org/problem?id=1159)]

> [Time: 3000MS] [Memory: 65536K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

无。


## 解题思路

设 **原序列S的逆序列为S'，**则这道题目的关键在于:

**最少需要补充的字母数 = 原序列S的长度 —  S和S'的最长公共子串长度**

这个公式我不证明，不难证

剩下的就小意思了，最基础的**LCS**题。

**注意本题空间开销非常大，需要适当的处理手法**

------

先看看几种不同的申请空间方法的区别：

- 1、**静态数组** ：开销大小为 `5001*5001` 的int是铁定超的.（据说用short int的话不会MLE，有兴趣的同学可以试试）
- 2、**动态数组** ：单纯的申请动态数组是不能解决这个问题的，动态数组只能增加空间利用率，但是本题最恶劣的数组大小还是 `5001*5001`，动态数组是不能改变这个事实的
- 3、**滚动数组** ：这里重点讲一下滚动数组在这个题目中的应用。自己目前理解的应用滚动数组的目的就是减少空间开销。首先可以在纸上简单模拟一下DP的转移过程，确定好最少行数或者列数之后,**重点就是在如何进行"滚动"以及如何用表达式控制这个滚动**。

对于本题，我用的是**行数以 `0--1--0--1` 的滚动方式，滚动表达式为 `i%2` 和 `(i-1)%2`** ，没错，就是强大的**求余滚动**

由于应用了滚动数组，那么空间开销就能够从 `5001*5001` 压缩到 `2*5001` 。

而且本题我为了稍微提高一点空间利用率，使用了 **动态二维滚动数组**，就是东邪（动态）西毒（滚动）的混合体，这样做的目的，只是对测试数据库的数据抱有一点点希望：我相信它们不全都是 5000 的长度，所以我想能尽可能再节省一点列数….不过时间就惨不忍睹,1157ms….但是空间开销却由MLE跌落到谷底的280K

最后跪求传说中 300K 16ms代码………….


------


顺便贴一下**LCS的图解算法**

![](/reports/POJ1159-Palindrome/img/01.png)

```
s1：2 5 7 9 3 1 2

s2：3 5 3 2 8
```

一. 使用二維陣列

二. 記錄每一格的結果，是由哪一格而來

- 1、 陣列開頭均設為空
- 2、 `S1[i]=S2[j]` 相同，`dp[i][j]` 则继承左上方向 `dp[i-1][j-1]` 的值 `+1`
- 3、 不相同 `dp[i][j]` 则继承 上方與左方中的最大數值

最后整个二維陣列中最大的值，就是s1和s2的**最长公共子串长度**



## AC 源码


```c
//Memory Time 
//280K  1157MS 

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
		/*Input*/

		char* s1=new char[n+1];
		char* s2=new char[n+1];   //s1的逆序列

		int **dp=new int*[n+1];   //定义二维动态滚动数组（本题以01行滚动）
		dp[0]=new int[n+1];
		dp[1]=new int[n+1];
		dp[0][0]=dp[1][0]=0; //动态数组初始化 行开头为全0
			
		for(i=1,j=n;i<=n;i++,j--)
		{
			dp[0][i]=dp[1][i]=0;  //动态数组初始化 列开头为全0

			char temp;
			cin>>temp;
			s1[i]=s2[j]=temp;
		}

		/*Dp-LCS*/

		int max_len=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{
				if(s1[i]==s2[j])
					dp[i%2][j]=dp[(i-1)%2][j-1]+1;   //如果字符相等，则继承前一行前一列的dp值+1
				else
					dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]); //否则，取上方或左方的最大dp值

				if(max_len<dp[i%2][j])
					max_len=dp[i%2][j];
			}

		cout<<n-max_len<<endl;

		delete s1;
		delete s2;
		delete[] dp;
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

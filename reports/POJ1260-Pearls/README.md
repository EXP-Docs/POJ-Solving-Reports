## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1260] [[Pearls](http://poj.org/problem?id=1260)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

给出几类珍珠，以及它们的单价，要求用最少的钱就可以买到相同数量的，相同（或更高）质量的珍珠。

【规定买任一类的珍珠n个(价格为p)，都要支付 `(n+10)*p` 的钱，即额外支付 `10*p` 】


## 解题思路

例如样例Input的第二个例子：

```
3

1 10

1 11

100 12
```

需要买第一类1个，第二类1个，第三类100个

按常规支付为 `(1+10)*10 + (1+10)*11 + (100+10)*12 = 1551` 元（一共买了102个珍珠）

但是如果全部都按照第三类珍珠的价格支付，同样是买102个，而且其中总体质量还被提高了，但是价格却下降了： `(102+10)*12 = 1344` 元

 

而对于样例Input的第一个例子：

```
2

100 1

100 2
```

按常规支付为 `(100+10)*1 + (100+10)*2 =330` 元

但是全部按第二类珍珠的价格支付，同样买200个，虽然总体质量提升了，但是价格也提高了： `(202+10)*2=424` 元


------


**本题关键点**在于：

- （1）要求要买的珍珠的数量是一定的
- （2）所买的珍珠的质量允许提高，但不允许下降（即可以用高质量珍珠替代低质量）
- （3）输入时，后输入的珍珠价格一定比前面输入的要贵
- （4）由（2）（3）知，珍珠的替代必须是连续的，不能跳跃替代（这个不难证明，因为假如用第 `i+2` 类去替代第i类珍珠，会使最终的支付价格降低，那么用第 `i+1` 类去替代第i类珍珠会使最终的支付价格更加低）


**根据这4个约束条件，那么购买珍珠的方案为**：

在珍珠类型的总区间 `[1,c]` 中划分多个子区间，其中在闭区间 `i1~j1` 的珍珠全部按第j1类珍珠的价格p1支付，在闭区间 `i2~j2` 的珍珠全部按第j2类珍珠的价格p2支付，…在闭区间 `in~jn` 的珍珠全部按第jn类珍珠的价格pn支付。 这些区间互不相交。

其余珍珠按其原价支付。

要求找出最优的划分方案，使得最终支付价格最低。


**令 `dp[i]` 表示在已知第i类珍珠时,所需支付的最低价格**

则**状态方程**为：

- `dp[i]=(a[i]+10)*p[i]+dp[i-1];`  // 当第i种珍珠出现时，未优化价格的情况
- `dp[i]=min(dp[i],(sum[i]-sum[j]+10)*p[i]+dp[j]);`  // 枚举j，价格优化
- `dp[0]=0;`  // Dp初始化



## AC 源码


```c
//Memory Time 
//220K   0MS 

#include<iostream>
using namespace std;

int min(int a,int b)
{
	return a<b?a:b;
}

int main(int i,int j)
{
	int test;
	cin>>test;
	while(test--)
	{
		/*Input & Initial*/

		int c;
		cin>>c;

		int* a=new int[c+1];  //某类珍珠数目
		int* p=new int[c+1];  //某类珍珠单价
		int* dp=new int[c+1]; //dp[i]表示在已知第i类珍珠时,所需支付的最低价格
		int* sum=new int[c+1];//sum[i]=∑a[i]

		sum[0]=0;
		for(i=1;i<=c;i++)
		{
			cin>>a[i]>>p[i];
			sum[i]=sum[i-1]+a[i];
		}

		/*Dp*/

		dp[0]=0;  //Dp初始化
		for(i=1;i<=c;i++)
		{
			dp[i]=(a[i]+10)*p[i]+dp[i-1];   //当第i种珍珠出现时，未优化价格的情况
			for(j=0;j<i;j++)  //枚举第i种珍珠前的每一种珍珠，寻找最优价格
				dp[i]=min(dp[i],dp[j]+(sum[i]-sum[j]+10)*p[i]);  //在求dp[i]前，对于每一个j<i，dp[j]的最优值已求出
		}                                                        //(sum[i]-sum[j]+10)*p[i]即第j+1~i种珍珠被第i种珍珠替代后的价格
		cout<<dp[c]<<endl;

		delete a,p,dp,sum;
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

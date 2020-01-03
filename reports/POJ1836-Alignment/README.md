## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1836] [[Alignment](http://poj.org/problem?id=1836)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

这是 [POJ2533](/reports/POJ2533-Longest%20Ordered%20Subsequence) 的扩展题。

题意不难，令到原队列的最少士兵出列后，使得新队列任意一个士兵都能看到左边或者右边的无穷远处。就是使新队列呈三角形分布就对了。


## 解题思路

**这里有一个陷阱**，看了一些别人的解题报告说“任一士兵旁边不能存在等高的士兵”，然后又举了一个例子说注意

```
3

5 5 5
```

的情况，我没看他们的程序，不知道他们是不是把这些例子特殊处理了，但完全没必要，因为“允许处于三角形顶部的两个士兵等高”，图形化就是如下图：

![](/reports/POJ1836-Alignment/img/01.png)



**其实蓝色士兵的身高和红色士兵的身高是完全没有关系的**。

 
要求最少出列数，就是留队士兵人数最大，如图，即左边的递增序列人数和右边的递减序列人数之和最大

因而**可转化为**求“**最长不降子序列**”和“**最长不升子序列**”问题


但是**不能直接套用LIS思想**，因为这题**不允许任一侧**的序列中出现等高士兵


------

基本**操作方法**：

对士兵的身高数组逐一进行枚举，枚举到的k值作为蓝色士兵，k+1值作为红色士兵，以这两个士兵分别作为 **最长不降子序列L1** 的终点和 **最长不升子序列L2** 的起点，即作为整个队列的分界点。

然后分别对两边进行dp，枚举到某一个m值时，使得 `L1+L2` 的长度为最大max，此时用总士兵人数n 减去max就是  最少出列人数

------


本题**不能使用LIS的 `O(n^2)` 常规算法**，因为一旦应用到本题，由于队列存在两段序列，要对分界点进行枚举，会导致整体时间复杂度上升到 `O(n^3)`，绝对TLE超时

本题**只能用LIS的 `O(n*logn)` 算法**，具体算法步骤直接看LIS的相关介绍就有了，这里不再重复。需要注意的是**要使用不同的二分法查找LIS和LDS序列**，还要注意在二分查找记录数组 `ord[]`时，搜索的起点和终点位置，详细可以看我的程序。

最后就是要**注意** LIS和LDS长度，还有ord的初始化（程序中我是直接释放，再重新申请的）、边界问题，全部在我的程序中都有详细体现。


## 测试数据

- 输入：[input](/reports/POJ1836-Alignment/testdata/input.dat)
- 输出：[output](/reports/POJ1836-Alignment/testdata/output.dat)

## AC 源码


```c
//Memory Time 
//232K   391MS 

//O(n*logn)算法，注意LIS和LDS使用不同的二分法
#include<iostream>
using namespace std;
const int inf=3;

//ord[]为不降序列
//二分法搜索digit，若str中存在digit，返回其下标
//若不存在，返回str中比digit小的最大那个数的（下标+1）
int binary_search_1(double ord[],double digit,int head,int length)
{
	int left=head,right=length;
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

//ord[]为不升序列
//二分法搜索digit，若str中存在digit，返回其下标
//若不存在，返回str中比digit大的最小那个数的（下标+1）
int binary_search_2(double ord[],double digit,int head,int length)
{
	int left=head,right=length;
	int mid;
	while(right!=left)
	{
		mid=(left+right)/2;
		if(digit==ord[mid])
			return mid;
		else if(digit>ord[mid])
			right=mid;
		else
			left=mid+1;
	}
	return left;
}

int main(int i,int j)
{
	int n;  //士兵数
	while(cin>>n)
	{
		double* h=new double[n+1];

		for(i=1;i<=n;i++)
			cin>>h[i];

		int max=0;  
		for(int m=1;m<=n;m++)  //对身高队列每一个值作为分界点，进行枚举
		{
			double* ord=new double[n+1];

			/*Dp-(0~m)-LIS*/

			ord[0]=-1;  //下界无穷小
			int len_LIS=1;
			for(i=1;i<=m;i++)
			{
				ord[len_LIS]=inf; //上界无穷大
				j=binary_search_1(ord,h[i],0,len_LIS);
				if(j==len_LIS)  //sq[i]大于ord最大（最后）的元素
					len_LIS++;
				ord[j]=h[i];
			}
			len_LIS--; //减去ord[0]的长度1

			/*Dp-(m+1~n)-LDS*/

			ord[m]=inf;  //下界无穷大
			int len_LDS=1;
			for(i=m+1;i<=n;i++)
			{
				ord[m+len_LDS]=-1; //上界无穷小
				j=binary_search_2(ord,h[i],m,m+len_LDS);
				if(j==m+len_LDS)  //sq[i]大于ord最小（最后）的元素
					len_LDS++;
				ord[j]=h[i];
			}
			len_LDS--;  //减去ord[m]的长度1

			//max为对于当前m的 最长不升子序列LIS 和 最长不降子序列LDS 长度之和

			if(max<len_LIS+len_LDS)
				max=len_LIS+len_LDS;

			delete ord;
		}
		
		cout<<n-max<<endl;

		delete h;
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

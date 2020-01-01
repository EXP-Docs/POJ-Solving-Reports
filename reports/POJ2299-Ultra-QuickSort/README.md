## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2299] [[Ultra-QuickSort](http://poj.org/problem?id=2299)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 排序]

------

## 问题描述

给出长度为n的序列，每次只能交换相邻的两个元素，问至少要交换几次才使得该序列为递增序列。


## 解题思路

一看就是冒泡，交换一次记录一次就可以了。

但是n的范围达到50W，冒泡O(n^2)的复杂度铁定超时（即使有7000ms，其实这**是一个陷阱**）。

直接用快排又不符合题目的要求（相邻元素交换），快排是建立在二分的基础上的，操作次数肯定比在所要求的规则下的交换次数要更少。


那么该怎么处理？


其实这题题目已经给出提示了：Ultra-QuickSort

特殊的快排，能和快排Quicksort相媲美的就是 **归并排序Mergesort** 了，O(nlogn)


但是**用归并排序并不是为了求交换次数，而是为了求序列的 逆序数**（学过《线代》的同学应该很熟悉了）。

一个 【乱序序列的 逆序数】 = 【在只允许相邻两个元素交换的条件下, 得到有序序列的交换次数】 。


------------


例如例子的

9 1 0 5 4

由于要把它排列为上升序列，上升序列的有序就是  后面的元素比前面的元素大

而对于序列9 1 0 5 4

9后面却有4个比9小的元素，因此9的逆序数为4

1后面只有1个比1小的元素0，因此1的逆序数为1

0后面不存在比他小的元素，因此0的逆序数为0

5后面存在1个比他小的元素4, 因此5的逆序数为1

4是序列的最后元素，逆序数为0


因此序列9 1 0 5 4的逆序数 `t=4+1+0+1+0 = 6`  ，恰恰就是冒泡的交换次数



**注意**：

- 保存逆序数的变量t，必须要用 `__int64` 定义，`int` 和 `long` 都是无法保存的，会导致WA。 以前的 `long long` 在现在的VC编译器已经无法编译了。
- `__int64` 类型的输出必须使用指定的c格式输出，`printf(“%I64d”,t);`
- `cout` 是无法输出 `__int64` 类型的
- 序列数组 `s[]` 用 `int` 就足够了，每个元素都是小于10E而已


## AC 源码


```c
//Memory Time
//3768K 2422MS 

#include<iostream>
using namespace std;

const int inf=1000000000;  //10E

__int64 t; //s[]数列逆序数

void compute_t(int* s,int top,int mid,int end)
{
	int len_L=mid-top+1;
	int len_R=end-mid;

	int* left=new int[len_L+2];
	int* right=new int[len_R+2];

	int i,j;
	for(i=1;i<=len_L;i++)
		left[i]=s[top+i-1];
	left[len_L+1]=inf;   //设置无穷上界，避免比较大小时越界

	for(j=1;j<=len_R;j++)
		right[j]=s[mid+j];
	right[len_R+1]=inf;   //设置无穷上界，避免比较大小时越界

	i=j=1;
	for(int k=top;k<=end;)
		if(left[i]<=right[j])
			s[k++]=left[i++];
		else
		{
			s[k++]=right[j++];
			t+=len_L-i+1;    //计算逆序数
		}

	delete left;
	delete right;

	return;
}

void mergesort(int* s,int top,int end)
{
	if(top<end)
	{
		int mid=(top+end)/2;
		mergesort(s,top,mid);
		mergesort(s,mid+1,end);
		compute_t(s,top,mid,end);
	}
	return;
}

int main(void)
{
	int n;  //序列长度
	while(cin>>n)
	{
		if(!n)
			break;

		/*Input*/

		int* s=new int[n+1];
		for(int i=1;i<=n;i++)
			cin>>s[i];

		/*Merge-Sort*/

		t=0;  //initial
		mergesort(s,1,n);

		/*Output*/

		printf("%I64d\n",t);

		/*Relax*/

		delete s;

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

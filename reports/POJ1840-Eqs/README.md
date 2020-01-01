## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1840] [[Eqs](http://poj.org/problem?id=1840)]

> [Time: 5000MS] [Memory: 65536K] [难度: 初级] [分类: 高效查找法]

------

## 问题描述

给出一个5元3次方程，输入其5个系数，求它的解的个数

其中系数 `ai∈[-50,50]`  自变量 `xi∈[-50,0）∪（0,50]`


> **注意** ： 若 `x1=a, x2=b, x3=c, x4=d, x5=e` 时，与 `x1=b, x2=a, x3=c, x4=d, x5=e` 代入方程后都得到值0，那么他们视为不同的解。


## 解题思路

直观的思路：暴力枚举，O(n^5)

题目Time Limit=5000ms，1ms大约可以执行1000条语句，那么5000ms最多执行500W次

每个变量都有100种可能值，那么暴力枚举，5层循环，就是要执行100^5=100E次，等着TLE吧。。。。

 

**要AC这题，就要对方程做一个变形**：

![](/reports/POJ1840-Eqs/img/01.png)

等价于：

![](/reports/POJ1840-Eqs/img/02.png)


即先枚举x1和x2的组合，把所有出现过的 左值 记录打表，然后再枚举x3 x4 x5的组合得到的 右值，如果某个右值等于已经出现的左值，那么我们就得到了一个解

时间复杂度从 O(n^5)降低到 O(n^2+n^3)，大约执行100W次


------


我们先定义一个映射数组 `hash[]`，初始化为0

对于方程左边，当 `x1=m`,  `x2=n` 时得到sum，则把用 `hash[]` 记录sum : `hash[sum]++`，表示sum这个值出现了1次。

**之所以是记录“次数”，而不是记录“是否已出现”**，

是因为我们**不能保证**函数的映射为 **1对1 映射**，更多的是存在 **多对1映射**。

例如当 `a1=a2` 时，`x1=m`, `x2=n` 我们得到了sum，但 `x1=n`, `x2=m`时我们也会得到sum，但是我们说这两个是不同的解，这就是 多对1 的情况了，如果单纯记录sum是否出现过，则会使得 解的个数 减少。

 

其次，为了使得 搜索sum是否出现 的操作为o(1)，我们把sum作为下标，那么hash数组的上界就取决于a1 a2 x1 x2的组合，四个量的极端值均为50

因此上界为 `50*50^3+50*50^3=12500000`，由于sum也可能为负数，因此我们对 `hash[]` 的上界进行扩展，扩展到25000000，当 `sum<0` 时，我们令 `sum+=25000000` 存储到 `hash[]`

由于数组很大，必须使用全局定义。

同时由于数组很大，用int定义必然会MLE，因此要用char或者short定义数组，推荐short。


## AC 源码


```c
//Memory Time
//49188K 532MS 

#include<iostream>
using namespace std;

short hash[25000001];  //hash[sum]表示值等于sum的的解的个数(多对1映射)

int main(void)
{
	int a1,a2,a3,a4,a5;  //系数
	while(cin>>a1>>a2>>a3>>a4>>a5)
	{
		memset(hash,0,sizeof(hash));

		for(int x1=-50;x1<=50;x1++)
		{
			if(!x1)
				continue;
			
			for(int x2=-50;x2<=50;x2++)
			{
				if(!x2)
					continue;
				int sum=(a1*x1*x1*x1 + a2*x2*x2*x2)*(-1);
				if(sum<0)
					sum+=25000000;
				hash[sum]++;
			}
		}

		int solution=0;

		for(int x3=-50;x3<=50;x3++)
		{
			if(!x3)
				continue;
			for(int x4=-50;x4<=50;x4++)
			{
				if(!x4)
					continue;
				for(int x5=-50;x5<=50;x5++)
				{
					if(!x5)
						continue;
					int sum=a3*x3*x3*x3 + a4*x4*x4*x4 + a5*x5*x5*x5;
					if(sum<0)
						sum+=25000000;
					if(hash[sum])
						solution+=hash[sum];
				}
			}
		}

		cout<<solution<<endl;
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

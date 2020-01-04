## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1942] [[Paths on a Grid](http://poj.org/problem?id=1942)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 排列组合]

------

## 问题描述

给定一个矩形网格的长m和高n，其中m和n都是unsigned int32类型，一格代表一个单位，就是一步，求从左下角到右上角有多少种走法，每步只能向上或者向右走。


## 解题思路


非常水的中学数学题，用**组合**做。

先**简单建立一个数学模型**：

只要给定了长m和高n，那么要从左下角走到右上角，不管怎么走，一定要往右走m次，往上走n次。

例如给定 `m=5`, `n=4`

- 那么可以这样走： 上上上上上右右右右
- 又可以这样走： 上右上右上右上右上

等等。。。关键是“上”和“右”的先后问题，就是组合问题了。


**那么数学模型就是**

从n+m个位置，选择n个位放“上” （那么剩下m个位一定是“右”）

![](/reports/POJ1019-Number%20Sequence/img/01.png)


------

**处理阶乘有三种算法**：

- （1）传统意义上的**直接递归**，n的规模最多到20+，太小了，在本题不适用，而且非常慢
- （2）**稍快一点的算法，就是利用log()化乘为加**，n的规模虽然扩展到1000+，但是由于要用三重循环，一旦n规模变得更大，耗时就会非常之严重,时间复杂度达到 `O(n*m*(n-m))`，本题规定了n，m用unsigned int32类型，就是说n,m的规模达到了21E以上，铁定TLE的。而且就算抛开时间不算，还存在一个致命的问题，就是精度损失随着n的增加会变得非常严重。
因为n有多大，就要进行n次对数运算，n规模一旦过大，就会丢失得非常严重了。所以这种方法是绝对不可取的，因为中途的精度丢失不是简单的四舍五入可以挽回的。
- （3）**拆分阶乘，逐项相除，再乘以前面所有项之积**。这种方法用一个循环就OK了，时间复杂度只有 O(n-m)，非常可观。



下面我**根据程序详细说说算法（3）**：

```cpp
double cnm=1.0;
while(b>0)
	cnm*=(double)(a- -)/(double)(b- -);
```

**这是我写的函数原型，计算的是 aCb**

这种算法巧妙地利用了分子分母的关系，而不是把公示中的3个阶乘单独处理。

例如当 `a=5`, `b=2` 时：

![](/reports/POJ1019-Number%20Sequence/img/02.png)

由于用了 double去计算组合数，那么最后要转化为 无符号整型 时就要处理精度问题，**有两种方法**：**四舍五入+强制类型转换**  或者 **用 `setprecision()` 函数**

详细看我的两个程序。


## AC 源码

## 解题方法一：四舍五入+强制类型转换

```c
/*强制类型转换输出*/

//Memory Time 
//220K   0MS 

#include<iostream>
#include<math.h>
using namespace std;

/*Compute (n+m)C min{n,m}*/

unsigned comp(unsigned n,unsigned m)
{
	unsigned a=m+n;
	unsigned b=(m<n?m:n);
	double cnm=1.0;
	while(b>0)
		cnm*=(double)(a--)/(double)(b--);

    cnm+=0.5;      //double转unsigned会强制截断小数，必须先四舍五入
	return (unsigned)cnm;
}

int main(void)
{
	unsigned m,n;
	while(true)
	{
		cin>>m>>n;
		if(!m && !n)//承认这题的猥琐吧！竟然有其中一边为0的矩阵，一定要&&，用||会WA
			break;

		cout<<comp(n,m)<<endl;
	}
	return 0;
}
```

## 解题方法二：setprecision()函数+自定义精度输出

```c
/*自定义精度输出*/

//Memory Time 
//220K   0MS 

#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

/*Compute (n+m)C min{n,m}*/

double comp(unsigned n,unsigned m)
{
	unsigned a=m+n;
	unsigned b=(m<n?m:n);
	double cnm=1.0;
	while(b>0)
		cnm*=(double)(a--)/(double)(b--);

	return cnm;
}

int main(void)
{
	unsigned m,n;
	while(true)
	{
		cin>>m>>n;
		if(!m && !n)
			break;

		cout<<fixed<<setprecision(0)<<comp(n,m)<<endl;  
		//fixed是为了固定小数位数
		//setprecision()函数是会自动四舍五入的，所以不用像强制类型转换那样预先+0.5
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

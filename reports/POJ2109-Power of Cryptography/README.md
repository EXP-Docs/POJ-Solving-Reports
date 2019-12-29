# [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2109] [[Power of Cryptography](http://poj.org/problem?id=2109)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 高精度算法]

------

## 问题描述

无。

## 解题思路

见代码注释。

## AC 源码

> [Download Link](/reports/POJ2109-Power%20of%20Cryptography/src)


```c
/*
	Author:     Exp
	Date:       2017-12-07
	Code:       POJ 2109
	Problem:    Power of Cryptography
	URL:		http://poj.org/problem?id=2109
*/

/*
	【题意分析】
	   有指数函数 k^n = p ，
	   其中k、n、p均为整数且 1<=k<=10^9 , 1<=n<= 200 , 1<=p<10^101
	   给定 n 和 p ，求底数 k

	【解题思路】
	   考虑到数值存储问题和精度问题，这题最直观的思路应该是使用 高精度算法 求解。
	   而事实上，这题也可用公式法求解，但需要一些技巧。


	   开方公式：k = n-sqrt(p)
	   但C++的数学函数库并没有提供k次方的开方函数，此时需要转换一下公式：
	       k = p^(1/n)

	   对p开k次方等价于求p的1/k次方，此时我们就可以用pow函数求解了：
	       k = pow(p, 1.0/n)


	   其实严格来说，如果这题没有限制 底数k 是整数，就不可能通过公式投机取巧。
	   简单来说，如果要使用公式法，那么题目中所有运算都只能基于double类型进行（int会溢出）

	   double的取值范围为10^(-307)~10^308，但小数精度只有前16位（可自行搜索double的精度丢失问题）.
	   也是就说，当我们用double存储p的时候, 它就已经开始出现误差, 其误差范围在10^(-15)的数量级左右.

	   此时套用公式对p开n次方根，须知开方运算是不会扩大误差范围的，
	   所以 n-sqrt(p) 的小数位误差范围依旧在10^(-15)的数量级以内，
	   又因为 k = n-sqrt(p) ，亦即计算所得的 n 的小数位误差范围也在10^(-15)的数量级以内,
	   显然这个误差级数仅会对n的小数部分存在影响，四舍五入后对整数部分是无影响的.
	   而题目已经限定了，n、k、p均是整数，因此使用公式法可以直接得到准确结果.

	   假若题目不存在整数限制，当n极大时，k会极小（无限迫近1，对小数精度极高），
	   此时公式法则会因为精度问题而失效.

*/

#include <math.h>
#include <iostream>
using namespace std;

int main(void) {
	double n , p;
	while(cin >> n >> p) {
		double tmp = pow(p, 1 / n);	// p开n次方
		int k = floor(tmp + 0.5);	// 四舍五入（+0.5后向下取整）
		cout << k << endl;
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

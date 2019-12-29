## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1003] [[Hangover](http://poj.org/problem?id=1003)]

> [Time: 1000MS] [Memory: 10000K] [难度: 水题] [分类: 无]

------

## 问题描述

无。

## 解题思路

见代码注释。

## AC 源码

> [Download Link](/reports/POJ1003-Hangover/src)


```c
/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1003
	Problem:    Hangover
	URL:		http://poj.org/problem?id=1003
*/

/*
    根据题意可建立以下数学模型：
	 令 ∑(1/n) >= c
	 其中 n∈[2, ∞), c∈[0.01, 5.20]且其精度含小数在内最多3个数字
	 给定c 求 n （若c在范围外，则不求解）

	分析：
	 本质就是变种的调和数列求和（数列中缺少1）
	 但调和数列是发散的，不存在准确的求和公式，只有近似公式：
	  调和数列 ∑(1/n) ~ ln(n+1) + R
	  其中 n∈[1, ∞), R为欧拉常数(R = 0.5772156649...)

	 但近似公式只有在n非常大的时候误差才可以忽略不计，
	 当n很小时，对本题而言误差是不可接受的。

	 因此本题用常规解法即可
	 （由于前n项和是固定的，用打表法也可, 不过题目考核范围较小，打表意义也不大）
*/



#include <iostream>
using namespace std;

/* 
 * 根据调和数列的和值反求项数
 * @param sum 目标和值
 * return 调和数列项数
 */
int harmonicSeries(double sum);


int main(void) {
	double sum = 0.0;
	while(true) {
		cin >> sum;
		if(sum < 0.01 || sum > 5.20) {
			break;
		}

		int n = harmonicSeries(sum);
		cout << n << " card(s)" << endl;
	}
	return 0;
}


int harmonicSeries(double sum) {
	int n = 2;
	double curSum = 0.0;
	while(curSum < sum) {
		curSum += (1.0 / n++);
	}
	return n - 2;	// n从2开始因此项数-1, 最后一次求和多了一次n++也要-1， 因此共-2
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

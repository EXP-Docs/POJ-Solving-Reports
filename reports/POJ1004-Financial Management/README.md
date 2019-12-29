## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1004] [[Financial Management](http://poj.org/problem?id=1004)]

> [Time: 1000MS] [Memory: 10000K] [难度: 水题] [分类: 无]

------

## 问题描述

无。

## 解题思路

2011年5月ACM珠海赛的试机题

水题，直接求解即可。

## AC 源码

> [Download Link](/reports/POJ1004-Financial%20Management/src)


```c
/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1004
	Problem:    Financial Management
	URL:		http://poj.org/problem?id=1004
*/

/*
	题意分析：
	 每次输入12个浮点数，求其平均数（注意输出精度为2位小数）
*/

#include <iomanip>
#include <iostream>
using namespace std;


int main(void) {
	const int N = 12;
	double sum = 0.0;

	for(int i = 0; i < N; i++) {
		double num = 0.0;
		cin >> num;
		sum += num;
	}

	double avg = sum / N;
	cout << fixed << setprecision(2) << '$' << avg << endl;

	//system("pause");
	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

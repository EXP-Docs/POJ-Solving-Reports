# [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1207] [[The 3n + 1 problem](http://poj.org/problem?id=1207)]

> [Time: 1000MS] [Memory: 10000K] [难度: 水题] [分类: 无]

------

## 问题描述

根据给定的算法，可以计算一个整数的循环数

现在给定一个区间，计算这个区间的所有数的循环数，把最大的循环数输出（输出的是整数 A 的循环数，而不是输出整数 A）


## 解题思路

注意的只有一点：

输入的两个区间端点不一定是从小到大输入的，因此要先对这两个数排一下序。

## AC 源码

> [Download Link](/reports/POJ1207-The%203n%20plus%201%20problem/src)


```c
/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1207
	Problem:    The 3n plus 1 problem
	URL:		http://poj.org/problem?id=1207
*/

/*
	题意分析：
	 给定了计算整数n的所有循环数算法（循环数列包括n自身）：
	 1. 	 input n
	 2. 	 print n
	 3. 	 if n = 1 then STOP
	 4. 		 if n is 奇数 then   n = 3n+1
	 5. 		 else   n = n/2
	 6. 	 GOTO 2

	 再给定范围 [i, j] 且 i,j∈(0,10000)
	 求 [i, j] 之间拥有最多循环数的整数n的循环数的个数
*/

#include <iostream>
using namespace std;


/* 
 * 计算整数的循环数个数
 * @param num 整数
 * return 循环数个数
 */
int cycleCnt(int num);


int main(void) {
	int i, j;
	while(cin >> i >> j) {
		int min = (i <= j ? i : j);
		int max = (i > j ? i : j);

		int maxCnt = -1;
		for(int n = min; n <= max; n++) {
			int cnt = cycleCnt(n);
			maxCnt = (maxCnt < cnt ? cnt : maxCnt);
		}
		cout << i << " " << j << " " << maxCnt << endl;
	}

	//system("pause");
	return 0;
}


int cycleCnt(int num) {
	int cnt = 1;
	while(num > 1) {
		if(num % 2 == 1) {
			num = 3 * num + 1;

		} else {
			num /= 2;
		}
		cnt++;
	}
	return cnt;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

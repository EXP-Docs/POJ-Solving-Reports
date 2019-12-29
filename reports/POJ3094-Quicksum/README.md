## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3094] [[Quicksum](http://poj.org/problem?id=3094)]

> [Time: 1000MS] [Memory: 10000K] [难度: 水题] [分类: 无]

------

## 问题描述

无。

## 解题思路

见代码注释。

## AC 源码

> [Download Link](/reports/POJ3094-Quicksum/src)


```c
/*
	Author:     Exp
	Date:       2017-12-01
	Code:       POJ 3094
	Problem:    Quicksum
	URL:		http://poj.org/problem?id=3094
*/

/*
	题意分析：
	 计算只含[大写字母+空格]的字符串的校验和.
	 其中每个字母有其对应的特征值，空格=0,A=1,B=2,...,Z=26
	 校验和 = 所有 [字符的位置(从1开始) * 字母特征值] 之和

*/


#include <memory.h>
#include <iostream>
using namespace std;


// 被校验字符串的最大长度
const static int MAX_LEN = 255;

/* 
 * 获取字符的特征值
 * @param c 字符
 * return 特征值
 */
int getFeatureVal(char c);


int main(void) {
	char str[MAX_LEN] = { '\0' };
	while(true) {
		gets(str);	// 输入字符串中包含空格，不能用cin接收
		int len = strlen(str);
		if(strlen(str) <= 0 || str[0] == '#') {
			break;
		}

		int quicksum = 0;
		for(int i = 0; i < len; i++) {
			quicksum += ((i + 1) * getFeatureVal(str[i]));
		}
		cout << quicksum << endl;

		memset(str, '\0', sizeof(char) * len);
	}
	return 0;
}


int getFeatureVal(char c) {
	return (c == ' ' ? 0 : (c - 'A' + 1));
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

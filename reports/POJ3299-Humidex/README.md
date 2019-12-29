## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3299] [[Humidex](http://poj.org/problem?id=3299)]

> [Time: 1000MS] [Memory: 65536K] [难度: 水题] [分类: 无]

------

## 问题描述

无。

## 解题思路

纯粹的数学公式，直接求解即可。

## AC 源码

> [Download Link](/reports/POJ3299-Humidex/src)


```c
/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 3299
	Problem:    Humidex
	URL:		http://poj.org/problem?id=3299
*/

/*
	题意分析：
	 已知温度转换公式：
	  humidex = temperature + h
	  h = (0.5555)× (e - 10.0)
	  e = 6.11 × exp [5417.7530 × ((1/273.16) - (1/(dewpoint+273.16)))]

	令 H = humidex，temperature = T，dewpoint = D， 其中 H,T,D ∈ [-100, 100]
	给定其中两个，求另一个 (输出精度为1位小数)
*/

#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

const static char T = 'T';
const static char D = 'D';
const static char H = 'H';
const static char E = 'E';
const static double INVALD_VAL = 999.0;	// 所有参数取值范围为[-100, 100]


/* 
 * 根据公式以及其中两个参数，求解第三个参数
 * @param nT 参数T，可能为无效值
 * @param nD 参数D，可能为无效值
 * @param nH 参数H，可能为无效值
 * return 第三个参数值
 */
void solve(double *nT, double *nD, double *nH);	// POJ上的C++编译器不支持&引用传值, 只能用指针


int main(void) {

	while(true) {
		bool isEnd = false;
		char letter = E;
		double nT, nD, nH;
		nT = nD = nH = INVALD_VAL;

		for(int i = 0; !isEnd && i < 2; i++) {
			cin >> letter;
			switch(letter) {
				case T: { cin >> nT; break; }
				case D: { cin >> nD; break; }
				case H: { cin >> nH; break; }
				default: { isEnd = true; break; }
			}
		}

		if(isEnd == true) {
			break;

		} else {
			solve(&nT, &nD, &nH);
			cout << fixed << setprecision(1) << "T " << nT << " D " << nD << " H " << nH << endl;
		}
	}
	return 0;
}


void solve(double *nT, double *nD, double *nH) {
	if(*nH == INVALD_VAL) {
		*nH= *nT + 0.5555 * (6.11 * exp(5417.7530 * ( 1.0 / 273.16 - 1.0 / (*nD + 273.16))) - 10.0);

	} else if(*nT == INVALD_VAL) {
		*nT= *nH - 0.5555 * (6.11 * exp(5417.7530 * ( 1.0 / 273.16 - 1.0 / (*nD + 273.16))) - 10.0);

	} else {
		*nD= 1.0 / ((1.0 / 273.16) - ((log((((*nH - *nT) / 0.5555) + 10.0) / 6.11)) / 5417.7530)) - 273.16;
	}
}

```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

# [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1005] [[I Think I Need a Houseboat](http://poj.org/problem?id=1005)]

> [Time: 1000MS] [Memory: 10000K] [难度: 水题] [分类: 无]

------

## 问题描述

Fred Mapper 正在考虑在路易斯安那州购买一些土地来建他自己的房子。在研究土地的过程中，他发现，路易斯安那州的土地每年都会被密西西比河侵蚀掉 50 平方里。因为 Fred 希望在这个房子里度过余生，所以他需要知道他的那些土地是否会被侵蚀掉。

在做了更多的调查之后，Fred 发现这些土地是以半圆的形状被侵蚀的。这个半圆所对应的正圆的圆心在坐标原点 `(0, 0)`, 坐标轴 x 轴将这个圆切成两半。在 x 轴下方的区域是河流。在第一年刚开始的时候，这个半圆的面积是 0.


![红色为侵蚀方向,蓝色为河水](/reports/POJ1005-I%20Think%20I%20Need%20a%20Houseboat/src/img/01.png)

问输入Fred Mapper家的坐标 `(x, y)`，他家所在的位置什么时候被河水侵蚀。


## 解题思路

Fred Mapper 的家 `(x, y)` 到侵蚀中心 `(0, 0)` 的距离就是侵蚀半径 R

那么 `Area = 1/2 * pi * R` 就是侵蚀到 Fred Mapper 家时的侵蚀面积

而侵蚀速度为每年 50

那么侵蚀到Fred Mapper家需要 `RestYear = Area / 50 = pi * R / 100` 年

又要求从第一年开始计算，最后一年不够一年按一年计算，那么 `RestYear + 1` 取整就可以了。


## AC 源码

> [Download Link](/reports/POJ1005-I%20Think%20I%20Need%20a%20Houseboat/src)


```c
/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1005
	Problem:    I Think I Need a Houseboat
	URL:		http://poj.org/problem?id=1005
*/

/*
	根据题意建立数学模型如下：
	  位于平面坐标第一二象限的一个半圆从原点(0,0)开始向(x,y)扩散，每次扩散50平方
	  求第几次扩散会覆盖到(x,y)， 其中y>0

	  勾股定理半径 R^2 = (x-0)^2 + (y-0)^2
	  半圆面积公式 Area = pi * R^2 / 2
	  当 Area 是 50 整数倍时, 扩散次数 cnt = Area / 50
	  当 Area 不是 50 整数倍时, 扩散次数 cnt = Area / 50 + 1	（亦即向上取整）
*/

#include <math.h>
#include <iostream>
using namespace std;

const static double PI = 3.141592654;	// 常量π
const static double HALF_PI = PI / 2;	// 半圆面积公式常量
const static double EACH_AREA = 50;	// 每次扩散面积

/* 
 * 求解扩散次数
 * @param x 扩散坐标x
 * @param y 扩散坐标y
 * return 扩散次数
 */
int diffuse(double x, double y);


int main(void) {
	int testCase = 0;	// 测试用例数
	cin >> testCase;

	for(int i = 1; i <= testCase; i++) {
		double x, y;
		cin >> x >> y;
		int cnt = diffuse(x, y);
		cout << "Property " << i << ": This property will begin eroding in year " << cnt << '.' << endl; 
	}
	cout << "END OF OUTPUT." << endl;

	//system("pause");
	return 0;
}


int diffuse(double x, double y) {
	double R2 = x * x + y * y;
	double Area = HALF_PI * R2;
	return (int) ceil(Area / EACH_AREA);	// 向上取整
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

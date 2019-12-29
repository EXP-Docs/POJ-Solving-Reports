# [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2586] [[Y2K Accounting Bug](http://poj.org/problem?id=2586)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 贪心]

------

## 问题描述

无。

## 解题思路

见代码注释。

## AC 源码

> [Download Link](/reports/POJ2586-Y2K%20Accounting%20Bug/src)


```c
/*
	Author:     Exp
	Date:       2017-12-25
	Code:       POJ 2586
	Problem:    Y2K Accounting Bug
	URL:		http://poj.org/problem?id=2586
*/

/*
	题意分析：
	 已知一个公司在某一年中，【每个月要么固定盈利s、要么固定亏损d】。
	 但是具体哪个月盈利、那个月亏损却不得而知。
	 不过可以肯定的是，这一年中，【任意的连续5个月盈亏和必定是亏损（< 0）】。
	 问这年是否存在盈利的可能，若可能盈利，【最大的盈利额】是多少？


    解题思路：
	  要求全年最大盈利额，最理想的情况是每月盈利，即12s
	  但这里有个大前提：【任意的连续5个月盈亏和必定是亏损】
	  
	  因此这题可用贪心法去求解：
	    从1月份开始，选择当月是盈或亏，但尽可能选择为盈利，
	      当且仅当无法满足【连续5月必亏损】这个条件时，当月才选择亏损


	  由于组合情况较少，可以把每5个月的所有盈亏组合情况列举出来：
      ① 当 s >= 4d 时 （即1个月的盈利抵得上4个月的亏损），
          无论如何组合，都无法满足【连续5月必亏损】的前提，
          因此为了满足这种情况，只可能所有月份均亏损
          即亏损月份为 [1-12]
	      全年无利润

      ② 当 s < 4d （但2s >= 3d） 时 （即1个月的盈利刚好小于4个月的亏损）,
		  此时只需保证每连续5个月至少有4个月是亏损即可，
		  根据贪心逻辑，全年盈亏月份为：sddddsddddsd
		  即盈利月份为 1、6、11
		    亏损月份为 [2-5]、[7-10]、12
		  全年最大利润为: 3s - 9d

      ③ 当 2s < 3d （但3s >= 2d）时 （即2个月的盈利刚好小于3个月的亏损）,
		  此时只需保证每连续5个月至少有3个月是亏损即可，
		  根据贪心逻辑，全年盈亏月份为：ssdddssdddss
		  即盈利月份为 [1-2]、[6-7]、[11-12]
		    亏损月份为 [3-5]、[8-10]
		  全年最大利润为: 6s - 6d

      ④ 当 3s < 2d （但4s >= d）时 （即3个月的盈利刚好小于2个月的亏损）,
		  此时只需保证每连续5个月至少有2个月是亏损即可，
		  根据贪心逻辑，全年盈亏月份为：sssddsssddss
		  即盈利月份为 [1-3]、[6-8]、[11-12]
		    亏损月份为 [4-5]、[9-10]
		  全年最大利润为: 8s - 4d

      ⑤ 当 4s < d 时 （即4个月的盈利刚好小于1个月的亏损）,
		  此时只需保证每连续5个月至少有1个月是亏损即可，
		  根据贪心逻辑，全年盈亏月份为：ssssdssssdss
		  即盈利月份为 [1,4]、[6-9]、[11-12]
		    亏损月份为 5、10
		  全年最大利润为: 10s - 2d


*/

#include <iostream>
using namespace std;

int main(void) {
	int s, d;
	while(cin >> s >> d) {

		int surplus = 0;	// 全年盈余
		if(4 * s < d) {
			surplus = 10 * s - 2 * d;
			
		} else if(3 * s < 2 * d) {
			surplus = 8 * s - 4 * d;

		} else if(2 * s < 3 * d) {
			surplus = 6 * s - 6 * d;

		} else if(s < 4 * d) {
			surplus = 3 * s - 9 * d;

		} else {
			surplus = -1;
		}

		if(surplus < 0) {
			cout << "Deficit" << endl;
		} else {
			cout << surplus << endl;
		}
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

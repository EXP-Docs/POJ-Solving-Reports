## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2739] [[Sum of Consecutive Prime Numbers](http://poj.org/problem?id=2739)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 素数]

------

## 问题描述

无。

## 解题思路

本题用一般的素数求法就可以做出来了，虽然可以AC，不过时间复杂度很大。

因此建议优化算法，优化的过程可以参考 [POJ-2262](/reports/POJ2262-Goldbachs%20Conjecture)。

## AC 源码

> [Download Link](/reports/POJ2739-Sum%20of%20Consecutive%20Prime%20Numbers/src)


```c
/*
	Author:     Exp
	Date:       2017-11-30
	Code:       POJ 2739
	Problem:    Sum of Consecutive Prime Numbers
	URL:		http://poj.org/problem?id=2739
*/

/*
	题意分析：
	 一个整数n有时可以被写成若干个连续素数之和的序列。
	 给定一个整数n，求出这些序列的个数（若n自身也是素数，则也算其中一种序列），其中n∈[2,10000]

	解题思路：
	 主要分两步走：
	 ① 求出10000以内所有素数
	 ② 在素数表中找出可以通过连续求和得到n的若干种组合


	 第①步只需要打表做一次即可，如何快速找到10000内的所有素数。
	 关于素数的求解方法，不外乎用到：
	  定义：只能被1或者自身整除的自然数（不包括1），称为素数
	  定理：如果一个数k是合数，那么它的最小质因数肯定<=sqrt(k) 
	        由于一个自然数若不是合数则必是素数，这个定理可以反过来用于素数：
			如果一个数k是素数, 那么k必不能被<=sqrt(k)的所有整数整除
	  算法：埃拉托斯特尼筛法，也简称筛法，是一种空间换时间算法.
	        筛法主要用于求出某一个范围内的所有素数，而不用于判断某个数是否为素数.
			其主要思想是利用了合数定理, 剔除范围内所有合数，剩下的必是素数.
			例如要求 (1, n] 以内的所有素数：
			  那么把2的所有倍数删掉（不包括2）；
			  在剩下的数中第一个是3，把3的所有倍数删掉（不包括3）；
			  在剩下的书中第一个是7，把7的所有倍数删掉（不包括7）......
			  一直重复直到遍历完 (1, sqrt(n)] 范围内的所有数，那么剩下的就是这个范围内的素数

	  常规情况下，
		使用定义+定理求解素数，时间复杂度约为O(n*sqrt(n))，超过千万级的话短时间内跑不动
		使用筛法求解素数，时间复杂度可达到O(n)，但空间复杂度也达到了O(n)

======================================================================================================

	 其实这题与POJ2262是类似的，都是围绕素数展开的操作.
	 因此第①步纯粹是走走形式求出素数集，这题的难点在于第②步.

	 理论上，根据哥德巴赫猜想，任意一个整数n只要足够大，都可以写成若干个素数之和的形式.
	 但是这种组合数比较多, 因此这题对组合范围做出了限制，要求是【连续素数】，且范围也压缩到【10000】以内

	 因此第②步其实可以暴力测试可行解：
	  在素数表中从2开始，在[2,n]范围内一直往后相加，若和值为n，则得到一个序列; 否则不用继续测试可行解;
	  在素数表中从3开始，在[3,n]范围内一直往后相加，若和值为n，则得到一个序列; 否则不用继续测试可行解;
	  ......
	  在素数表中从k开始，在[k,n]范围内一直往后相加，若和值为n，则得到一个序列; 否则不用继续测试可行解.
	  最后若n自身也素数，则序列数+1.

	  当然，这个测试方式是可以剪枝的：范围[k,n]可缩减到 [k, >=n/2的第一个素数]
	  这种剪枝原理是因为，若序列中出现1个以上>=n/2的数，和值必定>n.

	  还有一种剪枝可基于奇数与偶数相加的结果的奇偶性质确定：
	   若n是偶数, 则其序列必定有 含2的奇数个素数 或 不含2的偶数个素数
	   若n是奇数, 则其序列必定有 含2的偶数个素数 或 不含2的奇数个素数

*/


#include <memory.h>
#include <math.h>
#include <iostream>
using namespace std;

const static int LEN = 10001;							// 自然数数组长度(求解素数范围)
const static int SQRT_NUM = ceil(sqrt((double) LEN));	// 根据合数定理得到的质因数范围

/* 
 * 使用筛法找出自然数范围内的所有素数
 * @param markPrimes 素数标记集
 * return 范围内的素数个数
 */
int findPrimes(bool* markPrimes);

/* 
 * 把素数标记集转换成素数表
 * @param markPrimes 素数标记集
 * @param primeCnt 素数个数
 * return 素数表
 */
int* toPrimes(bool* markPrimes, int primeCnt);

/* 
 * 求解可以构成n的连续素数序列的个数
 * @param n 自然数n
 * @param primes 素数集
 * @param primeCnt 素数个数
 * return 序列个数
 */
int solveSerialNum(int n, int* primes, int primeCnt);


int main(void) {
	bool markPrimes[LEN];							// 素数标记集, 标记每个自然数是否为素数
	int primeCnt = findPrimes(markPrimes);			// 找出范围内所有素数
	int* primes = toPrimes(markPrimes, primeCnt);	// 素数表

	int n = 0;
	while(cin >> n && n > 0) {
		int serialCnt = solveSerialNum(n, primes, primeCnt);	// 求解可以构成n的连续素数序列的个数
		serialCnt += (markPrimes[n] ? 1 : 0);	// 若n自身是素数, 则序列数+1
		cout << serialCnt << endl;
	}

	delete[] primes;
	return 0;
}


int findPrimes(bool* markPrimes) {
	memset(markPrimes, true, sizeof(bool) * LEN);	// 注意memset是按字节覆写内存的
	markPrimes[0] = markPrimes[1] = false;
	int cnt = 2;	// 非素数个数

	for(int i = 2; i <= SQRT_NUM; i++) {
		if(markPrimes[i] == false) {
			continue;
		}

		// 筛掉最小素数的所有倍数
		int multiple = 2;	// i的倍率（因不包括自身, 从2倍开始）	
		while(true) {
			int mNum = i * multiple;	// i的倍数
			if(mNum >= LEN) {
				break;
			}

			if(markPrimes[mNum] == true) {	// 避免重复计数
				markPrimes[mNum] = false;
				cnt++;
			}
			multiple++;
		}
	}
	return LEN - cnt;
}

int* toPrimes(bool* markPrimes, int primeCnt) {
	int* primes = new int[primeCnt];
	for(int i = 0, j = 0; i < LEN && j < primeCnt; i++) {
		if(markPrimes[i] == true) {
			primes[j++] = i;
		}
	}
	return primes;
}


int solveSerialNum(int n, int* primes, int primeCnt) {
	const int HALF_N = n / 2;
	int cnt = 0;

	for(int i = 0; i < primeCnt && primes[i] < n; i++) {
		int sum = primes[i];

		for(int j = i + 1; j < primeCnt; j++) {
			sum += primes[j];

			if(sum == n) {
				cnt++;
				break;

			} else if(primes[j] >= HALF_N) {
				break;
			}
		}
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

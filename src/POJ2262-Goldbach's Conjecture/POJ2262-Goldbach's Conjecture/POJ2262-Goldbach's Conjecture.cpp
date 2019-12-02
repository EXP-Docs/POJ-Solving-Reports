/*
	Author:     Exp
	Date:       2017-11-30
	Code:       POJ 2262
	Problem:    Goldbach's Conjecture
	URL:		http://poj.org/problem?id=2262
*/

/*
	题意分析：
	 证明任意一个大于4的偶数n都可以写成两个奇素数（非2质数）之和, 其中n∈[6,1000000)且为偶数
	 其实就是证明100万以内的哥德巴赫猜想.

	解题思路：
	 主要分两步走：
	 ① 求出100万以内所有素数
	 ② 在这个素数集中找出两个奇素数，使其之和等于n（根据题意若存在多个组合则取差值最大的一组）

	 第①步只需要打表做一次即可，
	 第②步也不难：在素数表中找出比n小的最大一个素数x，
	   若y=n-x也在素数表中, 且 x,y != 2，则x,y就是解；
	   反之继续找比x小的下一个素数，重复这个步骤即可.

	 那么问题在于第①步，如何快速找到100万内的所有素数。
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
			  在剩下的数中第一个是7，把7的所有倍数删掉（不包括7）......
			  一直重复直到遍历完 (1, sqrt(n)] 范围内的所有数，那么剩下的就是这个范围内的素数


	  常规情况下，
		使用定义+定理求解素数，时间复杂度约为O(n*sqrt(n))，超过千万级的话短时间内跑不动
		使用筛法求解素数，时间复杂度可达到O(n)，但空间复杂度也达到了O(n)
*/

#include <memory.h>
#include <math.h>
#include <iostream>
using namespace std;


const static int LEN = 1000000;							// 自然数数组长度(求解素数范围)
const static int SQRT_NUM = ceil(sqrt((double) LEN));	// 根据合数定理得到的质因数范围

/* 
 * 使用筛法找出自然数范围内的所有素数
 * @param primes 素数表
 */
void findPrimes(bool* primes);

/* 
 * 打印哥德巴赫猜想结果
 * @param primes 素数集
 * @param n 合数，取值范围 [6, 10000000)
 */
void printGoldbach(bool* primes, int n);

int main(void) {
	bool primes[LEN];		// 素数集, 标记每个自然数是否为素数
	findPrimes(primes);		// 找出范围内所有素数

	int n = 0;
	while(cin >> n && n > 0) {
		printGoldbach(primes, n);	// 打印哥德巴赫猜想的结果
	}
	return 0;
}


void findPrimes(bool* primes) {
	memset(primes, true, sizeof(bool) * LEN);	// 注意memset是按字节覆写内存的
	primes[0] = primes[1] = false;

	for(int i = 2; i <= SQRT_NUM; i++) {
		if(primes[i] == false) {
			continue;
		}

		// 筛掉最小素数的所有倍数
		int multiple = 2;	// i的倍率（因不包括自身, 从2倍开始）	
		while(true) {
			int mNum = i * multiple;	// i的倍数
			if(mNum >= LEN) {
				break;
			}
			primes[mNum] = false;
			multiple++;
		}
	}
}

void printGoldbach(bool* primes, int n) {
	int x, y = 0;
	for(x = 3; x < n; x++) {
		if(primes[x] == false) {
			continue;
		}

		if(primes[n - x] == true) {
			y = n - x;
			break;
		}
	}

	if(x > 0 && y > 0) {
		cout << n << " = " << x << " + " << y << endl;
	} else {
		cout << "Goldbach's conjecture is wrong." << endl;
	}
}
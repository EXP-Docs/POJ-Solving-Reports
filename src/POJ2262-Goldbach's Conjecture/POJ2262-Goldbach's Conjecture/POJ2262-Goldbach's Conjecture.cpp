/*
	Author:     Exp
	Date:       2017-11-30
	Code:       POJ 2262
	Problem:    Goldbach's Conjecture
	URL:		http://poj.org/problem?id=2262
*/

/*
	���������
	 ֤������һ������4��ż��n������д����������������2������֮��, ����n��[6,1000000)��Ϊż��
	 ��ʵ����֤��100�����ڵĸ�°ͺղ���.

	����˼·��
	 ��Ҫ�������ߣ�
	 �� ���100��������������
	 �� ��������������ҳ�������������ʹ��֮�͵���n���������������ڶ�������ȡ��ֵ����һ�飩

	 �ڢٲ�ֻ��Ҫ�����һ�μ��ɣ�
	 �ڢڲ�Ҳ���ѣ������������ҳ���nС�����һ������x��
	   ��y=n-xҲ����������, �� x,y != 2����x,y���ǽ⣻
	   ��֮�����ұ�xС����һ���������ظ�������輴��.

	 ��ô�������ڵڢٲ�����ο����ҵ�100���ڵ�����������
	 ������������ⷽ����������õ���
	  ���壺ֻ�ܱ�1����������������Ȼ����������1������Ϊ����
	  �������һ����k�Ǻ�������ô������С�������϶�<=sqrt(k) 
	        ����һ����Ȼ�������Ǻ�����������������������Է���������������
			���һ����k������, ��ôk�ز��ܱ�<=sqrt(k)��������������
	  �㷨��������˹����ɸ����Ҳ���ɸ������һ�ֿռ任ʱ���㷨.
	        ɸ����Ҫ�������ĳһ����Χ�ڵ��������������������ж�ĳ�����Ƿ�Ϊ����.
			����Ҫ˼���������˺�������, �޳���Χ�����к�����ʣ�µı�������.
			����Ҫ�� (1, n] ���ڵ�����������
			  ��ô��2�����б���ɾ����������2����
			  ��ʣ�µ����е�һ����3����3�����б���ɾ����������3����
			  ��ʣ�µ����е�һ����7����7�����б���ɾ����������7��......
			  һֱ�ظ�ֱ�������� (1, sqrt(n)] ��Χ�ڵ�����������ôʣ�µľ��������Χ�ڵ�����


	  ��������£�
		ʹ�ö���+�������������ʱ�临�Ӷ�ԼΪO(n*sqrt(n))������ǧ�򼶵Ļ���ʱ�����ܲ���
		ʹ��ɸ�����������ʱ�临�ӶȿɴﵽO(n)�����ռ临�Ӷ�Ҳ�ﵽ��O(n)
*/

#include <memory.h>
#include <math.h>
#include <iostream>
using namespace std;


const static int LEN = 1000000;							// ��Ȼ�����鳤��(���������Χ)
const static int SQRT_NUM = ceil(sqrt((double) LEN));	// ���ݺ�������õ�����������Χ

/* 
 * ʹ��ɸ���ҳ���Ȼ����Χ�ڵ���������
 * @param primes ������
 */
void findPrimes(bool* primes);

/* 
 * ��ӡ��°ͺղ�����
 * @param primes ������
 * @param n ������ȡֵ��Χ [6, 10000000)
 */
void printGoldbach(bool* primes, int n);

int main(void) {
	bool primes[LEN];		// ������, ���ÿ����Ȼ���Ƿ�Ϊ����
	findPrimes(primes);		// �ҳ���Χ����������

	int n = 0;
	while(cin >> n && n > 0) {
		printGoldbach(primes, n);	// ��ӡ��°ͺղ���Ľ��
	}
	return 0;
}


void findPrimes(bool* primes) {
	memset(primes, true, sizeof(bool) * LEN);	// ע��memset�ǰ��ֽڸ�д�ڴ��
	primes[0] = primes[1] = false;

	for(int i = 2; i <= SQRT_NUM; i++) {
		if(primes[i] == false) {
			continue;
		}

		// ɸ����С���������б���
		int multiple = 2;	// i�ı��ʣ��򲻰�������, ��2����ʼ��	
		while(true) {
			int mNum = i * multiple;	// i�ı���
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
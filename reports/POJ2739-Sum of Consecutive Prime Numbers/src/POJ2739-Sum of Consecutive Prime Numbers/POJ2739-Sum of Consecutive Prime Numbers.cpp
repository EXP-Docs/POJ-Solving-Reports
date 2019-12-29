/*
	Author:     Exp
	Date:       2017-11-30
	Code:       POJ 2739
	Problem:    Sum of Consecutive Prime Numbers
	URL:		http://poj.org/problem?id=2739
*/

/*
	���������
	 һ������n��ʱ���Ա�д�����ɸ���������֮�͵����С�
	 ����һ������n�������Щ���еĸ�������n����Ҳ����������Ҳ������һ�����У�������n��[2,10000]

	����˼·��
	 ��Ҫ�������ߣ�
	 �� ���10000������������
	 �� �����������ҳ�����ͨ��������͵õ�n�����������


	 �ڢٲ�ֻ��Ҫ�����һ�μ��ɣ���ο����ҵ�10000�ڵ�����������
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

======================================================================================================

	 ��ʵ������POJ2262�����Ƶģ�����Χ������չ���Ĳ���.
	 ��˵ڢٲ�������������ʽ�����������������ѵ����ڵڢڲ�.

	 �����ϣ����ݸ�°ͺղ��룬����һ������nֻҪ�㹻�󣬶�����д�����ɸ�����֮�͵���ʽ.
	 ��������������Ƚ϶�, ����������Ϸ�Χ���������ƣ�Ҫ���ǡ��������������ҷ�ΧҲѹ������10000������

	 ��˵ڢڲ���ʵ���Ա������Կ��н⣺
	  ���������д�2��ʼ����[2,n]��Χ��һֱ������ӣ�����ֵΪn����õ�һ������; �����ü������Կ��н�;
	  ���������д�3��ʼ����[3,n]��Χ��һֱ������ӣ�����ֵΪn����õ�һ������; �����ü������Կ��н�;
	  ......
	  ���������д�k��ʼ����[k,n]��Χ��һֱ������ӣ�����ֵΪn����õ�һ������; �����ü������Կ��н�.
	  �����n����Ҳ��������������+1.

	  ��Ȼ��������Է�ʽ�ǿ��Լ�֦�ģ���Χ[k,n]�������� [k, >=n/2�ĵ�һ������]
	  ���ּ�֦ԭ������Ϊ���������г���1������>=n/2��������ֵ�ض�>n.

	  ����һ�ּ�֦�ɻ���������ż����ӵĽ������ż����ȷ����
	   ��n��ż��, �������бض��� ��2������������ �� ����2��ż��������
	   ��n������, �������бض��� ��2��ż�������� �� ����2������������

*/


#include <memory.h>
#include <math.h>
#include <iostream>
using namespace std;

const static int LEN = 10001;							// ��Ȼ�����鳤��(���������Χ)
const static int SQRT_NUM = ceil(sqrt((double) LEN));	// ���ݺ�������õ�����������Χ

/* 
 * ʹ��ɸ���ҳ���Ȼ����Χ�ڵ���������
 * @param markPrimes ������Ǽ�
 * return ��Χ�ڵ���������
 */
int findPrimes(bool* markPrimes);

/* 
 * ��������Ǽ�ת����������
 * @param markPrimes ������Ǽ�
 * @param primeCnt ��������
 * return ������
 */
int* toPrimes(bool* markPrimes, int primeCnt);

/* 
 * �����Թ���n�������������еĸ���
 * @param n ��Ȼ��n
 * @param primes ������
 * @param primeCnt ��������
 * return ���и���
 */
int solveSerialNum(int n, int* primes, int primeCnt);


int main(void) {
	bool markPrimes[LEN];							// ������Ǽ�, ���ÿ����Ȼ���Ƿ�Ϊ����
	int primeCnt = findPrimes(markPrimes);			// �ҳ���Χ����������
	int* primes = toPrimes(markPrimes, primeCnt);	// ������

	int n = 0;
	while(cin >> n && n > 0) {
		int serialCnt = solveSerialNum(n, primes, primeCnt);	// �����Թ���n�������������еĸ���
		serialCnt += (markPrimes[n] ? 1 : 0);	// ��n����������, ��������+1
		cout << serialCnt << endl;
	}

	delete[] primes;
	return 0;
}


int findPrimes(bool* markPrimes) {
	memset(markPrimes, true, sizeof(bool) * LEN);	// ע��memset�ǰ��ֽڸ�д�ڴ��
	markPrimes[0] = markPrimes[1] = false;
	int cnt = 2;	// ����������

	for(int i = 2; i <= SQRT_NUM; i++) {
		if(markPrimes[i] == false) {
			continue;
		}

		// ɸ����С���������б���
		int multiple = 2;	// i�ı��ʣ��򲻰�������, ��2����ʼ��	
		while(true) {
			int mNum = i * multiple;	// i�ı���
			if(mNum >= LEN) {
				break;
			}

			if(markPrimes[mNum] == true) {	// �����ظ�����
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
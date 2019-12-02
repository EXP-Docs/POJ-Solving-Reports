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
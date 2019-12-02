/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1207
	Problem:    The 3n plus 1 problem
	URL:		http://poj.org/problem?id=1207
*/

/*
	���������
	 �����˼�������n������ѭ�����㷨��ѭ�����а���n������
	 1. 	 input n
	 2. 	 print n
	 3. 	 if n = 1 then STOP
	 4. 		 if n is ���� then   n = 3n+1
	 5. 		 else   n = n/2
	 6. 	 GOTO 2

	 �ٸ�����Χ [i, j] �� i,j��(0,10000)
	 �� [i, j] ֮��ӵ�����ѭ����������n��ѭ�����ĸ���
*/

#include <iostream>
using namespace std;


/* 
 * ����������ѭ��������
 * @param num ����
 * return ѭ��������
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
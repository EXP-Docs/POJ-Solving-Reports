/*
	Author:     Exp
	Date:       2017-12-27
	Code:       POJ 3239
	Problem:    Solution to the n Queens Puzzle
	URL:		http://poj.org/problem?id=3239
*/

/*
	���������
	 N�ʺ�����: 
	  ��NxN������ �ݡ��ᡢб���ص��������ӣ�
	  ������N (N �� [8, 300]) ʱ, �������һ�ֽⷨ


	����˼·��
	  ��Ϊ�˱������ķ������ۣ��˴���ʼ����Ϊ��M�ʺ����⡱��
	 ����λ���С���һ�����͡�
	 
	 ��ͳ�ⷨ�ǡ����ݷ���DFS+��֦������������Nֵ���󣬻��ݷ��ᱬջ.
	 LRJ�ġ��㷨��������Ϣѧ����������Ľⷨ�ǡ�����ʽ�޲��㷨��(�����˹������㷨��һ��)
	 ����ʽ�㷨��M<10000���Ҷ��ǿɽ�ģ�������Ϊ����ʽ�㷨����������ԣ�
	 �����ٶ��Ӳ�ͬ���������Ӷ��仯���ҿ���ĳƪ���ĳ�����ʽ�㷨��M=10000ʱ�ĺ�ʱ�ȼ��ڻ��ݷ�M=30�ĺ�ʱ��

	 
	 ���⻹���á����취������ͨ����������Ǳ�ڵ���ѧ����ֱ�ӵõ��⣩��ͨ�⹫ʽ��ʱ�临�Ӷ�ΪO(1)
	 ͨ�⹫ʽ��ԭ����Դ����E.J.Hoffman��J.C.Loessi��R.C.Moore������1969�귢���һƪ��ѧ���ģ�
	 Ӣ��ԭ�ģ� http://penguin.ewu.edu/~trolfe/QueenLasVegas/Hoffman.pdf 
	 ԭ�����أ�http://download.csdn.net/download/lyy289065406/10184847
	 �������ģ��������룩��http://blog.csdn.net/lyy289065406/article/details/78955101
	 �������أ�http://download.csdn.net/download/lyy289065406/10184900


	 ��Ŀǰ����������ͨ�⹫ʽ������Ϊ�˱��ڱ�̣�������任��õ��ģ�
	 �任��������⹫ʽ���£�
	 �� ��m mod 6 != 2 �� m mod 6 != 3ʱ��
	   (A1):[2,4,6,8,...,m], [1,3,5,7,...,m-1]            (mΪż)
	   (A2):[2,4,6,8,...,m-1], [1,3,5,7,...,m-2], [m]     (mΪ��)

	 �� ��m mod 6 == 2 �� m mod 6 == 3ʱ��
	  �� n= m / 2 (mΪż��) �� n = (m-1)/2 (mΪ����)
       (B1):[n,n+2,n+4,...,m], [2,4,...,n-2], [n+3,n+5,...,m-1], [1,3,5,...,n+1]        (mΪż,nΪż)
	   (B2):[n,n+2,n+4,...,m-1], [1,3,5,...,n-2], [n+3,...,m], [2,4,...,n+1]            (mΪż,nΪ��)
	   (B3):[n,n+2,n+4,...,m-1], [2,4,...,n-2], [n+3,n+5,...,m-2], [1,3,5,...,n+1], [m] (mΪ��,nΪż)
	   (B4):[n,n+2,n+4,...,m-2], [1,3,5,...,n-2], [n+3,...,m-1], [2,4,...,n+1], [m]     (mΪ��,nΪ��)

	 ����������������: 
	   һ��һ������(���������Ҷ�����ϵģ��Ա����������)
	   ��i����Ϊj����ʾ�ڵ�i��j�з�һ���ʺ�.
	   ��������������֮���������������ϵ(���������žͿ�����), ������������j�ĵ���ֵΪ2
*/


#include <iostream>
using namespace std;

/* 
 * ÿ��1������ӡ��bgn��end������
 * @param bgn ��ʼֵ��������
 * @param end ��ֵֹ��������
 */
void print(int bgn, int end);


int main(void) {
	int m = 0;
	while(cin >> m && m > 0) {
		const int mod = m % 6;
		const bool mOdd = (m % 2 == 1);

		if(mod != 2 && mod != 3) {

			// A2
			if(mOdd == true) {
				print(2, m - 1);
				print(1, m);

			// A1
			} else {
				print(2, m);
				print(1, m - 1);
			}

		} else {
			int n = m / 2;
			const bool nOdd = (n % 2 == 1);

			if(mOdd == true) {

				// B4
				if(nOdd == true) {
					print(n, m - 2);
					print(1, n - 2);
					print(n + 3, m - 1);
					print(2, n + 1);
					print(m, m);

				// B3
				} else {
					print(n, m - 1);
					print(2, n - 2);
					print(n + 3, m - 2);
					print(1, n + 1);
					print(m, m);
				}

			} else {

				// B2
				if(nOdd == true) {
					print(n, m - 1);
					print(1, n - 2);
					print(n + 3, m);
					print(2, n + 1);

				// B1
				} else {
					print(n, m);
					print(2, n - 2);
					print(n + 3, m - 1);
					print(1, n + 1);
				}
			}
		}
	}
	return 0;
}


void print(int bgn, int end) {
	for(int i = bgn; i <= end; i+= 2) {
		cout << i << ' ';
	}
}
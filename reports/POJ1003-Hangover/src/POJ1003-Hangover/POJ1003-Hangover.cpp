/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1003
	Problem:    Hangover
	URL:		http://poj.org/problem?id=1003
*/

/*
    ��������ɽ���������ѧģ�ͣ�
	 �� ��(1/n) >= c
	 ���� n��[2, ��), c��[0.01, 5.20]���侫�Ⱥ�С���������3������
	 ����c �� n ����c�ڷ�Χ�⣬����⣩

	������
	 ���ʾ��Ǳ��ֵĵ���������ͣ�������ȱ��1��
	 �����������Ƿ�ɢ�ģ�������׼ȷ����͹�ʽ��ֻ�н��ƹ�ʽ��
	  �������� ��(1/n) ~ ln(n+1) + R
	  ���� n��[1, ��), RΪŷ������(R = 0.5772156649...)

	 �����ƹ�ʽֻ����n�ǳ����ʱ�����ſ��Ժ��Բ��ƣ�
	 ��n��Сʱ���Ա����������ǲ��ɽ��ܵġ�

	 ��˱����ó���ⷨ����
	 ������ǰn����ǹ̶��ģ��ô��Ҳ��, ������Ŀ���˷�Χ��С���������Ҳ����
*/



#include <iostream>
using namespace std;

/* 
 * ���ݵ������еĺ�ֵ��������
 * @param sum Ŀ���ֵ
 * return ������������
 */
int harmonicSeries(double sum);


int main(void) {
	double sum = 0.0;
	while(true) {
		cin >> sum;
		if(sum < 0.01 || sum > 5.20) {
			break;
		}

		int n = harmonicSeries(sum);
		cout << n << " card(s)" << endl;
	}
	return 0;
}


int harmonicSeries(double sum) {
	int n = 2;
	double curSum = 0.0;
	while(curSum < sum) {
		curSum += (1.0 / n++);
	}
	return n - 2;	// n��2��ʼ�������-1, ���һ����Ͷ���һ��n++ҲҪ-1�� ��˹�-2
}
/*
	Author:     Exp
	Date:       2017-12-06
	Code:       POJ 1328
	Problem:    Radar Installation
	URL:		http://poj.org/problem?id=1328
*/

/*
	���������
	  ����һ��ֱ������ϵ������x��Ϊ�����ߣ��������Ϸ��Ǻ����·���½��.
	  �ں������Ƿֲ�һЩ����, ��ҪҪ�ں������ϰ�װ���ɸ��״︲����Щ����,
	  ÿ���״�ĸ��ǰ뾶������ͬ�ҹ̶���.

	  ���ڸ������к���������(x,y), �Լ��״�ĸ��ǰ뾶d��
	  �ʿ��Ը������к�������С�״���.


	����˼·��
	  ���ȿ�����ȷ���ǣ�ֻҪ��������һ������λ�ó����״���󸲸ǰ뾶����y>d�������޽�.

	  �����к����� y<=d ��ǰ����ȥ˼�������⣬
	  ��ô����������������Ҫ֪����һ���״�Ҫ����һ������������԰�װ��Χ�Ƕ��١�

	  �Ժ�������(x,y)ΪԲ�ģ����״︲�ǰ뾶d��Բ������ǰ��������֪��
	  ���Բ��x��ض���������1��(y=d)�����2������(y<d).

	  ������Ϊ1��������2�������غϵ������������ô��2��������x���Ϲ��ɵ��������䣬
	  ���Կ��������ı����Ƿ�Χ��x���ϵ�ͶӰ (�ɴ˾Ϳ��԰Ѷ�ά�ļ�������ת����һά��������)

	  �������к�����x�����꣬��С�������μ���ÿ��������x���ϵ�ͶӰ���䣨ͶӰ���ܴ����ص�����
	  ͬʱ��ÿ���״�����1���㣬��ô�������ת���ɣ�

	  ����֪x�������ɸ����䣨���ܴ��ڽ�����������Ҫ����Щ�����ڷ����ɸ��㣬
	  ������������Щ�㣬ʹ��ÿ�����������ٴ���һ���㣬�������õĵ���������������١�
	
	  
	  ��ʹ��̰���㷨��⣺
	    ����ÿ���������˵�����������������������:
		�� �������һ������A ���Ҷ˵� A.R ����һ���㣬�ܷ��õ��� P+1 
		�� ����һ������B ����˵� B.L > A.R, 
		    ˵�� ����A �� ����B �޽�������ʱ������B ���Ҷ˵� B.R ����һ���㣬�ܷ��õ��� P+1 

		   ����˵�� ����A �� ����B �ཻ, ��ʱ��һ���жϣ��� B.R < A.R��
			˵�� ����B �� ����A ���ڲ�����ʱ��ԭ�������� A.R �ĵ��ƶ��� B.R��ȷ������B��һ���㣩���ܷ��õ�������

		�� �ظ��������ֱ���������䱻�������
*/


#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;


// ������x���ϵ�ͶӰ����
struct Interval {
	double left;	// ��˵���x���ϵ�����
	double right;	// �Ҷ˵���x���ϵ�����
};


/* 
 * ������⣺��ÿ�����������ٷ���һ���㣬ʹ�÷��õĵ����������
 * @param intervals ���伯��
 * @param size �������
 * return ��С�ķ��õ���
 */
int solve(Interval* intervals, int size);


/* 
 * �Ƚ���������Ĵ�С����������
 *  ��˵�ԽС�����䣬�������˳��ԽС
 * @param a ����a
 * @param b ����b
 * return a.left <= b.left
 */
bool compare(Interval a, Interval b);


int main(void) {
	int island, radius, testCase = 0;
	while((cin >> island >> radius) && island && radius) {
		const double R2 = radius * radius;	// �뾶ƽ��
		Interval* intervals = new Interval[island];

		bool isSolvable = true;
		for(int i = 0; i < island; i++) {
			double x, y;
			cin >> x >> y;
			if(y > radius) {	// ���ں��������״�����Ӱ�췶Χ���޽�
				isSolvable = false;
			}

			double offset = sqrt(R2 - y * y);	// ���ɶ���
			intervals[i].left = x - offset;
			intervals[i].right = x + offset;
		}

		int minRadar = (isSolvable ? solve(intervals, island) : -1);
		cout << "Case " << ++testCase << ": " << minRadar << endl;
		delete[] intervals;
	}
	return 0;
}


int solve(Interval* intervals, int size) {
	sort(intervals, intervals + size, compare);

	int minPoint = 1;
	double right = intervals[0].right;
	for(int i = 1; i < size; i++) {

		// ����i-1 �� ����i �޽���
		if(intervals[i].left > right) {
			minPoint++;
			right = intervals[i].right;

		// ����i-1 �� ����i �ڲ�
		} else if(intervals[i].right < right) {
			right = intervals[i].right;

		} else {
			// Undo: ����i-1 �� ����i �ཻ 
		}
	}
	return minPoint;
}


bool compare(Interval a, Interval b) {
	return a.left <= b.left;
}
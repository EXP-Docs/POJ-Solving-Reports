/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1005
	Problem:    I Think I Need a Houseboat
	URL:		http://poj.org/problem?id=1005
*/

/*
	�������⽨����ѧģ�����£�
	  λ��ƽ�������һ�����޵�һ����Բ��ԭ��(0,0)��ʼ��(x,y)��ɢ��ÿ����ɢ50ƽ��
	  ��ڼ�����ɢ�Ḳ�ǵ�(x,y)�� ����y>0

	  ���ɶ���뾶 R^2 = (x-0)^2 + (y-0)^2
	  ��Բ�����ʽ Area = pi * R^2 / 2
	  �� Area �� 50 ������ʱ, ��ɢ���� cnt = Area / 50
	  �� Area ���� 50 ������ʱ, ��ɢ���� cnt = Area / 50 + 1	���༴����ȡ����
*/

#include <math.h>
#include <iostream>
using namespace std;

const static double PI = 3.141592654;	// ������
const static double HALF_PI = PI / 2;	// ��Բ�����ʽ����
const static double EACH_AREA = 50;	// ÿ����ɢ���

/* 
 * �����ɢ����
 * @param x ��ɢ����x
 * @param y ��ɢ����y
 * return ��ɢ����
 */
int diffuse(double x, double y);


int main(void) {
	int testCase = 0;	// ����������
	cin >> testCase;

	for(int i = 1; i <= testCase; i++) {
		double x, y;
		cin >> x >> y;
		int cnt = diffuse(x, y);
		cout << "Property " << i << ": This property will begin eroding in year " << cnt << '.' << endl; 
	}
	cout << "END OF OUTPUT." << endl;

	//system("pause");
	return 0;
}


int diffuse(double x, double y) {
	double R2 = x * x + y * y;
	double Area = HALF_PI * R2;
	return (int) ceil(Area / EACH_AREA);	// ����ȡ��
}

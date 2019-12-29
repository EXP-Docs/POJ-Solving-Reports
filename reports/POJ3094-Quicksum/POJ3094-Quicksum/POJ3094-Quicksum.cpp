/*
	Author:     Exp
	Date:       2017-12-01
	Code:       POJ 3094
	Problem:    Quicksum
	URL:		http://poj.org/problem?id=3094
*/

/*
	���������
	 ����ֻ��[��д��ĸ+�ո�]���ַ�����У���.
	 ����ÿ����ĸ�����Ӧ������ֵ���ո�=0,A=1,B=2,...,Z=26
	 У��� = ���� [�ַ���λ��(��1��ʼ) * ��ĸ����ֵ] ֮��

*/


#include <memory.h>
#include <iostream>
using namespace std;


// ��У���ַ�������󳤶�
const static int MAX_LEN = 255;

/* 
 * ��ȡ�ַ�������ֵ
 * @param c �ַ�
 * return ����ֵ
 */
int getFeatureVal(char c);


int main(void) {
	char str[MAX_LEN] = { '\0' };
	while(true) {
		gets(str);	// �����ַ����а����ո񣬲�����cin����
		int len = strlen(str);
		if(strlen(str) <= 0 || str[0] == '#') {
			break;
		}

		int quicksum = 0;
		for(int i = 0; i < len; i++) {
			quicksum += ((i + 1) * getFeatureVal(str[i]));
		}
		cout << quicksum << endl;

		memset(str, '\0', sizeof(char) * len);
	}
	return 0;
}


int getFeatureVal(char c) {
	return (c == ' ' ? 0 : (c - 'A' + 1));
}
/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 3299
	Problem:    Humidex
	URL:		http://poj.org/problem?id=3299
*/

/*
	���������
	 ��֪�¶�ת����ʽ��
	  humidex = temperature + h
	  h = (0.5555)�� (e - 10.0)
	  e = 6.11 �� exp [5417.7530 �� ((1/273.16) - (1/(dewpoint+273.16)))]

	�� H = humidex��temperature = T��dewpoint = D�� ���� H,T,D �� [-100, 100]
	������������������һ�� (�������Ϊ1λС��)
*/

#include <math.h>
#include <iomanip>
#include <iostream>
using namespace std;

const static char T = 'T';
const static char D = 'D';
const static char H = 'H';
const static char E = 'E';
const static double INVALD_VAL = 999.0;	// ���в���ȡֵ��ΧΪ[-100, 100]


/* 
 * ���ݹ�ʽ�Լ���������������������������
 * @param nT ����T������Ϊ��Чֵ
 * @param nD ����D������Ϊ��Чֵ
 * @param nH ����H������Ϊ��Чֵ
 * return ����������ֵ
 */
void solve(double *nT, double *nD, double *nH);	// POJ�ϵ�C++��������֧��&���ô�ֵ, ֻ����ָ��


int main(void) {

	while(true) {
		bool isEnd = false;
		char letter = E;
		double nT, nD, nH;
		nT = nD = nH = INVALD_VAL;

		for(int i = 0; !isEnd && i < 2; i++) {
			cin >> letter;
			switch(letter) {
				case T: { cin >> nT; break; }
				case D: { cin >> nD; break; }
				case H: { cin >> nH; break; }
				default: { isEnd = true; break; }
			}
		}

		if(isEnd == true) {
			break;

		} else {
			solve(&nT, &nD, &nH);
			cout << fixed << setprecision(1) << "T " << nT << " D " << nD << " H " << nH << endl;
		}
	}
	return 0;
}


void solve(double *nT, double *nD, double *nH) {
	if(*nH == INVALD_VAL) {
		*nH= *nT + 0.5555 * (6.11 * exp(5417.7530 * ( 1.0 / 273.16 - 1.0 / (*nD + 273.16))) - 10.0);

	} else if(*nT == INVALD_VAL) {
		*nT= *nH - 0.5555 * (6.11 * exp(5417.7530 * ( 1.0 / 273.16 - 1.0 / (*nD + 273.16))) - 10.0);

	} else {
		*nD= 1.0 / ((1.0 / 273.16) - ((log((((*nH - *nT) / 0.5555) + 10.0) / 6.11)) / 5417.7530)) - 273.16;
	}
}

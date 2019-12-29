/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 1004
	Problem:    Financial Management
	URL:		http://poj.org/problem?id=1004
*/

/*
	题意分析：
	 每次输入12个浮点数，求其平均数（注意输出精度为2位小数）
*/

#include <iomanip>
#include <iostream>
using namespace std;


int main(void) {
	const int N = 12;
	double sum = 0.0;

	for(int i = 0; i < N; i++) {
		double num = 0.0;
		cin >> num;
		sum += num;
	}

	double avg = sum / N;
	cout << fixed << setprecision(2) << '$' << avg << endl;

	//system("pause");
	return 0;
}
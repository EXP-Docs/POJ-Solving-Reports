/*
	Author:     Exp
	Date:       2017-12-01
	Code:       POJ 3094
	Problem:    Quicksum
	URL:		http://poj.org/problem?id=3094
*/

/*
	题意分析：
	 计算只含[大写字母+空格]的字符串的校验和.
	 其中每个字母有其对应的特征值，空格=0,A=1,B=2,...,Z=26
	 校验和 = 所有 [字符的位置(从1开始) * 字母特征值] 之和

*/


#include <memory.h>
#include <iostream>
using namespace std;


// 被校验字符串的最大长度
const static int MAX_LEN = 255;

/* 
 * 获取字符的特征值
 * @param c 字符
 * return 特征值
 */
int getFeatureVal(char c);


int main(void) {
	char str[MAX_LEN] = { '\0' };
	while(true) {
		gets(str);	// 输入字符串中包含空格，不能用cin接收
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
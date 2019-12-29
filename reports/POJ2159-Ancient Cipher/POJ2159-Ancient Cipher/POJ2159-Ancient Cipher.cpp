/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 2159
	Problem:    Ancient Cipher
	URL:		http://poj.org/problem?id=2159
*/

/*
	题意分析：
	  有一明文（纯大写字母序列，长度<100），
	  对其使用 凯撒加密（替换加密） 和 乱序加密 后得到密文
	  根据这两种加密的特点，密文与明文必定等长，且同为纯大写字母序列。
	  现给定一对密文和明文，猜测它们是否配对。

	  首先需要明确这两种加密方式的特点：
	  ① 凯撒加密：令明文中所有字母均在字母表上向前/后以固定值偏移并替换
	  ② 乱序加密：给定乱序表，交换明文中每个字母的位置

	  解题思路先入为主肯定是通过某种手段另对明文加密或对密文解密，对结果字符串进行比较.
	  但是由于题目并未给出乱序表，因此此方案不可行 
	  （若单纯只有凯撒加密，是可以通过碰撞26次偏移值做逆向还原的，
	  但由于还存在乱序加密，且乱序表的长度最大为100，根据排列组合来看是不可能的）


	  为此切入点可以通过比较明文和密文在加密前后依然保有的共有特征，猜测两者是否配对：
	  ① 明文和密文等长
	  ② 乱序加密只改变了明文中字母的顺序，原本的字母并没有发生变化
	  ③ 把明文中每个字母看作一个变量，凯撒加密只改变了变量名称，该变量出现的次数没有发生变化
	  ④ 综合①②③的条件，若分别对明文和密文每个字母进行采样，分别求得每个字母的出现频次，
	     然后对频次数列排序，若明文和密文是配对的，可以得到两个完全一样的频次数列
	  ⑤ 比较频次数列会存在碰撞几率，亦即得到只是疑似解
	    （但由于题目没有给出乱序表，基本不可能得到准确解，疑似解已经足够了）
*/

#include <algorithm>
#include <iostream>
using namespace std;


const static int MAX_LEN = 101;		// 密文/明文最大长度
const static int FRE_LEN = 26;		// 频率数组长度（记录每个字母的出现次数）


/* 
 * 计算字符串中每个字母出现的频次
 * @param _in_txt 入参：纯大写字母的字符数组
 * @param _out_frequency 出参：长度为26的每个字母出现的频次数组
 */
void countFrequency(char* _in_txt, int* _out_frequency);

/* 
 * 比对两个频次数组是否完全一致（频次数组定长为26）
 * @param aFrequency 频次数组a
 * @param bFrequency 频次数组b
 * return true:完全一致; false:存在差异
 */
bool isSame(int* aFrequency, int* bFrequency);


int main(void) {
	char cipherTxt[MAX_LEN] = { '\0' };		// 密文
	char plaintTxt[MAX_LEN] = { '\0' };		// 明文
	int cFrequency[FRE_LEN] = { 0 };		// 密文频次数列
	int pFrequency[FRE_LEN] = { 0 };		// 明文频次数列

	cin >> cipherTxt >> plaintTxt;
	countFrequency(cipherTxt, cFrequency);
	countFrequency(plaintTxt, pFrequency);
	cout << (isSame(cFrequency, pFrequency) ? "YES" : "NO") << endl; 

	//system("pause");
	return 0;
}


void countFrequency(char* _in_txt, int* _out_frequency) {
	for(int i = 0; *(_in_txt + i) != '\0'; i++) {
		*(_out_frequency + (*(_in_txt + i) - 'A')) += 1;
	}
	sort(_out_frequency, _out_frequency + FRE_LEN);
}

bool isSame(int* aFrequency, int* bFrequency) {
	bool isSame = true;
	for(int i = 0; i < FRE_LEN; i++) {
		isSame = (*(aFrequency + i) == *(bFrequency + i));
		if(isSame == false) {
			break;
		}
	}
	return isSame;
}
/*
	Author:     Exp
	Date:       2017-11-29
	Code:       POJ 2159
	Problem:    Ancient Cipher
	URL:		http://poj.org/problem?id=2159
*/

/*
	���������
	  ��һ���ģ�����д��ĸ���У�����<100����
	  ����ʹ�� �������ܣ��滻���ܣ� �� ������� ��õ�����
	  ���������ּ��ܵ��ص㣬���������ıض��ȳ�����ͬΪ����д��ĸ���С�
	  �ָ���һ�����ĺ����ģ��²������Ƿ���ԡ�

	  ������Ҫ��ȷ�����ּ��ܷ�ʽ���ص㣺
	  �� �������ܣ���������������ĸ������ĸ������ǰ/���Թ̶�ֵƫ�Ʋ��滻
	  �� ������ܣ��������������������ÿ����ĸ��λ��

	  ����˼·����Ϊ���϶���ͨ��ĳ���ֶ�������ļ��ܻ�����Ľ��ܣ��Խ���ַ������бȽ�.
	  ����������Ŀ��δ�����������˴˷��������� 
	  ��������ֻ�п������ܣ��ǿ���ͨ����ײ26��ƫ��ֵ������ԭ�ģ�
	  �����ڻ�����������ܣ��������ĳ������Ϊ100������������������ǲ����ܵģ�


	  Ϊ����������ͨ���Ƚ����ĺ������ڼ���ǰ����Ȼ���еĹ����������²������Ƿ���ԣ�
	  �� ���ĺ����ĵȳ�
	  �� �������ֻ�ı�����������ĸ��˳��ԭ������ĸ��û�з����仯
	  �� ��������ÿ����ĸ����һ����������������ֻ�ı��˱������ƣ��ñ������ֵĴ���û�з����仯
	  �� �ۺϢ٢ڢ۵����������ֱ�����ĺ�����ÿ����ĸ���в������ֱ����ÿ����ĸ�ĳ���Ƶ�Σ�
	     Ȼ���Ƶ���������������ĺ���������Եģ����Եõ�������ȫһ����Ƶ������
	  �� �Ƚ�Ƶ�����л������ײ���ʣ��༴�õ�ֻ�����ƽ�
	    ����������Ŀû�и�����������������ܵõ�׼ȷ�⣬���ƽ��Ѿ��㹻�ˣ�
*/

#include <algorithm>
#include <iostream>
using namespace std;


const static int MAX_LEN = 101;		// ����/������󳤶�
const static int FRE_LEN = 26;		// Ƶ�����鳤�ȣ���¼ÿ����ĸ�ĳ��ִ�����


/* 
 * �����ַ�����ÿ����ĸ���ֵ�Ƶ��
 * @param _in_txt ��Σ�����д��ĸ���ַ�����
 * @param _out_frequency ���Σ�����Ϊ26��ÿ����ĸ���ֵ�Ƶ������
 */
void countFrequency(char* _in_txt, int* _out_frequency);

/* 
 * �ȶ�����Ƶ�������Ƿ���ȫһ�£�Ƶ�����鶨��Ϊ26��
 * @param aFrequency Ƶ������a
 * @param bFrequency Ƶ������b
 * return true:��ȫһ��; false:���ڲ���
 */
bool isSame(int* aFrequency, int* bFrequency);


int main(void) {
	char cipherTxt[MAX_LEN] = { '\0' };		// ����
	char plaintTxt[MAX_LEN] = { '\0' };		// ����
	int cFrequency[FRE_LEN] = { 0 };		// ����Ƶ������
	int pFrequency[FRE_LEN] = { 0 };		// ����Ƶ������

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
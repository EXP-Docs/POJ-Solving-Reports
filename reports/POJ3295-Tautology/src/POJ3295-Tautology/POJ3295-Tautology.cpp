/*
	Author:     Exp
	Date:       2017-12-27
	Code:       POJ 3295
	Problem:    Tautology
	URL:		http://poj.org/problem?id=3295
*/

/*
	���������
      ������p��q��r��s��t��K��A��N��C��E��10����ĸ��ɵ��߼����ʽWFF
      ���� 
	    p��q��r��s��t��ֵΪ1��true����0��false�������߼�����.

        K��A��N��C��EΪ�߼���������������£�
         K --> and:  w && x
         A --> or:  w || x
         N --> not :  !w
         C --> implies :  (!w) || x
         E --> equals :  w == x

      ��WFF�Ƿ�Ϊ������ʽ�� (��ǰ�᣺�������ʽ��֤�ǺϷ��ġ�)


    ����˼·��
	  ��ν������ʽ, ���ǲ���WFF�е��߼�����ȡ�κ�ֵ, �����߼����ʽ��ֵʼ��Ϊ��.
	  ��Ŀ�������߼�������5��, ����������Ϲ� 2^5 = 32 ����ϱ仯
	  ��ôֻҪ����WFF����32������е����н��, ����Ϊ��, ��WFF������ʽ.

	  ��ô����ʣ��������WFF.

	    �����������WFF���ʽΪ����ApNq
	      �������ĺ����ǣ� A(p, N(q))

	    ��Ϊ���ӵ�����ǣ�EKpNAqrCsNt
	      �京���ǣ�E(K(p, N(A(q, r)), C(s, N(t)))

	  ����Ҫ�������Ƕ�ױ��ʽ��ֵ, ��õ����ݽṹ��ջ��
	    �����ڲ㿪ʼ����, �����������

	  �ڱ�����, ����ֻ����һĿ�Ͷ�Ŀ�����, ����ڲ�����������ڱ��ʽĩ��,
	  Ϊ������WFF���ʽ���㷨�ǣ�
	    ��WFF���ʽ���һ���ַ���ǰ������
		�� �����߼���������Ѹ��߼������ĵ�ǰֵ(0��1)ֱ��ѹջ
		�� �����߼����, �������һĿ������Ŀ�������ջ��ȡ����Ӧ�����߼�����ֵ�����, �ѽ��ֵѹջ

	  ������Ŀ�Ѿ�������һ����ǰ�᣺�������ʽ��֤�ǺϷ��ġ�
	  ��������������迼��WFF���ʽ�Ƿ�����쳣�������
	  ���Ը��������㷨���㵽���ջ�ڱض�ֻʣһ��һ��Ԫ�أ���Ԫ�ؾ����������ʽ��ֵ.

	  ================================================================================
	  �����и�С���ɣ�
	    ���ڴ���5���߼�����, ����ö�ٻ����5��ѭ��Ƕ��.
		���ǵ���5������ֻ��0/1ֵ, ������һ��bit����һ������, ��5�����������һ��byte, 
		�ǾͿ����Ż���һ��ѭ����ö��[0, 31]����ͨ������ȡĳ���߼�������ֵ����

*/

#include <iostream>
#include <stack>
using namespace std;

// WFF�߼����ʽ��󳤶�
const int MAX_LEN =101;

// ö�ٱ����
// �����ַ�p,q,r,s,tȡֵ��ΧΪ0(��)��1(��), ������Ϲ�2^5�ֿ���
// ʹ��char�ĵ�5λ�ֱ������5����������0x1F��0001 1111���ɸ�����32�ֿ��ܵı仯ֵ
const char ENUM_CODE = 0X1F;

// �߼���������ֵ
const char P_MASK = 0x01;
const char Q_MASK = 0x02;
const char R_MASK = 0x04;
const char S_MASK = 0x08;
const char T_MASK = 0x10;

// �߼�������
#define p 'p'
#define q 'q'
#define r 'r'
#define s 's'
#define t 't'

// �߼������
#define K 'K'
#define A 'A'
#define N 'N'
#define C 'C'
#define E 'E'

// �߼�����
// (ע�⣺���ڲ�������bit����, ���ʹ�õ����߼����������λ�����)
#define _K(w, x) ((w) && (x))		//	K --> and:  w && x
#define _A(w, x) ((w) || (x))		//	A --> or:  w || x
#define _N(w) (!(w))				//	N --> not :  !w
#define _C(w, x) ((!(w)) || (x))	//	C --> implies :  (!w) || x
#define _E(w, x) ((w) == (x))		//	E --> equals :  w == x


/*  
 * �ж��߼����ʽ���������Ƿ�Ϊ��
 * @param WFF �߼����ʽ
 * @param code ��ǰ�ı���ֵ�����
 * return true:ֵΪ��; true:ֵΪ��
 */  
bool isTrue(char* WFF, char code);


/*  
 * ��ȡ�����ַ���ǰ�ı���ֵ
 * @param ch �����ַ�:p,q,r,s,t
 * @param code ��ǰ�ı���ֵ�����
 * return 0: ch = 0
 *        1: ch = 1 
 *        2: ch���Ǳ����ַ�
 */  
char toVal(char ch, char code);


/*  
 * ȡ��ջ��Ԫ��
 * @param st ջ
 * return ջ��Ԫ��
 */  
char getTop(stack<char>* wffStack);



int main(void) {
	char WFF[MAX_LEN];
	while(cin >> WFF && WFF[0] != '0') {
		bool isTautology = true;

		for(char code = 0; code < ENUM_CODE; code++) {
			isTautology &= isTrue(WFF, code);
			if(isTautology == false) {
				break;
			}
		}

		cout << (isTautology ? "tautology" : "not") << endl;
	}
	return 0;
}


bool isTrue(char* WFF, char code) {
	stack<char> wffStack;
	const int LEN = strlen(WFF);

	// �Ӻ���ǰ���ݱ��ʽ��ֵ
	for(int i = LEN - 1; i >= 0; i--) {
		char ch = WFF[i];
		char val = toVal(ch, code);

		// ch���߼�����, ֱ����ջ
		if(val <= 1) {
			wffStack.push(val);

		// ch���߼������, ��ջ��ȡ��Ԫ�������, �ѽ����ջ
		} else {

			// һĿ����
			if(N == ch) {
				char w = getTop(&wffStack);
				wffStack.push(_N(w));

			// ��Ŀ����
			} else {
				char w = getTop(&wffStack);
				char x = getTop(&wffStack);

				if(K == ch) {
					wffStack.push(_K(w, x));

				} else if(A == ch) {
					wffStack.push(_A(w, x));

				} else if(C == ch) {
					wffStack.push(_C(w, x));

				} else if(E == ch) {
					wffStack.push(_E(w, x));
				}
			}
		}
	}
	
	// ����ջ��ֻʣ��1��Ԫ����ֵΪ��
	return (wffStack.size() == 1 && wffStack.top() == 1);
}


char toVal(char ch, char code) {
	char val = 2; 
	switch(ch) {
		case p : { val = ((code & P_MASK) == 0 ? 0 : 1); break; }
		case q : { val = ((code & Q_MASK) == 0 ? 0 : 1); break; }
		case r : { val = ((code & R_MASK) == 0 ? 0 : 1); break; }
		case s : { val = ((code & S_MASK) == 0 ? 0 : 1); break; }
		case t : { val = ((code & T_MASK) == 0 ? 0 : 1); break; }
		default : { val = 2; }
	}
	return val;
}


char getTop(stack<char>* wffStack) {
	char e = wffStack->top();
	wffStack->pop();
	return e;
}
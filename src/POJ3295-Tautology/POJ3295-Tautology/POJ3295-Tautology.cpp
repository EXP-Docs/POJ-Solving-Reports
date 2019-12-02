/*
	Author:     Exp
	Date:       2017-12-27
	Code:       POJ 3295
	Problem:    Tautology
	URL:		http://poj.org/problem?id=3295
*/

/*
	题意分析：
      输入由p、q、r、s、t、K、A、N、C、E共10个字母组成的逻辑表达式WFF
      其中 
	    p、q、r、s、t的值为1（true）或0（false），即逻辑变量.

        K、A、N、C、E为逻辑运算符，含义如下：
         K --> and:  w && x
         A --> or:  w || x
         N --> not :  !w
         C --> implies :  (!w) || x
         E --> equals :  w == x

      问WFF是否为【永真式】 (大前提：【输入格式保证是合法的】)


    解题思路：
	  所谓的永真式, 就是不管WFF中的逻辑变量取任何值, 整个逻辑表达式的值始终为真.
	  题目给出的逻辑变量共5个, 根据排列组合共 2^5 = 32 种组合变化
	  那么只要计算WFF在这32种组合中的所有结果, 若均为真, 则WFF是永真式.

	  那么问题剩下如何求解WFF.

	    以样例输入的WFF表达式为例：ApNq
	      其真正的含义是： A(p, N(q))

	    更为复杂的情况是：EKpNAqrCsNt
	      其含义是：E(K(p, N(A(q, r)), C(s, N(t)))

	  对于要求解这类嵌套表达式的值, 最好的数据结构是栈：
	    从最内层开始计算, 逐层向外推演

	  在本题中, 由于只存在一目和二目运算符, 因此内层的运算总是在表达式末端,
	  为此推演WFF表达式的算法是：
	    从WFF表达式最后一个字符向前迭代：
		① 遇到逻辑变量，则把该逻辑变量的当前值(0或1)直接压栈
		② 遇到逻辑算符, 则根据是一目算符或二目算符，从栈顶取出对应两个逻辑变量值计算后, 把结果值压栈

	  由于题目已经给出了一个大前提：【输入格式保证是合法的】
	  因此整个过程无需考虑WFF表达式是否存在异常的情况，
	  所以根据上述算法运算到最后，栈内必定只剩一下一个元素，该元素就是整个表达式的值.

	  ================================================================================
	  另外有个小技巧：
	    由于存在5个逻辑变量, 常规枚举会产生5层循环嵌套.
		考虑到这5个变量只有0/1值, 可以用一个bit代表一个变量, 将5个变量编码成一个byte, 
		那就可以优化成一层循环（枚举[0, 31]），通过掩码取某个逻辑变量的值即可

*/

#include <iostream>
#include <stack>
using namespace std;

// WFF逻辑表达式最大长度
const int MAX_LEN =101;

// 枚举编码表
// 变量字符p,q,r,s,t取值范围为0(假)、1(真), 排列组合共2^5种可能
// 使用char的低5位分别代表这5个变量，则0x1F（0001 1111）可覆盖这32种可能的变化值
const char ENUM_CODE = 0X1F;

// 逻辑变量掩码值
const char P_MASK = 0x01;
const char Q_MASK = 0x02;
const char R_MASK = 0x04;
const char S_MASK = 0x08;
const char T_MASK = 0x10;

// 逻辑变量名
#define p 'p'
#define q 'q'
#define r 'r'
#define s 's'
#define t 't'

// 逻辑算符名
#define K 'K'
#define A 'A'
#define N 'N'
#define C 'C'
#define E 'E'

// 逻辑运算
// (注意：由于参数不是bit类型, 因此使用的是逻辑运算符而非位运算符)
#define _K(w, x) ((w) && (x))		//	K --> and:  w && x
#define _A(w, x) ((w) || (x))		//	A --> or:  w || x
#define _N(w) (!(w))				//	N --> not :  !w
#define _C(w, x) ((!(w)) || (x))	//	C --> implies :  (!w) || x
#define _E(w, x) ((w) == (x))		//	E --> equals :  w == x


/*  
 * 判断逻辑表达式的运算结果是否为真
 * @param WFF 逻辑表达式
 * @param code 当前的变量值编码表
 * return true:值为真; true:值为假
 */  
bool isTrue(char* WFF, char code);


/*  
 * 提取变量字符当前的编码值
 * @param ch 变量字符:p,q,r,s,t
 * @param code 当前的变量值编码表
 * return 0: ch = 0
 *        1: ch = 1 
 *        2: ch不是变量字符
 */  
char toVal(char ch, char code);


/*  
 * 取出栈顶元素
 * @param st 栈
 * return 栈顶元素
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

	// 从后向前推演表达式的值
	for(int i = LEN - 1; i >= 0; i--) {
		char ch = WFF[i];
		char val = toVal(ch, code);

		// ch是逻辑变量, 直接入栈
		if(val <= 1) {
			wffStack.push(val);

		// ch是逻辑运算符, 从栈中取出元素运算后, 把结果回栈
		} else {

			// 一目运算
			if(N == ch) {
				char w = getTop(&wffStack);
				wffStack.push(_N(w));

			// 二目运算
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
	
	// 最终栈内只剩下1个元素且值为真
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
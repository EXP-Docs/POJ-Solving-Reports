/*
	Author:     Exp
	Date:       2017-12-03
	Code:       POJ 1018
	Problem:    Communication System
	URL:		http://poj.org/problem?id=1018
*/

/*
	���������
	  ��Ŀ���������ñȽ��ƿڣ�����������Ŀ���Ĳ�����������������һ�£�

	              ������   ����m1     ����m2    ����m3
	              ������   B1   P1    B2  P2    B3 P3
	  ·���豸n1��  3     [100 25]   [150 35]  [80 25]
	  ·���豸n2��  2     [120 80]   [155 40]
	  ·���豸n3��  2     [100 100]  [120 110]

	  �򵥶��ԣ���n��ͨѶ�豸���ڱ����п���ȳ�����·��������
	  ÿ��·����������1�����ҡ���������m�����Ҹ���������
	  ��Ȼ����ͬ�ĳ���������·�����Լ۱ȶ��ǲ�һ���ģ�
	  ��Ӱ��·�����Լ۱ȵ�ȡ������ ����B �� �۸�P

	  ����ĳͨѶ��˾Ҫ�ɹ�n��·��������Ϊһ������ϵͳ��
	  ÿ��·�������ԴӲ�ͬ�ĳ����вɹ���

	  ���ڴ�����ڶ̰�ЧӦ���������ϵͳ�������� sysB ȡ������n��·������С�Ĵ���
	  ���������ϵͳ�ļ۸� sysP ������n��·�ɵļ۸�֮��

	  ������õ��Լ۱�ΪĿ��ȥѡ��n��·����װ����ϵͳ��
	  ����Լ۱ȵ�ֵ sysB/sysP �Ƕ��� ?


	����˼·��
	  ���������˳�ѧ��Χ���ж��ֽⷨ����ö�١�̰�ġ���������̬�滮�ȡ�
	  ʹ�ö�̬�滮�����Ͻ���˼·��

	  ������Ҫ��״̬��
	    ��ĿҪ�������״̬�Լ۱����� ����ͼ۸� ��������Ӱ��ģ����׹���DP��״̬ת�Ʒ��̡�
		Ϊ�˿ɽ�����״̬ת��Ϊ�������⼯��
		������[���ִ���]���������װ����ϵͳ��[��С�۸�]��
		���ͨ���Ƚ�������⼯�Ľ⼯�����Ժ����׵õ������Լ۱ȡ�


	  ���ݡ���[���ִ���]���������װ����ϵͳ��[��С�۸�]�� ���Ի���״̬ת������ͼ��
	  �񣺺ڵ��ʾ ״̬��ʼ/����
	  �𣺰׵��ʾ ����m��������·���豸n�� ����B
	  �w�����߱�ʾ ѡ�񳧼�m��������·���豸n�� �۸�P

	               �豸n1      �豸n2     �豸n3

	����m1            �� ------- �� ------- �� 
	               �u    �v  �u.    �v  �u    �v 
	             �u        �w .       �w        �v
	           �u        �u  .�v    �u  �v        �v
	����m2  �� ------ �� ---.--- �� ------- �� ----- ��
	           �v          .  �u
	             �v       . �u
	               �v    .�u
	����m3	          ��

	
	״̬ת������ͼ��ӳ�ˣ�
	  �� �ӿ�ʼ������״̬��ÿ��·�߶�����װ����ϵͳ��һ����ѡ��
	  �� ÿ��һ��·���豸���Ͷ�һ�����ѡ��
	  �� ÿ��·�ߵ�������ȡ���ڴ���ֵ��С���Ǹ�·��
	  �� ÿ��·�����������ߵļ۸�֮�;�����װϵͳ���ܼ�


	���ڿ��Ը��� ״̬ת������ͼ ���� ״̬ת�Ʒ��̣�DP���̣�:
	 �� n���豸��
		m��������
	    B(e, f) ��ʾ �豸e������f����ʱ�Ĵ���B
	    P(e, f) ��ʾ �豸e������f����ʱ�ļ۸�P
		���� e��[1,n]. f��[1,m]

	 �� dp(e, B) ��ʾѡ��[ǰe��]·���豸�����ɴ���ΪB��ϵͳ����֧������С�۸�
	 ע��B����ɢ�ģ�����Ϊ�̰�ЧӦ��[ǰe-1��]·���豸���ɵĴ���Ӱ��

	 ��ô״̬ת�Ʒ���Ϊ��
		�� �� e = 1 ʱ��
			for(f = 1 : m) {
				b = B(e, f);
				p = P(e, f);
				dp(e, b) = min{ dp(e, b), p };
			}
		�� �� e > 1 ʱ��
			for(e = 2 : n) {
				for(f = 1 : m) {
					for(bandwidth : ǰe-1�ξ�������Ч��ϵͳ����) {
						b = min{ B(e, f), bandwidth };		// �̰�ЧӦ
						dp(e, b) = min{ dp(e, b), dp(e - 1, bandwidth) + P(e, f) };
					}
				}
			}

		ע��Ϊ�˹���dp(e, B)״̬���飬��ʵ��ȱ��һ����Ҫ����������B��ȡֵ��Χ.
			����Ŀ��δ���������Χ��ֻ��ͨ�����Խ��в²⣬�Ӳ²�������� B��[1,400]

			��ʵ�����ݽṹ�Ƕȿ�������B����ɢ�ģ�dp(e, B) ���ʹ�� dp[e][map<B, P>] ����ʽ��
			����һά�����飬�ڶ�ά��map��ʹ���������ݽṹ������Ԥ�����B�ķ�Χ��
			��������STL��mapά�����۹��ߣ������TLE��ʱ����˷������������ݽṹ��
*/


#include <iomanip>
#include <iostream>
using namespace std;

const static int INVAILD = 0x7FFFFFFF;	// ��Чֵ
const static int MAX_B = 400;	// ������ֵ(�������ݵ����ޣ����������ݱ�������)


/**
 * ����·���豸�齨��ͨѶϵͳ
 */
class CSystem {
	public:
		CSystem(int eqNum);
		~CSystem();

		void init();	// ��ʼ��·��ϵͳ����
		void solve();	// ʹ��DP����·��ϵͳ�����豸����µ��Լ۱�
		void print();	// ��ӡ����������Լ۱ȣ�

	private:
		int min(int a, int b);	// ��������������Сֵ

	private:
		int eqNum;		// ·���豸��
		int* facNums;	// facNums[e]: ���������豸e�ĳ�����
		int** Bs;		// Bs[e][f]: �豸e������f����ʱ�Ĵ���B
		int** Ps;		// Ps[e][f]: �豸e������f����ʱ�ļ۸�P
		int** dp;		// dp[e][b]: ѡ��ǰe���豸�����ɴ���Ϊb��ϵͳ����֧������С�۸�
};


int main(void) {
	int testCase = 0;	// ����������
	cin >> testCase;
	for(int t = 0; t < testCase; t++) {
		int eqNum = 0;	// �豸��
		cin >> eqNum;

		CSystem* cSystem = new CSystem(eqNum);
		cSystem->init();	// ��ʼ��·��ϵͳ����
		cSystem->solve();	// ʹ��DP����·��ϵͳ�����豸����µ��Լ۱�
		cSystem->print();	// ��ӡ����������Լ۱ȣ�
		delete cSystem;
	}
	return 0;
}


CSystem::CSystem(int eqNum) {
	this->eqNum = eqNum;
	if(eqNum > 0) {
		this->facNums = new int[eqNum];
		this->Bs = new int*[eqNum];
		this->Ps = new int*[eqNum];
		this->dp = new int*[eqNum];
	}
}


CSystem::~CSystem() {
	if(eqNum > 0) {
		delete[] facNums; facNums = NULL;
		delete[] Bs; Bs = NULL;
		delete[] Ps; Ps = NULL;
		delete[] dp; dp = NULL;
	}
}


int CSystem::min(int a, int b) {
	return (a <= b ? a : b);
}


void CSystem::init(void) {
	for(int e = 0; e < eqNum; e++) {
		cin >> facNums[e];
		int facNum = facNums[e];

		Bs[e] = new int[facNum];
		Ps[e] = new int[facNum];
		for(int f = 0; f < facNum; f++) {
			cin >> Bs[e][f] >> Ps[e][f];
		}

		// �˴�����memset��ʼ��dp����Ϊmemsetֻ�ܳ�ʼ��Ϊ0��-1
		dp[e] = new int[MAX_B];
		for(int B = 0; B < MAX_B; B++) {
			dp[e][B] = INVAILD;
		}
	}
}


void CSystem::solve() {
	for(int e = 0; e < eqNum; e++) {
		int facNum = facNums[e];
		for(int f = 0; f < facNum; f++) {
			int B = Bs[e][f];	// ���ξ��ߵ��豸����
			int P = Ps[e][f];	// ���ξ��ߵ��豸�۸�

			// ��ʼ���״ξ��ߵĲ�����״̬
			if(e == 0) {
				dp[e][B] = min(dp[e][B], P);

			// ����ǰe�ξ��ߵĲ�����״̬
			} else {

				// ö��ǰһ�ξ���ʱ����Ч����
				for(int b = 0; b < MAX_B; b++) {
					if(dp[e - 1][b] < INVAILD) {	// ǰһ��״̬����
						int minB = min(B, b);		// ��ǰ״̬�Ĵ�����Ҫ����ǰһ��״̬����
						dp[e][minB] = min(dp[e][minB], dp[e - 1][b] + P);	// ����ת��״̬
					}
				}
			}
		}
	}
}


void CSystem::print() {
	double maxPCost = 0.0;	// �����Լ۱�
	if(eqNum > 0) {

		// ö�����һ�ξ��ߵĺ�ѡ�⼯���õ������Լ۱�
		for(int e = eqNum - 1, b = 0; b < MAX_B; b++) {
			if(dp[e][b] < INVAILD && dp[e][b] > 0) {
				double pCost = ((double) b) / ((double) dp[e][b]);
				maxPCost = (maxPCost < pCost ? pCost : maxPCost);
			}
		}
	}
	cout << fixed << setprecision(3) << maxPCost << endl;
}


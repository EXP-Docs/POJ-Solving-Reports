/*
	Author:     Exp
	Date:       2017-12-03
	Code:       POJ 1018
	Problem:    Communication System
	URL:		http://poj.org/problem?id=1018
*/

/*
	题意分析：
	  题目本身描述得比较绕口，这里利用题目给的测试用例的输入描述一下：

	              生产的   厂家m1     厂家m2    厂家m3
	              厂家数   B1   P1    B2  P2    B3 P3
	  路由设备n1：  3     [100 25]   [150 35]  [80 25]
	  路由设备n2：  2     [120 80]   [155 40]
	  路由设备n3：  2     [100 100]  [120 110]

	  简单而言，有n种通讯设备（在本题中可类比成网络路由器），
	  每种路由器最少有1个厂家、最多可以有m个厂家负责生产，
	  当然，不同的厂家生产的路由器性价比都是不一样的，
	  而影响路由器性价比的取决于其 带宽B 和 价格P

	  现在某通讯公司要采购n个路由器集成为一个网络系统，
	  每个路由器可以从不同的厂家中采购。

	  由于带宽存在短板效应，这个网络系统的最大带宽 sysB 取决于这n个路由中最小的带宽
	  而这个网络系统的价格 sysP 等于这n个路由的价格之和

	  问以最好的性价比为目标去选购n个路由组装网络系统，
	  这个性价比的值 sysB/sysP 是多少 ?


	解题思路：
	  此题属于运筹学范围，有多种解法，如枚举、贪心、搜索、动态规划等。
	  使用动态规划更贴合解题思路。

	  首先需要简化状态。
	    题目要求的最终状态性价比是由 带宽和价格 两个变量影响的，不易构造DP的状态转移方程。
		为此可将问题状态转化为以下问题集：
		【求在[各种带宽]的情况下组装网络系统的[最小价格]】
		最后通过比较这个问题集的解集，可以很容易得到最优性价比。


	  根据【在[各种带宽]的情况下组装网络系统的[最小价格]】 可以画出状态转移拓扑图：
	  ●：黑点表示 状态开始/结束
	  ○：白点表示 厂家m所生产的路由设备n的 带宽B
	  ╳：连线表示 选择厂家m所生产的路由设备n的 价格P

	               设备n1      设备n2     设备n3

	厂家m1            ○ ------- ○ ------- ○ 
	               ╱    ╲  ╱.    ╲  ╱    ╲ 
	             ╱        ╳ .       ╳        ╲
	           ╱        ╱  .╲    ╱  ╲        ╲
	厂家m2  ● ------ ○ ---.--- ○ ------- ○ ----- ●
	           ╲          .  ╱
	             ╲       . ╱
	               ╲    .╱
	厂家m3	          ○

	
	状态转移拓扑图反映了：
	  ① 从开始到结束状态的每条路线都是组装网络系统的一个候选解
	  ② 每多一个路由设备，就多一层决策选择
	  ③ 每条路线的最大带宽取决于带宽值最小的那个路由
	  ④ 每条路线上所有连线的价格之和就是组装系统的总价


	现在可以根据 状态转移拓扑图 构造 状态转移方程（DP方程）:
	 令 n：设备数
		m：厂家数
	    B(e, f) 表示 设备e被厂家f生产时的带宽B
	    P(e, f) 表示 设备e被厂家f生产时的价格P
		其中 e∈[1,n]. f∈[1,m]

	 令 dp(e, B) 表示选择[前e个]路由设备所构成带宽为B的系统所需支付的最小价格，
	 注意B是离散的，且因为短板效应受[前e-1个]路由设备构成的带宽影响

	 那么状态转移方程为：
		① 当 e = 1 时：
			for(f = 1 : m) {
				b = B(e, f);
				p = P(e, f);
				dp(e, b) = min{ dp(e, b), p };
			}
		② 当 e > 1 时：
			for(e = 2 : n) {
				for(f = 1 : m) {
					for(bandwidth : 前e-1次决策中有效的系统带宽) {
						b = min{ B(e, f), bandwidth };		// 短板效应
						dp(e, b) = min{ dp(e, b), dp(e - 1, bandwidth) + P(e, f) };
					}
				}
			}

		注：为了构造dp(e, B)状态数组，其实还缺了一个必要条件，带宽B的取值范围.
			而题目并未给出这个范围，只能通过测试进行猜测，从猜测情况来看 B∈[1,400]

			其实从数据结构角度看，由于B是离散的，dp(e, B) 最好使用 dp[e][map<B, P>] 的形式，
			即第一维是数组，第二维是map，使用这种数据结构就无需预测带宽B的范围。
			但是由于STL的map维护代价过高，会造成TLE超时，因此放弃了这种数据结构。
*/


#include <iomanip>
#include <iostream>
using namespace std;

const static int INVAILD = 0x7FFFFFFF;	// 无效值
const static int MAX_B = 400;	// 最大带宽值(测试数据的上限，若测试数据变更需调整)


/**
 * 若干路由设备组建的通讯系统
 */
class CSystem {
	public:
		CSystem(int eqNum);
		~CSystem();

		void init();	// 初始化路由系统参数
		void solve();	// 使用DP计算路由系统各种设备组合下的性价比
		void print();	// 打印结果（最优性价比）

	private:
		int min(int a, int b);	// 计算两个数的最小值

	private:
		int eqNum;		// 路由设备数
		int* facNums;	// facNums[e]: 可以生产设备e的厂家数
		int** Bs;		// Bs[e][f]: 设备e被厂家f生产时的带宽B
		int** Ps;		// Ps[e][f]: 设备e被厂家f生产时的价格P
		int** dp;		// dp[e][b]: 选择前e个设备所构成带宽为b的系统所需支付的最小价格
};


int main(void) {
	int testCase = 0;	// 测试用例数
	cin >> testCase;
	for(int t = 0; t < testCase; t++) {
		int eqNum = 0;	// 设备数
		cin >> eqNum;

		CSystem* cSystem = new CSystem(eqNum);
		cSystem->init();	// 初始化路由系统参数
		cSystem->solve();	// 使用DP计算路由系统各种设备组合下的性价比
		cSystem->print();	// 打印结果（最优性价比）
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

		// 此处不用memset初始化dp，因为memset只能初始化为0或-1
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
			int B = Bs[e][f];	// 本次决策的设备带宽
			int P = Ps[e][f];	// 本次决策的设备价格

			// 初始化首次决策的参数与状态
			if(e == 0) {
				dp[e][B] = min(dp[e][B], P);

			// 更新前e次决策的参数与状态
			} else {

				// 枚举前一次决策时的有效带宽
				for(int b = 0; b < MAX_B; b++) {
					if(dp[e - 1][b] < INVAILD) {	// 前一个状态存在
						int minB = min(B, b);		// 当前状态的带宽需要根据前一个状态而定
						dp[e][minB] = min(dp[e][minB], dp[e - 1][b] + P);	// 更新转移状态
					}
				}
			}
		}
	}
}


void CSystem::print() {
	double maxPCost = 0.0;	// 最优性价比
	if(eqNum > 0) {

		// 枚举最后一次决策的候选解集，得到最优性价比
		for(int e = eqNum - 1, b = 0; b < MAX_B; b++) {
			if(dp[e][b] < INVAILD && dp[e][b] > 0) {
				double pCost = ((double) b) / ((double) dp[e][b]);
				maxPCost = (maxPCost < pCost ? pCost : maxPCost);
			}
		}
	}
	cout << fixed << setprecision(3) << maxPCost << endl;
}


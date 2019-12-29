## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1018] [[Communication System](http://poj.org/problem?id=1018)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

某公司要建立一套通信系统，该通信系统需要n种设备，而每种设备分别可以有m1、m2、m3、…、mn个厂家提供生产，而每个厂家生产的同种设备都会存在两个方面的差别：带宽bandwidths 和 价格prices。

现在每种设备都各需要1个，考虑到性价比问题，要求所挑选出来的n件设备，要使得B/P最大。

其中B为这n件设备的带宽的最小值，P为这n件设备的总价。


## 测试数据

- 来源（已失效）：[Tehran 2002, First Iran Nationwide Internet Programming Contest（问题C）](http://sina.sharif.edu/~acmicpc/acmicpc02/inipc/inipcprobs.html)
- [input](/reports/POJ1018-Communication%20System/testdata/input.dat)
- [output](/reports/POJ1018-Communication%20System/testdata/output.dat)


## AC 源码

> [Download Link](/reports/POJ1018-Communication%20System/src)


------ 

### 解题思路一：动态规划

```c
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


```

------

### 解题思路二：枚举+剪枝

首先需要明确，要使得 B/P 最大，自然是要令 B 尽可能大，P 尽可能小。

由于 B 和 P 是两个相互制约的变量，而他们又要同时取得尽可能地取极值，那么可以先令其中一个值“暂时固定”下来。

令输入的行数就是设备的种类数，即第i行描述的是第i种设备，及提供第i种设备的厂家的产品信息。

**使用枚举+剪枝的做法**：

首先B的值肯定是厂家生产的所有设备中的某个带宽值，所以可以枚举所有的带宽，每次枚举 B 值时，B 值就被“暂时固定”了。

其次，记录所选取的 B 是属于第 k 种设备的，再从余下的设备中，选取其余 n-1 种设备各一个，要求所选取的设备的带宽 `>=B`（这是由题意确定的），而价格是要满足带宽的要求下的最小值。

当 n 种设备都选取后，计算 B/P，然后再枚举下一个 B，重复上述操作。比较不同的B值所得到的 B/P 值，选取最大的一个就是答案。

**准备工作**：

- 输入时先记录：对于每种设备，厂家所提供的最大带宽 `MaxB[]`
- 对所有设备（无论是否同种类）进行升序快排，以带宽为第一关键字，价格为第二关键字，设备所属的种类编号(`1~n`)为第三关键字。排序后存放在一维数组 `dev[]`

**剪枝**：

- （1）从小到大枚举 `dev[]` 中各个设备的带宽作为 B 值，设总设备数位 m，则从 1 枚举到 `m-(n-1)`。这是因为至少需要选择从枚举位置开始后面的 n 种设备，`m-(n-1)` 是上限值，即恰好最后 n 件设备分别为 n 种设备。
- （2）枚举 B 值的过程中，若发现 B 值比某种设备的最大带宽更大，则无需继续枚举，输出前面得到的 B/P 值。这是因为 B 是所有设备的最小带宽，若出现某个设备的最大带宽比 B 小，则说明 B 的选择是不合法的，又 `dev[]` 已按B升序排序，后面的 B 值更大，也不可能成立，因此无需继续枚举。
- （3）枚举 B 值过程中，对于每个 B 值，在选择其他设备时要记录选取不同种类的设备个数 count 。最后当 `count<n` 时，说明B值位置往后剩余的设备中已无法提供 n-1 种不同设备，可直接跳出枚举。


关于剪枝（2）比较难懂，再稍微解释一下，以题目给定的数据为例： 

```
1 3 
3 100 25 150 35 80 25
2 120 80 155 40
2 100 100 120 110
```

把该组数据升序排序，得到：

```
B:  80  100  100  120  120  150  155

P:  25  25   100   80  110   35   40

Id:  1   1     3    2    3    1    2
```

这样当 B 枚举到 150 的时候，即 `B=150` ,第三个供应商的所有设备都小于 150，取任何一个设备都会导致 `B<150`，矛盾。当然大于 150 的更不用枚举了，直接剪掉。

```c
//Memory Time 
//1688K  188MS 

#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

class info
{
public:
	int B;   //带宽
	double P;   //价格
	int id;  //设备号码
};

int cmp(const void* a,const void* b)
{
	info* x=(info*)a;
	info* y=(info*)b;

	if((x->B)==(y->B))   //当带宽相等时
	{
		if((x->P)==(y->P))   //当价格也相等时
			return (x->id)-(y->id);   //以编号为第三优先升序排序

		return (x->P)-(y->P);   //以价格为第二优先升序排序
	}

	return (x->B)-(y->B);   //以带宽为第一优先升序排序
}

double max(double a,double b)
{
	return a>b?a:b;
}

int main(int i,int j)
{
	int test;
	cin>>test;
	for(int t=1;t<=test;t++)
	{
		int n;  //设备数
		int m=0;  //生产商总数
		cin>>n;

		int* MaxB=new int[n+1];  //各种设备对应的带宽最大值
		info* dev=new info[100*100+1];     //记录所有厂家生产的产品信息

		int pd=0;  //dev[]指针

		/*Input*/

		
		for(i=1;i<=n;i++)
		{
			int mi;
			cin>>mi;
			m+=mi;

			MaxB[i]=-1;
			for(j=1;j<=mi;j++)
			{
				pd++;
				cin>>dev[pd].B>>dev[pd].P;
				dev[pd].id=i;

				MaxB[i]=max(MaxB[i],dev[pd].B);
			}
		}

		/*Qsort*/

		qsort(dev,m+1,sizeof(info),cmp);

		/*Enum*/

		bool flag=false;
		double ans=0;  // B/P的最大值
		for(i=1;i<=m-(n-1);i++)  //枚举所有设备带宽的最小带宽B
		{                        //m-(n-1)是剪枝，因为当设备数>生产商数时就不必枚举了
			bool* vist=new bool[n+1];
			memset(vist,false,sizeof(bool)*(n+1));

			vist[ dev[i].id ]=true;
			double price=dev[i].P;  //设备总价
			int count=1;   //计数器，记录已经选取的设备个数

			for(j=i+1;j<=m;j++)
			{
				if(vist[ dev[j].id ])
					continue;

				if(dev[i].B > MaxB[ dev[j].id ])  //剪枝
				{
					flag=true;  //当前枚举的 "所有设备带宽的最小带宽Bi" 比 "设备j的最大带宽MaxBj" 要大
					break;      //说明当前Bi已经越界，无需继续往后枚举
				}

				vist[ dev[j].id ]=true;
				price+=dev[j].P;
				count++;
			}
			if(flag || count<n)
				break;

			ans=max(ans,(dev[i].B/price));
		}

		cout<<fixed<<setprecision(3)<<ans<<endl;

		delete MaxB;
		delete dev;
	}
	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

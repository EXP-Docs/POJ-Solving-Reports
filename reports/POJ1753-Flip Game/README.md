# [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1753] [[Flip Game](http://poj.org/problem?id=1753)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 枚举]

------

## 问题描述

此题与 [POJ2965](/reports/POJ2965-The%20Pilots%20Brothers'%20refrigerator) 类似

## 解题思路

翻转棋，可以建模为多叉树

**本题难点有两个**：

- 一个就是不要以全黑（或全白）作为目标进行搜索，而是要把全黑（或全白）作为“根”，去搜索树叶，看看是否有 输入的棋盘状态。
- 另一个难点需要一点数学功底，就是要知道 树 的最大高度，这是“状态不存在”的判断标准

注意：其实每格棋子最多只可以翻转一次（实际是奇数次，但这没意义），只要其中一格重复翻了 2 次(不论是连续翻动还是不连翻动)，那么它以及周边的棋子和没翻动时的状态是一致的，由此就可以确定这个棋盘最多只能走 16 步，最多只能有翻出 2^16 种状态 


**本题有两种解法**：

- 一种是常规思路，枚举所有状态，直至找到目标状态，而且由于只需要输出该种状态所在树的深度，因此推荐BFS，比较快，但DFS也可以的
- ◇ 另外一种思路比较有技巧性，由于是 4×4 棋盘，因此利用了十六进制数的位数，通过一系列位运算达到目标

## AC 源码

> [Download Link](/reports/POJ1753-Flip%20Game/src)

```c
/*
	Author:     Exp
	Date:       2017-12-04
	Code:       POJ 1753
	Problem:    Flip Game
	URL:		http://poj.org/problem?id=1753
*/

/*
	【题意分析】
	 有一4x4棋盘，上面有16枚双面棋子（一面为黑，一面为白），
	 当翻动一只棋子时，该棋子上下左右相邻的棋子也会同时翻面。
	 以b代表黑面，w代表白面，给出一个棋盘状态，
	 问从该棋盘状态开始，使棋盘变成全黑或全白，至少需要翻转多少步


	【解题思路】
	  此题有多种解法，枚举、搜索（BFS、DFS）均可。
	  搜索的方法网上已有很多人给出（我本人几年前也给过2种搜索代码），
	  这里补充一下枚举的思路。

	  ========================================

	  首先需要等价变换一下问题，题目需要求的是棋盘从某状态到达全黑/全白的最小翻转步数，
	  可等价变成棋盘从全黑/全白状态开始，到达指定状态的最小翻转步数，更便于处理

	  为了简化问题，这里进一步把问题简化为【棋盘从全黑状态开始，到达指定状态的最小翻转步数】
	  只要求到全黑的答案，全白的答案是可以直接推导的，这个后面再说。


	  那么枚举的思路就很简单了：
		① 预先打表计算出【棋盘从全黑状态开始，到达所有不重复状态的最小翻转步数】
		② 任意给定一个状态，查表有这个状态，则直接输出步数；否则输出不可达

	  ========================================

	  为了便于记录棋盘状态，这里使用二进制数对棋盘状态进行压缩，具体方法如下：

	  对棋盘矩阵进行编码：
	    * * * *      从左到右分别为第 0, 1, 2, 3位
	    % % % %      从左到右分别为第 4, 5, 6, 7位
	    # # # #      从左到右分别为第 8, 9,10,11位
        @ @ @ @      从左到右分别为第12,13,14,15位

	  由于棋盘每一格只有黑白两种状态，可用0、1进行表示，由此可转换成二进制数：
	    @@@@ #### %%%% ****
	   15      ←         0

	  最终可以用一个 unsigned int 数（共32位，这里使用低16位）存储整个棋盘状态，
	  令 黑=0，白=1：
	    ① 当翻转某一位上的棋子时，相当于使该位与 二进制1 做异或运算.
		② 棋盘处于全黑状态时，unsigned int 的低16位值为 0x0000
		③ 棋盘处于全白状态时，unsigned int 的低16位值为 0xFFFF

	  ========================================

	  另一方面，不难可以看出每格棋子最多只可以翻转1次，
	  这是因为只要其中一格重复翻了2次(不论是连续翻动还是不连翻动)，
	  那么它以及周边的棋子和没翻动时的状态是一致的，
	  由此就可以确定这个4x4棋盘【理论上最多只能翻16次，共2^16 = 65536 种状态】


	  为了记录翻转过的棋子，可以把 unsigned int 数的高16位也利用起来，
	  令高16位为棋盘操作位，从全0（全黑）状态开始，翻动过的棋子位置标记为1，没翻动过的标记为0

	  这样我们就可以通过充分利用一个  unsigned int 数的32位，
	  记录棋盘在处于某个状态时的编码，包括翻转过的棋子位置、以及当前棋子的翻转情况。
	

	  ========================================

	  确定了棋盘状态的记录方式，就可以开始枚举所有棋盘状态了。
	  首先理解几个前提条件：
		① 棋盘初始状态为全0（暂不考虑全1）
		② 一次只能翻转一个棋子，不能重复翻转同一个棋子（因为会还原状态，无意义）
		③ 最多只能翻转 4x4 = 16 次
		④ 第 n 次的翻转操作是基于 第 n-1 次的所有可能的棋盘状态
		⑤ 可能存在不同的翻转次数，会得到相同的棋盘状态

	  根据①②③④，这里可以使用BFS的思想:
		从初始状态开始，分别记录16步（类比16层的树）翻转操作中每一步的所有棋盘状态。

	  而④⑤可以用来指导BFS过程的剪枝，用于加速搜索：
	    若第 i、j 步的（i<=j）翻转操作均出现了状态A，那么第j步的状态A舍弃，
		这是因为从第j步的状态A又会引申出大量重复状态，且步长必定比第i步长。


	  ========================================

	  上述解题方法是针对初始状态为全0（全黑）情况下的，
	  那么初始状态为全1（全白）需要重新计算一次所有状态么？
	  不需要，其实很简单。

	  当已经计算出初始状态为全0时、在16步内可到达的所有棋盘状态后，
	  对于给定某个棋盘状态，只要对该棋盘状态取反（黑变白、白变黑），
	  那么【取反后的棋盘状态到达全0需要的最小步数】等价于【原棋盘状态到达全1需要的最小步数】



	  注意这里有个误区：
	   【不能】先计算原棋盘状态到达全0需要的最小步数，再用16减去之
	   全0与全1导向的结果集并不是减法意义上的互补

	  事实上，把BFS搜索到的全状态列印出来可以发现：
	   ① 重复状态多达61440种，有效状态只有4096种
	   ② 有效状态在第8步之前就可全部找到（准确而言是0-7步），且不是呈对称分布
	   ③ 从全0到全1只需经过4步翻转
	   ④ 这种结果分布主要是受翻棋时所影响的棋子范围所决定的
*/


#include <set>
#include <iostream>
using namespace std;

// 无符号整型(32位)，用于记录棋盘编码，主要为了避免int32的负数影响
// 初始棋盘状态为全0（全黑）
// 高16位为棋盘操作位，翻动过的棋子位置标记为1
// 低16位为棋盘状态位, 记录当前棋盘状态（白朝上为1，黑朝上为0）
typedef unsigned int _UINT;


const static int MAX_STEP = 16;			// 可翻棋的最大步数
const static int MAX_STATUS = 65536;	// 总状态数 = 2^16（含重复数）


// 棋盘状态掩码：当翻转位置i的棋子时,STATUS_MASKS[i]为所有受影响的相邻位置
// 位置i：在4x4棋盘内，从左到右、从上到下按0-15依次编码
const static _UINT STATUS_MASKS[MAX_STEP] = {
	0x00000013, 0x00000027, 0x0000004E, 0x0000008C,
	0x00000131, 0x00000272, 0x000004E4, 0x000008C8,
	0x00001310, 0x00002720, 0x00004E40, 0x00008C80,
	0x00003100, 0x00007200, 0x0000E400, 0x0000C800
};


/**
 * 棋盘对象
 */
class Chess {
	public:
		Chess();
		~Chess();
		int getStep(int status);	// 计算从全0或全1状态到达指定棋盘状态的最小步数
		
	private:
		void bfsAllStatus(void);			// 记录不重复地翻动1-16步可得到的所有棋盘状态
		_UINT filp(_UINT chess, int bitPos);// 翻动棋盘上某个指定位位置的棋子
		
		int toStatus(_UINT chess);		// 从棋盘编码提取棋盘状态信息
		int getMaxBitPos(_UINT chess);	// 从棋盘编码提取棋盘操作信息，获得其中最大翻转编号的位置
		int getFilpCount(_UINT chess);	// 从棋盘编码提取棋盘操作信息，获取棋盘从全0状态开始共被翻动棋子的次数
		int min(int a, int b);		// 返回最小值

	private:
		set<_UINT>* chesses;	// 从棋盘全0开始，分别记录不重复地翻动1-16步可得到的所有棋盘编码
		int* steps;				// 从棋盘全0开始，到达指定棋盘状态需要翻动棋子的最小步数
};


int main(void) {
	// 一次计算把所有棋盘状态打表
	Chess* chess = new Chess();

	// 迭代输入棋盘状态 查表
	int chessStatus = 0;
	int byteCnt = 0;
	char byteBuff[5] = { '\0' };
	while(cin >> byteBuff && ++byteCnt) {
		int offset = 4 * (byteCnt - 1);
		for(int i = 0; i < 4; i++) {
			if(byteBuff[i] == 'w') {	// b标记为0, w标记为1
				chessStatus |= (0x00000001 << (i + offset));
			}
		}

		// 每输入4个字节求解一次
		if(byteCnt >= 4) {
			int step = chess->getStep(chessStatus);
			if(step >= 0) {
				cout << step << endl;
			} else {
				cout << "Impossible" << endl;
			}

			byteCnt = 0;
			chessStatus = 0;
		}
	}
	delete chess;
	return 0;
}


/**
 * 构造函数
 */
Chess::Chess() {
	this->chesses = new set<_UINT>[MAX_STEP + 1];

	this->steps = new int[MAX_STATUS];
	memset(steps, -1, sizeof(int) * MAX_STATUS);

	bfsAllStatus();
}


/**
 * 析构函数
 */
Chess::~Chess() {
	for(int s = 0; s <= MAX_STEP; s++) {
		chesses->clear();
	}
	delete[] chesses; chesses = NULL;
	delete[] steps; steps = NULL;
}


/**
 * 初始化不重复地翻动1-16步可得到的所有棋盘状态
 */
void Chess::bfsAllStatus(void) {
	const int ALL_ZERO_CHESS = 0;
	steps[0] = ALL_ZERO_CHESS;	// 初始状态，棋盘全黑
	chesses[0].insert(ALL_ZERO_CHESS);	// 即翻动0次的状态集

	// 记录以不重复的组合方式翻动1-16次的可以到达的所有状态集
	for(int filpStep = 1; filpStep <= MAX_STEP; filpStep++) {
		set<_UINT>* lastChesses = &chesses[filpStep - 1];	// 上一步的状态集
		set<_UINT>* nextChesses = &chesses[filpStep];		// 下一步的状态集

		// 迭代上一步每个棋盘状态，在其基础上均多翻一个棋子，作为下一步的状态集
		for(set<_UINT>::iterator its = lastChesses->begin(); its != lastChesses->end(); its++) {
			_UINT lastChess = *its;	// 上一次棋盘状态编码

			// 剪枝1：棋子是从低位编号开始翻动的，为了不重复翻动棋子，从上一棋盘状态的最高位编号开始翻动
			for(int pos = getMaxBitPos(lastChess) + 1; pos < MAX_STEP; pos++) {
				_UINT nextChess = filp(lastChess, pos);	// 翻动棋子得到下一个棋盘状态编码
				int status = toStatus(nextChess);		// 屏蔽高16位操作位，得到低16位的真正棋盘状态

				// 剪枝2：仅不重复的状态才需要登记到下一步的状态集
				// 注意这里使用steps数组进行全局状态判重，而不能仅仅使用nextStatus对本次翻动判重
				if(steps[status] < 0) {	
					steps[status] = filpStep;		// 状态首次出现的步数必定是最小步数
					nextChesses->insert(nextChess);

				} else {
					// Undo: 重复状态不再记录到状态集
					//  通过不同步数、翻棋组合可达到的重复状态共61440种，
					//  总翻棋次数才65536，换言之有效状态只有4096种，
					//  这步剪枝是很重要的，否则必定超时
				}
			}
		}

		// 剪枝3：当前状态集（因剪枝导致）全空，则后面所有状态集无需再计算
		if(nextChesses->empty()) {
			break;
		}
	}
}


/**
 * 翻动棋盘上某个指定位位置的棋子,
 *  此操作会同时改变棋盘编码的操作位（高16位）和状态位（低16位）
 * @param chess 翻转前的棋盘编码
 * @param bitPos 要翻转的棋子位置, 取值范围为[0, 15]，
 *				依次对应4x4棋盘上从左到右、自上而下的编号，也对应二进制数从低到高的进制位
 * return 翻转后的棋盘编码
 */
_UINT Chess::filp(_UINT chess, int bitPos) {
	_UINT OP_MASK = 0x00010000 << bitPos;		// 高16位:当前操作位
	_UINT STATUS_MASK = STATUS_MASKS[bitPos];	// 低16位:相关状态位
	return (chess ^ (OP_MASK | STATUS_MASK));	// 更新棋盘编码
}

/* 常规翻转棋子的方法，比较易懂但运算量大，不推荐
_UINT Chess::filp(_UINT chess, int bitPos) {

	// 高16位:当前操作位
	_UINT op = 0x00010000 << bitPos;

	// 低16位:相关状态位
	const _UINT BASE = 0x00000001;
	op |= BASE << bitPos;	// 翻转棋子自身位置
	if(bitPos > 3) { op |= BASE << (bitPos - 4);  }	// 翻转棋子上方的棋子
	if(bitPos < 12) { op |= BASE << (bitPos + 4);  }	// 翻转棋子下方的棋子

	int mod = bitPos % 4;
	if(mod != 0) { op |= BASE << (bitPos - 1);  }	// 翻转棋子左方的棋子
	if(mod != 3) { op |= BASE << (bitPos + 1);  }	// 翻转棋子右方的棋子

	return chess ^ op;	// 更新棋盘编码
}
*/

/**
 * 从棋盘编码提取棋盘状态信息（低16位）
 * return 棋盘状态信息
 */
int Chess::toStatus(_UINT chess) {
	const _UINT MASK = 0x0000FFFF;
	return (int) (chess & MASK);
}


/**
 * 从棋盘编码提取棋盘操作信息（高16位），获得其中最大翻转编号的位置
 * @param chess 棋盘编码
 * return 没有操作过则返回-1，否则返回0-15
 */
int Chess::getMaxBitPos(_UINT chess) {
	_UINT MASK = 0x80000000;
	int bitPos = -1;
	for(int i = MAX_STEP - 1; i >= 0; i--) {
		if((chess & MASK) == MASK) {	// 注意加括号, ==优先级比&要高
			bitPos = i;
			break;
		}
		MASK >>= 1;
	}
	return bitPos;
}


/**
 * 从棋盘编码提取棋盘操作信息（高16位），获取棋盘从全0状态开始共被翻动棋子的次数
 * @param chess 棋盘编码
 * return 被翻转次数
 */
int Chess::getFilpCount(_UINT chess) {
	const _UINT MASK = 0xFFFF0000;
	chess &= MASK;	// 屏蔽低16位的状态位

	// 判断高16位操作位有多少个1, 即为翻转次数
	int cnt = 0;
	while(chess > 0) {
		chess = (chess & (chess - 1));
		cnt++;
	}
	return cnt;
}


/**
 * 计算从全0或全1状态到达指定棋盘状态的最小步数
 * @param status 棋盘状态
 * return 最小步数（若不可达则返回-1）
 */
int Chess::getStep(int status) {
	int step = -1;
	if(status >= 0 && status < MAX_STATUS) {
		int bStep = steps[status];				// 从全0开始到达指定状态的步数
		int wStep = steps[toStatus(~status)];	// 取反，从全1开始到达状态chess的步数
		
		if(bStep >= 0 && wStep >= 0) {
			step = min(bStep, wStep);

		} else if(bStep >= 0) {
			step = bStep;

		} else if(wStep >= 0) {
			step = wStep;
		}
	}
	return step;
}


/**
 * 返回最小值
 * @param a 参数a
 * @param b 参数b
 * return 最小值
 */
int Chess::min(int a, int b) {
	return (a <= b ? a : b);
}

```

------

## 【附】历史代码

### 解法一：搜索

```c
/*代码一：DFS+Enum*/

//Memory Time 
//240K   344MS 

//本题只要求输出翻转的次数，因此BFS或DFS都适用

#include<iostream>
using namespace std;

bool chess[6][6]={false};//利用的只有中心的4x4
bool flag;
int step;
int r[]={-1,1,0,0,0};//便于翻棋操作
int c[]={0,0,-1,1,0};

bool judge_all(void)//判断“清一色”
{
	int i,j;
	for(i=1;i<5;i++)
		for(j=1;j<5;j++)
			if(chess[i][j]!=chess[1][1])
				return false;
	return true;
}

void flip(int row,int col)//翻棋
{
	int i;
	for(i=0;i<5;i++)
		chess[row+r[i]][col+c[i]]=!chess[row+r[i]][col+c[i]];
	return;
}

void dfs(int row,int col,int deep) //深搜的迭代回溯是重点，很容易混乱
{
	if(deep==step)
	{
		flag=judge_all();
		return;
	}

	if(flag||row==5)return;

	flip(row,col);       //翻棋
	if(col<4)
		dfs(row,col+1,deep+1);
	else
		dfs(row+1,1,deep+1);

	flip(row,col);      //不符合则翻回来
	if(col<4)
		dfs(row,col+1,deep);
	else
		dfs(row+1,1,deep);

	return;
}

int main(void)
{
	char temp;
	int i,j;
	for(i=1;i<5;i++)
		for(j=1;j<5;j++)
		{
			cin>>temp;
		    if(temp=='b') 
			    chess[i][j]=true;
		}

    for(step=0;step<=16;step++)  //对每一步产生的可能性进行枚举
	{                            //至于为什么是16，考虑到4x4=16格，而每一格只有黑白两种情况，则全部的可能性为2^16
		dfs(1,1,0);
		if(flag)break;
	}

	if(flag)
		cout<<step<<endl;
	else
		cout<<"Impossible"<<endl;
	return 0;
}
```

### 解法二：位运算

```c
/*代码二：BFS+Bit*/

//把矩阵看成一个16进制数
//每一行代表16进制数的一个字母（或数字），而每一个字母（或数字）又恰由4个二进制位数字0和1组成
//因此一个4x4矩阵是由16位0和1构成，是从 第0位 到 第15位
//如矩阵  

//        * * * *      从右到左分别为第 0, 1, 2, 3位
//        % % % %      从右到左分别为第 4, 5, 6, 7位
//        # # # #      从右到左分别为第 8, 9,10,11位
//        @ @ @ @      从右到左分别为第12,13,14,15位

//代表16进制数  

//   @@@@ #### %%%% ****
//  15      ←         0

//   将一个int的某位 取反 用该int与(0x1<<i)进行^操作。
  


#include<iostream> 

struct unit
{ 
	int x;   //用int的末16位记录16个位置的信息
	int rounds;   //记录第几轮达到当前的状态
	int i;   //记录该状态是通过翻动哪个棋子得来的，以避免返回先前的状态
}; 


//flip函数是从a状态通过翻动第i个棋子到达b状态

void flip(unit a, int i, unit& b)   //a是queue[p]的形参, 当前要翻动第i只棋子, b是queue[q]的引用
{ 
	int x = i / 4, y = i % 4;   //x、y为当前要翻动的第i只棋子所对应内节点的坐标（就是所翻动棋子的行x列y）
	b.x = a.x;      //即令queue[q].x=queue[p].x  ,即q先复制p（前一步）的状态，再对q进行翻转（对p状态无影响）
	b.x = ((b.x) ^ (0x1 << (i)));    //将一个b.x的第i位 取反，其实就是把 第i只棋子 翻转
	if (x > 0) 
		b.x = ((b.x) ^ (0x1 << (i - 4)));  //把 第i只棋子 上面的棋子翻转，当且仅当棋子i不在第0行时执行
	if (x < 3) 
		b.x = ((b.x) ^ (0x1 << (i + 4)));  //把 第i只棋子 下面的棋子翻转，当且仅当棋子i不在第3行时执行
	if (y > 0) 
		b.x = ((b.x) ^ (0x1 << (i - 1)));  //把 第i只棋子 右面的棋子翻转，当且仅当棋子i不在第0列时执行
	if (y < 3) 
		b.x = ((b.x) ^ (0x1 << (i + 1)));  //把 第i只棋子 左面的棋子翻转，当且仅当棋子i不在第3列时执行
	b.rounds = a.rounds + 1;   //当前执行翻转棋子的次数
	b.i = i; //记录当前翻转的是第i只棋子
	return;
} 

int main() 
{ 
	/*queue*/ 
	unit queue[100000];     //queue是一个队列，记录所有状态
	queue[0].x = 0;   //初始化为16进制的0（16进制的0和10进制的0是一样的）
	queue[0].i = -1; 
	queue[0].rounds = 0; 
	
	//judge used 
	bool used[100000]={false};    //used记录已经存在的状态
	/*read in*/ 
	char str[10]; 
	for (int i = 0; i < 4; i++) 
	{ 
		scanf("%s", str);  //一次输入一行字符串str（串长为4），输4次
		for (int j = 0; j < 4; j++)
			if (str[j] == 'b')  
				queue[0].x = ((0x1 << (i * 4 + j)) | (queue[0].x));  //位运算，遇b该位置1
	}                     // 0x1为16进制的1

	int p = 0, q = 0;     //p，q分别是队列的头尾指针

	//其实queue[p].x代表每一步的翻转前状态，queue[q].x代表每一步的翻转后状态

	while (!((queue[q].x == 0) || (queue[q].x == 0xFFFF)))      //当16进制数queue[q].x 不为0（全0）或15（全1）时执行
	{ 
		for (int i = 0; i < 16; i++)   //最多翻动16只棋子，i代表第i只棋子
		{ 
			if(queue[p].i==i)   //若翻动当前棋子i的前一步所翻的棋子queue[p].i就是i，则跳过不翻动
				continue; 
			q++;   //尾指针后移一位，为新状态“开辟”新的记录空间
			flip(queue[p], i, queue[q]); 
			if (used[queue[q].x])  //以棋盘的状态（一个16进制数）作为数组used的下标，对应的对象为true时说明这个状态已经出现过
				q--;               //在得到一个新状态的时候要检验之前时候存在这个状态，如果存在就把这个状态舍弃，即q--  
			                        //但是下一次循环则继续翻下一只棋子，与状态的舍弃无关，相当于本次所翻的棋子操作无效
			else
				used[queue[q].x]=true; //若该状态没有出现过，则记录该状态
			if ((queue[q].x == 0) || (queue[q].x == 0xFFFF))break; //棋盘状态为全0或全1时跳出for，由于while的条件关系，自然也跳出while
		} 

		if (p==q) //此条件为真时，当且仅当BFS到最后一层的最后一种状态时仍没有匹配的状态（全0或全1）
		{         //简单来说，就是当搜索到最后一层时，程序通过条件结束for,而不是通过break
			printf("Impossible");    //直至搜索结束，队列queue中都没有目标状态（此时为impossible）。 
			break; 
		} 

		p++; //头指针后移一位，把当前状态作为初始状态
	} 
	if ((queue[q].x == 0) || (queue[q].x == 0xFFFF))   //这是为了隔离因"impossible"时跳出while的情况
		printf("%d\n", queue[q].rounds); 
	return 0; 
} 
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

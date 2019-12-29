# [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2965] [[The Pilots Brothers' refrigerator](http://poj.org/problem?id=2965)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 枚举]

------

## 问题描述

此题与 [POJ1753](/reports/POJ1753-Flip%20Game) 类似

## AC 源码

> [Download Link](/reports/POJ2965-The%20Pilots%20Brothers'%20refrigerator/src)

### 解题思路一：枚举+状态压缩

```c
/*
	Author:     Exp
	Date:       2017-12-04
	Code:       POJ 2965
	Problem:    The Pilots Brothers' refrigerator
	URL:        http://poj.org/problem?id=2965
*/

/*
	题意分析：
	  有一冰箱，上面4x4共16个开关（"-"状态表示open，"+"状态表close）， 
	  当改变一个开关状态时，该开关所在行、列的全部开关状态也会同时改变。 

	  给出一个开关状态，问从该状态开始，使得所有开关打开（全"-"），
	  至少需要操作多少步，并把操作过程打印出来（打印所操作开关的行列坐标，坐标从1开始）


	解题思路：
	  这题和 POJ 1753 的解题思路是一模一样的，只是存在几个差异点，使得解题技巧稍微提高了一点.
	  没做 POJ 1753 的同学先去做了那题，理解了再回头做这题.

	  我这里偷懒，大部分都是直接套用了自己 POJ 1753 的代码，
	  因此详细的解题思路就不再复述了（大体思路都是 打表枚举所有状态，然后根据输入的状态查表）
	  
	  
	  这里只列出两题的差异，以及针对差异的处理手法（请在已理解并解决POJ 1753的前提下再看）：

		① 最终状态只有全0一种（即所有开关打开）， 而POJ-1753是全0或全1均可.
		   因此本题只需要枚举从全0状态到达任意状态的过程，无需考虑全1

		② 反转开关影响的是全列+全行共7个开关，而POJ-1753仅相邻棋子被影响

		③ 与 POJ-1753 一样，最多只能不重复地操作16次，即同样存在2^16=65536种状态，
		   但由于反转单个开关的影响范围改变了，这65536种不重复状态都是不重复的
		   （证明略，可BFS列印所有状态得到印证）

		④ 这题要求输出反转开关的过程，且题目标注为Special Judge（亦即一题多解）

		   这是因为操作同样的若干个开关，操作顺序不会影响最终导向的状态, 
		   因此反转对象是固定的，反转顺序随意打印，导致了一题多解的存在
		   （但由于不存在重复状态，反转次数是固定的）

		   在本题同样参考 POJ-1753 的状态压缩方式，即使用 unsigned int 存储开关状态，
		   高16位为操作码，低16位为状态码，那么所有操作过的开关都可以从高16位提取，
		   而且通过开关在操作码中的二进制位置，可以反向映射到4x4矩阵的行列坐标（行除4，列模4）
*/

#include <iostream>
using namespace std;


// 无符号整型(32位)，用于记录开关矩阵编码，主要为了避免int32的负数影响  
// 初始开关矩阵状态为全0（全"-"，即open）  
// 高16位为开关矩阵操作位，翻动过的开关位置标记为1  
// 低16位为开关矩阵状态位, 记录当前开关矩阵状态（"+"朝上为1:close，"-"朝上为0:open）  
typedef unsigned int _UINT;


const static int MAX_STEP = 16;			// 可反转开关矩阵的最大步数
const static int MAX_STATUS = 65536;	// 总状态数 = 2^16


// 开关矩阵状态掩码：当翻转位置i的开关时,STATUS_MASKS[i]为所有受影响的行列位置 
// 位置i：在4x4开关矩阵内，从左到右、从上到下按0-15依次编码  
const static int STATUS_MASKS[16] = {
	0x0000111F, 0x0000222F, 0x0000444F, 0x0000888F,
	0x000011F1, 0x000022F2, 0x000044F4, 0x000088F8,
	0x00001F11, 0x00002F22, 0x00004F44, 0x00008F88,
	0x0000F111, 0x0000F222, 0x0000F444, 0x0000F888
};


/**
 * 4x4的开关矩阵对象
 */
class SwitchGroup {
	public:
		SwitchGroup();
		~SwitchGroup();
		void print(int status);		// 打印从全0（open）到指定状态的最小操作步数以及操作过程
		
	private:
		void bfsAllStatus(void);				// 记录不重复地翻动1-16步可得到的所有开关矩阵状态
		_UINT filp(_UINT _switch, int bitPos);	// 翻动开关矩阵上某个指定位位置的开关
		
		int toStatus(_UINT _switch);		// 从开关矩阵编码提取状态信息
		int getMaxBitPos(_UINT _switch);	// 从开关矩阵编码提取操作信息，获得其中最大翻转编号的位置
		int getFilpCount(_UINT _switch);	// 从开关矩阵编码提取操作信息，获取从全0状态开始共被翻动开关的次数

	private:
		_UINT* switchs;		// 记录从全0(open)开始到达每个状态的开关矩阵编码
};


int main(void) {
	// 一次计算把所有开关矩阵状态打表
	SwitchGroup* switchGroup = new SwitchGroup();

	// 迭代输入开关矩阵状态 查表
	int switchStatus = 0;
	int byteCnt = 0;
	char byteBuff[5] = { '\0' };
	while(cin >> byteBuff && ++byteCnt) {
		int offset = 4 * (byteCnt - 1);
		for(int i = 0; i < 4; i++) {
			if(byteBuff[i] == '+') {	// -标记为0, +标记为1
				switchStatus |= (0x00000001 << (i + offset));
			}
		}

		// 每输入4个字节求解一次
		if(byteCnt >= 4) {
			switchGroup->print(switchStatus);
			
			byteCnt = 0;
			switchStatus = 0;
		}
	}
	delete switchGroup;
	return 0;
}


/**
 * 构造函数
 */
SwitchGroup::SwitchGroup() {
	this->switchs = new _UINT[MAX_STATUS];
	memset(switchs, -1, sizeof(_UINT) * MAX_STATUS);

	bfsAllStatus();
}


/**
 * 析构函数
 */
SwitchGroup::~SwitchGroup() {
	delete[] switchs;
	switchs = NULL;
}


/**
 * 初始化不重复地翻动1-16步可得到的所有开关矩阵状态
 *
 *   由于这题所有状态都不重复（状态数达到65536），
 *   相比POJ1753的状态数要多得多（只有4096）。
 *   而且POJ1753可以对无效状态剪枝，而本题由于所有状态都有效，则无法这样剪枝
 *   在这种情况下，不能再像POJ1753那样使用STL的set容器维护BFS队列，
 *   否则会因为set的维护代价过高TLE
 *
 *   因此本题还是切为常规的BFS队列方法搜索所有状态
 *   （理论上是可以根据开关状态对称分布的特性剪枝的，但少了一半搜索，多了一倍运算，提升不明显）
 */
void SwitchGroup::bfsAllStatus(void) {
	const int ALL_OPEN = 0;
	_UINT bfsQueue[MAX_STATUS];		// 初始状态：开关矩阵全open
	int head = 0, tail = 0;
	bfsQueue[tail++] = ALL_OPEN;

	while(head < tail) {
		_UINT lastSwitch = bfsQueue[head++];
		int status = toStatus(lastSwitch);	// 屏蔽高16位操作位，得到低16位的真正开关矩阵状态
		switchs[status] = lastSwitch;		// 保存开关矩阵状态对应的开关矩阵编码

		// 剪枝1：开关是从低位编号开始反转的，为了不重复反转开关，从上一开关矩阵状态的最高位编号开始翻动 
		for(int pos = getMaxBitPos(lastSwitch) + 1; pos < MAX_STEP; pos++) {
			_UINT nextSwitch = filp(lastSwitch, pos);	// 反转开关得到下一个开关矩阵编码
			bfsQueue[tail++] = nextSwitch;
		}
	}
}


/**
 * 反转开关矩阵上某个指定位位置的开关,
 *  此操作会同时改变开关矩阵编码的操作位（高16位）和状态位（低16位）
 * @param _switch 翻转前的开关矩阵编码
 * @param bitPos 要反转的开关位置, 取值范围为[0, 15]，
 *				依次对应4x4矩阵上从左到右、自上而下的编号，也对应二进制数从低到高的进制位
 * return 翻转后的开关矩阵编码
 */
_UINT SwitchGroup::filp(_UINT _switch, int bitPos) {
	_UINT OP_MASK = 0x00010000 << bitPos;		// 高16位:当前操作位
	_UINT STATUS_MASK = STATUS_MASKS[bitPos];	// 低16位:相关状态位
	return (_switch ^ (OP_MASK | STATUS_MASK));	// 更新棋盘编码
}


/**
 * 从开关矩阵编码提取开关矩阵状态信息（低16位）
 * return 开关矩阵状态信息
 */
int SwitchGroup::toStatus(_UINT _switch) {
	const _UINT MASK = 0x0000FFFF;
	return (int) (_switch & MASK);
}


/**
 * 从开关矩阵编码提取操作信息（高16位），获得其中最大反转编号的位置
 * @param _switch 开关矩阵编码
 * return 没有操作过则返回-1，否则返回0-15
 */
int SwitchGroup::getMaxBitPos(_UINT _switch) {
	_UINT MASK = 0x80000000;
	int bitPos = -1;
	for(int i = MAX_STEP - 1; i >= 0; i--) {
		if((_switch & MASK) == MASK) {	// 注意加括号, ==优先级比&要高
			bitPos = i;
			break;
		}
		MASK >>= 1;
	}
	return bitPos;
}


/**
 * 从开关矩阵编码提取操作信息（高16位），获取从全0状态开始共被翻动开关的次数
 * @param _switch 开关矩阵编码
 * return 被翻转次数
 */
int SwitchGroup::getFilpCount(_UINT _switch) {
	const _UINT MASK = 0xFFFF0000;
	_switch &= MASK;	// 屏蔽低16位的状态位

	// 判断高16位操作位有多少个1, 即为翻转次数
	int cnt = 0;
	while(_switch > 0) {
		_switch = (_switch & (_switch - 1));
		cnt++;
	}
	return cnt;
}


/**
 * 打印从全0（open）到指定开关矩阵状态的最小操作步数以及操作过程
 * @param status 开关矩阵状态
 * return 最小步数（若不可达则返回-1）
 */
void SwitchGroup::print(int status) {
	if(status >= 0 && status < MAX_STATUS) {
		_UINT _switch = switchs[status];

		// 打印步数
		int step = getFilpCount(_switch);
		cout << step << endl;

		// 打印反转开关过程
		for(int mask = 0x00010000, bit = 0; bit < MAX_STEP; bit++, mask <<= 1) {
			if((_switch & mask) > 0) {
				cout << (bit / 4) + 1 << " " << (bit % 4) + 1 << endl;
			}
		}
	}
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

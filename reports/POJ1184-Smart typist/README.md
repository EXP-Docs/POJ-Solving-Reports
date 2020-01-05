## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1184] [[Smart typist](http://poj.org/problem?id=1184)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 状态压缩]

------

## 问题描述

通过给定的六种操作将一个六位数变为另一个六位数，求需要的最少操作数。

**六种操作**：

- 左移和右移：将光标位置左移一位或右移一位，在第一位时无法左移，最后一位时无法右移。
- 左交换和右交换：将光标位置的数字与第一位或最后一位交换
- 增大或减小：将光标位置的数字增大或减小1


## 解题思路

**BFS+状态压缩**。


初步想法：

- 很难找到有效的贪心算法
- 没有明显的局部最优特性，无法动态规划
- 考虑搜索


直观的想法：

- 直接进行搜索，从初态开始，知道找到末态的最优解为止。
- 无论空间，时间都行不通
- 6个位置×1000000个不同的数＝6000000个状态
- 必须减少状态数


两种操作的分离：

- 这六种操作对一个数有两种影响，一种是交换两个数位的位置，另一种是改变某个数位的值。
- 当且仅当光标到达某一数位，对这一数位的值的改变才可能发生，而且其发生的时间并不重要。
- 所以全部操作可分为两种：一种是移位和交换操作，一种是增大和减小操作。
- 将操作分离成：先对原数的各数位重新排列（利用移位和交换操作），然后对光标到达过的位置进行增大或减小。


**问题转化**：

- 1.对每一种排列和光标到达情况，求出最少需要的操作数。(此过程与输入无关)
- 2.求出在每一种排列下，需要的增大和减小操作的次数。(要求所有需要改变值的数位均被访问过)

------


**解题第一步**

　**状态数**：

　　6个位置×720种排列情况×26种光标访问情况

　　进一步缩小状态数：

　　因为光标是连续移动的，所以除了第6位以外，假如某一位被访问过，则它之前的数位均被访问过。第6位可用右交换操作访问，不在此列

　　由此得到十种光标访问情况：

　　1 被访问过

　　1,2 被访问过

　　1,2,3 被访问过

　　1,2,3,4 被访问过

　　1,2,3,4,5 被访问过

　　1,6 被访问过

　　1,2,6 被访问过

　　1,2,3,6 被访问过

　　1,2,3,4,6 被访问过

　　1,2,3,4,5,6 被访问过

　　现在状态数为6×720×10,可以接受了

　**搜索方法**：

　　对左移，右移，左交换，右交换四种操作进行搜索。

　　其中不难发现左移操作是多余操作，因为可以先改变数字大小再右移或者交换。

　　无法预知搜索深度，最优解多在浅层获得，故采用广度优先算法。

------


**解题第二步**

　　对所有满足要求的情况(即需要改变大小的数位光标都访问过)，找出需要总操作最少的，输出。


## AC 源码


```c
//Memory Time 
//3000K  0MS 

#include<iostream>
#include<queue>
#include<cmath>
using namespace std;

class oper  //记录每步操作情况(只针对移位和换位操作，并不包括值大小的改变操作)，得到所有排列的状态
{
public:
	int num[6];  //第step步操作后的 "数字串"
	int state;  //第step步操作后对 "数字串各个位置的访问状态" ,其值对应VistState的行数，分别为0~9
	int pos;  //第step步操作后 "光标在数字串中的位置" ，分别为0~5
	int step; //当前操作的 "步数"
};

int VistState[10][6]=    /*访问状态数组，通过swap0、swap1与右移操作得到的"数字串各个位置的访问状态"*/
{                        /*一行代表一种访问状态，1表示数字串该位置被访问了，0表示没有访问*/

	1,0,0,0,0,0,  /*访问状态0: 初始状态(pos=0)*/
	1,1,0,0,0,0,  /*访问状态1: 状态0通过右移操作得到(pos=1)，或者状态1通过swap0操作得到(pos=1)*/
	1,1,1,0,0,0,  /*访问状态2: 状态1通过右移操作得到(pos=2)，或者状态2通过swap0操作得到(pos=2)*/
	1,1,1,1,0,0,  /*访问状态3: 状态2通过右移操作得到(pos=3)，或者状态3通过swap0操作得到(pos=3)*/
	1,1,1,1,1,0,  /*访问状态4: 状态3通过右移操作得到(pos=4)，或者状态4通过swap0操作得到(pos=4)*/
	1,0,0,0,0,1,  /*访问状态5: 状态0通过swap1操作得到(pos=0)，或者状态5通过swap0操作得到(pos=0)*/
	1,1,0,0,0,1,  /*访问状态6: 状态1通过swap1操作得到(pos=1)，或者状态5通过右移操作得到(pos=1),或者状态6通过swap0操作得到(pos=1)*/
	1,1,1,0,0,1,  /*访问状态7: 状态2通过swap1操作得到(pos=2)，或者状态6通过右移操作得到(pos=2),或者状态7通过swap0操作得到(pos=2)*/
	1,1,1,1,0,1,  /*访问状态8: 状态3通过swap1操作得到(pos=3)，或者状态7通过右移操作得到(pos=3),或者状态8通过swap0操作得到(pos=3)*/
	1,1,1,1,1,1   /*访问状态9: 状态4通过swap1操作得到(pos=4)，或者状态8通过右移操作得到(pos=4),或者状态9通过右移操作得到(pos=5),
	                           或者状态4通过右移操作得到(pos=5)，或者状态9通过swap0操作得到，或者状态9通过swap1操作得到*/
};   
     /*不难注意到:swap0操作前后,光标位置pos不变,访问状态不变 ; swap0操作前后,pos不变;
                  右移操作后,pos+1  ; 无需左移操作                                   */

int comb[720][8];  //记录某个数字串num的全部排列组合情况(各个数字值不变，位置不同)，共6!=720种
                   //comb[][0~5]=num[0~5], comb[][6]=state , comb[][7]=step
int idx=0;  //comb的行索引
bool vist[6][6][6][6][6][6][6][10];  //标记出现过的状态，前6维为数字串num[]，第7维为光标所在的位置pos，第8维为访问状态state

void BFS(void);  //搜索所有"通过位移和换位操作"得到的排列组合状态
bool CheckVist(oper* a);   //状态检查
void ChangeVist(oper* a);  //状态变更

int main(void)
{
	memset(vist,false,sizeof(vist));
	BFS();  //预处理: 对每一种排列和光标到达情况，求出最少需要"移位和换位的操作数"。(此过程与输入无关)

	char Init_ANum[6];  //初始字符串
	int Init_DNum[6];   //初始数字串
	char Aim_ANum[6];   //目标字符串
	int Aim_DNum[6];    //目标数字串
	
	while(cin>>Init_ANum>>Aim_ANum)
	{
		for(int k=0;k<6;k++)   //字符串转换为数字串
		{
			Init_DNum[k]=Init_ANum[k]-'0';
			Aim_DNum[k]=Aim_ANum[k]-'0';
		}

		int MinOper=1000000;  //从str得到aim最少需要的操作数
		for(int i=0;i<idx;i++)
		{
			int cnt=comb[i][7];  //comb[i][7]=step,为移位和换位的总操作数
			bool flag=true;
			for(int j=0;j<6;j++)
			{                //comb[i][6]=state
				if(!VistState[ comb[i][6] ][j] && (Init_DNum[ comb[i][j] ]!=Aim_DNum[j]))  //str[]与aim[]在位置j的数字值不等，且该位置没有被访问过
				{
					flag=false;  //comb[i]不符合要求
					break;
				}
				else
					cnt+=abs(Init_DNum[ comb[i][j] ] - Aim_DNum[j]);  //在同一位置，值改变的次数(每一改变1)就是操作数
			}

			if(flag)
				MinOper=MinOper<cnt?MinOper:cnt;
		}

		cout<<MinOper<<endl;
	}

	return 0;
}

/*搜索所有"通过位移和换位操作"得到的排列组合状态*/
void BFS(void)
{
	oper a,b;
	queue<oper>Q;
	
	for(int i=0;i<6;i++)
		a.num[i]=i;
	a.pos=a.state=a.step=0;

	Q.push(a);  //入队
	ChangeVist(&a);

	while(!Q.empty())
	{
		a=Q.front(); //取队尾
		Q.pop();  //队尾元素出队

		/*记录所有组合情况*/

		for(int k=0;k<6;k++)
			comb[idx][k]=a.num[k];
		comb[idx][6]=a.state;
		comb[idx++][7]=a.step;

		if(a.pos>0)  //swap0操作前提条件，注意swap0操作前后的访问状态不变，光标位置也不变
		{            //因此无需处理b.state与b.pos

			/*swap0操作*/

			b=a;  //备份
			b.step=a.step+1;
			swap(b.num[0],b.num[b.pos]);  //交换num第0位与第pos位
			if(!CheckVist(&b))  //状态检查
			{
				ChangeVist(&b);
				Q.push(b);    //入队
			}
		}

		if(a.pos<5)  //右移right或swap1操作前提条件
		{
			/*right操作，注意光标位置pos会改变*/

			b=a;
			b.step=a.step+1;
			b.pos++;
			if(b.state<9)
				b.state++;

			if(!CheckVist(&b))  //状态检查
			{
				ChangeVist(&b);
				Q.push(b);    //入队
			}

			/*swap1操作,注意光标位置pos不变*/

			b=a;
			b.step=a.step+1;
			swap(b.num[5],b.num[b.pos]);  //交换num第5位与第pos位
			if(b.state<5)
				b.state+=5;

			if(!CheckVist(&b))  //状态检查
			{
				ChangeVist(&b);
				Q.push(b);    //入队
			}
		}
	}
	return;
}

/*状态检查*/
bool CheckVist(oper* a)
{
	int* p=a->num;
	return vist[*p][*(p+1)][*(p+2)][*(p+3)][*(p+4)][*(p+5)][a->pos][a->state];
}

/*状态变更*/
void ChangeVist(oper* a)
{
	int* p=a->num;
	vist[*p][*(p+1)][*(p+2)][*(p+3)][*(p+4)][*(p+5)][a->pos][a->state]=true;
	return;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

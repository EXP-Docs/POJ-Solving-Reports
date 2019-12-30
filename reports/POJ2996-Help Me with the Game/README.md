## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2996] [[Help Me with the Game](http://poj.org/problem?id=2996)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 模拟法]

------

## 问题描述

无。


## 解题思路

**提示：** 很烦很简单的国际象棋棋盘**模拟**，输入比较麻烦而已。

这题是 [POJ2993](http:///exp-blog.com/2018/06/17/pid-534/) 的相反情况，有趣的是，不难发现 2996 的题目和 2993 的题目字符也是相反的：

- POJ2996-Help Me with the Game
- POJ2993-Emag eht htiw Em Pleh


**输出要求：**

- (1) 不论黑白，KQRBN P均是依次输出，强制大写，但不输出“P”，只输出其坐标
- (2) 对白棋的位置，小行优先大行输出（行的数字越小则优先）同行则按列的顺序(`a~h`)
- (3) 对黑棋的位置，大行优先小行输出（行的数字越大则优先）同行则按列的顺序(`a~h`)
- (4) 从 (2) (3) 点可以看出，黑棋总是先被输入，白棋总是后输入，即黑棋总在棋盘上方，白棋总在棋盘下方，所以输入完成后，对于黑色棋子只需要按类型次序输出，同类型棋子的顺序就是输入的顺序；而白色棋子要考虑同类型棋子之间的排序，而同类型棋子之间又仅需要考虑不同行棋子之间的排序，同一行棋子的排序就是输入顺序
- (5) 棋子可能不齐全，不存在的棋子不输出，用标记解决
- (6) 最后的棋子后面不带逗号，要找出最后的棋子


**注意：** 坐标系的变换


## AC 源码


```c
//Memory Time 
//236K    0MS 


#include<iostream>
using namespace std;

class white_piece
{
public:
	int row;
	char col;
	bool flag;        //在class中bool型的默认值为false
}K,Q,R[3],B[3],N[3];

bool pawn[9]['i']={false};      //记录白色pawn的位置
int PR=0,PB=0,PN=0;  //同类型棋子的指针

class black_piece
{
public:
	int row;
	char col;
	bool flag;
}k,q,r[2],b[2],n[2],p[8];

int pr=0,pb=0,pn=0,pp=0;  

char chess[9]['i'];      // ASCII: 'i'>'I',use the Row 1 to 8,and Col 'a' to 'h'
int x,z;
char y;
int w_count=0;        //白棋总数
int b_count=0;        //黑棋总数

void judge(void)
{
	if(chess[x][y]=='.' || chess[x][y]==':')
		return;
	else if(chess[x][y]=='k')        //黑棋判断
	{
		k.row=9-x;
		k.col=y;
		k.flag=true;
		b_count++;
		return;
	}
	else if(chess[x][y]=='q')
	{
		q.row=9-x;
		q.col=y;
		q.flag=true;
		b_count++;
		return;
	}
	else if(chess[x][y]=='r')
	{
		r[pr].row=9-x;
		r[pr++].col=y;
		b_count++;
		return;
	}
	else if(chess[x][y]=='b')
	{
		b[pb].row=9-x;
		b[pb++].col=y;
		b_count++;
		return;
	}
	else if(chess[x][y]=='n')
	{
		n[pn].row=9-x;
		n[pn++].col=y;
		b_count++;
		return;
	}
	else if(chess[x][y]=='p')
	{
		p[pp].row=9-x;
		p[pp++].col=y;
		b_count++;
		return;
	}
	else if(chess[x][y]=='K')        //白棋判断
	{
		K.row=9-x;
		K.col=y;
		K.flag=true;
		w_count++;
		return;
	}
	else if(chess[x][y]=='Q')
	{
		Q.row=9-x;
		Q.col=y;
		Q.flag=true;
		w_count++;
		return;
	}
	else if(chess[x][y]=='R')
	{
		R[PR].row=9-x;
		R[PR++].col=y;
		w_count++;
		return;
	}
	else if(chess[x][y]=='B')
	{
		B[PB].row=9-x;
		B[PB++].col=y;
		w_count++;
		return;
	}
	else if(chess[x][y]=='N')
	{
		N[PN].row=9-x;
		N[PN++].col=y;
		w_count++;
		return;
	}
	else if(chess[x][y]=='P')
	{
		pawn[9-x][y]=true;
		w_count++;
		return;
	}
}

void Print(void)
{
	cout<<"White: ";
	if(K.flag)
	{
		cout<<'K'<<K.col<<K.row;
		if(--w_count>0)
			cout<<',';
	}
	if(Q.flag)
	{
		cout<<'Q'<<Q.col<<Q.row;
		if(--w_count>0)
			cout<<',';
	}

	if(PR==2)
		if(R[1].row<R[0].row)
		{
			R[2]=R[0];
			R[0]=R[1];
			R[1]=R[2];
		}
	for(x=0;x<PR;x++)
	{
		cout<<'R'<<R[x].col<<R[x].row;
		if(--w_count>0)
			cout<<',';
	}

	if(PB==2)
		if(B[1].row<B[0].row)
		{
			B[2]=B[0];
			B[0]=B[1];
			B[1]=B[2];
		}
	for(x=0;x<PB;x++)
	{
		cout<<"B"<<B[x].col<<B[x].row;
		if(--w_count>0)
			cout<<',';
	}

	if(PN==2)
		if(N[1].row<N[0].row)
		{
			N[2]=N[0];
			N[0]=N[1];
			N[1]=N[2];
		}
	for(x=0;x<PN;x++)
	{
		cout<<'N'<<N[x].col<<N[x].row;
		if(--w_count>0)
			cout<<',';
	}

	for(x=1;x<=8;x++)
		for(y='a';y<='h';y++)
			if(pawn[x][y])
			{
				cout<<y<<x;
				if(--w_count>0)
			        cout<<',';
			}
	
	cout<<endl;

	cout<<"Black: ";
	if(k.flag)
	{
		cout<<'K'<<k.col<<k.row;
		if(--b_count>0)
			cout<<',';
	}
	if(q.flag)
	{
		cout<<'Q'<<q.col<<q.row;
		if(--b_count>0)
			cout<<',';
	}
	for(x=0;x<pr;x++)
	{
		cout<<'R'<<r[x].col<<r[x].row;
		if(--b_count>0)
			cout<<',';
	}
	for(x=0;x<pb;x++)
	{
		cout<<"B"<<b[x].col<<b[x].row;
		if(--b_count>0)
			cout<<',';
	}
	for(x=0;x<pn;x++)
	{
		cout<<'N'<<n[x].col<<n[x].row;
		if(--b_count>0)
			cout<<',';
	}
	for(x=0;x<pp;x++)
	{
		cout<<p[x].col<<p[x].row;
		if(--b_count>0)
			cout<<',';
	}

	cout<<endl;

	return;
}

int main(void)
{
	char temp;

	/*Input*/

	for(z=0;z<33;z++)
		cin>>temp;

	for(x=1;x<=8;x++)
	{
		cin>>temp;
		for(y='a';y<='h';y++)
		{
			cin>>temp>>chess[x][y]>>temp>>temp;
			judge();
		}
		for(z=0;z<33;z++)
		    cin>>temp;
	}

	/*Print*/

	Print();

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2993] [[Emag eht htiw Em Pleh](http://poj.org/problem?id=2993)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 模拟法]

------

## 问题描述

无。


## 解题思路

**提示：** 很烦很简单的国际象棋棋盘**模拟**，输入比较麻烦而已。

这题是 [POJ2996](/reports/POJ2996-Help%20Me%20with%20the%20Game) 的相反情况，有趣的是，不难发现 2993 的题目和 2996 的题目字符也是相反的：

- POJ2993-Emag eht htiw Em Pleh
- POJ2996-Help Me with the Game


## AC 源码


```c
//Memory Time 
//212K   0MS 


#include<iostream>
#include<string>
using namespace std;

class whit
{
public:
	int row;
	char col;
	char pie;
}ww[16];

class blac
{
public:
	int row;
	char col;
	char pie;
}bb[16];

int main(void)
{
	char white[63],black[63];
	gets(white);
	gets(black);

	int x,y,z,r;

	int count_w=0;
	int count_b=0;
	const int length_w=strlen(white);
	const int length_b=strlen(black);

	for(x=7,y=0;x<length_w;)
		if(white[x]>='B' && white[x]<='R')
		{
			ww[y].pie=white[x];
			ww[y].col=white[x+1];
			ww[y].row=white[x+2]-'0';  //字符转数字
			y++;
			x+=4;
			count_w++;
		}
		else if(white[x]>='a' && white[x]<='h')
		{
			ww[y].pie='P';
			ww[y].col=white[x];
			ww[y].row=white[x+1]-'0';
			y++;
			x+=3;
		    count_w++;
		}
		else
			break;

		for(x=7,y=0;x<length_b;)
		if(black[x]>='B' && black[x]<='R')
		{
			bb[y].pie=black[x]+32;      //大写字母转换小写字母
			bb[y].col=black[x+1];
			bb[y].row=black[x+2]-'0';
			y++;
			x+=4;
			count_b++;
		}
		else if(black[x]>='a' && black[x]<='h')
		{
			bb[y].pie='p';
			bb[y].col=black[x];
			bb[y].row=black[x+1]-'0';
			y++;
			x+=3;
		    count_b++;
		}
		else
			break;

		char chess[9]['i'];

		memset(chess,':',sizeof(chess));

		for(x=1;x<=7;x+=2)
			for(y='a';y<='g';y+=2)
				chess[x][y]='.';
		for(x=2;x<=8;x+=2)
			for(y='b';y<='h';y+=2)
				chess[x][y]='.';

		for(x=0;x<count_w;x++)
			chess[9-ww[x].row][ww[x].col]=ww[x].pie;

		for(x=0;x<count_b;x++)
			chess[9-bb[x].row][bb[x].col]=bb[x].pie;

		cout<<"+---+---+---+---+---+---+---+---+"<<endl;
		
		for(x=1,r=2;x<=7;x+=2,r+=2)
		{
			cout<<'|';
			for(y='a',z='b';y<='g';y+=2,z+=2)
				cout<<"."<<chess[x][y]<<".|:"<<chess[x][z]<<":|";
			cout<<endl;
			cout<<"+---+---+---+---+---+---+---+---+"<<endl;
			cout<<'|';
			for(y='a',z='b';y<='g';y+=2,z+=2)
				cout<<":"<<chess[r][y]<<":|."<<chess[r][z]<<".|";
			cout<<endl;
			cout<<"+---+---+---+---+---+---+---+---+"<<endl;
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

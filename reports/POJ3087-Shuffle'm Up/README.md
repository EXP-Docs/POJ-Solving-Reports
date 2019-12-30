## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3087] [[Shuffle'm Up](http://poj.org/problem?id=3087)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 模拟法]

------

## 问题描述

已知两堆牌s1和s2的初始状态，牌数均为c，按给定规则能将他们相互交叉组合成一堆牌s12，再将s12的最底下的c块牌归为s1，最顶的c块牌归为s2，依此循环下去。

现在输入s1和s2的初始状态 以及 预想的最终状态s12

问s1 s2经过多少次洗牌之后，最终能达到状态s12，若永远不可能相同，则输出"-1"。


## 解题思路

很浅白的模拟题

**直接模拟就可以了，关键在于状态记录，然后判重**

若s1和s2在洗牌后的状态，是前面洗牌时已经出现过的一个状态，且这个状态不是预想的状态S12，就说明无论怎样再洗牌都不可能达到S12了，因为这个洗牌操作已经陷入了一个“环”

如果状态没有重复过，则一直模拟洗牌，直至s12出现

记录状态可以用 `map<string,bool>vist`, Map的缺省值为0

知道这个就不难了


## AC 源码


```c
//Memory Time 
//204K   0MS 

#include<iostream>
#include<string>
#include<map>
using namespace std;

int main(int i,int k)
{
	int test,c;
	int t=0;
	cin>>test;
	while(++t<=test)
	{
		cin>>c;
		char s1[201];   //牌堆1
		char s2[201];   //牌堆2
		char s12[401];  //预设最终的牌堆状态
		cin>>s1>>s2>>s12;

		map<string,bool>vist;   //记录出现过的洗牌状态(map缺省值为0)
		vist[s12]=true;

		int step=0;  //洗牌次数
		while(true)
		{
			char s[201];  //当前s1与s2洗牌后的状态
			int ps=0;  //s[]指针
			for(i=0;i<c;i++)    //s1与s2洗牌
			{
				s[ps++]=s2[i];
				s[ps++]=s1[i];
			}
			s[ps]='\0';

			step++;
			
			if(!strcmp(s,s12))   //当洗牌后的状态能达到预设状态时，输出
			{
				cout<<t<<' '<<step<<endl;
				break;
			}
			else if(vist[s] && strcmp(s,s12))  //当前洗牌后状态 与 前面出现过的状态重复了，但该状态不是预设状态
			{                                  //说明预设的状态无法达到
				cout<<t<<' '<<-1<<endl;
				break;
			}

			vist[s]=true;   //状态记录

			for(i=0;i<c;i++)   //分拆出s1与s2
				s1[i]=s[i];
			s1[i]='\0';

			for(k=0;i<2*c;i++,k++)
				s2[k]=s[i];
			s2[i]='\0';
		}
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

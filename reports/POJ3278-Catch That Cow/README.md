## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3278] [[Catch That Cow](http://poj.org/problem?id=3278)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: BFS]

------

## 问题描述

给定两个整数n和k

通过 `n+1` 或 `n-1` 或 `n*2` 这 3 种操作，使得 `n==k`

输出最少的操作次数

## 解题思路


水题，**三入口的BFS**。

**注意**的地方有二：

- 由于用于广搜的 队列数组 和 标记数组  相当大，如果定义这两个数组时把它们扔到局部去，编译是可以的，但肯定执行不了，提交就等RE吧。 大数组必须开为 全局 ，这是常识。。
- **剪枝**：直接广搜一样等着RE吧 (不剪枝的同学输入 `n=0`  `k=100000` 试试)。。。具体怎么剪枝看程序


## AC 源码


```c
//Memory Time 
//1292K   0MS 

#include<iostream>
using namespace std;

const int large=200030;

typedef class
{
	public:
		int x;
		int step;
}pos;

int n,k;
bool vist[large];   //数组较大，必须开为全局数组，不然肯定RE
pos queue[large];

void BFS(void)
{
	int head,tail;
	queue[head=tail=0].x=n;
	queue[tail++].step=0;

	vist[n]=true;

	while(head<tail)
	{
		pos w=queue[head++];

		if(w.x==k)
		{
			cout<<w.step<<endl;
			break;
		}

		if(w.x-1>=0 && !vist[w.x-1])     //w.x-1>=0  是剪枝
		{
			vist[w.x-1]=true;
			queue[tail].x=w.x-1;
			queue[tail++].step=w.step+1;
		}
		if(w.x<=k && !vist[w.x+1])     //w.x<=k  是剪枝
		{
			vist[w.x+1]=true;
			queue[tail].x=w.x+1;
			queue[tail++].step=w.step+1;
		}
		if(w.x<=k && !vist[2*w.x])     //w.x<=k  是剪枝
		{
			vist[2*w.x]=true;
			queue[tail].x=2*w.x;
			queue[tail++].step=w.step+1;
		}
	}

	return;
}

int main(void)
{
	while(cin>>n>>k)
	{
		memset(vist,false,sizeof(vist));
		BFS();
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

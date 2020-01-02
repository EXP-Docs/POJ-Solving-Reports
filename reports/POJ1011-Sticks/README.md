## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1011] [[Sticks](http://poj.org/problem?id=1011)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 搜索]

------

## 问题描述

2011 POJ 暑假集训题 Problem E，POJ上有中文版。


## 解题思路

**DFS+剪枝**


[POJ2362](/reports/POJ2362-Square) 的强化版，**重点在于剪枝**

 
令InitLen为所求的最短原始棒长，maxlen为给定的棒子堆中最长的棒子，sumlen为这堆棒子的长度之和，那么InitLen必定在范围 `[maxlen，sumlen]` 中

根据棒子的灵活度（棒子越长，灵活度越低） DFS前先对所有棒子降序排序


**剪枝**：

- 由于所有原始棒子等长，那么必有 `sumlen%Initlen==0`；
- 若能在 `[maxlen,sumlen-InitLen]` 找到最短的InitLen，该InitLen必也是 `[maxlen,sumlen]`的最短；若不能在 `[maxlen,sumlen-InitLen]` 找到最短的InitLen，则必有 `InitLen=sumlen`；
- 由于所有棒子已降序排序，在DFS时，若某根棒子不合适，则跳过其后面所有与它等长的棒子；
- 最重要的剪枝：对于某个目标InitLen，在每次构建新的长度为InitLen的原始棒时，检查新棒的第一根 `stick[i]`，若在搜索完所有 `stick[]` 后都无法组合，则说明 `stick[i]` 无法在当前组合方式下组合，不用往下搜索(往下搜索会令 `stick[i]`被舍弃)，直接返回上一层


## AC 源码


```c
//Memory Time 
//252K   16MS 
/* 2011 POJ暑假集训题-Problem E */

#include<iostream>
#include<algorithm>
using namespace std;

int cmp(const void* a,const void* b)
{
	return *(int*)b-*(int*)a;
}

int n;  //木棒数量

bool dfs(int* stick,bool* vist,int len,int InitLen,int s,int num)  //len:当前正在组合的棒长  InitLen:目标棒长  
{                                                                  //s:stick[]的搜索起点  num:已用的棒子数量
	if(num==n)
		return true;

	int sample=-1;
	for(int i=s;i<n;i++)
	{
		if(vist[i] || stick[i]==sample)  //剪枝3,等长的木棒只搜索一次
			continue;

		vist[i]=true;
		if(len+stick[i]<InitLen)
		{
			if(dfs(stick,vist,len+stick[i],InitLen,i,num+1))
				return true;
			else
				sample=stick[i];
		}
		else if(len+stick[i]==InitLen)
		{
			if(dfs(stick,vist,0,InitLen,0,num+1))
				return true;
			else
				sample=stick[i];
		}
		vist[i]=false;

		if(len==0)  //剪枝4，构建新棒时，对于新棒的第一根棒子，在搜索完所有棒子后都无法组合
			break;  //则说明该棒子无法在当前组合方式下组合，不用往下搜索(往下搜索会令该棒子被舍弃)，直接返回上一层
	}
	return false;
}

int main(void)
{
	while(cin>>n && n)
	{
		int* stick=new int[n];
		bool* vist=new bool[n];
		int sumlen=0;

		for(int i=0;i<n;i++)
		{
			cin>>stick[i];
			sumlen+=stick[i];
			vist[i]=false;
		}

		qsort(stick,n,sizeof(stick),cmp);
		int maxlen=stick[0];   //最大的棒为InitLen的搜索起点

		bool flag=false;
		                     //剪枝1,若能在[maxlen,sumlen-InitLen]找到最短的InitLen，该InitLen必也是[maxlen,sumlen]的最短
		for(int InitLen=maxlen;InitLen<=sumlen-InitLen;InitLen++)  //InitLen:原始棒长
		{   //剪枝2,InitLen必是sumlen的约数
			if(!(sumlen%InitLen) && dfs(stick,vist,0,InitLen,0,0))
			{
				cout<<InitLen<<endl;
				flag=true;
				break;
			}
		}
		if(!flag)
			cout<<sumlen<<endl;

		delete stick;
		delete vist;
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

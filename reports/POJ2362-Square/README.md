## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2362] [[Square](http://poj.org/problem?id=2362)]

> [Time: 3000MS] [Memory: 65536K] [难度: 初级] [分类: 搜索]

------

## 问题描述

给定一堆不定长度的小棒子，问他们能否构成一个正方形。


## 解题思路

[POJ1011](/reports/POJ1010-STAMPS) 的热身题，**DFS+剪枝**

本题大致做法就是对所有小棒子长度求和sum，sum就是正方形的周长，`sum/4` 就是边长side 。

**问题就转变为**：这堆小棒子能否刚好组合成为4根长度均为side的大棒子

不难理解，小棒子的长度越长，其灵活性越差。

例如长度为5的一根棒子的组合方式要比5根长度为1的棒子的组合方式少，这就是灵活性的体现。

由此，我们**首先要对这堆小棒子降序排序，从最长的棒子开始进行DFS**


**剪枝**，有3处可剪：

- 要组合为正方形，必须满足 `sum%4==0`；
- 所有小棒子中最长的一根，必须满足 `Max_length <= side`，这是因为小棒子不能折断；
- 当满足前两个条件时，只需要能组合3条边，就能确定这堆棒子可以组合为正方形。


## AC 源码


```c
//Memory Time 
//244K   79MS 

#include<iostream>
#include<algorithm>
using namespace std;

int cmp(const void* a,const void* b)  //降序
{
	return *(int*)b-*(int*)a;
}

int n;  //木棒数量
int side;  //正方形边长
bool dfs(int* stick,bool* vist,int num,int len,int s)  //num:已组合的正方形的边数  len:当前组合的边已组合的长度,len<=side
{                                                      //s:stick[]的搜索起点
	if(num==3)   //剪枝3，当满足剪枝1和2的要求时，只需组合3条side，剩下的棒子必然能够组成最后一条side
		return true;

	for(int i=s;i<n;i++)
	{
		if(vist[i])
			continue;

		vist[i]=true;
		if(len+stick[i]<side)
		{
			if(dfs(stick,vist,num,len+stick[i],i))  //继续构建当前side
				return true;
		}
		else if(len+stick[i]==side)
		{
			if(dfs(stick,vist,num+1,0,0))  //构建新side
				return true;
		}
		vist[i]=false;
	}

	return false;
}

int main(void)
{
	int time;
	cin>>time;
	for(int t=0;t<time;t++)
	{	
		int sum=0;  //所有木棒长度之和

		cin>>n;
		int* stick=new int[n];
		bool* vist=new bool[n];

		for(int i=0;i<n;i++)
		{
			cin>>stick[i];
			vist[i]=false;

			sum+=stick[i];
		}		

		if(n<4 || sum%4!=0)    //剪枝1，不能构成正方形
		{
			cout<<"no"<<endl;
			continue;
		}

		qsort(stick,n,sizeof(int),cmp);   //降序排列，先组合长棒，因为长棒相对于短棒的组合灵活性较低

		side=sum/4;  //边长
		if(side<stick[0])   //剪枝2，side<max_stick
		{
			cout<<"no"<<endl;
			continue;
		}

		if(dfs(stick,vist,0,0,0))
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;

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

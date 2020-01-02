## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1010] [[STAMPS](http://poj.org/problem?id=1010)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 搜索]

------

## 问题描述

题意比较难懂。大致如下：

第一行数字是邮票的面值，每一个数字就是一个不同的种类，哪怕面值相同。以0结束。

第二行数字是顾客所需要的邮票总面值。每个数字就是一个顾客的需求，以0结束。

每两行是一组case。以EOF结束输入。

顾客是集邮爱好者，所以你必须尽可能的给他不同种类的邮票。

但是一位顾客最多只能拿4张邮票。

显然，我们拥有的邮票就是第一行中的数据。


## 解题思路

DFS寻找所有的解，再逐一比较寻找最优解，剪枝是关键。

关于tie。

满足顾客需求的解就是可行解。

邮票种类最多的可行解为最优。

如果存在两个以上的最优解的邮票种类是一样的，张数最少的更优

张数也一样的话，这些最优解中最大面值较大的更优。

若邮票种类、张数、最大面值三者都分别相同，则认为这些最优解相同，输出tie。

没有解就是none。


**解法大致有三种**。

- 1、**枚举**。反正最多拿4张，可以4重循环暴搜最优解。
- 2、**DFS**。每次搜索后，如果有解，更新最优解，关键在剪枝。
- 3、**三维DP**。这个没怎么研究，不太懂……

> 我用的是第二种DFS


**关于剪枝**：

- 1、最多拿四张邮票，如果同一面值的邮票种类超过5，以5计算。 为什么不以4计算呢？因为tie
- 2、若DFS的深度超过了4，那么就返回。（最多四张邮票）
- 3、技巧剪枝： 先对输入的邮票按面值升序排序，DFS到面值k时，不再搜索面值 `<k` 的邮票。 同时排序也是为了保证DFS的最优解的邮票种类最多。

## 测试数据

- 来源：[Pacific Northwest 1998](http://www.cs.berkeley.edu/~hilfingr/programming-contest/pacific-northwest/1998/ContestProblems/)
- 下载：[download](/reports/POJ1010-STAMPS/testdata.zip)
- 输入：[input](/reports/POJ1010-STAMPS/testdata/input.dat)
- 输出：[output](/reports/POJ1010-STAMPS/testdata/output.dat)

## AC 源码


```c
//Memory Time 
// 228K   0MS 

#include<iostream>
#include<algorithm>
using namespace std;

const int size=26;

int value[size];  //第i种邮票面值value[i]
int pv;  //value[]指针
int time[size];  //标记第i种邮票被分配过的次数

bool flag;  //标记是否已经出现过解
bool flag_tie;  //标记是否为tie
int solve[6];  //solve[0]:邮票张数  solve[5]:邮票种数  solve[1..4]:持有的邮票面值，0表示不持有
int BestSolve[6];  //最优解

void dfs(int need,int num,int type,int pre);  //need:总面值 num:邮票张数  type:邮票种数
int max4(int* s);  //返回s[1..4] 4个数中的最大值
void best(int num,int type);  //更新最优解

int main(void)
{
	while(true)
	{
		pv=0;
		int type[size]={0};  //面值为i的邮票的种数type[i]

		int tmp;
		while(true)
		{
			if(scanf("%d",&tmp)==EOF)
				exit(0);
			if(tmp==0)
				break;

			if(type[ tmp ]<5)     //剪枝，同面额的邮票种类超过5，则按5计算
			{
				type[ tmp ]++;
				value[pv++]=tmp;
			}
		}
		sort(value,value+pv);  //要使分配的邮票的种类尽可能多
		                       //只需在搜索前把邮票面值升序排序，从最小面额开始搜索

		int need;  //顾客需求
		while(cin>>need && need)
		{
			flag=false;
			flag_tie=false;
			memset(solve,0,sizeof(solve));
			memset(BestSolve,0,sizeof(BestSolve));
			memset(time,0,sizeof(time));

			/*Search*/

			dfs(need,0,0,0);

			/*Output*/

			cout<<need;
			if(BestSolve[0]==0)
				cout<<" ---- none"<<endl;
			else
			{
				cout<<" ("<<BestSolve[5]<<"):";

				if(flag_tie)
					cout<<" tie"<<endl;
				else
				{
					sort(BestSolve+1,BestSolve+5);
					for(int i=1;i<=4;i++)
					{
						if(BestSolve[i]==0)
							continue;
						cout<<' '<<BestSolve[i];
					}
					cout<<endl;
				}
			}
		}
	}
	return 0;
}

void dfs(int need,int num,int type,int pre)  //need:总面值 num:邮票张数  type:邮票种数
{
	if(num==5)  //剪枝，顾客持有邮票张数不超过4
		return;

	if(need==0)
	{
		if(!flag)
		{
			if(type==BestSolve[5])  //最优解的种类type相同
			{
				if(num==BestSolve[0])  //最优解的张数num相同
				{
					int Maxs=max4(solve);  //solve的最大面值
					int MaxBs=max4(BestSolve); //BestSolve的最大面值

					if(Maxs==MaxBs)    //存在多个最优解
						flag_tie=true;
					else if(Maxs>MaxBs)  //种类、张数都相同的情况下，最大面值较大的解优先
					{
						flag_tie=false;
						best(num,type);
					}
				}
				else if(num<BestSolve[0])  //种类相同情况下，张数少的解优先
				{
					flag_tie=false;
					best(num,type);
				}
			}
			else if(type>BestSolve[5])  //种类多的解优先
			{
				flag_tie=false;
				best(num,type);
			}
		}
		else
		{
			flag=true;
			best(num,type);
		}
		
		return;
	}

	for(int i=pre;i<pv;i++)   //i=pre 剪枝，不重复搜索比当前面值小的邮票，同时避免错误的tie
	{
		if(need>=value[i])
		{
			solve[num+1]=value[i];

			if(time[i]!=0)
			{
				time[i]++;
				dfs(need-value[i],num+1,type,i);
			}
			else
			{
				time[i]++;
				dfs(need-value[i],num+1,type+1,i);
			}

			solve[num+1]=0;  //回溯
			time[i]--;
		}
		else
			return;  //value已排序
	}

	return;
}

int max4(int* s)  //返回s[1..4] 4个数中的最大值
{
	int a=s[1]>s[2]?s[1]:s[2];
	int b=s[3]>s[4]?s[3]:s[4];

	return a>b?a:b;
}

void best(int num,int type)  //更新最优解
{
	BestSolve[0]=num;
	BestSolve[5]=type;

	for(int k=1;k<=4;k++)
		BestSolve[k]=solve[k];
	return;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

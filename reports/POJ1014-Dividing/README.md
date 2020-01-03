## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1014] [[Dividing](http://poj.org/problem?id=1014)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 背包]

------

## 问题描述

有分别价值为1,2,3,4,5,6的6种物品，输入6个数字，表示相应价值的物品的数量，问一下能不能将物品分成两份，是两份的总价值相等，其中一个物品不能切开，只能分给其中的某一方，当输入六个0是（即没有物品了），这程序结束，总物品的总个数不超过20000


输出：每个测试用例占三行：

- 第一行： Collection #k: k为第几组测试用例
- 第二行：是否能分（具体形式见用例）
- 第三行：空白（必须注意，否则PE）


## 解题思路

**有两种解决方法**：

- **第一种**是几乎百度上所有同学都热衷的**多重背包**，确实这题就是《背包九讲》里面的“多重背包”的应用题，直接套 `O(V*Σlog n[i])` 的模板就毫无悬念地AC了，《背包九讲》里面提供的是“多重背包+二进制优化”算法，百度上也有不少同学加入了自己的想法去进一步优化，例如利用“抽屉原理”证明并“取模优化”的可行性等，这些同学都做了不少功课，值得我们学习。
- **第二种**方法是几乎没有同学使用的**DFS**，本题用DFS也能0ms跑完，可能大家都被《背包九讲》冲昏了头脑，都想着套模板去了，但又看不懂模板。呻吟“研究了背包多长时间都不完全明白”的同学不妨试试DFS。其实本来不少DP题都可以用搜索过的，大家不要钻牛角尖。


## AC 源码

## 解题方法一：多重背包+二进制优化

```c
//Memory Time 
//656K  16MS 

/*多重背包+二进制优化*/

#include<iostream>
using namespace std;

int n[7];  //价值为i的物品的个数
int v;  //背包容量
int SumValue;  //物品总价值
bool flag;    //标记是否能平分SumValue
int dp[100000];  //状态数组

int max(int a,int b)
{
	return a>b?a:b;
}

/*完全背包*/
void CompletePack(int cost,int weight)
{
	for(int i=cost;i<=v;i++)
	{
		dp[i]=max(dp[i],dp[i-cost]+weight);
		if(dp[i]==v)    //剪枝，当能够平分SumValue时退出
		{
			flag=true;
			return;
		}
	}
			
	return;
}

/*01背包*/
void ZeroOnePack(int cost,int weight)
{
	for(int i=v;i>=cost;i--)
	{
		dp[i]=max(dp[i],dp[i-cost]+weight);
		if(dp[i]==v)    //剪枝
		{
			flag=true;
			return;
		}
	}
	return;
}

/*多重背包*/
void MultiplePack(int cost,int weight,int amount)
{
	if(cost*amount>=v)
	{
		CompletePack(cost,weight);
		return;
	}

	if(flag)    //剪枝
		return;

	/*二进制优化*/
	int k=1;
	while(k<amount)
	{
		ZeroOnePack(k*cost,k*weight);

		if(flag)    //剪枝
			return;

		amount-=k;
		k*=2;
	}
	ZeroOnePack(amount*cost,amount*weight);

	return;
}

int main(int i)
{
	int test=1;
	while(cin>>n[1]>>n[2]>>n[3]>>n[4]>>n[5]>>n[6])
	{
		SumValue=0;  //物品总价值

		for(i=1;i<=6;i++)
			SumValue+=i*n[i];

		if(SumValue==0)
			break;

		if(SumValue%2)    //sum为奇数，无法平分
		{
			cout<<"Collection #"<<test++<<':'<<endl;
			cout<<"Can't be divided."<<endl<<endl;    //注意有空行
			continue;
		}

		v=SumValue/2;
		memset(dp,-1,sizeof(dp));
		dp[0]=0;
		flag=false;

		for(i=1;i<=6;i++)
		{
			MultiplePack(i,i,n[i]);

			if(flag)    //剪枝
				break;
		}

		if(flag)
		{
			cout<<"Collection #"<<test++<<':'<<endl;
			cout<<"Can be divided."<<endl<<endl;
			continue;
		}
		else
		{
			cout<<"Collection #"<<test++<<':'<<endl;
			cout<<"Can't be divided."<<endl<<endl;
			continue;
		}
	}
	return 0;
}
```

## 解题方法二：DFS

```c
//Memory Time 
//452K 0MS 

/*DFS*/

#include<iostream>
using namespace std;

int n[7];  //价值为i的物品的个数
int SumValue;  //物品总价值
int HalfValue;  //物品平分价值
bool flag;    //标记是否能平分SumValue

void DFS(int value,int pre)
{
	if(flag)
		return;

	if(value==HalfValue)
	{
		flag=true;
		return;
	}

	for(int i=pre;i>=1;i--)
	{
		if(n[i])
		{
			if(value+i<=HalfValue)
			{
				n[i]--;
				DFS(value+i,i);

				if(flag)
					break;
			}
		}
	}
	return;
}

int main(int i)
{
	int test=1;
	while(cin>>n[1]>>n[2]>>n[3]>>n[4]>>n[5]>>n[6])
	{
		SumValue=0;  //物品总价值

		for(i=1;i<=6;i++)
			SumValue+=i*n[i];

		if(SumValue==0)
			break;

		if(SumValue%2)    //sum为奇数，无法平分
		{
			cout<<"Collection #"<<test++<<':'<<endl;
			cout<<"Can't be divided."<<endl<<endl;    //注意有空行
			continue;
		}

		HalfValue=SumValue/2;
		flag=false;

		DFS(0,6);

		if(flag)
		{
			cout<<"Collection #"<<test++<<':'<<endl;
			cout<<"Can be divided."<<endl<<endl;
			continue;
		}
		else
		{
			cout<<"Collection #"<<test++<<':'<<endl;
			cout<<"Can't be divided."<<endl<<endl;
			continue;
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

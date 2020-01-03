## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1015] [[Jury Compromise](http://poj.org/problem?id=1015)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

在遥远的国家佛罗布尼亚，嫌犯是否有罪，须由陪审团决定。陪审团是由法官从公众中挑选的。先随机挑选n 个人作为陪审团的候选人，然后再从这n 个人中选m 人组成陪审团。选m 人的办法是：控方和辩方会根据对候选人的喜欢程度，给所有候选人打分，分值从0 到20。为了公平起见，法官选出陪审团的原则是：选出的m 个人，必须满足辩方总分D和控方总分P的差的绝对值|D-P|最小。如果有多种选择方案的|D-P| 值相同，那么选辩控双方总分之和D+P最大的方案即可。

**输出**：

选取符合条件的最优m个候选人后，要求输出这m个人的辩方总值D和控方总值P，并升序输出他们的编号。


## 解题思路

**动态规划**。


为叙述问题方便，现将任一选择方案中，辩方总分和控方总分之差简称为“**辩控差**”，辩方总分和控方总分之和称为“**辩控和**”。第i 个候选人的辩方总分和控方总分之差记为 `V(i)` ，辩方总分和控方总分之和记为 `S(i)`。

现用 `dp(j, k)` 表示，取j 个候选人，使其辩控差为k 的所有方案中，辩控和最大的那个方案（该方案称为“方案 `dp(j, k)` ”）的辩控和。

并且，我们还规定，如果没法选j 个人，使其辩控差为k，那么 `dp(j, k)` 的值就为 -1，也称方案 `dp(j, k)` 不可行。本题是要求选出m 个人，那么，如果对k 的所有可能的取值，求出了所有的 `dp(m, k) (-20×m≤ k ≤ 20×m)`，那么陪审团方案自然就很容易找到了。

问题的关键是建立递推关系。需要从哪些已知条件出发，才能求出 `dp(j, k)` 呢？显然，方案 `dp(j, k)` 是由某个可行的方案 `dp(j-1, x)( -20×m ≤ x ≤ 20×m)` 演化而来的。

可行方案 `dp(j-1, x)` 能演化成方案 `dp(j, k)` 的必要条件是：存在某个候选人i，而 i 在方案 `dp(j-1, x)`中没有被选上，且 `x+V(i) = k`。在所有满足该必要条件的 `dp(j-1, x)`中，选出 `dp(j-1, x) + S(i)`  的值最大的那个，那么方案 `dp(j-1, x)` 再加上候选人i，就演变成了方案 `dp(j, k)`。

这中间需要将一个方案都选了哪些人都记录下来。不妨将方案 `dp(j, k` 中最后选的那个候选人的编号，记在二维数组的元素 `path[j][k]` 中。那么方案 `dp(j, k)` 的倒数第二个人选的编号，就是 `path[j-1][k-V[path[j][k]]]` 。假定最后算出了解方案的辩控差是k，那么从 `path[m][k]` 出发，就能顺藤摸瓜一步步回溯求出所有被选中的候选人。

初始条件，只能确定 `dp(0, 0) = 0` ，其他均为 -1 。由此出发，一步步自底向上递推，就能求出所有的可行方案 `dp(m, k)( -20×m ≤ k ≤ 20×m)`。实际解题的时候，会用一个二维数组dp 来存放 `dp(j, k)` 的值。而且，由于题目中辩控差的值k 可以为负数，而程序中数租下标不能为负数，所以，在程序中不妨将辩控差的值都加上修正值 `fix=400`，以免下标为负数导致出错。

为什么 `fix=400`？这是很显然的，m上限为20人，当20人的d均为0，p均为20时，会出现辨控差为-400。修正后回避下标负数问题，区间整体平移，从 `[-400,400]` 映射到 `[0,800]` 。

此时初始条件修正为 `dp(0, fix) = 0` ，其他均为 -1。

DP后，从第m行的 `dp(m, fix)` 开始往两边搜索最小 `|D-P|` 即可，第一个不为 `dp[m][k]!=-1` 的位置k就是最小 `|D-P|` 的所在。

最后就是求m个人的D和P，由于 `D+P = dp(m, |D-P|)` ，`|D-P|` 已知。

那么 `D= (D+P + |D-P|)/2`  ,  `P=(D+P-|D-P|) / 2`

计算D和P时注意修正值fix


## AC 源码


```c
//Memory Time 
//388K   16MS 

#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int n;  //候选人数
int m;  //当选人数
int dp[21][801];   //dp[j][k]：取j个候选人，使其辩控差为k的所有方案中，辩控和最大的方案的辩控和
int path[21][801];  //记录所选定的候选人的编号

/*回溯，确认dp[j][k]方案是否曾选择过候选人i*/
bool select(int j,int k,int i,int* v)
{
	while(j>0 && path[j][k]!=i)
	{
		k-=v[ path[j][k] ];
		j--;
	}
	return j?false:true;
}

int main(void)
{
	int time=1;
	while(cin>>n>>m && n)
	{
		/*Initial*/

		int j,k,i;
		int* p=new int[n+1];  //每个人的控方值
		int* d=new int[n+1];  //每个人的辩方值
		int* s=new int[n+1];  //每个人的辨控和
		int* v=new int[n+1];  //每个人的辨控差
		memset(dp,-1,sizeof(dp));
		memset(path,0,sizeof(path));
		
		/*Input*/

		for(i=1;i<=n;i++)
		{
			cin>>p[i]>>d[i];

			s[i]=p[i]+d[i];
			v[i]=p[i]-d[i];
		}
		int fix=m*20;  //总修正值，修正极限为从[-400,400]映射到[0,800]

		/*DP*/

		dp[0][fix]=0;   //由于修正了数值，因此dp[0][fix]才是真正的dp[0][0]
		for(j=1;j<=m;j++)
			for(k=0;k<=2*fix;k++)
			{
				if(dp[j-1][k]>=0)   //区间已平移，dp[0][fix]才是真正的dp[0][0]
				{
					for(i=1;i<=n;i++)
						if(dp[j][ k+v[i] ] < dp[j-1][k]+s[i])
						{
							if(select(j-1,k,i,v))
							{
								dp[j][ k+v[i] ] = dp[j-1][k]+s[i];
								path[j][ k+v[i] ] = i;
							}
						}
				}
			}


		/*Output*/

		for(k=0;k<=fix;k++)
			if(dp[m][fix-k]>=0 || dp[m][fix+k]>=0)    //从中间向两边搜索最小辨控差的位置k
				break;

		int div=dp[m][fix-k] > dp[m][fix+k] ? (fix-k):(fix+k);  //最小辨控差

		cout<<"Jury #"<<time++<<endl;
		cout<<"Best jury has value ";
		//辩方总值 = （辨控和+辨控差+修正值）/2
		cout<<(dp[m][div]+div-fix)/2<<" for prosecution and value ";
		//控方总值 = （辨控和-辨控差+修正值）/2
		cout<<(dp[m][div]-div+fix)/2<<" for defence:"<<endl;

		int* id=new int[m];
		for(i=0,j=m,k=div;i<m;i++)
		{
			id[i]=path[j][k];
			k-=v[ id[i] ];
			j--;
		}
		sort(id,id+m);   //升序输出候选人编号
		for(i=0;i<m;i++)
			cout<<' '<<id[i];
		cout<<endl<<endl;

		/*Relax*/

		delete p;
		delete d;
		delete s;
		delete v;
		delete id;
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

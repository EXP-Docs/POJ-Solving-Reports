## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3274] [[Gold Balanced Lineup](http://poj.org/problem?id=3274)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 高效查找法]

------

## 问题描述

农夫约翰的N（1≤N≤100000）头奶牛有很多相同之处。其实，约翰己经将每头奶牛的不同之处归纳成为K（1≤K≤30）种特性，比如说，1号特性可以代表她身上有斑点，2号特性代表她更喜欢用Pascal而不是C来写程序等等。 

约翰使用“特性标识符”来描述奶牛的各种特性：一个特性标识符就是一个二进制长度 为K的整数，每位比特可以标识一头奶牛的一个特性。比如一头奶牛的特性标识符是13,将13写成二进制：1101, 从右向左看，就表示这头奶牛具冇1、3、4号特性，但没有2号特性。 

约翰把N头奶牛排成了一排，发现在有些连续区间里的奶牛，每种特性出现的次数是一样的，约翰把这样的区间称为“平衡的”。作为一个喜欢研究的人，约翰希望你能帮忙找出平衡区间的最大长度。 


## 解题思路

经典题，不转化问题很难做，先根据官方的方法转化问题，

把“求最远的两行间各个特征出现次数相等”**转化为**“求最远的相同两行”，再用Hash查找。

这是**官方解题报告**——

```
Consider the partial sum sequence of each of the k features built by taking the sum of all the values up to position i. The problem is equivalent to:
Given an array s[n][k], find i,j, with the biggest separation for which s[ i ][l]-s[j][l] is constant for all.

The problem is now to do this efficiently. Notice that s[ i ][l]-s[j][l] being
constant for all is equivalent to s[ i ][l]-s[j][l]=s[ i ][1]-s[j][1] for all, which can be rearranged to become s[ i ][l]-s[ i ][1]=s[j][l]-s[j][1] for all. Therefore, we can construct another array a[n][k] where a[ i ][j]=s[ i ][j]-s[ i ][1] and the goal is to find i and j with the biggest separation for which　a[ i ][l]=a[j][l] for all l.

This can be done by sorting all the a[ i ] entries, which takes O(nklogn) time
(although in practice rarely will all k elements be compared). Another　alternative is to go by hashing, giving an O(nk) solution. Both solutions are　fairly straightforward once the final array is constructed.
```


**大概意思就是**：

数组 `sum[i][j]` 表示从第1到第i头cow属性j的出现次数。

所以题目要求等价为:

求满足公式 `sum[i][0]-sum[j][0]=sum[i][1]-sum[j][1]=.....=sum[i][k-1]-sum[j][k-1] (j<i)` 中最大的 `i-j` 。

 
将上式变换可得到：

```
sum[i][1]-sum[i][0] = sum[j][1]-sum[j][0]
sum[i][2]-sum[i][0] = sum[j][2]-sum[j][0]
......
sum[i][k-1]-sum[i][0] = sum[j][k-1]-sum[j][0]
```
 

令 `C[i][y]=sum[i][y]-sum[i][0] (0<y<k)`

初始条件 `C[0][0~k-1]=0`

所以只需求满足 `C[i][]==C[j][]` 中最大的 `i-j`，其中 `0<=j<i<=n`。

`C[i][]==C[j][]` 即二维数组 `C[][]` 第i行与第j行对应列的值相等，

那么原题就转化为求C数组中 相等且相隔最远的两行的距离 `i-j`。

------

**以样例为例**

```
　　7 3
　　7
　　6
　　7
　　2
　　1
　　4
　　2
```

先把7个十进制特征数转换为二进制，并**逆序**存放到**特征数组** `feature[][]`，得到：
<br/>　　（行数为cow编号，自上而下从1开始；列数为特征编号，自左到右从0开始）

```
　　7 ： 1 1 1
　　6 ： 0 1 1
　　7 ： 1 1 1
　　2 ： 0 1 0
　　1 ： 1 0 0
　　4 ： 0 0 1
　　2 ： 0 1 0
```


再求**sum数组**，逐行累加得，sum数组为
<br/>　　（数组 `sum[i][j]` 表示从第1到第i头cow属性j的出现次数）

```
　　1 1 1
　　1 2 2
　　2 3 3
　　2 4 3
　　3 4 3
　　3 4 4
　　3 5 4
```

再利用 `C[i][y]=sum[i][y]-sum[i][0]` 求C数组，即所有列都减去第一列
　　（注意C数组有第0行，为全0）

```
　　0 0 0
　　0 0 0
　　0 1 1
　　0 1 1
　　0 2 1
　　0 1 0
　　0 1 1
　　0 2 1
```

显然第2行与第6行相等，均为011，且距离最远，距离为 `6-2=4` ，这就是所求。

------

但是最大数据有10W个，即10W行，因此**不能直接枚举找最大距离，必须用Hash查找相同行，找到相同行再比较最大距离**。

> 注意**C数组的值可能为负数，因此生成key值时要注意保证key为非负数**。


## Hint

**官方对Hint的解释：**

```
INPUT DETAILS:

The line has 7 cows with 3 features; the table below summarizes the　correspondence:
　　Feature 3:   1   1   1   0   0   1   0
　　Feature 2:   1   1   1   1   0   0   1
　　Feature 1:   1   0   1   0   1   0   0
　　Key: 　　　7   6   7   2   1   4   2
　　Cow #:　　1   2   3   4   5   6   7

OUTPUT FORMAT:

\* Line 1: A single integer giving the size of the largest contiguous balanced group of cows.


OUTPUT DETAILS:

In the range from cow \#3 to cow \#6 (of size 4), each feature appears in exactly 2 cows in this range:
　　Feature 3:     1   0   0   1  -> two total
　　Feature 2:     1   1   0   0  -> two total
　　Feature 1:     1   0   1   0  -> two total
　　Key:　　　　7   2   1   4
　　Cow #:　　　3   4   5   6
```


## 测试数据

- 来源（已失效）：[USACO 2007 March Gold](http://www.cppblog.com/Felicia/archive/2007/12/29/39923.html)
- 输入：[input](/reports/POJ3080-Blue%20Jeans/testdata/input.dat)
- 输出：[output](/reports/POJ3080-Blue%20Jeans/testdata/output.dat)



## AC 源码


```c
//Memory  Time
//44152K 1141MS 

#include<iostream>
#include<cmath>
using namespace std;

const int size=100001;
const int mod=99991;

int feature[size][30];  //feature[i][j]标记第i只牛是否有特征j
int sum[size][30];  //从第1到第i只牛，特征j总共出现了sum[i][j]次
int c[size][30];  //c[i][j]=sum[i][j]-sum[i][0] , 即所有列都减去第一列后，值保存在c[][]
int N;  //牛数量
int K;  //特征数
int MaxLen;  //最大距离

typedef class HASH
{
	public:
		int pi;  //保存c[i][j]的行地址c[i]的下标i
		class HASH* next;
		HASH()
		{
			next=0;
		}
}HashTable;

HashTable* hash[mod];

/*检查c[ai][]与c[bi][]是否对应列相等*/
bool cmp(int ai,int bi)
{
	for(int j=0;j<K;j++)
		if(c[ai][j]!=c[bi][j])
			return false;
	return true;
}

void Hash(int ci)
{
	int key=0;   //生成关键字
	for(int j=1;j<K;j++)
		key+=c[ci][j]*j;
	key=abs(key)%mod;  //由于c[][]有正有负，因此key值可能为负数

	if(!hash[key])  //新key
	{
		HashTable* pn=new HashTable;

		pn->pi=ci;
		hash[key]=pn;
	}
	else  //key值冲突
	{
		HashTable* pn=hash[key];

		if(cmp(pn->pi,ci))
		{
			int dist=ci-(pn->pi);
			if(MaxLen<dist)
				MaxLen=dist;
			return;  //由于pi与ci对应列数字相等，且pi地址必定比ci小
		}            //而要求的是最大距离，因此不需要保存ci，判断距离后直接返回
		else
		{
			while(pn->next)
			{
				if(cmp(pn->next->pi,ci))
				{
					int dist=ci-(pn->next->pi);
					if(MaxLen<dist)
						MaxLen=dist;
					return;
				}
				pn=pn->next;
			}

			//地址冲突但c[][]各列的值不完全相同

			HashTable* temp=new HashTable;
			temp->pi=ci;
			pn->next=temp;
		}
	}
	return;
}

int main(void)
{
	freopen("in.txt","r",stdin);
	while(cin>>N>>K)
	{
		/*Initial*/
		
		for(int p=0;p<K;p++)
		{
			c[0][p]=0; //第0只牛的特征默认为全0
			sum[0][p]=0;
		}

		memset(hash,0,sizeof(hash));
		Hash(0);  //把第0只牛先放入哈希表
		MaxLen=0;

		/*Input*/

		for(int i=1;i<=N;i++)
		{
			int Dexf;   //十进制特征数
			cin>>Dexf;

			for(int j=0;j<K;j++)
			{
				feature[i][j]=Dexf%2;  //Dexf转换为逆序二进制
				Dexf/=2;

				sum[i][j]=sum[i-1][j]+feature[i][j];
				c[i][j]=sum[i][j]-sum[i][0];
			}

			Hash(i);
		}

		/*Output*/

		cout<<MaxLen<<endl;
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

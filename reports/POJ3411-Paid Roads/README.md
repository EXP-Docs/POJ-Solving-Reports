## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3411] [[Paid Roads](http://poj.org/problem?id=3411)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 搜索]

------

## 问题描述

有n座城市和m（1<=n，m<=10）条路。现在要从城市1到城市n。有些路是要收费的，从a城市到b城市，如果之前到过c城市，那么只要付P的钱，如果没有去过就付R的钱。求的是最少要花多少钱。

> **注意：路径是有向的**。


## 解题思路

**DFS**。这题当有了思路后，做起来是没有难度的，但是思维推算能力要求很高。


**这题难点在于“城市与城市之间可能存在多条路径”**：

- 1、输入数据时可能会出现多条 从城市a到城市b的路径信息，但是费用有所差别；
- 2、对于 从城市a到城市b 的同一条路径，允许重复走。


有人会问，重复走同一条路径有什么意义？单纯增加费用而已，为什么不能标记所有路径，每条路只允许走一次，这样费用不是更少么？

我开始也是陷入了这种思维，但是这种想法其实“对一半，错一半”。

先来看一组数据：

```
6 5

1 2 1 10 10

2 3 4 10 100

2 4 2 15 15

4 1 1 12 12

3 6 6 10 10
```

如果每条路只允许走一次，那么方案只有1个：

`1->2->3->6` 共135元

但这组数据的正确答案是67元。为什么？正确的方案如下：

`1->2->4->1->2->3->6` 共67元

显然 `1->2` 重复走了一次，目的是为了先到达城市4，从而使得 `2->3` 这段路的费用从100缩减到10元。

看到这里很多同学好像就恍然大悟，但是问题马上又来了。如果同一条路允许重复走，那么就不能标记了，但一旦不标记，失去了搜索的限制条件，DFS就无法结束，不是陷入死循环了？

我刚才说这种思路“对一半，错一半”，“对”是对在“重复走会增加费用”，“错”是错在“重复走的对象不是某一条路，而是某一个环路”。在同一个环路重复走才会真正增加费用。但是标记环路是很麻烦的，那么能不能根据某一条路或某一个城市重复走过的次数来判断当前所走的方案已经出现了环路？ 答案是可以的。

上述的例子已经验证过了，同一条路可以重复走，但是不能无限重复走，重复的次数是有限的。那么应该重复多少次才合理？这与m值有关。题目的m值范围为 `<=10`，那么当人一个城市被到达的次数若 `>3` 次（不包括3），所走的方案必然出现了环路（网上的同学称之为“**闸数**”）。

因此只需把 `bool vist[]` 修改为 `int vist[]` 进行标记，本题就能解决了。


> 注：最近刚刚接触了C++的面向对象，所以程序用class写了一次，用C风格写了一次。


## 测试数据

- 输入：[input](/testdata/input.dat)
- 输出：[output](/testdata/output.dat)


## AC 源码

### 解题风格一：C++面向对象

```c
//Memory Time 
//248K   0MS  

/*---- C++面向对象 ----*/

#include<iostream>
using namespace std;

class Road
{
	public:
		int a,b,c,p,r;
};

class info
{
	public:
		info():MinCost(2000)   //C++的'='和'()'都能赋值
		{					   //但构造函数这里只能用'()'
			road=new Road[11];
			vist=new int[11];
			memset(vist,0,sizeof(int)*11);
			vist[1]=1;   //从城市1出发，因此预记录到达1次
		}
		~info()
		{
			delete[] road;
			delete[] vist;
		}

		void input(void);
		void output(void);
		void DFS(int a,int fee);

	protected:
		int n;  //城市数
		int m;  //道路数
		int MinCost;  //最小总花费
		int *vist;  //记录城市的访问次数,每个城市最多经过3次
		Road *road;  //每条道路的付费规则
};

void info::input(void)
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>road[i].a>>road[i].b>>road[i].c>>road[i].p>>road[i].r;

	return;
}

void info::output(void)
{
	if(MinCost==2000)
		cout<<"impossible"<<endl;
	else
		cout<<MinCost<<endl;

	return;
}

void info::DFS(int a,int fee)   //a:当前所在城市,fee:当前方案的费用
{
	if(a==n && MinCost>fee)
	{
		MinCost=fee;
		return;
	}

	for(int i=1;i<=m;i++)  //枚举道路
	{
		if(a==road[i].a && vist[ road[i].b ]<=3)
		{
			int b=road[i].b;
			vist[b]++;

			if(vist[ road[i].c ])
				DFS(b,fee+road[i].p);
			else
				DFS(b,fee+road[i].r);

			vist[b]--;       //回溯
		}
	}
	return;
}

int main(void)
{
	info poj3411;
	poj3411.input();
	poj3411.DFS(1,0);
	poj3411.output();
	return 0;
}
```

### 解题风格二：C风格

```c
//Memory Time 
//248K  16MS 

/*---- C风格 ----*/

#include<iostream>
using namespace std;

int n;  //城市数
int m;  //道路数
int vist[11];  //记录城市的访问次数,每个城市最多经过3次
int MinCost;  //最小总花费
struct
{
	int a,b,c,p,r;
}road[11];  //每条道路的付费规则

void DFS(int a,int fee)   //a:当前所在城市,fee:当前方案的费用
{
	if(a==n && MinCost>fee)
	{
		MinCost=fee;
		return;
	}

	for(int i=1;i<=m;i++)  //枚举道路
	{
		if(a==road[i].a && vist[ road[i].b ]<=3)
		{
			int b=road[i].b;
			vist[b]++;

			if(vist[ road[i].c ])
				DFS(b,fee+road[i].p);
			else
				DFS(b,fee+road[i].r);

			vist[b]--;       //回溯
		}
	}
	return;
}

int main(void)
{
	while(cin>>n>>m)
	{
		memset(vist,0,sizeof(vist));
		vist[1]=1;    //从城市1出发，因此预记录到达1次
		MinCost=2000;

		for(int i=1;i<=m;i++)
			cin>>road[i].a>>road[i].b>>road[i].c>>road[i].p>>road[i].r;

		DFS(1,0);
		if(MinCost==2000)
			cout<<"impossible"<<endl;
		else
			cout<<MinCost<<endl;
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

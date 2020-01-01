## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3253] [[Fence Repair](http://poj.org/problem?id=3253)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 哈夫曼树]

------

## 问题描述

有一个农夫要把一个木板钜成几块给定长度的小木板，每次锯都要收取一定费用，这个费用就是当前锯的这个木版的长度。

给定各个要求的小木板的长度，及小木板的个数n，求最小费用。

**提示**：

以

```
3

8 8 5
```

为例：

先从无限长的木板上锯下长度为 21 的木板，花费 21

再从长度为21的木板上锯下长度为5的木板，花费5

再从长度为16的木板上锯下长度为8的木板，花费8

总花费 = `21+5+8 =3 4`


## 解题思路

利用**Huffman思想**，要使总费用最小，那么每次只选取最小长度的两块木板相加，再把这些“和”累加到总费用中即可。

本题虽然利用了Huffman思想，但是直接用**HuffmanTree**做会超时，可以用**优先队列**做。


因为**朴素的HuffmanTree思想是**：

- （1）先把输入的所有元素升序排序，再选取最小的两个元素，把他们的和值累加到总费用
- （2）把这两个最小元素出队，他们的和值入队，重新排列所有元素，重复（1），直至队列中元素个数 `<=1`，则累计的费用就是最小费用


HuffmanTree超时的原因是每次都要重新排序，极度浪费时间，即使是用快排。


一个**优化的处理**是：

- （1）只在输入全部数据后，进行一次升序排序  (以后不再排序)
- （2）队列指针p指向队列第1个元素，然后取出队首的前2个元素，把他们的和值累计到总费用，再把和值sum作为一个新元素插入到队列适当的位置。由于原队首的前2个元素已被取出，因此这两个位置被废弃，我们可以在插入操作时，利用后一个元素位置，先把队列指针`p+1`，使他指向第2个废弃元素的位置，然后把sum从第3个位置开始向后逐一与各个元素比较，若大于该元素，则该元素前移一位，否则sum插入当前正在比较元素（队列中大于等于sum的第一个元素）的前一个位置
- （3）以当前p的位置作为新队列的队首，重复上述操作

另一种处理方法是利用STL的优先队列，priority_queue，非常方便简单高效，虽然priority_queue的基本理论思想还是上述的优化思想，但是STL可以直接用相关的功能函数实现这些操作，相对简单，详细参见我的程序。

> 注意priority_queue与qsort的比较规则的返回值的意义刚好相反。


## 测试数据

- 来源（已失效）：[USACO 2006 November Gold](http://ace.delos.com/TESTDATA/NOV06_4.htm)

> 从测试数据看得到是存在大数的情况的，要使用 `__int64`



## AC 源码

### 解题方法一： 优先队列

```c
/*优先队列*/

//Memory Time 
//376K   516MS 

#include<iostream>
using namespace std;

int cmp(const void* a,const void* b)
{
	return *(int*)a-*(int*)b;
}

int main(void)
{
	int n;
	while(cin>>n)
	{
		__int64 * w=new __int64[n+1];  //每块木板的价值

		for(int p=1;p<=n;p++)
			scanf("%I64d",&w[p]);

		qsort(w,n+1,sizeof(__int64),cmp);

		__int64 mincost=0;
		for(int i=1;i<=n-1;i++)  //每次枚举余下数列的前2个（最小）的元素，则i到n-1即可
		{
			__int64 sum=w[i]+w[i+1];   //此时w[i]和w[i+1]已经没有用了
			mincost+=sum;

			for(int j=i+2;j<=n;j++)  //寻找w[i]+w[i+1]即sum在余下数列的合适位置，并插入
			{
				if(sum>w[j])   //sum大于当前元素
				{
					w[j-1]=w[j];  //当前元素前移一格
					if(j==n)   //sum大于最后的元素(即大于所有元素)
					{
						w[j]=sum; //插入到最后
						break;
					}
				}
				else
				{
					w[j-1]=sum;  //插入到比sum大的第一个元素前面(此前的元素均被前移)
					break;
				}
			}
		}

		printf("%I64d\n",mincost);
	}
	return 0;
}
```

### 解题方法二：  STL优先队列

```c
/*STL 优先队列*/

//Memory Time 
//512K   47MS 

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

//比较规则，最小优先
class cmp
{
public:
	bool operator()(const __int64 a,const __int64 b)const
	{
		return a>b;
	}
};

int main(void)
{
	int n;  //需要切割的木板个数
	while(cin>>n)
	{
		priority_queue<__int64,vector<__int64>,cmp>Queue;  //定义优先队列

		for(int i=1;i<=n;i++)
		{
			__int64 temp;
			scanf("%I64d",&temp);
			Queue.push(temp);       //输入要求的木板长度（费用）并入队
		}

		__int64 mincost=0;   //最小费用
		while(Queue.size()>1)  //当队列中小于等于一个元素时跳出
		{
			__int64 a=Queue.top();  //得到队首元素的值，并使其出队
			Queue.pop();
			__int64 b=Queue.top();  //两次取队首，即得到最小的两个值
			Queue.pop();

			Queue.push(a+b);  //入队
			mincost+=a+b;
		}

		printf("%I64d\n",mincost);

		while(!Queue.empty())  //清空队列
			Queue.pop();
	}
	return 0;
}
```

### 解题方法三：  ~~朴素思想-哈夫曼树~~ （TLE）

```c
/*朴素思想 --->>  TLE*/

#include<iostream>
using namespace std;

const __int64 inf=1e18;

int cmp(const void* a,const void* b)
{
	return *(int*)a-*(int*)b;
}

int main(int p)
{
	int n;
	while(cin>>n)
	{
		__int64* w=new __int64[2*n];  //每块木板的价值

		for(int i=0;i<2*n;i++)
			w[i]=inf;

		for(p=0;p<n;p++)
			scanf("%I64d",&w[p]);

		int mincost=0;
		while(true)
		{
			qsort(w,2*n,sizeof(__int64),cmp);

			if(w[1]==inf)
				break;

			w[p]=w[0]+w[1];
			w[0]=w[1]=inf;
			mincost+=w[p++];
		}

		cout<<mincost<<endl;

		delete w;
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

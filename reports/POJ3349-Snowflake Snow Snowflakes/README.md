## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3349] [[Snowflake Snow Snowflakes](http://poj.org/problem?id=3349)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 高效查找法]

------

## 问题描述

在n （n<100000)个雪花中判断是否存在两片完全相同的雪花，每片雪花有6个角,每个角的长度限制为1000000

两片雪花相等的条件：

雪花6个角的长度按顺序相等（这个顺序即可以是顺时针的也可以是逆时针的）



## 解题思路

**Hash**： **连加求余法** 求key 值，**链地址法**解决冲突。

设雪花6片叶子的长度为 `len1~len6`，则：

```
key=( len1+len2+len3+len4+len5+len6)%prime
   =( len1%prime +len2%prime +len3%prime +len4%prime +len5%prime +len6)%prime
```

为了避免出现大数，这里使用了**同余模定理**求key


> **注意**：这里的key千万不能用平方和，本来这题时间就很紧凑了，乘法运算更加严重浪费时间，所以采用了连加求key，只要prime足够大，同样能够把地址冲突降低到最低，我取了10n（就是100W）内的最大的**素数**作为prime, 取 `prime=999983` 。

------

**基本做法**：

从上面的处理手法能够知道：**当且仅当两片雪花的key值一样时，这两片雪花才有可能相同**。

 
在输入第k个雪花信息的时候，先求出其key值，若在hash[]中key值没有出现过，则直接存放信息。但如果在hash[key]中已经保存有其他地址，说明此前出现过key值相同的其他雪花，这些雪花信息以链表的形式存放在hash[key]中，**这时在为第k个雪花信息寻找存放空间的同时，必然在链表中逐一访问这些具有相同key值的雪花，所以我们就能在寻址的同时，顺便逐一比较第k个雪花与这些雪花的信息**，一旦发现k与某个雪花是一样的，则**标记**，然后等待后续输入完成后，直接输出寻找到两片一样的雪花。

但是当所有输入结束后都没有标记过，则说明不存在一样的雪花。


------

这时肯定又会有同学有**疑问**：

Key值只能说明两片雪花的叶子长度之和相等，但是不能说明6片叶子分别相等，更加不能说明6片叶子按顺序相等。那么当我们寻找到key值相同的两片雪花时，我们该如何比较两片雪花？

其实是可以的。假设有两片雪花，A 和 B

我们**固定A，先按顺时针方向比较**：

```
　若A0==B0，则按顺序比较A1和B1.........比较A5和B5
　只要当出现Ai != Bi，则把B顺时针转动一次，
　若A0==B1，则按顺序比较A1和B2.........比较A5和B0
　。。。。。
　以此类推，直至B转动了5次，若还不相同，则说明这两片雪花在顺时针方向不等。
```
 

**再比较逆时针方向**：

```
　同样固定A，若A0==B5，则按顺序比较A1和B4.........比较A5和B0
　只要当出现Ai != B（5-i），则把B逆时针转动一次，
　若A0==B4，则按顺序比较A1和B3.........比较A5和B5
　。。。。。
　以此类推，直至B转动了5次，若还不相同，则说明这两片雪花在逆时针方向不等。
```
 

如是者，比较两片雪花最坏的情况为要比较 `36*2 = 72` 次！！！

可想而知当 `n=10W` 时，若任意两片比较，则最坏要比较 `72*(10W)^2` 次


------

在**这里给出两条公式**：

- 设i为A、B的第i片叶子，j为B当前顺时针转过的格数
<br/>　　那么  `A（i） ---> B（ (i+j)%6 ）`
- 设i为A、B的第i片叶子，j为B当前逆时针转过的格数
<br/>　　那么  `A（i） ---> B（ (5-i-j+6)%6 ）`


因此，为了尽可能第降低比较次数，那么我们就需要把雪花按key值分类，此时就务求prime在恰当的范围内尽可能大，使得地址冲突 (出现两个或以上key值相同的雪花) 的情况尽可能降到最低，**最理想的情况就是：当且仅当两片雪花是相同的时候，他们的key值才相等**。那么根据前面的算法思路（只对key值相同的两片雪花进行比较），**在最理想情况下，我们最多仅需比较1次就能得到“存在雪花相同”结果，最少比较0次就能得到“不存在一样的雪花”的结果**。


经过测试发现，prime取100W左右的素数时，key的离散程度是相对比较高的，冲突也就很少，prime再大，对离散化程度影响不大，而且会浪费空间。

而当prime取10W左右的素数时，出现key值相同的情况达到6K多个，此时Hash的优势根本体现不了。


## AC 源码


```c
//Memory  Time 
//16696K 3766MS 

#include<iostream>
using namespace std;

const __int64 prime=999983;  // 10n内最大的素数（本题n=10W）

class
{
public:
	__int64 len[6];  //6瓣叶子的长度
}leaf[100001];

typedef class HashTable
{
public:
	__int64 len[6];   //记录6瓣叶子的长度信息
	HashTable* next;  //用于冲突时开放寻址

	HashTable()  //Initial
	{
		next=0;
	}
}Hashtable;

Hashtable* hash[prime+1];

/*计算第k个雪花的关键字key*/

__int64 compute_key(int k)
{
	__int64 key=0;
	for(int i=0;i<6;i++)
	{
		key+=(leaf[k].len[i]) % prime;
		key%=prime;   //利用同余模定理计算key，避免出现大数
	}

	return ++key;  //键值后移1位，把key的范围从0~999982变为 1~999983
}

/*从顺时针方向判断两片雪花是否相同*/

bool clockwise(Hashtable* p,int k)
{
	for(int j=0;j<6;j++)  //顺时针转动j格
	{
		bool flag=true;
		for(int i=0;i<6;i++)
			if(leaf[k].len[i] != p->len[(i+j)%6])
			{
				flag=false;
				break;
			}
		if(flag)
			return true;
	}
	return false;
}

/*从逆时针方向判断两片雪花是否相同*/

bool counterclockwise(Hashtable* p,int k)
{
	for(int j=0;j<6;j++)  //逆时针转动j格
	{
		bool flag=true;
		for(int i=0;i<6;i++)
			if(leaf[k].len[i] != p->len[(5-i-j+6)%6])
			{
				flag=false;
				break;
			}
		if(flag)
			return true;
	}
	return false;
}

/*把第k个雪花信息插入HashTable*/
/*当插入的位置已存在其他雪花信息时，顺便比较*/

bool insert(int k)
{
	__int64 key=compute_key(k);

	if(!hash[key])
	{
		Hashtable* temp=new Hashtable;

		for(int i=0;i<6;i++)
			temp->len[i]=leaf[k].len[i];

		hash[key]=temp;  //保存key对应的地址
	}
	else  //地址冲突,开放寻址,顺便比较
	{
		Hashtable* temp=hash[key];

		if(clockwise(temp,k) || counterclockwise(temp,k))  //检查雪花是否相同
			return true;

		while(temp->next)    //寻址
		{
			temp=temp->next;

			if(clockwise(temp,k) || counterclockwise(temp,k))  //检查雪花是否相同
				return true;
		}

		temp->next=new Hashtable;    //申请空间，保存新雪花信息
		for(int i=0;i<6;i++)
			temp->next->len[i]=leaf[k].len[i];
	}
	return false;
}

int main(int i,int j)
{
	int n;  //雪花数
	while(cin>>n)
	{
		/*Initial*/

		memset(hash,0,sizeof(hash));  // 0 <-> NULL

		/*Input*/

		bool flag=false;  //记录输入过程中是否出现了相同的雪花
		for(i=1;i<=n;i++)
		{
			for(j=0;j<6;j++)
				scanf("%I64d",&leaf[i].len[j]);

			/*Hash*/

			if(!flag)    //当前还没有出现相同的雪花
				flag=insert(i);
			             //若出现相同的雪花，则还需后续输入，但不再处理
		}

		/*Output*/

		if(flag)
			cout<<"Twin snowflakes found."<<endl;
		else
			cout<<"No two snowflakes are alike."<<endl;

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

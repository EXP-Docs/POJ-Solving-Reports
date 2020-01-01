## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3432] [[Count Squares](http://poj.org/problem?id=3432)]

> [Time: 3000MS] [Memory: 65536K] [难度: 初级] [分类: 高效查找法]

------

## 问题描述

[POJ2002](/reports/POJ2002-Squares) 的山寨题。


## 解题思路

参看[POJ2002](/reports/POJ2002-Squares)，把数据规模从 `n=1000` 修改为 `n=2000` 就能AC了。

> 注意这种题一定不能图方便用STL的map标记，map效率不高，必定超时的。

## AC 源码


```c
//Memory Time
//336K   313MS 

#include<iostream>
using namespace std;

const int prime=1999;  //长度为n区间的最大素数 (本题n=2000)

typedef class
{
	public:
		int x,y;
}Node;

typedef class HashTable
{
	public:
		int x,y;   //标记key值对应的x,y
		HashTable* next;  //当出现地址冲突时，开放寻址

		HashTable()  //Initial
		{
			next=0;
		}
}Hashtable;

Node pos[2001];
Hashtable* hash[prime];   //hash[]是指针数组，存放地址

void insert_vist(int k)
{
	int key=((pos[k].x * pos[k].x)+(pos[k].y * pos[k].y))%prime +1;   //+1是避免==0
	                                                                  //使key从[0~1998]后移到[1~1999]
	if(!hash[key])
	{
		Hashtable* temp=new Hashtable;
		temp->x=pos[k].x;
		temp->y=pos[k].y;
		hash[key]=temp;
	}
	else   //hash[key]已存地址，地址冲突
	{
		Hashtable* temp=hash[key];
		
		while(temp->next)     //开放寻址，直至next为空
			temp=temp->next;

		temp->next=new HashTable;   //申请新节点，用next指向，记录x、y
		temp->next->x=pos[k].x;
		temp->next->y=pos[k].y;
	}
	return;
}

bool find(int x,int y)
{
	int key=((x * x)+(y * y))%prime +1;

	if(!hash[key])   //key对应的地址不存在
		return false;
	else
	{
		Hashtable* temp=hash[key];

		while(temp)
		{
			if(temp->x==x && temp->y==y)
				return true;

			temp=temp->next;
		}
	}

	return false;
}

int main(void)
{
	int n;
	while(cin>>n)
	{
		if(!n)
			break;

		memset(hash,0,sizeof(hash));   //0 <-> NULL

		for(int k=1;k<=n;k++)
		{
			cin>>pos[k].x>>pos[k].y;
			insert_vist(k);   //插入哈希表，标记散点
		}

		int num=0;  //正方形的个数
		for(int i=1;i<=n-1;i++)
			for(int j=i+1;j<=n;j++)
			{
				int a=pos[j].x-pos[i].x;
				int b=pos[j].y-pos[i].y;

				int x3=pos[i].x+b;
				int y3=pos[i].y-a;
				int x4=pos[j].x+b;
				int y4=pos[j].y-a;
				
				if(find(x3,y3) && find(x4,y4))
					num++;

				x3=pos[i].x-b;
				y3=pos[i].y+a;
				x4=pos[j].x-b;
				y4=pos[j].y+a;

				if(find(x3,y3) && find(x4,y4))
					num++;
			}

		cout<<num/4<<endl;  //同一个正方形枚举了4次
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

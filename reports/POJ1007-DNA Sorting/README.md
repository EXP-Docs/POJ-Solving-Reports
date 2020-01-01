## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1007] [[DNA Sorting](http://poj.org/problem?id=1007)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 排序]

------

## 问题描述

输入m个长度为n的DNA序列，把他们按照逆序数从小到大稳定排序输出。

> “稳定排序”就是当序列中出现A1==A2时，排序前后A1与A2的相对位置不发生改变。


## 解题思路

没难度，先求各个字符串的逆序数，再按逆序数对字符串快排，用 `qsort()` 函数。

虽然快排不是稳定的排序，但是只要在定义排序规则函数 `cmp` 做适当处理，`a==b` 时返回0，即不处理a和b，就不会改变他们之间的相对位置了。


## AC 源码


```c
//Memory Time 
//252K   16MS 

#include<iostream>
#include<algorithm>
using namespace std;

typedef class dna
{
	public:
		int num;  //逆序数
		char sq[110];  //DNA序列
}DNAStr;

int InversionNumber(char* s,int len)
{
	int ans=0;  //s逆序数
	int A,C,G;  //各个字母出现次数，T是最大的，无需计算T出现次数
	A=C=G=0;
	for(int i=len-1;i>=0;i--)
	{
		switch(s[i])
		{
		    case 'A':A++;break;  //A是最小的，无逆序数
			case 'C':
				 {
					 C++;
					 ans+=A;  //当前C后面出现A的次数就是这个C的逆序数
					 break;
				 }
			case 'G':
				{
					G++;
					ans+=A;
					ans+=C;
					break;
				}
			case 'T':
				{
					ans+=A;
					ans+=C;
					ans+=G;
					break;
				}
		}
	}
	return ans;
}

int cmp(const void* a,const void* b)
{
	DNAStr* x=(DNAStr*)a;
	DNAStr* y=(DNAStr*)b;
	return (x->num)-(y->num);
}

int main(void)
{
	int n,m;
	while(cin>>n>>m)
	{
		DNAStr* DNA=new DNAStr[m];
		for(int i=0;i<m;i++)
		{
			cin>>DNA[i].sq;
			DNA[i].num = InversionNumber(DNA[i].sq,n);
		}
		qsort(DNA,m,sizeof(DNAStr),cmp);
		for(int j=0;j<m;j++)
			cout<<DNA[j].sq<<endl;
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

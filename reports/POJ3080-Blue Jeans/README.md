## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3080] [[Blue Jeans](http://poj.org/problem?id=3080)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 串]

------

## 问题描述

就是求k个长度为60的字符串的**最长连续公共子串**， `2<=k<=10`

规定：

- 最长公共串长度小于3不输出
- 若出现等长的最长的子串，则输出字典序最小的串


## 解题思路

**LCS**问题，纠结了几个月放着没做的题目。。

一直以为要用**KMP**或者**后缀数组**来做。。。

然后我就拼命学后缀。。。

今天偶然发现直接 暴力 能够达到 0ms 的效果= =

所以。。。暴力吧。。。不愧为初级的题。。。

------


暴力思想很简单：

开二维 `DNA[][]` 保存所有DNA序列

- 1、 以 `DNA[0]` 为母版，顺次截取60个长度 `length=1` 的子串 `dna[]` ，检查其他 `DNA[i]` 是否都有子串dna，若是则把 `dna[]` 复制到 `obj[]`，否则枚举下一个长度length的子串；若obj与新的dna等长，则比较两者字典序，当dna字典序小时，复制到obj
- 2、 第1步循环60次后 `length+1`。
<br/>　　顺次截取59个长度 `length=2` 的子串 `dna[]`，重复1的操作更新obj。。
- 3、 第2步循环59次后 `length+1`。
<br/>　　顺次截取58个长度 `length=3` 的子串 `dna[]`，继续。。
- ...........
- 60、 第59步循环2次后 `length+1`。
<br/>　　顺次截取1个长度 `length=60` 的子串 `dna[]`，继续重复操作更新obj。。
- 61、 输出obj


## 测试数据

- 来源：[2006 South Central USA Regional Programming Contest （问题4）](http://acm2006.cct.lsu.edu/problems/)
- 下载：[download](/reports/POJ3080-Blue%20Jeans/testdata.zip)
- 输入：[input](/reports/POJ3080-Blue%20Jeans/testdata/input.dat)
- 输出：[output](/reports/POJ3080-Blue%20Jeans/testdata/output.dat)


## AC 源码


```c
//Memory Time 
//248K   16MS 

#include<iostream>
#include<string.h>
using namespace std;

const int len=60;

int main(int i,int j)
{
	int test;
	cin>>test;
	for(int t=1;t<=test;t++)
	{
		int n;  //DNA个数
		cin>>n;
		char** DNA=new char*[n];
		for(int p=0;p<n;p++)
		{
			DNA[p]=new char[len+1];
			cin>>DNA[p];
		}

		char obj[len+1];  //所有DNA的公共串
		int StrLen=0;    //最长公共串长度
		int length=1;    //当前枚举的公共串长度

		for(i=0;;i++)  //枚举公共串dna[]
		{
			/*截取DNA[0][]中以pi为起点，长度为length的子串dna[]*/
			char dna[len+1];
			int pi=i;
			if(pi+length>len)
			{
				length++;
				i=-1;
				if(length>len)
					break;
				continue;
			}
			for(j=0;j<length;j++)
				dna[j]=DNA[0][pi++];
			dna[j]='\0';

			/*检查其他DNA[][]是否都存在字符串dna[]*/
			bool flag=true;
			for(int k=1;k<n;k++)
				if(!strstr(DNA[k],dna))  //存在一个DNA不含有dna[]
				{
					flag=false;
					break;
				}

			/*确认最大公共串*/
			if(flag)
			{
				if(StrLen<length)
				{
					StrLen=length;
					strcpy(obj,dna);	
				}
				else if(StrLen==length)
				{
					if(strcmp(obj,dna)>0)  //存在相同长度的公共串时，取最小字典序的串
						strcpy(obj,dna);
				}
			}
		}

		if(StrLen<3)
			cout<<"no significant commonalities"<<endl;
		else
			cout<<obj<<endl;

		delete DNA;
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

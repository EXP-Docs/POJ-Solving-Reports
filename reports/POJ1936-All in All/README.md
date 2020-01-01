## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1936] [[All in All](http://poj.org/problem?id=1936)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 串]

------

## 问题描述

无。


## 解题思路

水题一道，直接去**模拟**吧。

在s2中找s1的子串而已，本来还想用LCS的，后来想想，这样空间消耗太大，用滚动数组又麻烦。。。毕竟列数最多高达10W = = 所以还是算了，直接模拟更快= =


**注意**下标范围 int是够不到10W的，要用 long 。


## AC 源码


```c
//Memory Time 
//364K  0MS 

#include<iostream>
#include<string>
using namespace std;

int main(long i, long j)
{
	char s1[100000],s2[100000];
	while(cin>>s1>>s2)
	{
		long len1=strlen(s1);
		long len2=strlen(s2);
		i=0;
		j=0;
		while(true)
		{
			if(i==len1)
			{
				cout<<"Yes"<<endl;
				break;
			}
			else if(i<len1 && j==len2)
			{
				cout<<"No"<<endl;
				break;
			}
			if(s1[i]==s2[j])
			{
				i++;
				j++;
			}
			else
				j++;
		}
		memset(s1,'\0',sizeof(s1));
		memset(s2,'\0',sizeof(s2));
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

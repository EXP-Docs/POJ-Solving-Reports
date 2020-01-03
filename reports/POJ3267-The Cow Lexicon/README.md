## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3267] [[The Cow Lexicon](http://poj.org/problem?id=3267)]

> [Time: 2000MS] [Memory: 65536K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

给出一个主串，和一本字典，问最少在主串删除多少字母，可以使其匹配到字典的单词序列。

> 是匹配单词序列，而不是一个单词


## 解题思路

主要是知道状态方程的含义

**`dp[i]` 表示从message中第i个字符开始，到第L个字符（结尾处）这段区间所删除的字符数，初始化为 `dp[L]=0`**

由于我的程序是从message尾部向头部检索匹配，所以是下面的状态方程：

![](/reports/POJ3267-The%20Cow%20Lexicon/img/01.png)

**从程序可以看出，第i个位置到L所删除的字符数，总是先取最坏情况，只有可以匹配单词时才进入第二条方程进行状态优化更新。**


**第一条方程不难理解，只要弄懂 `dp[i]` 的意义就能简单推导**

第二条方程难点在 `dp[pm]+(pm-i)-len`

从程序知道，pm是message的指针（其中i表示当前所匹配的单词在message中的起始位置），pd是字典的指针

**匹配的过程是**：

当确认message第i位和某单词的首位吻合时，就开始逐字匹配，字符相同则两个指针同时向后移动一次，否则pd固定，pm移动。当因为 `pm>L` 跳出匹配时，说明匹配失败，`dp[i]`状态不变；当 `pd==单词长度` 时，单词匹配成功，进行 `dp[i]` 的状态优化。


显然，匹配成功时，`pm-i` 代表匹配过程中，从位置i到pm的区间长度，再减去单词长度len，则得到从i到pm所删除的字符数 `(pm-i)-len` 。又 `dp[pm]` 表示从pm到L所删除的字符数（根据检索方向，`dp[pm]`的值在此前已经被作为最坏打算处理，因此并不是空值）

从而 `dp[pm]+(pm-i)-len` 表示i到L删除的字符数，不难证明这个值一定比 `dp[i]` 相等或更优，因此取min赋值给 `dp[i]`。

**这是本题最难的地方**。

最后输出 `dp[0]` 就可以了，`dp[0]` 的意思相信大家都明白了。


## AC 源码


```c
//Memory Time 
//336K   79MS 

#include<iostream>
#include<string>
using namespace std;

int min(int a,int b)
{
	return a<b?a:b;
}

int main(int i,int j)
{
	int w,L;
	while(cin>>w>>L)
	{
		/*Read In*/

		int* dp=new int[L+1];
		char* mesg=new char[L];
		string* dict=new string[w];

		cin>>mesg;
		for(i=0;i<w;i++)
			cin>>dict[i];

	    /*Initial*/

		dp[L]=0;       //dp[i]表示从i到L所删除的字符数

		/*Dp-Enum*/

		for(i=L-1;i>=0;i--)  //从message尾部开始向前检索
		{
			dp[i]=dp[i+1]+1;  //字典单词和message无法匹配时，删除的字符数（最坏的情况）
			for(j=0;j<w;j++) //对字典单词枚举
			{
				int len=dict[j].length();
				if(len<=L-i && dict[j][0]==mesg[i])  //单词长度小于等于当前待匹配message长度
				{                                    //且单词头字母与信息第i个字母相同
					int pm=i;  //message的指针
					int pd=0;  //单词的指针
					while(pm<L) //单词逐字匹配
					{
						if(dict[j][pd]==mesg[pm++])
							pd++;
						if(pd==len)
						{     //字典单词和message可以匹配时，状态优化（更新）
							dp[i]=min(dp[i],dp[pm]+(pm-i)-len);//dp[pm]表示从pm到L删除的字符数
							break;                            //(pm-i)-pd表示从i到pm删除的字符数
						}                                     //则dp[pm]+(pm-i)-pd表示从i到L删除的字符数
					}
				}
			}
		}
		cout<<dp[0]<<endl;

		delete dp,mesg,dict;
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

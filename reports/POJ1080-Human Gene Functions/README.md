## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1080] [[Human Gene Functions](http://poj.org/problem?id=1080)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 动态规划]

------

## 问题描述

无。


## 解题思路

**LCS的变形**而已

> **注意**LCS的子串可以是离散的，不必连续，用**动态规划**


设 `dp[i][j]` 为取s1第i个字符，s2第j个字符时的最大分值

则决定dp为最优的情况有三种（ `score[][]` 为 `s1[i]` 和 `s2[j]` 两符号的分数）：

- 1、  s1取第i个字母，s2取 `'-'`： `dp[i-1][j]+score[ s1[i-1] ]['-'];`
- 2、  s1取 `'-'`，s2取第j个字母： `dp[i][j-1]+score['-'][ s2[j-1] ];`
- 3、  s1取第i个字母，s2取第j个字母： `dp[i-1][j-1]+score[ s1[i-1] ][ s2[j-1] ];`

即 :

```
dp[i][j]=max( 
	dp[i-1][j]+score[ s1[i-1] ]['-'],
	dp[i][j-1]+score['-'][ s2[j-1] ],
	dp[i-1][j-1]+score[ s1[i-1] ][ s2[j-1] ] 
);
```


------------


**注意**初始化。

不仅仅只有

`dp[0][0] = 0`

也不仅仅是

```
dp[0][0] = 0
dp[1][0] = score[ s1[i-1] ]['-']
dp[0][1] = score['-'][ s2[j-1] ]
```

必须全面考虑到所有情况:

- 当 `i=j=0` 时，`dp[i][j]=0`
- 当 `i=0` 时，`dp[0,j] = dp[0][j-1] + score['-'][ s2[j-1] ]`
- 当 `j=0` 时，`dp[i,0] = dp[i-1][0] + score[ s1[i-1] ]['-']`



## AC 源码


```c
//Memory Time 
//300K   0MS  

#include<iostream>
using namespace std;
const int inf=-5;  //无穷小

int score['T'+1]['T'+1];  //积分表

void initial(void)  //打表
{
	score['A']['A']=5;
	score['C']['C']=5;
	score['G']['G']=5;
	score['T']['T']=5;
	score['-']['-']=inf;
	score['A']['C']=score['C']['A']=-1;
	score['A']['G']=score['G']['A']=-2;
	score['A']['T']=score['T']['A']=-1;
	score['A']['-']=score['-']['A']=-3;
	score['C']['G']=score['G']['C']=-3;
	score['C']['T']=score['T']['C']=-2;
	score['C']['-']=score['-']['C']=-4;
	score['G']['T']=score['T']['G']=-2;
	score['G']['-']=score['-']['G']=-2;
	score['T']['-']=score['-']['T']=-1;
	return;
}

int max(int a,int b,int c)
{
	int k=(b>c?b:c);
	return a>k?a:k;   //注意求三个数最大值时，a>b?a:(b>c?b:c)在C++中是错误的
}                     //b的值没有因为(b>c?b:c)而改变，必须把三个数拆开求最大值

int main(int i,int j)
{
	initial();

	int test;
	cin>>test;
	while(test--)
	{
		/*Input*/

		int len1,len2;

		cin>>len1;
		char* s1=new char[len1+1];
		cin>>s1;

		cin>>len2;
		char* s2=new char[len2+1];
		cin>>s2;

		int **dp=new int*[len1+1];   //申请动态二维数组，第一维
		dp[0]=new int[len2+1];

		/*Initial*/

		dp[0][0]=0;
		for(i=1;i<=len1;i++)
		{
			dp[i]=new int[len2+1];  //申请动态二维数组，第二维
			dp[i][0]=dp[i-1][0]+score[ s1[i-1] ]['-'];   //注意下标，dp数组是从1开始，s1和s2都是从0开始
		}
		for(j=1;j<=len2;j++)
			dp[0][j]=dp[0][j-1]+score['-'][ s2[j-1] ];
		
		/*Dp*/

		for(i=1;i<=len1;i++)
			for(j=1;j<=len2;j++)
			{
				int temp1=dp[i-1][j]+score[ s1[i-1] ]['-'];
			    int temp2=dp[i][j-1]+score['-'][ s2[j-1] ];
			    int temp3=dp[i-1][j-1]+score[ s1[i-1] ][ s2[j-1] ];
			    dp[i][j]=max(temp1,temp2,temp3);
			}

		cout<<dp[len1][len2]<<endl;

		delete[] dp;
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

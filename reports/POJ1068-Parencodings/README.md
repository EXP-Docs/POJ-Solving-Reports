## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1068] [[Parencodings](http://poj.org/problem?id=1068)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 模拟法]

------

## 问题描述

对于给出的原括号串，存在两种数字密码串：

- p序列：当出现匹配括号对时，从该括号对的右括号开始往左数，直到最前面的左括号数，就是pi的值。
- w序列：当出现匹配括号对时，包含在该括号对中的所有右括号数（包括该括号对），就是wi的值。


**题目要求**：

- 对给出的p数字串，求出对应的s串。
- 串长限制均为20


## 解题思路

模拟题，难度不大，关键读懂题意。

在处理括号序列时可以使用一个小技巧，把括号序列转化为01序列，左0右1，处理时比较方便


## AC 源码


```c
//Memory  Time 
//256K     0MS 

#include<iostream>
using namespace std;

int main(void)
{
	int p[21]={0};      //使  p[0]=0
	int w[20];
	int str[40];     //括号串，左0右1
	int n;

	int cases;
	cin>>cases;
	while(cases--)
	{
		memset(str,0,sizeof(str));   //str串初始化为全0

		cin>>n;

		int i,j,k;

		/*Input P-sequence*/

		for(i=1;i<=n;i++)
			cin>>p[i];

		/*Convert the P-sequence to the string of parenthesese*/

		for(j=0,i=1;i<=n;i++)        //把P数列转化为01串，左括为0，右括为1
			for(k=0;;k++)
				if(k<p[i]-p[i-1])    //以每个右括为终点，把括号串分成多个01子串（子串左边全是0，右边只有唯一的1.每个子串至少含一个1）
					j++;              //k为各个子串的指针，j为str串的指针
				else if(k==p[i]-p[i-1])
				{
					str[j++]=1;
					break;
				}

		const int length=j;   //str串长

        /*Convert the string of parenthesese to the W-sequence*/

		int count;
		for(i=0;i<length;i++)    //str串向W数列转换
			if(str[i]==1)      //在str中遇到1（右括）就回溯，找出离其最近的0（左括）
			{
				count=2; //计数器初始化为2是因为当前正在寻找的配对的01将置换为两个'F'
				for(j=i-1;;j--)
				{
					if(str[j]==0)
					{
						str[i]=str[j]='F';  //01配对后就都置为'F'
						break;
					}
					else
						count++; //在回溯找0的过程中，每遇到一个F，计数器就+1
				}
				cout<<count/2<<' ';  //计数器的个数就是当前 括号对 所包含的 括号对 (包括当前括号对)数量的两倍
			}
		cout<<endl;
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

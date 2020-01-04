## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1850] [[Code](http://poj.org/problem?id=1850)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 排列组合]

------

## 问题描述

与 [POJ1496](http://exp-blog.com/2018/06/23/pid-997/) 基本一致。

输出某个str字符串在字典中的位置，由于字典是从 `a=1` 开始的，因此str的位置值就是 在str前面所有字符串的个数 `+1`。

规定输入的字符串必须是升序排列。**不降序列是非法字符串**

不要求用循环输入去输入若干组字符串，但 **若输入非法字符串则输出0，且结束程序，这是和 [POJ1496](http://exp-blog.com/2018/06/23/pid-997/) 最猥琐的区别**，很多同学只注意到规定str的长度不同，以为把str数组长度改一下直接复制就能AC再多刷一题了，殊不知老是WA却找不到原因，大概就是这里出问题了

> 本题Str最长为10个字符


## 解题思路

**组合数学**题，（也属 **递推数学**，是因为**杨辉三角**和组合数之间的关系）


**第一步当然首先判断输入的str是否是升序序列**


若符合第一步，则首先计算比str长度少的所有字符串个数

假设str为 vwxyz ，则其长度为5，那么

![](/reports/POJ1850-Code/img/01.png)

------

**第二步就是关键了，长度为2的字符串，根据开头字母不同，就有25种不同情况，编程去处理是很困难的。这里必须要用数学方法去处理。**

![](/reports/POJ1850-Code/img/02.png)


**所以用一个简单的循环就能计算出 比str长度少的所有字符串个数 了**

> 这就是数学的威力，把受限的取法转换为不限制的取法

------

**第三步，就是求长度等于str，但值比str小的字符串个数**

这个看我程序的注释更容易懂，所以这里就不再啰嗦了，值得注意的是这步我同样利用了公式（1）,所以如果看到某些地方取字母的时候看上去好像没有遵守“升序规则”，本来要限制取字母的地方却没有限制，那一定是用公式（1）变换了



**第四步，把前面找到的所有字符串的个数之和再+1，就是str的值**

之所以+1，是因为此前的所有操作都只是找str之前的字符串，并不包括str本身

------

**最后**，剩下一个问题就是怎样得到每一个 的值，这个我发现很多同学都是利用打表做的，**利用的就是 组合数 与 杨辉三角 的关系**（建立一个二维数组 `C[n]`，就能看到他们之间关系密切啊！区别就是顶点的值，杨辉三角为1，组合数为0）

其实这个“关系”是有数学公式的：

![](/reports/POJ1850-Code/img/03.png)


其实组合数也可以直接用计算方法做(n的规模可以至少扩展到1000)，不过这里n的规模只有26，打表应该是更快的


## AC 源码


```c
//Memory Time 
// 208K   0MS 

#include<iostream>
#include<string>
using namespace std;

int c[27][27]={0};

/*打表，利用杨辉三角计算每一个组合数nCm*/

void play_table(void)
{
	for(int i=0;i<=26;i++)
		for(int j=0;j<=i;j++)
			if(!j || i==j)
				c[i][j]=1;
			else
				c[i][j]=c[i-1][j-1]+c[i-1][j];
	c[0][0]=0;
	return;
}

int main(int i,int j)
{
	play_table();

	char str[11];
	while(cin>>str)
	{
		int len=strlen(str);

		/*检查str是否符合升序排列*/

		for(i=1;i<len;i++)
			if(str[i-1]>=str[i])
			{
				cout<<0<<endl;   //本题只要求输入一次就允许结束程序
				return 0;        //因此若使用循环输入，一旦str不符合字典要求（如aab,ba等）就要结束程序
			}                    //这是与POJ1496的最隐蔽区别
		
		int sum=0;  //str的值，初始为0
			
		/*计算长度比str小的字符串个数*/
			
		for(i=1;i<len;i++)
			sum+=c[26][i];  //c[26][i]表示 长度为i的字符串的个数
			
		/*计算长度等于len，但值比str小的字符串个数*/
			
		for(i=0;i<len;i++)  //i为str的指针，对每一个位置枚举 允许选择的字符ch
		{
			char ch= (!i)?'a':str[i-1]+1;   //ch = str[i-1]+1 根据升序规则，当前位置的ch至少要比str前一位置的字符大1
			while(ch<=str[i]-1)   //ch<=str[i]-1 根据升序规则，当前位置的ch最多只能比 str这个位置实际上的字符 小1
			{
				sum+=c['z'-ch][len-1-i];  //'z'-ch ： 小于等于ch的字符不允许再被选择，所以当前能够选择的字符总数为'z'-ch
				ch++;                     //len-1-i  ： ch位置后面（不包括ch）剩下的位数，就是从'z'-ch选择len-1-i个字符
			}
		}
			
		cout<<++sum<<endl;     // 此前的操作都是寻找比str小的所有字符串的个数，并不包括str本身，因此这里要+1
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

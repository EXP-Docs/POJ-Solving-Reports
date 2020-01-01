## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1016] [[Numbers That Count](http://poj.org/problem?id=1016)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 串]

------

## 问题描述

题意不难懂，对于任意的数字串n，都可以压缩存储为c1 d1 c2 d2 .... ck dk 形式的数字串

而存在一些特别的数字串，其压缩前后的样子是一模一样的，定义这种数字串为self-inventorying


当我们把n看成原串，

A为n压缩1次后的数字串，

B为n压缩2次后的数字串（即A压缩1次后的数字串）

....以此类推

K为n压缩k次后的数字串（即K-1压缩k-1次后的数字串）

由此**则可以延伸出数字串n的3种属性**：

- n压缩1次就马上出现self-inventorying特性，即 n n n n n n n .....
- n压缩j次后的数字串J出现self-inventorying特性，即 n A B C....H I J J J J J J J
- n压缩j次后的数字串J，每再压缩K次，重新出现数字串J，即n A B... J ..K J ..K J..K J

其中K称为循环间隔，`K>=2`

现给定一字符串，输出其属性。 

属性1优于属性2，属性2优于属性3


## 解题思路

**字符串处理**，纯粹的**模拟题**

压缩n时要注意，ck可能是1位，也可能是2位，需要判断。


设R(n)为描述整数n的压缩数字串


1、 当R(n)==R(R(n))时，则n is self-inventorying

2、 对于整数n：

```c
令N = n
for j=1 to 15
{   
	令tj =R(N)
	若R(tj)== R(R(tj)) ，则n is self-inventorying after j steps 且 break
	否则  N=tj
}
```

3、 对于整数n：

```c
令N = n，记录num[0]= n
for j=1 to 15
{     
	令tj =R(N)，记录num[j]=tj
	for i=0 to j-2 (保证k>=2)
	{        
		若tj== num[i] ，则n enters an inventory loop of length k ( k=j-i )
		break
	}
}
```

4、 当且仅当n的3种属性都不存在时，n can not be classified after 15 iterations


## 测试数据

- 来源（已失效）：[East Central North America 1998](http://plg1.cs.uwaterloo.ca/~acm00/regional98/real/)
- 输入：[input](/reports/POJ3080-Blue%20Jeans/testdata/input.dat)
- 输出：[output](/reports/POJ3080-Blue%20Jeans/testdata/output.dat)



## AC 源码


```c
//Memory Time 
//232K   32MS 

#include<iostream>
#include<string>
using namespace std;

/*压缩数字串n，存放到t*/
void R(char* n,char* t)
{
	int i,j;
	int time[10]={0};  //记录n中各个数字出现的次数
	for(i=0;n[i];i++)
		time[ n[i]-'0' ]++;

	for(i=0,j=0;i<10;i++)
	{
		if(time[i])
		{
			if(time[i]<10)  //数字i出现次数<10，即占1位
			{
				t[j++]=time[i]+'0';
				t[j++]=i+'0';
			}
			else    //数字i出现次数>=10，即占2位
			{
				t[j++]=time[i]/10+'0';
				t[j++]=time[i]%10+'0';
				t[j++]=i+'0';
			}
		}
	}
	t[j]='\0';

	return;
}

int main(int i,int j)
{
	char n[16][85];    //n[0]为原串，n[1~15]分别为n连续压缩15次的数字串

	while(cin>>n[0] && n[0][0]!='-')
	{
		bool flag1=false;    //属性1，n is self-inventorying
		int flag2=0;         //属性2，n is self-inventorying after j steps，顺便记录j
		int flag3=0;         //属性3，n is enters an inventory loop of length k，顺便记录k

		for(i=1;i<=15;i++)
			R(n[i-1],n[i]);

		if(!strcmp(n[0],n[1]))  //属性1，n压缩1次就是其本身
			flag1=true;

		if(!flag1)
		{
			for(j=1;j<15;j++)
				if(!strcmp(n[j],n[j+1]))  //属性2, n压缩j次后的数字串n[j]具有属性1
				{
					flag2=j;
					break;
				}

			if(!flag2)
			{
				for(j=1;j<=15;j++)  //属性3，两两枚举各次压缩的数字串，注意循环间隔>=2
				{
					for(i=0;i<=j-2;i++)
					{
						if(!strcmp(n[j],n[i]))
						{
							flag3=j-i;
							break;
						}
					}
					if(flag3)
						break;
				}
			}
		}

		if(flag1)
			cout<<n[0]<<" is self-inventorying"<<endl;
		else if(flag2)
			cout<<n[0]<<" is self-inventorying after "<<flag2<<" steps"<<endl;
		else if(flag3)
			cout<<n[0]<<" enters an inventory loop of length "<<flag3<<endl;
		else
			cout<<n[0]<<" can not be classified after 15 iterations"<<endl;
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

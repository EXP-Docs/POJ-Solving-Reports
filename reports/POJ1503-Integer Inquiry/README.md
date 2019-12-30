## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1503] [[Integer Inquiry](http://poj.org/problem?id=1503)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 高精度算法]

------

## 问题描述

无。


## 解题思路

就是多个**大数**相加的问题


## AC 源码


```c
//Memory   Time 
//184K      0MS 

#include<iostream>
#include<cstring>
using namespace std;

const int large=1000;
char sum_temp[large];
char digit_temp[large];

int plus(int j,int carry_bit)
{
	int count;
	count=(sum_temp[j]-'0')+(digit_temp[j]-'0')+carry_bit;
	sum_temp[j]=count%10+'0';
	if(count<10)
		return 0;
	else
		return 1;
}

int main(void)
{
	int length,i,j,k;
	int max=0,carry_bit=0;
	char digit[large],sum[large];

	memset(sum_temp,'0',sizeof(sum_temp));

	for(i=-1;strcmp(digit,"0");)
	{
		i++;
		gets(digit);
		length=strlen(digit)-1;

		memset(digit_temp,'0',sizeof(digit_temp));

		for(k=0,j=length;j>=0;--j,++k)
			digit_temp[k]=digit[j];        //倒置
		if(max<length)
			max=length;
		for(carry_bit=0,j=0;j<=max;j++)     //每两个长数相加一次进位必须初始化进位值
			carry_bit=plus(j,carry_bit);
	    if(carry_bit==1)         //最高位进位检查
		    sum_temp[++max]='1';
	    for(i=max,j=0;i>=0;--i,++j)
		{
		    if(i==max&&sum_temp[i]=='0')   //检查并消去高位0
			{
		    	--max;
		    	continue;
			}
		    sum[j]=sum_temp[i];         //倒置
		}
		sum[j]='\0';           //末尾添加结束符
	}
	cout<<sum<<endl;
	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

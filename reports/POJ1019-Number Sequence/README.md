## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1019] [[Number Sequence](http://poj.org/problem?id=1019)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 递推关系]

------

## 问题描述

有一串数字串，其规律为

1 12 123 1234 12345 123456 1234567 12345678 123456789 12345678910 1234567891011 123456789101112······k

输入位置n，计算这一串数字第n位是什么数字，注意是数字，不是数！例如 12345678910 的第10位是1，而不是10，第11位是0，也不是10。总之多位的数在序列中要被拆分为几位数字，一个数字对应一位。


## 解题思路

首先建议数学底子不好的同学，暂时放一放这题，太过技巧性了，连理解都很困难。


**模拟分组**，把1看做第1组，12看做第2组，123看做第3组……那么第i组就是存放数字序列为 `[1,i]`的正整数，但第i组的长度不一定是i


已知输入查找第n个位的n的范围为 (`1 ≤ n ≤ 2147483647`)，那么至少要有31268个组才能使得数字序列达到有第2147483647位。


> 注意：2147483647 刚好是int的正整数最大极限值，所以对于n用int定义就足矣。但是 `s[31268]` 存在超过2147483647的位数，因此要用 `unsigned` 或 `long` 之类的去定义 `s[]`


详细的解题思路请参照程序的注释。

其中**数学难点有二**：

- `(int)log10((double)i)+1`
- `(i-1)/(int)pow((double)10,len-pos)%10`

非常技巧性的处理手法，其意义已在程序中标明。


**另外要注意**的就是 `log()` 和 `pow()` 函数的使用。

两个都是重载函数，函数原型分别为

- `double log(double)`
- `float log(float)`
- `double pow(double, double)`
- `float pow(float, float)`

所以当传参的类型不是 double 或 float 时，必须强制转换为其中一种类型，否则编译出错。一般建议用 double


## AC 源码


```c
//Memory Time 
//476K    0MS 

#include<iostream>
#include<math.h>
using namespace std;

const int size=31269;

unsigned a[size];   //a[i] 表示第i组数字序列的长度
unsigned s[size];   //s[i] 表示前i组数字序列的长度
                     //第i组存放的数字序列为 [1,i]的正整数，但第i组的长度不一定是i
                     //例如数字13要被看做1和3两个位，而不是一个整体

/*打表，预先获取第2147483647个位的序列分组情况*/

void play_table(void)
{
	a[1]=s[1]=1;
	for(int i=2;i<size;i++)
	{
		a[i]=a[i-1]+(int)log10((double)i)+1;  //log10(i)+1 表示第i组数字列的长度 比 第i-1组 长的位数
		s[i]=s[i-1]+a[i];      //前i组的长度s[i] 等于 前i-1组的长度s[i-1] + 第i组的长度a[i]
	}                          //log()是重载函数，必须对int的i强制类型转换，以确定参数类型
	return;
}

/*计算序列第n个位置上的数字*/

int compute(int n)
{
	int i=1;
	while(s[i]<n)
		i++;    //确定整个数字序列的第n个位置出现在第i组

	int pos=n-s[i-1];   //pos为 整个数字序列的第n个位置 在 第i组中的下标值

	int len=0;
	for(i=1;len<pos;i++)  //从第1组开始遍历第i前的每一个组，利用log10(i)+1递推第i组的长度
		len+=(int)log10((double)i)+1;  //len为第i组(n所在的组)的长度

	return (i-1)/(int)pow((double)10,len-pos)%10;  
	       //之所以i-1，是因为前面寻找第i组长度时，i++多执行了一次
	       //i=i-1 此时i刚好等于第n位个置上的数 （数是整体，例如123一百二十三，i刚好等于123，但n指向的可能是1，2或3）
	       //pos为n指向的数字在第i组中的下标值
	       //len为第i组的长度
	       //那么len-pos就是第i组中pos位置后多余的数字位数
	       //则若要取出pos位上的数字，就要利用(i-1)/pow(10,len-pos)先删除pos后多余的数字
	       //再对剩下的数字取模，就可以得到pos
	       //例如要取出1234的2，那么多余的位数有2位：34。那么用1234 / 10^2，得到12，再对12取模10，就得到2

}          //pow()是重载函数，必须对int的i强制类型转换，以确定参数类型

int main(void)
{
	play_table();

	int test;
	cin>>test;
	while(test--)
	{
		int n;
		cin>>n;
		cout<<compute(n)<<endl;
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

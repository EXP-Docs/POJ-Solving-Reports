## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1008] [[A+B Problem](http://poj.org/problem?id=1008)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 模拟法]

------

## 问题描述

无。

## 解题思路

模拟题，细心点就好了，没难度。

Habb 历一年 365 天

Tzolkin 历一年 260 天

先计算 Habb 历从第 0 天到输入日期的总天数 sumday

`Sumday/day` 就是 Tzolkin 历的年份

Tzolkin 历的天数 Name 每 20 一循环，先建立 Tzolkin 历天数Name与 `1~20` 的映射，

因此 `Sumday % 20 + 1` 就是 Tzolkin 历的天数 Name

Tzolkin 历的天数 ID 每 13 一循环，且从 1 开始，则 `Sumday % 13 + 1` 就是 Tzolkin 历的天数 ID

## AC 源码

```c
//Memory Time  
//264K   0MS 

#include<iostream>
using namespace std;

/*得到Haab历月份对应的数字*/
int GetMonth(char* month)
{
	int ASCII=0;
	for(int i=0;month[i];i++)
		ASCII+=month[i];

	switch(ASCII)
	{
	    case 335:return 1;  //pop
		case 221:return 2;  //no
		case 339:return 3;  //zip
		case 471:return 4;  //zotz
		case 438:return 5;  //tzec
		case 345:return 6;  //xul
		case 674:return 7;  //yoxkin
		case 328:return 8;  //mol
		case 414:return 9;  //chen
		case 338:return 10;  //yax
		case 318:return 11;  //zac
		case 304:return 12;  //ceh
		case 305:return 13;  //mac
		case 636:return 14;  //kankin
		case 433:return 15;  //muan
		case 329:return 16;  //pax
		case 534:return 17;  //koyab
		case 546:return 18;  //cumhu
		case 552:return 19;  //uayet
	}
}
/*计算Haab历从第0天到现在的天数*/
int HaabDay(int day,int month,int year)
{
	int sumday=0;
	for(int i=0;i<year;i++) //Haab历法一年有365天
		sumday+=365;

	for(int j=1;j<month;j++)
		sumday+=20;

	return sumday+day;
}

int main(void)
{
	char TzolkinDayName_Str[21][10]={"0","imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok","chuen","eb","ben","ix","mem","cib","caban","eznab","canac","ahau"};
	int day;
	char doc;  //注意输入格式有 "."
	char month[10];
	int year;

	int test;
	cin>>test;
	cout<<test<<endl;
	while(test-- && (cin>>day>>doc>>month>>year))  //日期. 月份 年数
	{
		int sumday=HaabDay(day,GetMonth(month),year);

		int TzolkinYear=sumday/260;   //Tzolkin历法一年有260天
		int TzolkinDayName=sumday%20+1;
		int TzolkinDayId=sumday%13+1;

		cout<<TzolkinDayId<<' '<<TzolkinDayName_Str[TzolkinDayName]<<' '<<TzolkinYear<<endl;
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

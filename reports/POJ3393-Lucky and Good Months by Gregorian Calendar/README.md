## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3393] [[Lucky and Good Months by Gregorian Calendar](http://poj.org/problem?id=3393)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 模拟法]

------

## 问题描述

科普文一篇，文章80%都是无用信息，因为都是常识，但是又不得不看，因为有20%是常人不知道的历史常识。


**定义**：

- Goog month ： 该月第一个工作日为星期一的月份
- Luckly month： 该月最后一个工作日为星期五的月份

问： 给定一个Gregorian Calendar格里高公历的 时间闭区间（就是包括端点的年月了）

【开始年、月】 ~ 【结束年、月】

在这个时间区间内，有多少个Goog month，有多少个Luckly month



**文章要点**：

- Gregorian Calendar格里高公历 就是现在广泛使用公历（西历），下面简称GC
- GC的起始日期为 1年1月1号，该日为星期六
- GC平年有365天，闰年366天（2月多1天）
- GC有12个月，各月的天数和现在的使用的西历一致
- GC在1582年之前（不包括1582），若该年份能被4整除，则为闰年
- GC在1582年之后（包括1582），判断闰年的标准（满足下面随便一个）：
<br/>　（1）能被4整除，但不能被100整除；
<br/>　（2）能被400整除。
- 由于历史原因，GC规定1700年无条件为闰年
- 由于历史原因，GC规定1752年9月3日 ~ 13日共11天不存在，即1752年9月只有19天
- GC一星期有7天，排序为Sun,Mon,Tue,Wed,Thu,Fri,Sat，和现在的星期一致，其中Mon到Fri为工作日，Sun和Sat为休息日


## 解题思路

直接**模拟**就OK了，水题。


**先做一个判断闰年的函数 leap()**

输入时间区间的  起始年sy月sm 和 终止年ey月em 后，

先计算1年1月到sy年sm-1月（若sm=1，则计算到sy-1年12月）的天数day

注意此时day的天数刚好计算到sm-1月的最后一天

若day+1，则恰好进入所输入的时间区间 【开始年、月】 ~ 【结束年、月】 的第一天

**计算day时要注意**：

- （1）1582年前后闰年判断标准改变了
- （2）1700无条件闰年
- （3）1752年9月少了11天



**判断第day天是星期几**：

由于1年1月1号为星期六，一星期有7天，

因此 `(day+5)%7` 就能计算第day天是星期几。

不能直接 `day%7`，`day%` 就是默认1年1月1号为星期日，至于为什么要先+5，这个不难推导，读者自己想想就明白了


-------


**判断某月是不是Good month和Luckly month**：

计算天数day后，令day++，进入sm的1号

此时判断sm的1号是不是为Good month，使用上面给出计算第day天是星期几的方法，若

1号为星期日（0）、星期六（6）或星期一（1），则该月为Good month

从sm月开始，把天数day逐月递增，逐月判断该月是否为Good month，判断方法都是一样的。

不难发现，若第k月为Good month，则第k-1月必定为Luckly month，因此两个计数器同时增加即可。


------


**注意3点**：

- （1）边界：若sm为Good month，计数器good++，但计数器luck不变，因为sm-1月不在时间区间内。 若计算到em为Good month，则计数器luck++，good不变，因为day一开始就+1了，当day逐月递增到em时，实则day此时为第em+1月的1号，此时判断的是em+1月是否为Good month，若是，则第em月为Luckly month，但em+1月在时间区间内，不计入计数器
- （2）逐月递增时，若到达1752年9月，要 减11天
- （3）闰年平年的月份天数不同



## AC 源码


```c
//Memory Time 
//216K   0MS 

#include<iostream>
using namespace std;

int Month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};   //平年月
int Lmonth[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};  //闰年月
enum week{Sun,Mon,Tue,Wed,Thu,Fri,Sat};  //星期

bool leap(int year);  //判断year是否为闰年
int ComputeDay(int y,int m);  //计算从第1年1月1日到第y年m-1月的总天数+1 (即只包括第m个月的第一天)

int main(int i,int j,int* pm)
{
	int test;
	cin>>test;
	for(int t=0;t<test;t++)
	{
		int ys,ms,ye,me;
		cin>>ys>>ms>>ye>>me;

		int luck=0,good=0;
		int day=ComputeDay(ys,ms);

		if(((day+5)%7<=Mon) || ((day+5)%7==Sat))  //计算起始ys年ms月1号为星期几，判断是否为good month
			good++;                               //1年1月1号是星期六，而原本默认是星期日，因此+5调整

		/*计算从ys年ms+1开始 到ye-1年的月份是否为good month*/

		for(i=ys;i<ye;i++)
		{
			if(leap(i))
				pm=Lmonth;
			else
				pm=Month;

			if(i==ys)
				j=ms;
			else
				j=1;
			for(;j<=12;j++)
			{
				day+=*(pm+j);
				if(i==1752 && j==9)
					day-=11;
                                                          //由于day开始时+1缘故，当j时，计算的是第j+1月是否为good month
				if(((day+5)%7<=Mon) || ((day+5)%7==Sat))  //计算j+1月1号为星期几，判断是否为good month
				{
					good++;
					luck++;  //当j+1月为good month，j月必为luck month
				}
			}
		}

		/*计算第ye年的good month*/

		if(leap(i))
			pm=Lmonth;
		else
			pm=Month;

		if(i==ys)   //若ye==ys
			j=ms;
		else
			j=1;

		for(;j<=me;j++)
		{
			day+=*(pm+j);
			if(i==1752 && j==9)
				day-=11;
                                                      //由于day开始时+1缘故，当j时，计算的是第j+1月是否为good month
			if(((day+5)%7<=Mon) || ((day+5)%7==Sat))  //计算j+1月1号为星期几，判断是否为good month
			{
				if(j!=me)
					good++;

				luck++;  //当j+1月为good month，j月必为luck month
			}
		}
		
		cout<<luck<<' '<<good<<endl;
	}
	return 0;
}

bool leap(int year)  //判断year是否为闰年
{
	if(year<1582)
		return !(year%4);   //当year<1582时，只要能被4整除就是闰年
	else
	{
		if(year==1700) //当year=1700时，历史原因，无条件为闰年
			return true;

		if((!(year%4)&&(year%100)) || !(year%400))   //当year>=1582时，能被4整除且不被100整除为闰年
			return true;                             //或能被400整除时为闰年
	}
	return false;
}

int ComputeDay(int y,int m)  //计算从第1年1月1日到第y年m-1月的总天数+1 (即只包括第m个月的第一天)
{                            //"+1"是为了使从当月末变为下月初
	int i,j,day=1;
	for(i=1;i<y;i++)
		if(leap(i))
			day+=366;
		else
			day+=365;

	for(j=1;j<m;j++)
		if(leap(i))
			day+=Lmonth[j];
		else
			day+=Month[j];

	if(y>1752)
		day-=11;
	else if(y==1752 && m>9)
		day-=11;

	return day;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

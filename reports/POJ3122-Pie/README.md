## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3122] [[Pie](http://poj.org/problem?id=3122)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 二分法]

------

## 问题描述

就是公平地分披萨pie

我生日，买了n个pie，找来f个朋友，那么总人数共f+1人

每个pie都是高为1的圆柱体，输入这n个pie的每一个尺寸（半径），如果要公平地把pie分给每一个人（就是所有人得到的pie尺寸一致，但是形状可以不同），而**且每个人得到的那份pie必须是从同一个pie上得到的**

后面那句很重要，

就是说如果有3个pie，尺寸分别为1，2，3，

如果要给每人尺寸为2的pie，那么最多分给2个人，而不是3个人

因为第一个pie尺寸为1，小于2，扔掉

第二个pie尺寸为2，等于2，刚好分给一个人

第三个pie尺寸为3，切出尺寸为2的一份，分给一个人，剩下的尺寸为1的就扔掉


> 千万不要陷入  `(1+2+3)/2=3` 人的误区，这样就变成求平均了。


## 解题思路

非常水的**二分题**，千万要注意，输入的是朋友的数量f，分pie是分给所有人，包括自己在内共f+1人

下界 `low=0`，即每人都分不到pie

上界 `high=maxsize`，每人都得到整个pie，而且那个pie为所有pie中最大的 (上界就是 n个人n个pie，每个pie还等大)

对当前上下界折中为mid，计算"**如果按照mid的尺寸分pie，能分给多少人**"


**求某个pie（尺寸为size）按照mid的尺寸，能够分给的人数，就直接 `size / mid`，舍弃小数就可以**

由于每个pie都是圆的，为了保证精度和减少运算，我的程序在计算过程中把 π 先忽略，仅仅用半径`R²`去计算，最后的结果再乘π


没难度的二分题，若果WA要多多留意是不是精度问题，因为算法思路是很明确的，精度才是最头疼的



## AC 源码


```c
//Memory Time 
//340K   79MS 

#include<iostream>
#include<iomanip>
using namespace std;

const double pi=3.14159265359; //百度搜pi就有了，我逐位提交，这是最短的pi长度，再短就WA了
                               //懒得测试精度的同学就把尽可能多位数的pi放进程序，肯定不会WA
const double esp=1e-6;     //根据题目要求的精度，为了实数二分法设定的最小精度限制值

int main(void)
{
	int test;
	cin>>test;
	while(test--)
	{
		int n,f;     //n:pie数  f:朋友数
		cin>>n>>f;
		double* v=new double[n+1];    //每个pie的size
		f++;   //加上自己的总人数

		double maxsize=0.0;
		for(int i=1;i<=n;i++)
		{
			cin>>v[i];
			v[i]*=v[i];      //半径平方，计算pie的体积时先不乘pi，为了提高精度和减少时间

			if(maxsize<v[i])
				maxsize=v[i];
		}

		double low=0.0;     //下界，每人都分不到pie
		double high=maxsize;//上界，每人都得到整个pie，而且那个pie为所有pie中最大的
		double mid;

		while(high-low>esp)  //还是那句，实数double的二分结束条件不同于整数int的二分结束条件
		{
			mid=(low+high)/2;  //对当前上下界折中，计算"如果按照mid的尺寸分pie，能分给多少人"

			int count_f=0;  //根据mid尺寸能分给的人数
			for(int i=1;i<=n;i++)  //枚举每个pie
				count_f+=(int)(v[i]/mid);  //第i个pie按照mid的尺寸去切，最多能分的人数（取整）
			                               //就是说如果mid尺寸为1.5，pie总尺寸为2，那么这个pie最多分给一个人
			                               //剩下的0.5要扔掉

			if(count_f < f)       //当用mid尺寸分，可以分的人数小于额定人数
				high=mid;         //说明mid偏大，上界优化
			else
				low=mid;          //否则mid偏小，下界优化（注意'='一定要放在下界优化，否则精度会出错）
		}

		cout<<fixed<<setprecision(4)<<mid*pi<<endl;  //之前的计算都只是利用半径平方去计算，最后的结果要记得乘pi

		delete v;
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

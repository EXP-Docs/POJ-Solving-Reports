## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1905] [[Expanding Rods](http://poj.org/problem?id=1905)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 二分法]

------

## 问题描述

一根两端固定在两面墙上的杆 受热弯曲后变弯曲

求前后两个状态的杆的中点位置的距离


## 解题思路


**几何**和**二分**的混合体

如图：

- 蓝色为杆弯曲前，长度为L
- 红色为杆弯曲后，长度为s
- h是所求

![](/img/01.png)



依题意知 `S=(1+n*C)*L`

又从图中得到三条关系式：

- （1）角度→弧度公式 `θr = 1/2*s`
- （2）三角函数公式  `sinθ= 1/2*L/r`
- （3）勾股定理  `r^2 – (r – h)^2 = (1/2*L)^2`


把四条关系式化简可以得到

![](/img/02.png)


逆向思维解二元方程组：

- 要求（1）式的h，唯有先求r
- 但是由于（2）式是三角函数式，直接求r比较困难

 
因此**要用顺向思维解方程组**：

在h的值的范围内枚举h的值，计算出对应的r，判断这个r得到的(2)式的右边  与 左边的值S的大小关系（ `S = (1+n*C)*L` ）


很显然的**二分查找**了。。。。。

------


那么**问题只剩下 h 的范围是多少了**。

下界自然是0 (不弯曲) ，**关键确定上界**。

题中提及到 `Input data guarantee that no rod expands by more than one half of its original length.`

意即输入的数据要保证没有一条杆能够延伸超过其初始长度的一半，

就是说 `max(S) = 3/2 L`

理论上把上式代入（1）(2)方程组就能求到h的最小上界，但是实际操作很困难

因此这里可以做一个范围扩展，把h的上界扩展到 `1/2L`，不难证明这个值必定大于h的最小上界，那么h的范围就为  `0<=h<1/2L`

这样每次利用下界low和上界high就能得到中间值mid，寻找最优的mid使得(2)式左右两边差值在精度范围之内，那么这个mid就是h。


另外，**精度问题是必须注意的**，由于数据都是double，当low无限接近high时， 若二分查找的条件为 `while(low<high)`，会很容易陷入死循环，或者在得到要求的精度前就输出了不理想的“最优mid”

精度的处理方法参考我的程序。


## AC 源码


```c
//Memory Time 
//244K   0MS 

#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

const double esp=1e-5;   //最低精度限制

int main(void)
{
	double L,n,c,s;   //L:杆长 ，n:温度改变度 ， c:热力系数  ，s:延展后的杆长（弧长）
	double h;    //延展后的杆中心 到 延展前杆中心的距离
	double r;   //s所在圆的半径

	while(cin>>L>>n>>c)
	{
		if(L<0 && n<0 && c<0)
			break;

		double low=0.0;    //下界
		double high=0.5*L; //  0 <= h < 1/2L   (1/2L并不是h的最小上界，这里做一个范围扩展是为了方便处理数据)

		double mid;
		s=(1+n*c)*L;
		while(high-low>esp)  //由于都是double，不能用low<high，否则会陷入死循环 
		{                    //必须限制low与high的精度差
			mid=(low+high)/2;
			r=(4*mid*mid+L*L)/(8*mid);

			if( 2*r*asin(L/(2*r)) < s )     //h偏小
				low=mid;
			else       //h偏大
				high=mid;
		}
		h=mid;

		cout<<fixed<<setprecision(3)<<h<<endl;
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

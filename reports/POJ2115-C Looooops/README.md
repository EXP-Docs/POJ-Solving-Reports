## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2115] [[C Looooops](http://poj.org/problem?id=2115)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 同余模]

------

## 问题描述

对于C的 `for(i=A ; i!=B ;i +=C)` 循环语句，问在k位存储系统中循环几次才会结束。

若在有限次内结束，则输出循环次数。

否则输出死循环。


## 解题思路

题意不难理解，只是利用了 **k位存储系统** 的数据特性进行循环。

例如int型是16位的，那么int能保存 2^16 个数据，即最大数为65535（本题默认为无符号），

当循环使得i超过65535时，则i会返回0重新开始计数

如 `i=65534`，当 `i+=3` 时，`i=1`

其实就是 `i=(65534+3)%(2^16)=1`


有了这些思想，设对于某组数据要循环x次结束，那么本题就很容易得到方程：

`x = [(B-A+2^k)%2^k] / C`

即 `Cx=(B-A)(mod 2^k)`  此方程为 **模线性方程**，本题就是求X的值。


------



下面将结合 《**算法导论**》 第2版进行简述，因此先把上面的方程变形，统一符号。

令：

- `a = C`
- `b = B-A`
- `n = 2^k`

那么原模线性方程变形为：

`ax = b (mod n)`

该方程有解的充要条件为 `gcd(a,n) | b` ，即 `b % gcd(a,n) == 0`

令 `d = gcd(a,n)`

有该方程的 最小整数解为 `x = e (mod n/d)`

其中 `e = [x0 mod(n/d) + n/d] mod (n/d)` ，`x0` 为方程的最小解

那么原题就是要计算 `b % gcd(a,n)` 是否为0，若为0则计算最小整数解，否则输出FOREVER


当有解时，关键在于计算**最大公约数** `d = gcd(a,n)` 与 **最小解** `x0`

参考《算法导论》，引入**欧几里得扩展方程** `d=ax+by` ，

通过EXTENDED_EUCLID算法（P571）求得d、x、y值，其中返回的x就是最小解 `x0`，求d的原理是辗转相除法（**欧几里德算法**）

再利用 `MODULAR-LINEAR-EQUATION-SOLVER` 算法（P564）通过 `x0` 计算x值。

注意 `x0`可能为负，因此要先 `+ n/d` 再 `模 n/d`。

![](/reports/POJ2115-C%20Looooops/img/01.png)


以上方法的推导过程大家自己看《算法导论》。。。这里不证明，只直接使用。


------


**注意**：

- 计算 `n=2^k` 时，用位运算是最快的，`1<<k` （1左移k位）就是 `2^k`
- 但是使用 `long long` 的同学要注意格式， `1LL<<k`
- 使用 `__int64` 的同学要强制类型转换 `(__int64)1<<k`

不然会WA



## 测试数据

- 来源：[CTU Open 2004（问题C）](http://contest.felk.cvut.cz/04prg/solved/index.html)
- 下载：[download](/reports/POJ2115-C%20Looooops/testdata.zip)
- 输入：[input](/reports/POJ2115-C%20Looooops/testdata/input.dat)
- 输出：[output](/reports/POJ2115-C%20Looooops/testdata/output.dat)


## AC 源码


```c
//Memory Time 
//212K   0MS 

#include<iostream>
using namespace std;

//d=ax+by,其中最大公约数d=gcd(a,n)，x、y为方程系数，返回值为d、x、y
__int64 EXTENDED_EUCLID(__int64 a,__int64 b,__int64& x,__int64& y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;  //d=a，x=1,y=0,此时等式d=ax+by成立
	}
	__int64 d=EXTENDED_EUCLID(b,a%b,x,y);
	__int64 xt=x;
	x=y;
	y=xt-a/b*y;  //系数x、y的取值是为满足等式d=ax+by
	return d;
}

int main(void)
{
	__int64 A,B,C,k;
	while(scanf("%I64d %I64d %I64d %I64d",&A,&B,&C,&k))
	{
		if(!A && !B && !C && !k)
			break;

		__int64 a=C;
		__int64 b=B-A;
		__int64 n=(__int64)1<<k;  //2^k
		__int64 x,y;
		__int64 d=EXTENDED_EUCLID(a,n,x,y);  //求a,n的最大公约数d=gcd(a,n)和方程d=ax+by的系数x、y

		if(b%d!=0)  //方程 ax=b(mod n) 无解
			cout<<"FOREVER"<<endl;
		else
		{
			x=(x*(b/d))%n;  //方程ax=b(mod n)的最小解
			x=(x%(n/d)+n/d)%(n/d);  //方程ax=b(mod n)的最整数小解
			printf("%I64d\n",x);
		}
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

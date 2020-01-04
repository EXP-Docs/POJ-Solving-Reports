## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1845] [[Sumdiv](http://poj.org/problem?id=1845)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 同余模]

------

## 问题描述

求A^B的所有约数（即因子）之和，并对其取模 9901再输出。


## 解题思路

要求有较强 数学思维 的题。

应用定理主要有三个：

- （1）**整数的唯一分解定理**：
<br/>　　任意正整数都有且只有一种方式写出其素因子的乘积表达式。
<br/>　　`A=(p1^k1)*(p2^k2)*(p3^k3)*....*(pn^kn)`   其中pi均为素数
- （2）**约数和公式**：
<br/>　　对于已经分解的整数 `A=(p1^k1)*(p2^k2)*(p3^k3)*....*(pn^kn)`
<br/>　　有A的所有因子之和为 `S = (1+p1+p1^2+p1^3+...p1^k1) * (1+p2+p2^2+p2^3+….p2^k2) * (1+p3+ p3^3+…+ p3^k3) * .... * (1+pn+pn^2+pn^3+...pn^kn)`
- （3）**同余模公式**：
<br/>　　`(a+b)%m=(a%m+b%m)%m`
<br/>　　`(a*b)%m=(a%m*b%m)%m`

------

有了上面的数学基础，那么本题解法就很简单了：

**1: 对A进行素因子分解**

分解A的方法：

- A首先对第一个素数2不断取模，
- 当 `A%2==0` 时 ，记录2出现的次数 `+1`，`A/=2`；
- 当 `A%2!=0` 时，则A对下一个连续素数3不断取模...
- 以此类推，直到 `A==1` 为止。

注意特殊判定，当A本身就是素数时，无法分解，它自己就是其本身的素数分解式。

最后得到 `A = p1^k1 * p2^k2 * p3^k3 *...* pn^kn`

故 `A^B = p1^(k1*B) * p2^(k2*B) *...* pn^(kn*B)`;

------

**2：A^B的所有约数之和为**

`sum = [1+p1+p1^2+...+p1^(a1*B)] * [1+p2+p2^2+...+p2^(a2*B)] *...* [1+pn+pn^2+...+pn^(an*B)]`

------

**3: 用递归二分求等比数列1+pi+pi^2+pi^3+...+pi^n**

（1）若n为奇数,一共有偶数项，则：

```
　1 + p + p^2 + p^3 +...+ p^n
= (1+p^(n/2+1)) + p * (1+p^(n/2+1)) +...+ p^(n/2) * (1+p^(n/2+1))
= (1 + p + p^2 +...+ p^(n/2)) * (1 + p^(n/2+1))
```

上式红色加粗的前半部分恰好就是原式的一半，那么只需要不断递归二分求和就可以了，后半部分为幂次式，将在下面第4点讲述计算方法。

（2）若n为偶数,一共有奇数项,则:

```
　1 + p + p^2 + p^3 +...+ p^n
= (1+p^(n/2+1)) + p * (1+p^(n/2+1)) +...+ p^(n/2-1) * (1+p^(n/2+1)) + p^(n/2)
= (1 + p + p^2 +...+ p^(n/2-1)) * (1+p^(n/2+1)) + p^(n/2);
```

上式红色加粗的前半部分恰好就是原式的一半，依然递归求解

------

**4：反复平方法计算幂次式p^n**

这是本题关键所在，求n次幂方法的好坏，决定了本题是否TLE。

以 `p=2`， `n=8` 为例

常规是通过连乘法求幂，即 `2^8=2*2*2*2*2*2*2*2`

这样做的要做8次乘法

而反复平方法则不同，

定义幂sq=1，再检查n是否大于0，

```
While，循环过程若发现n为奇数，则把此时的p值乘到sq
{
　n=8>0 ，把p自乘一次， p=p*p=4     ，n取半 n=4
　n=4>0 ，再把p自乘一次， p=p*p=16   ，n取半 n=2
　n=2>0 ，再把p自乘一次， p=p*p=256  ，n取半 n=1，sq=sq*p
　n=1>0 ，再把p自乘一次， p=p*p=256^2  ，n取半 n=0，弹出循环
}
```

则 `sq=256` 就是所求，显然反复平方法只做了3次乘法


## AC 源码


```c
//Memory Time 
//336K   0MS 

#include<iostream>
using namespace std;

const int size=10000;
const int mod=9901;

__int64 sum(__int64 p,__int64 n);  //递归二分求 (1 + p + p^2 + p^3 +...+ p^n)%mod
__int64 power(__int64 p,__int64 n);  //反复平方法求 (p^n)%mod

int main(void)
{
	int A,B;
	int p[size];//A的分解式,p[i]^n[i]
	int n[size];

	while(cin>>A>>B)
	{
		int i,k=0;  //p,n指针

		/*常规做法：分解整数A (A为非质数)*/
		for(i=2;i*i<=A;)   //根号法+递归法
		{
			if(A%i==0)
			{
				p[k]=i;
				n[k]=0;
				while(!(A%i))
				{
					n[k]++;
					A/=i;
				}
				k++;
			}
			if(i==2)  //奇偶法
				i++;
			else
				i+=2;
		}
		/*特殊判定：分解整数A (A为质数)*/
		if(A!=1)
		{
			p[k]=A;
			n[k++]=1;
		}

		int ans=1;  //约数和
		for(i=0;i<k;i++)
			ans=(ans*(sum(p[i],n[i]*B)%mod))%mod;  //n[i]*B可能会超过int，因此用__int64

		cout<<ans<<endl;
	}
	return 0;
}

__int64 sum(__int64 p,__int64 n)  //递归二分求 (1 + p + p^2 + p^3 +...+ p^n)%mod
{                          //奇数二分式 (1 + p + p^2 +...+ p^(n/2)) * (1 + p^(n/2+1))
	if(n==0)               //偶数二分式 (1 + p + p^2 +...+ p^(n/2-1)) * (1+p^(n/2+1)) + p^(n/2)
		return 1;
	if(n%2)  //n为奇数,
		return (sum(p,n/2)*(1+power(p,n/2+1)))%mod;
	else     //n为偶数
		return (sum(p,n/2-1)*(1+power(p,n/2+1))+power(p,n/2))%mod;
}

__int64 power(__int64 p,__int64 n)  //反复平方法求(p^n)%mod
{
	__int64 sq=1;
	while(n>0)
	{
        if(n%2)
            sq=(sq*p)%mod;
        n/=2;
        p=p*p%mod;
    }
	return sq;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

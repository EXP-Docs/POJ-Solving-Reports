## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2388] [[Who's in the Middle](http://poj.org/problem?id=2388)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 排序]

------

## 问题描述

给定n个数，输出中间值（注意不是求平均）。


## 解题思路

可以用 `sort`，干脆快捷，但是注意排序起止位置。

也可以用 `quicksort`，(最好用**随机快排**，尝试一下 `srand` 和 `rand`) 。

没什么要注意的水题，不过真要注意的话，就不要用冒泡、插入、选择排序之类的O(n^2)算法，1W个数铁定超时。


## 测试数据

- 输入：[input](/reports/POJ1016-Numbers%20That%20Count/testdata/input.dat)
- 输出：[output](/reports/POJ1016-Numbers%20That%20Count/testdata/output.dat)


## AC 源码


```c
//Memory  Time
//292K    47MS  

#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;

int main(void)
{
	int n;
	while(cin>>n)
	{
		int* milk=new int[n+1];

		for(int i=1;i<=n;i++)
			cin>>milk[i];

		sort(milk+1,milk+n+1);

		cout<<milk[n/2+1]<<endl;

		delete milk;
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

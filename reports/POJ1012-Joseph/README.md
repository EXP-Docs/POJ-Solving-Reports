## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1012] [[Joseph](http://poj.org/problem?id=1012)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 递推关系]

------

## 问题描述

有k个坏人k个好人坐成一圈，前k个为好人（编号 `1~k`），后k个为坏人(编号 `k+1~2k`)

现在有一个报数m，从编号为1的人开始报数，报到m的人就要自动死去。

问当m为什么值时，可以使得在出现好人死亡之前，k个坏人先全部死掉？

 
注意：

- 当前一轮第m个人死去后，下一轮的编号为1的人 为 前一轮编号为 m+1 的人
- 前一轮恰好是最后一个人死掉，则下一轮循环回到开头那个人报 “1”


## 解题思路

经典的**约瑟夫**水题


由于k值比较少（`1~13`），暴力枚举m就可以了

**递推公式**为：

```
ans[i];  //第i轮杀掉 对应当前轮的编号为ans[i]的人
ans[0]=0;
ans[i]=(ans[i-1]+m-1)%(n-i+1);  // i>1,  总人数n=2k 则n-i为第i轮剩余的人数
```


有耐心的同学可以自己推导一下公式，**推导时要注意2点**:

**第一**：每轮都是以前一轮死掉的人的后一个人作为“1”开始顺序编号的

如： `k=2  (n=4)  m=7`

```
1
4
3
2
```

那么最初的编号如下

![](/img/01.png)


第一轮报数后，3号被杀掉，那么以3号后面的一个人“4”作为下一轮的“1”重新编号

![](/img/02.png)


**第二**： `f[i]=(f[i-1]+m)%(n-i);   (i>1)`

这是网上一些地方给出的递推公式，**对于本题而言是不正确**的。因为**这种递推公式针对的是从0开始报数的Joseph，本题是从1开始报数的，必须要变形**


------


最后就是由于本题k值有限，只有13个值，那么POJ的数据测试就极有可能重复测试每个k值的结果，为了节省总体时间，我们的程序只在第一次得到k值的时候计算m值，然后保存下来，当k值再次出现时，就直接把保存的结果输出，不再计算m。这是在服务器打表的处理。



另外有了递推的程序后，我们就知道了每个k值对应的m值。

此时追求0ms AC的同学可以利用递推程序的结果，再写一个程序，直接在程序里面打表

`int Joseph[]={0,2,7,5,30,169,441,1872,7632,1740,93313,459901,1358657,2504881,1245064};`


## AC 源码


```c
//Memory Time
//184K   250MS 

#include<iostream>
using namespace std;

int main(void)
{
	int Joseph[14]={0};  //打表，保存各个k值对应的m值

	int k;
	while(cin>>k)
	{
		if(!k)
			break;

		if(Joseph[k])
		{
			cout<<Joseph[k]<<endl;
			continue;
		}

		int n=2*k;  //总人数
		int ans[30]={0};  //第i轮杀掉 对应当前轮的编号为ans[i]的人
		                  //PS:每一轮都以报数为“1”的人开始重新编号

		int m=1;    //所求的最少的报数
		for(int i=1;i<=k;i++)  //轮数
		{
			ans[i]=(ans[i-1]+m-1)%(n-i+1);   //n-i为剩余的人数
			if(ans[i]<k)  //把好人杀掉了,m值不是所求
			{
				i=0;
				m++;  //枚举m值
			}
		}
		Joseph[k]=m;
		cout<<m<<endl;
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

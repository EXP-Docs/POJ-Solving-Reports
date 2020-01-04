## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1013] [[Counterfeit Dollar](http://poj.org/problem?id=1013)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 逻辑推理]

------

## 问题描述

有一打（12枚）硬币，其中有且仅有1枚假币，11枚真币

用 `A~L` 作为各个硬币的代号

假币可能比真币略轻，也可能略重

现在利用天枰，根据Input输入的3次称量，找出假币，并输出假币是轻还是重。


## 解题思路

模拟法要考虑的情况较繁琐，可利用简单的**逻辑推理**进行解题。

注意Input一行代表一次称量，每行有三个字符串，分别为

Left   right     status

代表该次称量时，天枰左盘放的硬币、天枰右盘放的硬币、天枰右盘的状态


**共三种状态**：

- Up：右盘上升，说明右盘可能有轻假币，也可能左盘有重假币。
- Down：右盘下降，说明右盘可能有重假币，也可能左盘有轻假币。
- Even：右盘与左盘平衡，由于假币有且仅有1枚，则说明此时天枰两边的硬币全为真币。


**注意题目的字眼**：

- 1、有且仅有1枚假币
- 2、假币相对于真币的重量，可能轻可能重
- 3、只称量3次，且称量3次恰好且必能找到假币
- 4、每次称量时天枰两边的硬币数目一样
- 5、选取哪些硬币称量由input决定


从3、4、5可知，由于无法知道每次选取称量的硬币，那么3次称量可能只选用了几个硬币，也可能仅有一两个硬币没有选上，那么用模拟法去记录每次用于称量的硬币的状态（真假，其中假币又有轻重之分）并推导没有被称量的硬币状态（或状态变化）是很困难的，虽然人很容易做到这点，但计算机却很难去“推导”，因为称量硬币的方法是无规律的且非常多。

那么只能通过适当转化问题后用另一种有效的方法去解决。


虽然称量硬币的方法是无规律且未知的，但是称量硬币后的结果却只有3个，up、down和 even。且当出现even时，天枰两边的硬币必然都为真币，假币必定在余下的硬币之间（这是因为假币有且只有一枚），那么我们就可以定义一个标记数组 `zero[]` 去标记even时的真币，在以后的处理把他们排除在外。

而唯一难以处理的是up和down的状态，因为假币可能轻可能重，则这两种状态都无法得知究竟假币出现在天枰的哪边。



**处理up和down状态方法**：

当出现up或down状态时，天枰两边的所有硬币都应该被怀疑为假币（已标记必定为真币的硬币不必被怀疑）。

首先 `time[]` 记录每个硬币的被怀疑程度：

- `time[i]=0` 表示该硬币i不被怀疑（即其可能为真币）
- 定义在up状态盘的硬币为“轻怀疑假币”，通过 `--` 操作加深其被怀疑为轻假币的程度，“负号”为轻假币的怀疑方向
- 定义在down状态盘的硬币为“重怀疑假币”，通过 `++` 操作加深其被怀疑为重假币的程度，“正号”为重假币的怀疑方向。

那么若一枚真币被怀疑为“轻假币”时，它就可能通过下次称量通过“++”操作取消嫌疑了。

初始化所有硬币的怀疑程度均为0。

称量完毕后，找出被怀疑程度最大（注意取绝对值）的硬币，它就是假币。

而当其怀疑方向为正时，则其为重假币。为负时，为轻假币。


## AC 源码


```c
//Memory Time 
//252K   0MS 

#include<iostream>
#include<cmath>
using namespace std;

int main(void)
{
	int cases;
	cin>>cases;
	for(int c=1;c<=cases;c++)
	{
		char left[3][6],right[3][6],status[3][6];

		int time['L'+1]={0};  //标记各个字母被怀疑的次数
		bool zero['L'+1]={false};  //标记绝对为真币的字母（令天枰平衡的所有字母）

		for(int k=0;k<3;k++)
			cin>>left[k]>>right[k]>>status[k];	

		for(int i=0;i<3;i++)
		{
			switch(status[i][0])  //检查天枰状态
			{
			    case 'u':     //up，天枰左重右轻
					{
						for(int j=0;left[i][j];j++)
						{
							time[ left[i][j] ]++;  //左重
							time[ right[i][j] ]--;  //右轻
						}
						break;
					}
				case 'd':     //down，天枰左轻右重
					{
						for(int j=0;left[i][j];j++)
						{
							time[ left[i][j] ]--;  //左轻
							time[ right[i][j] ]++;  //右重
						}
						break;
					}
				case 'e':     //down，天枰平衡
					{
						for(int j=0;left[i][j];j++)
						{
							zero[ left[i][j] ]=true;   //绝对真币
							zero[ right[i][j] ]=true;   //绝对真币
						}
						break;
					}
			}
		}

		int max=-1;  //查找被怀疑程度最高的硬币（假币）
		char alpha;
		for(int j='A';j<='L';j++)
		{
			if(zero[j])  //绝对真币
				continue;

			if(max<=abs(time[j]))
			{
				max=abs(time[j]);
				alpha=j;
			}
		}

		cout<<alpha<<" is the counterfeit coin and it is ";
		if(time[alpha]>0)
			cout<<"heavy."<<endl;
		else
			cout<<"light."<<endl;
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

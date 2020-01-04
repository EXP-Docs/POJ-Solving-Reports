## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3096] [[Surprising Strings](http://poj.org/problem?id=3096)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 基础算法]

------

## 问题描述

定义D-pairs表示取字符串s中相距为D的两个字母所构成的字母对，该字母对中两个字母的位置顺序与他们在主串s中的位置顺序一致

定义D-unique表示，若从字符串s中取出所有相距为D的字母对D-pairs，且这些D-pairs都是独一无二的，那么成字符串s是一个D-unique串

D的取值范围为 `0 ~ s.len()-2`

假如字符串s对于所有的D都有D-unique成立，则字符串s是令人惊讶的

 

现在输入一些字符串，问他们能不能令人惊讶


## 解题思路

令人惊讶的中级水题= =

用**STL的map标记D-unique是否重复出现就OK**了


**也可以用ASCII标记**，取两个大写字母的ASCII构成一个四位数作为key就可以了，**比map快一点点**



**层次关系**：

- 对于某个D，当所有D-pairs都不同时，s是D-unique
- 对于所有D，s都有D-unique时，它是surprising string

 

**注意**：

- 长度小于等于2的s都是surprising string
- 其实我感觉这题暴力也能AC= =，S最大长度也就79...


## AC 源码


## 解题方法一：`STL<map>`标记

```c
/*STL<map>标记*/

//Memory Time 
//212K   16MS 

#include<iostream>
#include<string>
#include<map>
using namespace std;

int main(void)
{
	char s[80];
	while(cin>>s && s[0]!='*')
	{
		int len=strlen(s);
		if(len<=2)  //长度小于等于2的串必定是surprising String
		{
			cout<<s<<" is surprising."<<endl;
			continue;
		}

		bool mark=true;  //标记s是否为Surprising String
		for(int d=0;d<=len-2;d++)  //d为当前所选取的两个字母之间的距离，d(max)=len-2
		{
			map<string,bool>flag;

			bool sign=true;  //标记D-pairs字母对是不是D-unique
			for(int i=0;i<=len-d-2;i++)  //i为所选取的两个字母中第一个字母的下标
			{
				char pair[3]={s[i],s[i+d+1],'\0'};  //构成D-pairs字母对
				
				if(!flag[ pair ])
					flag[ pair ]=true;
				else
				{
					sign=false;  //存在相同的D-pairs,该字母对不是D-unique
					break;
				}
			}
			if(!sign)
			{
				mark=false;  //存在非D-unique，s不是Surprising String
				break;
			}
		}
		if(mark)
			cout<<s<<" is surprising."<<endl;
		else
			cout<<s<<" is NOT surprising."<<endl;
	}
	return 0;
}
```


## 解题方法二：ASCII标记

```c
/*ASCII标记*/

//Memory Time 
//212K   0MS 

#include<iostream>
#include<string>
using namespace std;

int main(void)
{
	char s[80];
	while(cin>>s && s[0]!='*')
	{
		int len=strlen(s);
		if(len<=2)  //长度小于等于2的串必定是surprising String
		{
			cout<<s<<" is surprising."<<endl;
			continue;
		}
		bool mark=true;  //标记s是否为Surprising String
		for(int d=0;d<=len-2;d++)  //d为当前所选取的两个字母之间的距离，d(max)=len-2
		{
			bool flag['Z'*100+'Z'+1];   //标记D-pairs字母对
			memset(flag,false,sizeof(flag));

			bool sign=true;  //标记D-pairs字母对是不是D-unique
			for(int i=0;i<=len-d-2;i++)  //i为所选取的两个字母中第一个字母的下标
			{
				int pair=s[i]*100+s[i+d+1];  //D-pairs字母对的ASCII码所构成的四位数

				if(!flag[pair])
					flag[pair]=true;
				else
				{
					sign=false;  //存在相同的D-pairs,该字母对不是D-unique
					break;
				}
			}
			if(!sign)
			{
				mark=false;  //存在非D-unique，s不是Surprising String
				break;
			}
		}
		if(mark)
			cout<<s<<" is surprising."<<endl;
		else
			cout<<s<<" is NOT surprising."<<endl;
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

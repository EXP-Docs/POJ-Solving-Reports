## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2503] [[Babelfish](http://poj.org/problem?id=2503)]

> [Time: 3000MS] [Memory: 65536K] [难度: 初级] [分类: 高效查找法]

------

## 问题描述

输入一个字典，字典格式为“英语 -> 外语”的一一映射关系

然后输入若干个外语单词，输出他们的 英语翻译单词，如果字典中不存在这个单词，则输出“eh”


## 解题思路

水题，输入时顺便用STL的map标记外语是否出现过，然后再用map建立“外语 -> 英语”的映射，那么输出时先查找“出现”的标记，若有出现过，再输出映射，否则输出“eh”。

用STL毫无难度（要真说难，也就是空行的处理有一点技巧），也可以用**hash**做，不过比较麻烦


## AC 源码


```c
//Memory  Time
//17344K 1563MS 

#include<iostream>
#include<string>
#include<map>
using namespace std;

int main(void)
{
	char english[11],foreign[11];

	map<string,bool>appear;  //记录foreign与engliash的配对映射是否出现
	map<string,string>translate; //记录foreign到engliash的映射

	/*Input the dictionary*/

	while(true)
	{
		char t;  //temporary

		if((t=getchar())=='\n')  //判定是否输入了空行
			break;
		else     //输入english
		{
			english[0]=t;
			int i=1;
			while(true)
			{
				t=getchar();
				if(t==' ')
				{
					english[i]='\0';
					break;
				}
				else
					english[i++]=t;
			}
		}
		
		cin>>foreign;
		getchar();  //吃掉 输入foreign后的 回车符

		appear[foreign]=true;
		translate[foreign]=english;
	}

	/*Translate*/

	char word[11];
	while(cin>>word)
	{
		if(appear[word])
			cout<<translate[word]<<endl;
		else
			cout<<"eh"<<endl;
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

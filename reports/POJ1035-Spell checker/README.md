## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1035] [[Spell checker](http://poj.org/problem?id=1035)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: 串]

------

## 问题描述

输入一部字典，输入若干单词

- 若某个单词能在字典中找到，则输出corret
- 若某个单词能通过 **变换** 或 **删除** 或 **添加**一个字符后，在字典中找得到，则输出这些单词，输出顺序根据  输入的那部字典的字典序
- 若某个单词无论操作与否都无法在字典中找得到，则输出空


## 解题思路

没难度的字符串处理。 暴力吧！**模拟**吧！

基本思路就是逐个比较 待查单词 与 字典单词 的长度，当且仅当两者长度之差的绝对值 `<=1` 时才进行检查操作。

## 测试数据

- 来源：[Northern Eurasia Contests（NEERC 1998 - 问题G）](http://neerc.ifmo.ru/past/1998.html)
- 下载：[download](/reports/POJ1035-Spell%20checker/testdata.zip)

## AC 源码


```c
//Memory Time 
//456K  157MS 

#include<iostream>
#include<string.h>
using namespace std;

char dict[10001][16];
char word[51][16];

int DictNum=0; //字典计数器
int WordNum=0; //单词计数器

void Input(void);
bool Change(char* word,char* dict);  //检查字符串word能否通过变换得到dict
bool Del(char* word,char* dict);  //检查字符串word能否通过删除得到dict
bool Add(char* word,char* dict);  //检查字符串word能否通过添加得到dict

int main(void)
{
	Input();

	int* DictLen=new int[DictNum];  //记计算字典中各个单词的长度
	for(int n=0;n<DictNum;n++)
		DictLen[n]=strlen(dict[n]);

	for(int i=0;i<WordNum;i++)
	{
		int* address=new int[DictNum];  //记录word[i]通过变化得到的单词在dict中的下标
		int pa=0; //address指针

		bool flag=false;  //标记字典中是否含有单词word[i]
		int len=strlen(word[i]);

		for(int k=0;k<DictNum;k++)  //遍历字典
		{
			if(DictLen[k]==len)  //Change or Equal
			{
				if(!strcmp(word[i],dict[k]))
				{
					flag=true;
					break;
				}
				else if(Change(word[i],dict[k]))
					address[pa++]=k;
			}
			else if(len-DictLen[k]==1)  //Delete
			{
				if(Del(word[i],dict[k]))
					address[pa++]=k;
			}
			else if(DictLen[k]-len==1)  //Add
			{
				if(Add(word[i],dict[k]))
					address[pa++]=k;
			}
		}

		/*Output*/

		if(flag)
			cout<<word[i]<<" is correct"<<endl;
		else
		{
			cout<<word[i]<<": ";
			for(int j=0;j<pa;j++)
				cout<<dict[ address[j] ]<<' ';
			cout<<endl;
		}

		delete address;
	}
	return 0;
}

void Input(void)
{
	while(cin>>dict[DictNum] && dict[DictNum++][0]!='#');
	while(cin>>word[WordNum] && word[WordNum++][0]!='#');

	DictNum--;  //剔除'#'
	WordNum--;
	return;
}

bool Change(char* word,char* dict)  //WordLen==DictLen
{
	int dif=0;  //记录word与dict中在相同位置出现不同字符的个数
	
	while(*word)
	{
		if(*(word++) != *(dict++))
		{
			dif++;
			if(dif>1)
				return false;
		}
	}
	return true;
}

bool Del(char* word,char* dict)  //WordLen==DictLen+1
{
	int dif=0;  //记录word与dict中在对应位置出现不同字符的个数

	while(*word)
	{
		if(*word != *dict)
		{
			word++;  //word后移一位再匹配
			dif++;
			if(dif>1)
				return false;
		}
		else
		{
			word++;
			dict++;
		}
	}
	return true;
}

bool Add(char* word,char* dict)  //WordLen==DictLen-1
{	
	int dif=0;  //记录word与dict中在对应位置出现不同字符的个数

	while(*dict)
	{
		if(*word != *dict)
		{
			dict++;  //dict后移一位再匹配
			dif++;
			if(dif>1)
				return false;
		}
		else
		{
			word++;
			dict++;
		}
	}
	return true;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3371] [[Flesch Reading Ease](http://poj.org/problem?id=3371)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 模拟法]

------

## 问题描述

给出一篇规范的文章，求其 句子数、单词数 和 音节数

把这3个值代入题目给出的公式，输出其结果，保留2位小数。

> “规范”即文章没有错误的标点符号，字母在适当的位置有大小写。


## 解题思路

**模拟法**做，我做了整整5天的BT题,，就是被标点符号害的！！！

别听信网上谗言，我个人总结出**这题的标点符号只有6个**！！！

> **注**：下面的分隔符不包括 括号（），所有分隔符均为 英式标点符号

- **标记单词分隔符： 逗号（,） 和 空格（ ）**
- **句子分隔符：句号（.） 问号（?） 冒号（:） 分号（;） 感叹号（!）**

不存在上述标点符号以外的符号！！！所有符号只占一个字符的位置！！

什么 省略号、引号、连字符、问号+叹号、斜杠 等等符号统统不存在！！


知道这个，后面的就好做了：

- **每出现一个单词分隔符，单词数+1**
- **每出现一个句子分隔符，句子数+1**


> **注意**： 由于用 `while(cin>>msg)` 输入文章，因此是按 空字符 把文章分开若干片段，直到出现EOF时才结束输入，因此msg中的单词分隔符不会出现空格，只要当msg最后一个字符为字母时，就说明此时的单词分隔符为空格。



**音节数是最难处理的，其规律如下**：

- （1）当单词总长度 `<=3` 时，音节数无条件+1
- （2）当单词总长度 `>3` 时，单词中每出现一个元音字母（a、e、i、o、u、y），音节数+1，但是连续的元音字母只按1个音节计算，且当单词后缀为-es、-ed和-e时，后缀的元音字母e不列为音节数计算。但是后缀-le例外，要计算音节数。

 
**注意**：

- (1) 元音字母要判断12个，6个小写，6个大写。
- (2) 输入的文章每个字符只能扫描一次，若重复扫描会超时。


## AC 源码


```c
//Memory Time 
//244K   0MS 

#include<iostream>
#include<iomanip>
using namespace std;

int word=0;     //单词数
int sentance=0; //句子数
int syllable=0; //音标数

bool isalpha(char ch)  //检查字符ch是否为字母
{
	if(ch>='A' && ch <='Z')
		return true;
	if(ch>='a' && ch <='z')
		return true;
	return false;
}

bool isvowel(char ch)  //检查字符ch是否为元音字母
{
	if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='y')
		return true;
	if(ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U' || ch=='Y')
		return true;
	return false;
}

bool isword(char ch)  //检查字符ch是否为单词分隔符
{
	if(ch==',')
		return true;
	return false;
}

bool issentance(char ch)  //检查字符ch是否为句子分隔符
{
	if(ch=='.' || ch=='?'  || ch==':' || ch==';' || ch=='!')
		return true;
	return false;
}

int main(void)
{
	char msg[1000];

	while(cin>>msg)   //以空格为标记，截取文章片段
	{	
		int wordlen=0;
		bool flag_frevowel=false;   //当当前字符为元音时，检查前一字符是否为元音的标记
		int syl=0;  //假设当前单词长度>3时，记录音节数的变化量。若单词实际长度<=3，则syllable-syl
		int i;

		for(i=0;msg[i];i++)
		{
			if(isalpha(msg[i]))   //当前字符为 字母
			{
				wordlen++;  //当前所处理的单词的已知长度 (已知长度<=实际长度)

				if(wordlen<=3)  //当 已知长度<=3 时
				{
					if(!isalpha(msg[i+1]))   //检查单词实际长度是否<=3
					{
						syllable++;     //当实际长度<=3时，syllable无条件+1
						syllable-=syl;   //实际音节数调整，单词实际长度<=3，则syllable减去 "假设单词长度>3时" 音节数的变化量syl
						syl=0;
						continue;
					}
				}

				if(isvowel(msg[i]))    //当前字母为 元音字母
				{
					if(msg[i]=='e')
					{
						if(!isalpha(msg[i+1]) && msg[i-1]=='l')  //-le
						{
							syllable++;
							syl++;      //由于不知道单词的实际长度，因此总音节数syllable与音节数变化量syl同时递增
							continue;
						}
						else if(!isalpha(msg[i+1]))  // -e
							continue;
						else if((msg[i+1]=='d' || msg[i+1]=='s') && !isalpha(msg[i+2]))  // -ed  -es
							continue;
					}

					/*处理连续或单个元音*/

					if(!flag_frevowel)   //当前字母为元音，但前一字符不是元音
					{
						flag_frevowel=true;
						syllable++;
						syl++;
						continue;
					}
					else     //当前字母为元音，但前一字母也是元音，即出现连续元音，syllable不计数
						continue;
				}

				flag_frevowel=false;   //当前字母不是元音
			}
			else if(isword(msg[i]))   //当前字符为 单词分隔符
			{
				flag_frevowel=false;
				wordlen=0;  //当前单词操作已结束，长度清零，计算下一单词
				syl=0;
				word++;
			}
			else if(issentance(msg[i]))   //当前字符为 句子分隔符
			{
				flag_frevowel=false;
				wordlen=0;  //当前单词操作已结束，长度清零，计算下一单词
				word++;
				syl=0;
				sentance++;
			}

		}

		if(isalpha(msg[i-1]))     //当前文章片段最后一个字符为 字母
			word++;
	}

	cout<<fixed<<setprecision(2)<<206.835-1.015*(double)word/(double)sentance-84.6*(double)syllable/(double)word<<endl;
	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

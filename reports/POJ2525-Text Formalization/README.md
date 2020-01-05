## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2525] [[Text Formalization](http://poj.org/problem?id=2525)]

> [Time: 1000MS] [Memory: 65536K] [难度: 高级] [分类: 基础算法]

------

## 问题描述

首先说明，下面所述的“大致题意”并不是题目的原意，但是按照题目原意去做是不可能AC的，因为测试数据库与题目原意出入非常大。另外顺便建议，刚玩POJ的同学没事不要做这题，因为如果没有测试数据库你会疯掉的，有测试数据库也很容易疯掉的。


------

有两种类型的字符串，分别为Contraction和Acronym，它们都有其扩展形式Expand。现在给出C个Contraction和A个Acronym的扩展形式，格式如下：

"contraction or acronym" -> "expansion"

其中红色部分，引号和箭号之间可能有空格，可能无空格。


然后再给出数篇Text，每篇Text用一个独占一行的#分隔（注意若有数个#连续出现，则不是分隔符），而且每篇Text都包含有数行，每行的长度最多为80。

要求把每篇Text出现Contraction和Acronym的位置都分别用其扩展式替换，然后重新输出扩展后的Text。

**关于扩展式的分析：**

------

**1、  Contraction**

Contraction在Text中有3种表现形式，按照优先级分别为

- "as listed,"（原型） 
- "uppercased,"（尽数大写）
- "capitalized."（首字母大写）

举例说明： 

给定Contraction为isn’t，其扩展式为is not ，那么在检测Text时，

- 若检测到isn’t，则替换为is not
- 若检测到ISN’T，则替换为IS NOT
- 若检测到Isn’t，则替换为Is not

若检测到诸如IsN’t的其他串，由于不属于以上3种情况的任意一种，则不替换，直接输出原串。

**注意**：

- 3种形式必须根据优先级检测，即若有"as listed,"，则不能替换为"uppercased,"或"capitalized." ；若有"uppercased,"则不能替换为"capitalized."。
- 扩展式与Contraction的表现形式必须一致。

------

**2、Acronym**

Acronym在Text中只有一种表现形式，就是"as listed,"，但替换时有2个特殊要求：

- 对于同一篇Text，Acronym只能被替换1次，且替换的位置为其第一次出现的位置，其他位置不替换。
- 替换Acronym的时候，必须在其替换式的最后加上“空格（Acronym原型）”。

例如：给定Acronym为CS，其扩展式为Computing Science，那么应该把Text中的CS替换为 `Computing Science （CS）`

------

**3、非字母串的Contraction与Acronym**

前2点都是在Contraction与Acronym都是由字母组成的基础上的替换模式。

当Contraction或Acronym由非字母的字符串构成时，其扩展式只有"as listed,"一种形式，而Acronym替换后依然要加上“空格（Acronym原型）”。

例如：

- 给定的Contraction为 `<!=>` ，其扩展式为a-c+d，那么在Text检测到 `<!=>` 就直接替换为a-c+d，无大小写之分。
- 给定Acronym为 `&&&`，其扩展式为 `**rr!!$`，那么在Text检测到 `&&&` 就直接替换为 `**rr!!$ （&&&）`

------

**4、Contraction与Acronym可以是任意字符串的前缀或后缀，依然要替换**

**5、不能迭代替换，就是说只能针对原本属于Text的字符串替换，不能对扩展后的Expand串替换**



## 解题思路

其实如果原题题意和测试数据库的测试项是一致的话，这题是很简单的**模拟题**，**字符串替换**而已，不应该放到“高级题”里面。


原题题意故意误导的错误信息有3点：（**注意下面是错误信息**）

- 1、 Contraction与Acronym不是任何单词的前缀或后缀
- 2、 Text是规范的字母串+标点
- 3、"contraction or acronym" -> "expansion" 红色部分两引号间固定有2个空格



而从测试数据库真正反应出来的信息是：（**注意下面是正确信息**）

- 1、Contraction与Acronym可以是任何字符（串）的前缀或后缀
- 2、Text纯粹是一些字符串的组合
- 3、"contraction or acronym" -> "expansion"红色部分两个引号之间的空格数目不固定


明白到上面所述，本题的处理就很简单了。由于要匹配的字符串很多，因此本题用**TrieTree**的效率是最高的， **hash**很可能会超时。

- 1、 把Contraction与Acronym录入到TrieTree，这里的**TrieTree要做一个简单的变形**，就是原本在结点中用于标记单词的布尔量flag，改为整型id，id=0表示从TrieTree到当前结点的字符串不是Contraction或Acronym； id>0表示TrieTree到当前结点的字符串是Contraction或Acronym，并且id就是其扩展式的映射。
- 2、 建立扩展串二维数组，行为id，对应的行就是Contraction或Acronym的扩展式。
- 3、 下面称上述2步为“字典录入”，字典录入的时候，在录入Contraction时，顺便同时录入其3种形式，而且必须按照优先顺序录入id。而这样录入可能会导致后面录入时出现重复，为了保证优先性，若在录入某个Contraction或Acronym时，该位置的id已经不为0，则跳过不录入，避免优先级低的扩展串替换了优先级高的扩展串。
- 4、 在录入Acronym的时候，当存放其扩展串都Expand时，顺便把“空格（Acronym原型）”放到其扩展串末尾。
- 5、  因此检测Text时，对Acronym的id设置标记是否扩展过一次，扩展过的不再扩展，当读入下一篇Text时（#号），标记清零。
- 6、  对Text逐行读入，逐行替换后输出。由于Contraction与Acronym可以是任意字符串的前缀或后缀，对每一行的检测应该逐个字符检测，即对于字符c，若TrieTree中以c为首的字符串的分支指针均为NULL，则直接输出c，否则递归检查其是否为Contraction或Acronym，若是则替换，若不是依然直接输出c，继续检测下一字符。


## 测试数据

- 来源：[Alberta Collegiate Programming Contest 2003.10.18（问题D）](http://ugweb.cs.ualberta.ca/~acpc/2003/)
- 下载：[download](/reports/POJ2525-Text%20Formalization/testdata.zip)
- 输入1：[input-1](/reports/POJ2525-Text%20Formalization/testdata/input-1.dat)
- 输出1：[output-1](/reports/POJ2525-Text%20Formalization/testdata/output-1.dat)
- 输入2：[input-2](/reports/POJ2525-Text%20Formalization/testdata/input-2.dat)
- 输出2：[output-2](/reports/POJ2525-Text%20Formalization/testdata/output-2.dat)


## AC 源码


```c
//Memory Time 
//692K   32MS 

#include<iostream>
#include<cmath>
using namespace std;

struct Trie_Node   //TrieTree结点
{
	int id;					//标记从Root到当前Node的字符串是否为单词
							//id为该单词录入TrieTree的顺序编号, id=0表示该单词不存在
	int len;				//单词长度
	Trie_Node* next[128];	//分支，规模为未扩展ASCII的字符数
};

class solve
{
public:
	solve(int c,int a):C(c),A(a)
	{
		id=0;
		Trie_Node* Root=new Trie_Node;		//构造TrieTree的根结点
		initial(Root);						//初始化根结点

		Expand=new char*[C*3+A+1];			//申请扩展串的空间
		for(int i=1;i<=C*3+A;i++)
			Expand[i]=new char[StrSize()];

		EntryWord(Root);					//录入每个串的扩展串(字典登记)
		ReadText(Root);						//扩展文章
	}
	~solve()
	{
		for(int i=1;i<=C*3+A;i++)
			delete[] Expand[i];
	}

	int StrSize(void) const{return 81;}		//字符串的长度尺寸
	char UppAlp(char c);					//c若为小写字母，返回其大写；若为其他字符，返回其本身

	void initial(Trie_Node* p);				//初始化TireTree的结点
	void EntryWord(Trie_Node* Root);		//录入每个串的扩展串(字典登记)，并把其id映射到扩展串数组Expand
	void ReadText(Trie_Node* Root);			//逐行读入Text，逐行扩展输出
	
protected:

	int C;			//Contraction数量
	int A;			//Acronym数量
	int id;			//录入TrieTree的单词的顺序编号
	int KeyId;		//顺序编号<=KeyId的单词为Contraction ，顺序编号>KeyId的单词为Acronym
	char** Expand;	//记录Contraction和Acronym的扩展串,用id作为映射
};

void solve::initial(Trie_Node* p)
{
	p->id=0;
	p->len=0;
	memset(p->next,0,sizeof(p->next));
	return;
}

void solve::EntryWord(Trie_Node* Root)  
{
	int i,j,k;		//temporary
	char tc;

	/*录入Contraction到Trieree，同时录入其3种形式*/

	for(i=1;i<=C;i++)
	{
		Trie_Node* p1=Root;		//at list
		Trie_Node* p3=Root;		//uppercased
		Trie_Node* p2=Root;		//capitalized
		bool flag1=false,flag2=false,flag3=false;	//优先级标记，已录入扩展串的id不会被覆盖

		char Tmps[200];
		gets(Tmps);

		for(j=1;Tmps[j]!='\"';j++)
		{
			//at list
			if(!p1->next[Tmps[j]])
			{
				p1->next[Tmps[j]]=new Trie_Node;
				initial(p1->next[Tmps[j]]);
			}
			p1->next[Tmps[j]]->len = p1->len+1;
			p1 = p1->next[Tmps[j]];

			//uppercased
			tc=UppAlp(Tmps[j]);
			if(!p2->next[tc])
			{
				p2->next[tc]=new Trie_Node;
				initial(p2->next[tc]);
			}
			p2->next[tc]->len = p2->len+1;
			p2 = p2->next[tc];

			//capitalized
			tc=(j==1?UppAlp(Tmps[j]):Tmps[j]);
			if(!p3->next[tc])
			{
				p3->next[tc]=new Trie_Node;
				initial(p3->next[tc]);
			}
			p3->next[tc]->len = p3->len+1;
			p3=p3->next[tc];
		}

		//录入编号，建立缩写与扩展形式的映射
		//由于优先原则，若id此前已登记到TrieTree，则以后均不登记
		if(p1->id)
			flag1=true;
		else
			p1->id=++id;	
		
		if(p2->id)
			flag2=true;
		else
			p2->id=++id;

		if(p3->id)
			flag3=true;
		else
			p3->id=++id;

		/*录入Contraction的扩展形式到Expand*/

		while(Tmps[++j]!='\"');		//跳过 "->" 部分
		k=j+1;
		for(j=0;Tmps[k]!='\"';k++,j++)
		{
			//at list
			if(!flag1)
				Expand[p1->id][j]=Tmps[k];

			//uppercased
			if(!flag2)
				Expand[p2->id][j]=UppAlp(Tmps[k]);

			//capitalized
			if(!flag3)
			{
				if(j==0)
					Expand[p3->id][j]=UppAlp(Tmps[k]);
				else
					Expand[p3->id][j]=Tmps[k];
			}
		}
		if(!flag1)
			Expand[p1->id][j]='\0';
		
		if(!flag2)
			Expand[p2->id][j]='\0';

		if(!flag3)
			Expand[p3->id][j]='\0';
	}

	/*录入Acronym到Trieree*/

	KeyId=id;		//分界点编号登记

	for(i=1;i<=A;i++)
	{
		Trie_Node* p=Root;
		bool flag=false;

		char Tmps[200];
		gets(Tmps);

		for(j=1;Tmps[j]!='\"';j++)
		{
			if(!p->next[Tmps[j]])
			{
				p->next[Tmps[j]]=new Trie_Node;
				initial(p->next[Tmps[j]]);
			}
			p->next[Tmps[j]]->len = p->len+1;
			p = p->next[Tmps[j]];
		}
		if(p->id)
			flag=true;
		else
			p->id=++id;

		/*录入Acronym的扩展形式到Expand*/
		
		if(!flag)
		{
			while(Tmps[++j]!='\"');
			k=j+1;
			for(j=0;Tmps[k]!='\"';k++,j++)
				Expand[p->id][j]=Tmps[k];

			//Acronym的扩展串要求在最后加上" (Acronym)"
			Expand[id][j++]=' ';
			Expand[id][j++]='(';

			for(k=1;Tmps[k]!='\"';k++)
				Expand[id][j++]=Tmps[k];

			Expand[id][j++]=')';
			Expand[id][j]='\0';
		}
	}
    return;
}

void solve::ReadText(Trie_Node* Root)
{
	int i,j,f;

	bool* FirstApp;		//标记Acronym是否已经扩展过一次
	FirstApp=new bool[id+1];
	for(f=KeyId+1;f<=id;f++)
		FirstApp[f]=false;

	char* line=new char[StrSize()];
	while(gets(line))	//逐行输入文章
	{
		for(i=0;line[i];i++)
		{
			/*文章结束符*/
			if(line[i]=='#' && line[i+1]!='#')
			{
				printf("#");
				for(f=KeyId+1;f<=id;f++)	//清空acronym首次出现的标记
					FirstApp[f]=false;

				break;
			}

			Trie_Node* p=Root;

			//以当前字符line[i]为首的单词没有登记到TrieTree，直接输出
			if(!p->next[ line[i] ])	
			{
				printf("%c",line[i]);
				continue;
			}

			//以当前字符line[i]为首的单词可能有登记到TrieTree，检查后续字符是否构成单词
			for(j=i;!p->id;j++)
			{
				if(p->next[line[j]])
					p=p->next[line[j]];
				else
					break;
			}
			if(p->id!=0)	
			{
				if(p->id <= KeyId)		//以字符line[i]为首的单词为Contraction
				{
					printf("%s",Expand[p->id]);
					i+=p->len-1;
				}
				else if(p->id>KeyId && !FirstApp[p->id])//以字符line[i]为首的单词为Acronym
				{										//且在当前Text从未被扩展过
					FirstApp[p->id]=true;
					printf("%s",Expand[p->id]);
					i+=p->len-1;
				}
				else if(p->id>KeyId && FirstApp[p->id])//以字符line[i]为首的单词为Acronym
				{										//且在当前Text已被扩展过，直接输出line[i]
					printf("%c",line[i]);
				}
			}
			else	//以字符line[i]为首的单词均未登记到TrieTree，直接输出line[i]
			{
				printf("%c",line[i]);
			}
		}
		printf("\n");	//文章Text每行换行
	}

	delete[] FirstApp;
	return;
}

char solve::UppAlp(char c)
{
	if(c<'a' || c>'z')
		return c;

	return c-32;
}

int main(void)  
{
	int c,a;
	scanf("%d %d",&c,&a);
	getchar();		//下次输入函数为gets()，则此处要吃掉回车符

	solve poj2525(c,a);

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

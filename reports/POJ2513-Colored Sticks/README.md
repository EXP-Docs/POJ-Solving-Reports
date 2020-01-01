## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2513] [[Colored Sticks](http://poj.org/problem?id=2513)]

> [Time: 5000MS] [Memory: 128000K] [难度: 初级] [分类: trie树]

------

## 问题描述

给定一些木棒，木棒两端都涂上颜色，求是否能将木棒首尾相接，连成一条直线，要求不同木棒相接的一边必须是相同颜色的。


## 解题思路

可以用**图论**中**欧拉路**的知识来解这道题，首先可以把木棒两端看成节点，把木棒看成边，这样相同的颜色就是同一个节点。

**问题便转化为**：给定一个图，是否存在“**一笔画**”经过涂中每一点，以及经过每一边一次。

这样就是**求图中是否存在欧拉路Euler-Path**。

回顾经典的“**七桥问题**”，相信很多同学马上就明白了什么是 欧拉路 了，这里不多作解释。


由图论知识可以知道，**无向图存在欧拉路的充要条件为**：

- ① 图是连通的；
- ② 所有节点的度为偶数，或者有且只有两个度为奇数的节点。


其中**①图的连通性**用程序判断比较麻烦，先放一下。

这里先说说**②关于度数**的判断方法：

节点的度用颜色出现次数来统计，如样例中，蓝色blue出现三次（不管是出度还是入度），那么blue节点的度就为3，同样地，我们也可以通过输入得到其他全部节点的度，于是，我们有：

```
Blue=3
Red=2
Violet=1
Cyan=2
Magenta=2
```

![](/reports/POJ2513-Colored%20Sticks/img/01.png)

用一个一维数组就能记录了，然后分别 模2，就能判断颜色节点的奇偶性。

只要奇度数的节点数的个数 `==1` 或 `>=3` ，即使①图连通，欧拉路也必不存在。
 
但是若 奇度数的节点数的个数 `==0` 或 `==2`，那么我们继续进行①图的连通性证明：

**证明①图的连通性，使用并查集MergeSet是非常高效的方法**。

基本方法：

初始化所输入的n个节点为n棵树，那么就有一个n棵树的森林，此时每棵树的有唯一的节点（根），该节点的祖先就是它本身。再通过不断地输入边，得到某两个节点（集合）之间的关系，进而合并这两个节点（集合），那么这两个集合就构成一个新的集合，集合内的所有节点都有一个共同的新祖先，就是这个集合（树）的根。

最后只要枚举任意一个节点，他们都具有相同的祖先，那么就能证明图时连通的了。

但是单纯使用并查集是会超时的，因为这样会导致每次寻找某个节点的祖先时，平均都会花费O(n/2)时间，最坏情况，当n==50W时，O(n/2)大概为25ms，那么要确定50W个节点是否有共同祖先时，总费时为 `50W*25ms` ，铁定超时。


因此必须使用并查集时必须压缩路径，前几次搜索某个节点k的祖先时，在不断通过父亲节点寻找祖先节点时，顺便把从k到最终祖先节点S中经过的所有节点的祖先都指向S，那么以后的搜索就能把时间降低到O(1)


由于并查集必须利用 数组的下标 与 存储的对象，使用int是比较方便的处理方法，但是题目的“颜色节点”是string，不方便用来使用并查集，即使用map也不行，虽然STL的map是基于hash的基础上，但并不高效，在本题中使用会超时。


为此可以使用Trie字典树，得到每个颜色单词对应的int编号id ，可以说利用Trie把string一一映射到int，是本题后续处理的关键所在。关于动态创建字典树的方法去百度，这里不多说，下面只用用一个图简单说明一下用Trie字典树标识第一个颜色单词blue：

![](/reports/POJ2513-Colored%20Sticks/img/02)

这个题目涉及了多个基本数据结构和算法，综合性很强，非常有代表性，能够A到这题确实是受益良多。


**知识考查点**：

- **字典树**
- **欧拉路径**：其中又考察了判断是否为连通图
- **并查集** 及其优化方法（路径压缩）


**输出约束条件**：
- POSSIBLE：  奇度数节点个数 `==0` 或 `==2`  且  图连通
- IMPOSSIBLE：奇度数节点个数 `==1` 或 `>=3`  或  图不连通


> 注意创建TrieTree链表时，C++不存在NULL，要用 0 替代 NULL


## AC 源码


```c
/* TrieTree + MergeSet + EulerPath*/

//Memory Time
//77460K 2047MS 

#include<iostream>
using namespace std;  

const int large=500000;  //25W条棒子，有50W个端点

class TrieTree_Node   //字典树节点
{
	public:
		bool flag;   //标记到字典树从根到当前节点所构成的字符串是否为一个(颜色)单词
		int id;     //当前颜色(节点)的编号
		TrieTree_Node* next[27];

		TrieTree_Node()   //initial
		{
			flag=false;
			id=0;
			memset(next,0,sizeof(next));  //0 <-> NULL
		}
}root;   //字典树根节点

int color=0;  //颜色编号指针，最终为颜色总个数

int degree[large+1]={0};   //第id个节点的总度数
int ancestor[large+1];   //第id个节点祖先


/*寻找x节点的最终祖先*/

int find(int x)
{
	if(ancestor[x]!=x)
		ancestor[x]=find(ancestor[x]);   //路径压缩
	return ancestor[x];
}

/*合并a、b两个集合*/

void union_set(int a,int b)
{
	int pa=find(a);
	int pb=find(b);
	ancestor[pb]=pa;   //使a的祖先 作为 b的祖先
	return;
}

//利用字典树构造字符串s到编号int的映射

int hash(char *s)  
{
	TrieTree_Node* p=&root;  //从TrieTree的根节点出发搜索单词(单词不存在则创建)

    int len=0;
    while(s[len]!='\0')
    {
		int index=s[len++]-'a';  //把小写字母a~z映射到数字的1~26，作为字典树的每一层的索引

        if(!p->next[index])  //当索引不存在时，构建索引
			p->next[index]=new TrieTree_Node;

		p=p->next[index];
    }

	if(p->flag)  //颜色单词已存在
		return p->id;  //返回其编号
	else   //否则创建单词
	{
		p->flag=true;
		p->id=++color;
		return p->id;   //返回分配给新颜色的编号
	}
}

int main(void)  
{
	/*Initial the Merge-Set*/

    for(int k=1;k<=large;k++)   //初始化，每个节点作为一个独立集合
		ancestor[k]=k;  //对于只有一个节点x的集合，x的祖先就是它本身

	/*Input*/

	char a[11],b[11];
    while(cin>>a>>b)  
    {
		/*Creat the TrieTree*/

		int i=hash(a);
		int j=hash(b);  //得到a、b颜色的编号

		/*Get all nodes' degree*/

        degree[i]++;
        degree[j]++;   //记录a、b颜色出现的次数(总度数)

		/*Creat the Merge-Set*/

		union_set(i,j);
	}

	/*Judge the Euler-Path*/

	int s=find(1);  //若图为连通图，则s为所有节点的祖先
	                    //若图为非连通图，s为所有祖先中的其中一个祖先

	int num=0;  //度数为奇数的节点个数

	for(int i=1;i<=color;i++)
	{
		if(degree[i]%2==1)
			num++;
				
		if(num>2)   //度数为奇数的节点数大于3，欧拉路必不存在
		{
			cout<<"Impossible"<<endl;
			return 0;
		}

		if(find(i)!=s)   //存在多个祖先，图为森林，不连通
		{
			cout<<"Impossible"<<endl;
			return 0;
		}
	}

	if(num==1) //度数为奇数的节点数等于1，欧拉路必不存在
		cout<<"Impossible"<<endl;
	else       //度数为奇数的节点数恰好等于2或不存在，存在欧拉路
		cout<<"Possible"<<endl;

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

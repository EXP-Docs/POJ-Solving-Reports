## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1094] [[Sorting It All Out](http://poj.org/problem?id=1094)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 拓扑排序]

------

## 问题描述

无。


## 解题思路

**提示：** 拓扑排序

这道题有隐含这一信息，每输入一对关系，如果判定有结果，则可以忽略后面输入数据，即使后面输入数据能改变结果，也不用管。所以应该每输入一个关系就去更新当前的图，然后进行一趟拓扑排序。一旦产生结果，再对后面的数据处理下，就可以输出结果。

------

下面罗列所有可能的情况（类似于**状态机**）:


一、当输入的字母全部都在前n个大写字母范围内时：

（1）最终的图 可以排序：
<br/>　　在输入结束前如果能得到最终的图（就是用这n个字母作为顶点，一个都不能少）；
<br/>　　而且最终得到的图  无环；
<br/>　　只有唯一一个 无前驱（即入度为0）的节点，但允许其子图有多个无前驱的节点。
<br/>　　在这步输出排序后，不再对后续输入进行操作

（2）输出矛盾
<br/>　　在输入结束前如果最终图的子图有环
<br/>　　在这步输出矛盾后，不再对后续输入进行操作

（3）输出无法确认排序
<br/>　　这种情况必须全部关系输入后才能确定，其中又有2种可能
<br/>　　　　① 最终图的字母一个不缺，但是有多个  无前驱节点
<br/>　　　　② 输入结束了，但最终的图仍然字母不全，与 无前驱节点 的多少无关

二、当输入的字母含有 非前n个大写字母 的字母时（超出界限）：

（1）输出矛盾
<br/>　　输入过程中检查输入的字母（节点），若 前n个大写字母 全部出现，则在最后一个大写字母出现的那一步 输出矛盾

（2）输出无法确认排序
<br/>　　最后一步输入后，前n个大写字母 仍然未全部出现，则输出 无法确认排序

------

**注意：**

在使用“无前驱节点”算法时必须要注意，在“矛盾优先”的规律下，必须考虑一种特殊情况，就是多个无前驱节点与环共存时的情况，即输入过程中子图都是有 多个无前驱节点，最后一步输入后出现了环，根据算法的特征，很容易输出“不能确认排序”，这是错的，必须适当修改算法，输出“矛盾”。

例如：

```
6 6
A<F
B<D
C<E
F<D
D<E
E<F
```

输出矛盾


## AC 源码


```c
//Memory Time 
//276K   0MS 

#include<iostream>
using namespace std;

int n,m;  //n节点下限，m关系对
char top_out[26];  //排序输出列表
int po=0;  //输出列表的指针

typedef class degree
{
public:
	int in;      //入度
	char to[26];   //记录指向的所有顶点，以便删除出度的操作
	int pt;    //数组to的指针
};

int top_sort(degree alph[],bool mark[],int num)
{
	/*假设图G的当前子图为F*/

	memset(top_out,'\0',sizeof(top_out));
	po=0;
	
	int del_n=0;
	int zero=0;  //记录图F中入度为0的节点个数
	for(int i='A';i<'A'+n;i++)
		if(mark[i] && !alph[i].in)
			zero++;

	bool flag=false;
	while(zero>0)
	{
		if(zero>1)  //图F的无前驱节点的个数不唯一，排序无法确定
			flag=true;  //考虑到"矛盾"的优先性，避免在多个0入度节点情况下，最后一步输入刚好出现环（此时为矛盾）
		                //所以这里先不返回值，而是先标记，执行拓扑，根据情况决定返回值

		for(int k='A';k<='A'+n;k++)   //寻找图F的唯一的前驱节点
			if(mark[k] && !alph[k].in)
			{
				mark[k]=false;       //删除图F的唯一无前驱节点k
				del_n++;            //记录删除的节点数
				top_out[po++]=k;    //k记录到排序输出列表
				for(int i=0;i<alph[k].pt;i++)   //删除节点k的所有出度边
					alph[ alph[k].to[i] ].in--;
				break;
			}

		zero=0;
		for(int j='A';j<='A'+n;j++)
			if(mark[j] && !alph[j].in)
				zero++;
	}

    if(flag && del_n==num)
		return 3;
	if(del_n<num)   //说明图F存在有向环,矛盾，与0入度节点的多少无关。因为矛盾优先
		return 2;
	if(!flag && del_n==num && del_n<n)  //图F能排序，但不能确定图G是否能排序，还需继续输入观察
		return 3;
	if(!flag && del_n==n)    //图G能排序
		return 1;
}

int main(void)
{
	int num;      //标记前n个字母出现个数,用于最终检查是否前n个字母均已被读入
	     //*_t[]是用于备份的额外数组
	bool mark['Z'+1],mark_t['Z'+1];  //标记当前图G所使用的字母（节点）
	degree alph['Z'+1],alph_t['Z'+1];   

	while(true)
	{
		/*Input*/

		cin>>n>>m;

		if(!n||!m)
			break;
		
		/*Initial*/

		memset(mark,false,sizeof(mark));
		memset(mark_t,false,sizeof(mark_t));
		num=0;

		for(int k='A';k<'A'+n;k++)
		{
			alph[k].in=alph_t[k].in=0;
			alph[k].pt=alph_t[k].pt=0;
			memset(alph[k].to,'\0',sizeof(alph[k].to));
			memset(alph_t[k].to,'\0',sizeof(alph_t[k].to));
		}
		
		/*Structure Maps*/

		char x,symbol,y;  //临时变量
		bool flag=false;
		bool sign=false;
		int value;   //记录拓扑返回的值
		int step;   //记录当前情况发生的步骤
		for(int pair=1;pair<=m;pair++)
		{
			cin>>x>>symbol>>y;

			if(x>='A'+n || y>='A'+n)  //当输入的节点不在前n个字母范围内时
				sign=true;       //不再进行拓扑,单纯检查后续输入是否把前n个字母都输入了
				                 //为了区分非前n个字母的字母的输入时间，是在确认了排序或矛盾之前还是之后
			                     //在确认 排序或矛盾之前:flag=false,sign=true
			                     //在确认 排序或矛盾之后:flag=true,sign=true

			if(!mark[x] && x<'A'+n)
				num++;
			if(!mark[y] && y<'A'+n)
				num++;

			if(!flag && !sign)
			{
				value=0;

			    mark[x]=mark[y]=true;        //顶点标记
			    mark_t[x]=mark_t[y]=true;

			    alph[y].in++;                //入度标记
			    alph_t[y].in++;

			    alph[x].to[ alph[x].pt++ ]=y;        //指向标记 & 指针移动
			    alph_t[x].to[ alph_t[x].pt++ ]=y;

			/*Top-Sort & Sign*/
				
				value=top_sort(alph_t,mark_t,num);  //每次输入后图都被更新，要重新拓扑
			    if(value==1)       //排序确认
				{
			     	step=pair;    //记录确认排序的位置
			    	flag=true;    //不再对后续输入处理
				}
		    	else if(value==2)  //矛盾
				{
			    	step=pair;    //记录矛盾发生的位置
			    	flag=true;    //不再对后续输入处理
				}
		    	else if(value==3 && pair<m)  //排序（暂时）无法确认，需继续处理后续输入 
			    	for(int k='A';k<'A'+n;k++)        //数据还原
					{
				    	mark_t[k]=mark[k];
				    	alph_t[k].in=alph[k].in;
					}

				if(pair==m && value==0)
					value=3;
			}

			if(sign && !flag && num==n)  //在确认 排序或矛盾之前,当存在有非前n个字母的节点时的"矛盾"
			{
				step=pair;
				value=2;
			}
			else if(sign && !flag && pair==m && num<n) //在确认 排序或矛盾之前,当存在有非前n个字母的节点时的"无法确认排序"
				value=3;
		}

		if(value==1)
		{
			cout<<"Sorted sequence determined after "<<step<<" relations: ";
			for(int i=0;i<po;i++)
				cout<<top_out[i];
			cout<<'.'<<endl;
		}
		else if(value==2)
			cout<<"Inconsistency found after "<<step<<" relations."<<endl;
		else if(value==3)
			cout<<"Sorted sequence cannot be determined."<<endl;
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

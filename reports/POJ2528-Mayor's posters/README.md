## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2528] [[Mayor's posters](http://poj.org/problem?id=2528)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 线段树]

------

## 问题描述

有一面墙，被等分为1QW份，一份的宽度为一个单位宽度。现在往墙上贴N张海报，每张海报的宽度是任意的，但是必定是单位宽度的整数倍，且 `<=1QW` 。后贴的海报若与先贴的海报有交集，后贴的海报必定会全部或局部覆盖先贴的海报。现在给出每张海报所贴的位置（左端位置和右端位置），问张贴完N张海报后，还能看见多少张海报？（看见一部分也算看到。）


## 解题思路

水题，**区间压缩映射（离散化）**+ **线段树**


首先**建立模型**：

给定一条数轴，长度为1QW，然后在数轴上的某些区间染色，第i次对区间染色为i，共染色N次。给出每次染色的区间，问最后能看见多少种颜色。



**常规思路**：

若第i次在区间 `[ai, bi]`染色，则把 `[ai, bi]` 的每一格都染色为i。后染的颜色覆盖先染的颜色。由于染色N次，定义一个标记数组tagcol，从数轴第一格开始检查，一直检查到最后，出现过得颜色则记录到tagcol，最后统计tagcol中不同颜色的个数，就是所求。

数据规模太大，必定TLE。

------


应该**用线段树去求解**，这题只是线段树的入门水题，不懂线段树的同学去找一些相关资料大概学习一下，然后看一下我代码中注释，这题就有思路做了。我推荐你们去看看“浙江大学acm校队”的关于线段树的PPT，里面有线段树从入门到精通的案例，也有涉及离散化的介绍，百度搜就有了。

然后我这里补充几点线段树的知识，网上关于线段树的资料很多有误导：

- 1、 线段树是二叉树，且必定是平衡二叉树，但不一定是完全二叉树。
- 2、 对于区间 `[a,b]`，令 `mid=(a+b)/2`，则其左子树为 `[a,mid]`，右子树为 `[mid+1,b]`，当 `a==b` 时，该区间为线段树的叶子，无需继续往下划分。
- 3、 线段树虽然不是完全二叉树，但是可以用完全二叉树的方式去构造并存储它，只是最后一层可能存在某些叶子与叶子之间出现“空叶子”，这个无需理会，同样给空叶子按顺序编号，在遍历线段树时当判断到 `a==b` 时就认为到了叶子，“空叶子”永远也不会遍历到。
- 4、 之所以要用完全二叉树的方式去存储线段树，是为了提高在插入线段和搜索时的效率。用 `p*2`，`p*2+1` 的索引方式检索p的左右子树要比指针快得多。
- 5、 线段树的精髓是，能不往下搜索，就不要往下搜索，尽可能利用子树的根的信息去获取整棵子树的信息。如果在插入线段或检索特征值时，每次都非要搜索到叶子，还不如直接建一棵普通树更来得方便。



但是这题单纯用线段树去求解一样不会AC，原因是建立一棵 `[1,1QW]`的线段树，其根系是非常庞大的，TLE和MLE是铁定的了。所以**必须离散化**。

通俗点说，**离散化就是压缩区间**，使原有的长区间映射到新的短区间，但是区间压缩前后的覆盖关系不变。举个例子：

有一条1到10的数轴（长度为9），给定4个区间 `[2,4] [3,6] [8,10] [6,9]`，覆盖关系就是后者覆盖前者，每个区间染色依次为 1 2 3 4。

现在我们抽取这4个区间的8个端点，2 4 3 6 8 10 6 9

然后删除相同的端点，这里相同的端点为6，则剩下2 4 3 6 8 10 9

对其升序排序，得2 3 4 6 8 9 10

然后**建立映射**

| 2 | 3 | 4 | 6 | 8 | 9 | 10 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| ↓ | ↓ | ↓ | ↓ | ↓ | ↓ | ↓ |
| 1 | 2 | 3 | 4 | 5 | 6 | 7 |

那么新的4个区间为 `[1,3] [2,4] [5,7] [4,6]`，覆盖关系没有被改变。新数轴为1到7，即原数轴的长度从9压缩到6，显然构造 `[1,7]` 的线段树比构造 `[1,10]` 的线段树更省空间，搜索也更快，但是求解的结果却是一致的。

离散化时有一点必须要注意的，就是必须先剔除相同端点后再排序，这样可以减少参与排序元素的个数，节省时间。

> **附**：海报张数上限为10000，即其端点映射的新数轴长度最多为20000。因此建立长度为1QW的离散数组dis时，可以使用unsigned short类型，其映射值最多为20000，这样可以节约空间开销。


## 测试数据

- 来源：[Alberta Collegiate Programming Contest 2003.10.18（问题G）](http://ugweb.cs.ualberta.ca/~acpc/2003/)
- 下载：[download](/testdata.zip)



## AC 源码


```c
//Memory Time 
//21276K 547MS 

#include<iostream>
#include<algorithm>
using namespace std;

class LineTree_Node
{
public:
	int s,e;		//区间端点
	int col;		//区间颜色
	LineTree_Node():s(0),e(0),col(0){}
};

class solve
{
public:
	solve(int n):N(n)
	{
		Initial();
		Input();
		CreatLineTree(1,Maxp,1);
		Solution();
	}
	~solve()
	{
		for(int i=1;i<=N;i++)
			delete[] reg[i];

		delete[] ep;
		delete[] dis;
		delete[] tagcol;
		delete[] LT;
	}

	void Initial(void);							//初始化并申请存储空间
	void Input(void);							//输入
	void CreatLineTree(int sp,int tp,int p);	//构造[sp,tp]线段树
	void Solution(void);						//插入区间，统计颜色
	void Insert(int a,int b,int p,int color);	//[a,b]:把区间[a,b]插入线段树
												//p:当前所在线段树的位置
												//color:当前区间的染色
	void DFS(int p);							//遍历线段树,计算线段树中不同颜色的个数

protected:

	int N;					//海报数(区间数)
	int Maxp;				//记录(压缩后的)最大端点,用于建造区间[1,Maxp]的线段树
	LineTree_Node* LT;		//线段树

	int **reg;				//顺序存储输入的区间（每张海报的宽度）
	int *ep;				//顺序存储输入的每个区间的2个端点
	unsigned short *dis;	//映射端点，压缩区间（离散化）

	bool* tagcol;			//标记能看见的颜色
	int cnt;				//计数器，记录线段树中能看见的不同的颜色数
};

void solve::Initial(void)
{
	cnt=0;

	reg=new int*[N+1];
	for(int i=1;i<=N;i++)
		reg[i]=new int[2];

	ep=new int[2*N+1];
	dis=new unsigned short[1e7+1];
	memset(dis,0,sizeof(unsigned short)*(1e7+1));

	tagcol=new bool[N+1];
	memset(tagcol,false,sizeof(bool)*(N+1));

	return;
}

void solve::Input(void)
{
	int p=0;
	for(int i=1;i<=N;i++)
	{
		scanf("%d %d",&reg [ i ][0],&reg [ i ][1]);

		/*避免相通的端点重复映射到不同的值*/
		/*也为了减少参与排序的元素个数，这里必须做标记*/
		/*同时为了节约空间，本用于离散化的dis[]数组暂时用来标记端点*/

		if(dis[reg[i][0]]==0)
		{
			ep[p++]=reg[i][0];
			dis[reg[i][0]]=1;
		}

		if(dis[reg[i][1]]==0)
		{
			ep[p++]=reg[i][1];
			dis[reg[i][1]]=1;
		}
	}

	/*离散化*/

	sort(ep,ep+p);			//区间端点排序

	unsigned short hash=0;
	for(int j=0;j<p;j++)
		dis[ep[j]]=++hash;	//把排好序的端点依次映射到1,2,...,Maxp

	Maxp=hash;
	LT=new LineTree_Node[4*Maxp+1];

	return;
}

void solve::CreatLineTree(int sp,int tp,int p)	
{
	LT[p].s=sp;
	LT[p].e=tp;

	if(sp==tp)
		return;

	/*注意线段树不一定都是完全二叉树*/
	/*但是为了处理方便，加快搜索效率*/
	/*我们完全可以把线段树以完全二叉树的形式进行构造、存储*/

	int mid=(sp+tp)>>1;
	CreatLineTree(sp,mid,p*2);
	CreatLineTree(mid+1,tp,p*2+1);
	
	return;
}

void solve::Solution(void)
{
	for(int i=1;i<=N;i++)
		Insert(dis[reg[i][0]],dis[reg[i][1]],1,i);	//逐个区间(海报)对线段树染色

	DFS(1);
	printf("%d\n",cnt);
	return;
}

void solve::Insert(int a,int b,int p,int color)
{
	if(b<LT[p].s || a>LT[p].e)	//[a,b]与[s,e]完全无交集
		return;					//说明[a,b]不被[s,e]所在的子树包含，无需向下搜索

	if(a<=LT[p].s && b>=LT[p].e)//[a,b]完全覆盖[s,e]
	{
		LT[p].col=color;//[s,e]染单色，暂时无需对[s,e]的子树操作(这是由线段树的搜索机制决定的)
		return;			//因此直接返回
	}

	/*若能执行到这里，说明[a,b]部分覆盖[s,e]*/

	if(LT[p].col>=0)	//[s,e]本为无色或者单色
	{											//由于不知道[a,b]覆盖了[s,e]多少
		LT[p*2].col=LT[p*2+1].col=LT[p].col;	//因此先由[s,e]的孩子继承[s,e]的单色
		LT[p].col=-1;							//[s,e]由于被部分覆盖，染色为多色
	}

	/*若能执行到这里，说明[s,e]为多色*/
	/*细化处理[s,e]的孩子，确定[s,e]中哪部分的区间是什么颜色*/

	Insert(a,b,p*2,color);
	Insert(a,b,p*2+1,color);

	return;
}

void solve::DFS(int p)
{
	if(LT[p].col==0)	//[s,e]为无色，其孩子也必为无色，无需继续搜索
		return;

	if(LT[p].col>0)		//[s,e]为单色，则无需向下搜索
	{					//因为其子区间必被[s,e]覆盖,能看见的只有[s,e]的颜色
		if(!tagcol[LT[p].col])
		{
			tagcol[LT[p].col]=true;
			cnt++;
		}
		return;
	}

	if(LT[p].col==-1)	//[s,e]为多色，说明能在[s,e]看到集中颜色
	{					//搜索其子区间具体有什么颜色
		DFS(p*2);
		DFS(p*2+1);
	}
	return;
}


int main(void)
{
	int test;
	scanf("%d",&test);
	for(int t=1;t<=test;t++)
	{
		int n;
		scanf("%d",&n);
		solve poj2528(n);
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

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3177] [[Redundant Paths](http://poj.org/problem?id=3177)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 连通分量/割边/割点]

------

## 问题描述

为了保护放牧环境，避免牲畜过度啃咬同一个地方的草皮，牧场主决定利用不断迁移牲畜进行喂养的方法去保护牧草。然而牲畜在迁移过程中也会啃食路上的牧草，所以如果每次迁移都用同一条道路，那么该条道路同样会被啃咬过度而遭受破坏。

现在牧场主拥有F个农场，已知这些农场至少有一条路径连接起来（不一定是直接相连），但从某些农场去另外一些农场，至少有一条路可通行。为了保护道路上的牧草，农场主希望再建造若干条道路，使得每次迁移牲畜时，至少有2种迁移途径，避免重复走上次迁移的道路。已知当前有的R条道路，问农场主至少要新建造几条道路，才能满足要求？


## 解题思路

“使得每次迁移牲畜时，至少有2种迁移途径，避免重复走上次迁移的道路。”就是说当吧F个农场看作点、路看作边构造一个无向图G时，图G不存在桥。

那么可以**建立模型**：

给定一个连通的无向图G，至少要添加几条边，才能使其变为双连通图。

这题是和 [POJ3352](/reports/POJ3352-Road%20Construction) 一模一样的题，只不过表述方式不同而已。

详细解题过程请参考我 [POJ3352](/reports/POJ3352-Road%20Construction) 的解题报告，有详细叙述。

看完 [POJ3352](/reports/POJ3352-Road%20Construction) 的解题报告，再回来看看本题要注意的一些地方：

本题和 [POJ3352](/reports/POJ3352-Road%20Construction) 最大的区别就是， [POJ3352](/reports/POJ3352-Road%20Construction) 保证了没有重边，而**本题有重边**。

而 [POJ3352](/reports/POJ3352-Road%20Construction) 的解题报告已经说过，当两点之间出现重边时，就不可以利用Low值去划分【边双连通分量】了，因为此时不同Low值的两点可能属于同一个【边双连通分量】！


**那么如何解决重边的问题**？

- 1、 构造图G时把重边也考虑进来，然后在划分边双连通分量时先把桥删去，再划分，其中桥的一端的割点归入当前正在划分的边双连通分量。这个处理比较麻烦；
- 2、 在输入图G的边时，若出现重边，则不把重边放入图G，然后在划分边双连通分量时依然用Low划分。

两者相权，当然是第2种方法更好处理了。

其实用**邻接矩阵**去存储图G的同学，**是无需考虑重边的问题的**。

但是用**邻接链表**去存储图G的同学**就不得不考虑了**，因为基本上都是用头插入法在链表中插入边的，所以无法检测重边。而改用尾插入法，则可以在指针从链头移到链尾的同时，顺便加一个判断，出现重边则不再插入，否则插入到尾部。


## 测试数据

- 输入：[input](/reports/POJ3177-Redundant%20Paths/testdata/input.dat)
- 输出：[output](/reports/POJ3177-Redundant%20Paths/testdata/output.dat)


## AC 源码


```c
//236K   16MS  

#include&lt;iostream&gt;
using namespace std;

class Node
{
public:
    int id;
    class Node* next;
    Node():id(0),next(0){}
};

class solve
{
public:
    solve(int f,int r):F(f),R(r)
    {
        Initial();          
        Input_Creat();
        Tarjan(1,-1);       //本题给定的图G为连通的，因此从任意节点开始搜索均可
        printf("%d\n",BCC_SP_D_E());
    }
    ~solve()
    {
        delete[] DFN;
        delete[] Low;
        delete[] degree;

        EmptyList();
    }

    int min(int a,int b) const{return a&lt;b?a:b;}

    void Initial(void);             //申请存储空间并初始化
    void Input_Creat(void);         //输入并创建图G
    void AddEdge(int a,int b);      //向链表插入边a&lt;-&gt;b (尾插入法，避免重边)

    void Tarjan(int s,int father);  //计算Low[]数组，用于寻找所有边双连通分量
    int BCC_SP_D_E(void);           //把每个边双连通分量(BCC)构造为缩点(SP)，并计算每个缩点的度数(D)
                                    //返回值为使得图G为双连通所需添加的最少的边(E)的数量

    void DelLink(Node* p);          //释放以p为表头的整条链
    void EmptyList(void);           //释放邻接链表

protected:

    int F;                  //the number of islands
    int R;                  //the number of roads
    Node** LinkHead;        //邻接链表表头

    int TimeStamp;          //(外部)时间戳
    int* DFN;               //DFN[u]: 结点u的搜索次序(时间戳)
    int* Low;               //Low[u]: 结点u或u的子树能够追溯到的最早的栈中结点的次序号

    int* degree;            //记录每个缩点的总度数
};

void solve::Initial(void)
{
    LinkHead=new Node*[F+1];
    for(int i=1;i&lt;=F;i++)
        LinkHead[i]=0;

    TimeStamp=0;
    DFN=new int[F+1];
    Low=new int[F+1];
    memset(DFN,0,sizeof(int)*(F+1));
    memset(Low,0,sizeof(int)*(F+1));

    degree=new int[F+1];
    memset(degree,0,sizeof(int)*(F+1));

    return;
}

void solve::Input_Creat(void)
{
    int a,b;
    Node* tmp;
    for(int j=1;j&lt;=R;j++)
    {
        scanf("%d %d",&amp;a,&amp;b);

        if(!LinkHead[a])
            LinkHead[a]=new Node;
        if(!LinkHead[b])
            LinkHead[b]=new Node;

        AddEdge(a,b);
    }
    return;
}

void solve::AddEdge(int a,int b)
{
    Node* pa=LinkHead[a];
    Node* p1=new Node;
    p1-&gt;id=b;

    while(pa-&gt;next)
    {
        pa=pa-&gt;next;
        if(pa-&gt;id==p1-&gt;id)  //出现重边，重边不插入链表
            return;
    }
    pa-&gt;next=p1;

    Node* pb=LinkHead[b];
    Node* p2=new Node;
    p2-&gt;id=a;

    while(pb-&gt;next)         //能执行到这里说明a&lt;-&gt;b不是重边
        pb=pb-&gt;next;        //直接搜索到链表尾部插入
    pb-&gt;next=p2;

    return;
}

void solve::Tarjan(int s,int father)
{
    DFN[s]=Low[s]=++TimeStamp;
    for(Node* p=LinkHead[s]-&gt;next;p;p=p-&gt;next)
    {
        int t=p-&gt;id;
        if(t!=father &amp;&amp; DFN[t]&lt;DFN[s])
        {
            if(DFN[t]==0)           //s-&gt;t为树枝边
            {
                Tarjan(t,s);
                Low[s]=min(Low[s],Low[t]);
            }
            else                    //s-&gt;t为后向边
            {
                Low[s]=min(Low[s],DFN[t]);
            }
        }
    }
    return;
}

int solve::BCC_SP_D_E(void)
{
    for(int i=1;i&lt;=F;i++)
        if(LinkHead[i])
        {
            for(Node* p=LinkHead[i]-&gt;next;p;p=p-&gt;next)  //枚举图G中每两个连通的点i&lt;-&gt;j
            {                                           //由于图G为无向图，则连通是双向的
                int j=p-&gt;id;
                if(Low[i]!=Low[j])      //图G中Low值相同的两个点必定在同一个边双连通分量(即同一个缩点)中
                {                       //检查i、j是否不在同一个缩点中

                    degree[Low[i]]++;   //结点i所在的缩点的度+1
                    degree[Low[j]]++;   //结点j所在的缩点的度+1
                }
            }
        }

    int leave=0;            //记录总度数=1（叶子）的缩点
    for(int k=1;k&lt;=F;k++)   //枚举各个缩点的度数D
        if(degree[k]/2==1)  //由于是无向图，因此每个缩点的度都重复计算了2次，除2后才是真实的度数
            leave++;

    return (leave+1)/2;     //将一棵树连成一个边双连通分量至少需要添加的边数=(叶子节点数+1)/2
}

void solve::DelLink(Node* p)
{
    if(p-&gt;next)
        p=p-&gt;next;
    delete[] p;
    return;
}

void solve::EmptyList(void)
{
    for(int i=1;i&lt;=F;i++)
        if(LinkHead[i])
            DelLink(LinkHead[i]);
    return;
}

int main(void)
{
    int f,r;
    while(scanf("%d %d",&amp;f,&amp;r)!=EOF)
        solve poj3177(f,r);

    return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

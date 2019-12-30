## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1062] [[Expensive dowry](http://poj.org/problem?id=1062)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 最短路径算法]

------

## 问题描述

每个物品看成一个节点，酋长的允诺也看作一个物品， 如果一个物品加上金币可以交换另一个物品，

则这两个节点之间有边，权值为金币数，求第一个节点到所有节点的最短路。

因为有等级限制，所以枚举每个点作为最低等级，选取符合所有符合等级限制的点


## 解题思路

难得的中文题，虽然语言相通但是不好解决...

这是**最短路**问题，不过因为存在着等级的差异所以需要**枚举**一下。本题的思路就是对冒险者的等级进行枚举，也就是说冒险者只能和在他等级以上的人进行交易。这样枚举的好处是能够把所有的情况都考虑进去。有一点需要注意：酋长的等级不一定是最高的。


主要考察**dijkstra**算法的运用。

很多同学对dijkstra有一种与生俱来的恐惧，首当其冲就是因为它的名字...

其实dijkstra很简单的，我只说一个我认为能够很好理解**dijkstra精髓**的关键点：

**新源点合并到旧源点时，新源点到旧源点的边权的移交（也可理解为松弛）**

弄清了这个，dijkstra就不难了，我觉得dijkstra和Prim有异曲同工之妙。

构图时要注意的是，酉长的承诺不是 最初的源点，它是一个目标点，也就是说点到点的指向方向是由 无替代品的点 逐渐指向到 酉长的承诺1点，题意说明的是一个回溯的过程，因此可以定义一个最初的源点0点，它到其他各点的权值就是每个物品的原价，而点A到点B的权值 就是 物品B在有第A号替代品情况下的优惠价


## AC 源码


```c
//Memory Time 
//300K   32MS 

#include<iostream>   
using namespace std; 

const int inf=0x7fffffff;   //无限大  
  
int M,N;//M为等级差，N为物品数目   
int price[101][101];   //物品i在有第t号替代品情况下的优惠价pricr[t][i],当t=0时说明i无替代品，此时为原价
int lv[101];   //第i号物品主人的等级lv[i]
int x[101];//第i号物品的替代品总数x[i]   
  
int dist[101];//最初的源点0到任意点i的最初距离（权值），相当于每个物品的原价   
  
bool vist[101];   //记录点i是否已被访问
 
/*Initial and Input*/  

void data_init()   
{   
    memset(price,0,sizeof(price));   
    memset(lv,0,sizeof(lv));   
    memset(dist,inf,sizeof(dist));   
    memset(vist,false,sizeof(vist));  
	
    cin>>M>>N;   
    for(int i=1;i<=N;i++)   
    {   
        cin>>price[0][i]>>lv[i]>>x[i];   //price[0][i]物品i无替代品时的原价
  
        for(int j=1;j<=x[i];j++)   
        {   
            int t,u;   //t替代品编号，u优惠价(临时变量)
			cin>>t>>u;
            price[t][i]=u;   //物品i在有第t号替代品情况下的优惠价，即点t到点i的权值
        }   
    }   
}   

/*Dijkstra Algorithm*/   

int dijkstra()   
{   
       
    int node;//记录与当前源点距离最短的点   
    int sd;//最短距离   
    int i,j;
  
    for(i=1;i<=N;i++)   
        dist[i]=price[0][i];  //假设最初的源点就是0点，初始化最初源点到各点的权值dist[i]

    for(i=1;i<=N;i++)   //由于1点是目标点，因此最坏的打算是进行n次寻找源点到其他点的最短路，并合并这两点（不再访问相当于合并了）
    {   
        node=0;   
        sd=inf;   
        for(j=1;j<=N;j++)   
        {   
            if(!vist[j] && sd>dist[j])   //在未访问的点中，寻找最短的一条
            {   
                sd=dist[j];   
                node=j;   //记录该点
            }   
        }   
        if(node==0)   //若node没有变化，说明所有点都被访问，最短路寻找完毕
            break;   
           
        vist[node]=true;   //记录node点已被访问
        for(j=1;j<=N;j++)   
        {   
            if(!vist[j] && price[node][j] > 0 && dist[j] > dist[node] + price[node][j])   //把未访问但与node（新源点）连通的点进行松弛
                dist[j]=dist[node]+price[node][j];   
        }   
    }   
    return dist[1];   //返回当前次交易后目标点1在等级lv[i]约束下的最短距离
}   
  
int main()   
{
    data_init();   //初始化并输入数据
   
    int temp_price;    //当前次交易后目标点1在等级lv[i]约束下的最少价格
	int maxlv;       //最大等级(酉长的等级不一定是最大的)
    int minprice=inf;    //最低价格(初始化为无限大)
   
    for(int i=1;i<=N;i++)   
    {   
		/*在等级限制下，寻找允许被当前点访问的点*/
           
        maxlv=lv[i];   //把当前物品的等级暂时看做最高等级
        for(int j=1;j<=N;j++)   //遍历其他各点
        {   
            if(lv[j]>maxlv || maxlv-lv[j]>M)   //当其它物品j的等级比当前物品高(保证单向性)，或者两者等级之差超出限制M时
                vist[j]=true;    //物品j则强制定义为“已访问”状态，不参与后续操作
            else  
                vist[j]=false;   //否则物品j定义为“未访问”状态，参与后续操作
        }   

        temp_price=dijkstra();   //记录当前次交易后目标点1在等级lv[i]约束下的最短距离(最少价格)

        if(minprice>temp_price)   //寻找各次交易后的最少价格，最终确认最少价格
            minprice=temp_price;   
    }   
    cout<<minprice<<endl;   
  
    return 0;   
}  
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2706] [[Connect](http://poj.org/problem?id=2706)]

> [Time: 1000MS] [Memory: 65536K] [难度: 中级] [分类: 模拟法]

------

## 问题描述

一种类似围棋的游戏，有黑白两种颜色的棋子。

规定黑棋为先手，白棋为后手。

放下棋子A后，若A的8个马步方位（即中国象棋的“马”或国际象棋的“骑士”的“日”字走法）至少存在1个同色的棋子，且当连接A与这些棋子时，其连线不切割已经有的线，则连接。

黑棋的目标是连出一条从X轴的0列到N列的路；

白棋的目标是连出一条从Y轴的0行到N行的路。

就是说某一方要赢棋，当且仅当其把自己的两个“终域”连接在一起，完全阻隔对方的连接。

按照以上规则，判断黑棋所走的最后一步是否为赢棋的一步。


## 解题思路

比较麻烦的**模拟**，但是难度不大，难点主要在于判断连线是否相交。

![](/img/01.png)

如上图放下一只棋子后，先检查其附近的8个方位是否存在同色棋子，若存在，则检查是否允许与该同色棋子连线。

检查连线方法如下图，以30度的方位为例：

![](/img/02.png)

如上图，当放下新棋子后，若检测到30度方位存在与其同色的棋子，则在连接蓝线之前，先检查是否已存在9条红色的线，当且仅当这9条红线都不存在时，才允许连接蓝线。

其他7个方位也是同样做法。


最后要判断黑棋的最后一步是不是为赢棋的一步，只需要做**两次BFS**：

- **第一次BFS**：以黑棋的0终域为起点，寻找是否存在到N终域的路。
- **第二次BFS**：先删去最后一步棋，再以黑棋的0终域为起点，寻找是否存在到N终域的路。
- **当第一次BFS结果为true，第二次BFS结果为false时，则说明黑棋的最后一步为赢棋的一步**。


## 测试数据

- 来源（已失效）：[Mid-Central USA 2005](http://mcpc.cigas.net/archives.html)
- 输入：[input](/testdata/input.dat)
- 输出：[output](/testdata/output.dat)


## AC 源码


```c
//Memory Time 
//340K    0MS 

#include<iostream>
using namespace std;

const int size=23;
const int num=251;
int n;  //chess size
int m;  //move steps
int lastx,lasty;
int map[size][size];  //对坐标为(x,y)的棋子编号
bool link[num][num];  //标记某两个编号的棋子是否有连线

int posx[]={0,-1,-2,-2,-1,1,2,2,1};   //对应于(x,y)的八个方位
int posy[]={0,2,1,-1,-2,-2,-1,1,2};

typedef class chess
{
	public:
	int color;   //黑棋:1 白棋:0
	int r,c;
	int connet[8];  //记录与当前棋子直接相连的棋子编号
	int pc;  //connet的指针

	chess()
	{
		color=-1;
		pc=0;
	}
}PEG;

void LinePeg(PEG* peg,int i);  //把棋子peg[i]与与其相邻的八个方位的同色棋子连线
bool CheckWin(PEG* peg,bool flag);  //BFS,检查先手(黑棋)是否把终域连接在一起(赢家)

int main(void)
{
	while(cin>>n>>m)
	{
		if(!n && !m)
			break;

		memset(map,0,sizeof(map));
		memset(link,false,sizeof(link));
		PEG* peg=new PEG[m+1];
		
		for(int i=1;i<=m;i++)
		{
			int x,y;
			cin>>x>>y;
			map[x][y]=i;  //编号记录
			peg[i].r=x;
			peg[i].c=y;

			if(i%2)
				peg[i].color=1;  //黑棋
			else
				peg[i].color=0;  //白棋

			if(i==m)  //记录最后一步棋
			{
				lastx=x;
				lasty=y;
			}

			LinePeg(peg,i);  //把最新下的棋子与其附近的同色棋子相连
		}
		if(CheckWin(peg,true) && !CheckWin(peg,false))
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;
	}
	return 0;
}

/*把棋子(x,y)与与其相邻的八个方位的同色棋子连线*/
void LinePeg(PEG* peg,int i)
{
	int color=peg[i].color;
	for(int k=1;k<=8;k++)
	{
		int r=peg[i].r+posx[k];
		int c=peg[i].c+posy[k];
		
		if(r>=0 && r<=n && c>=0 && c<=n)  //检查边界
		{
			if(map[r][c] && peg[ map[r][c] ].color==color)  //检查颜色
			{
				switch(k)  //"日"字对角连线
				{
				    case 1:  //30度方位
					{
						if(link[ map[r][c-2] ][ map[r+1][c] ])
							break;
						if(c-3>=0 && link[ map[r][c-3] ][ map[r+1][c-1] ])
							break;
						if(c+1<=n && link[ map[r][c-1] ][ map[r+1][c+1] ])
							break;
						if(r-1>=0)
						{
							if(link[ map[r-1][c-2] ][ map[r+1][c-1] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r+1][c] ])
								break;
							if(link[ map[r-1][c] ][ map[r+1][c-1] ])
								break;
						}
						if(r+2<=n)
						{
							if(link[ map[r+2][c-2] ][ map[r][c-1] ])
								break;
							if(link[ map[r+2][c-1] ][ map[r][c-2] ])
								break;
							if(link[ map[r+2][c] ][ map[r][c-1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 2:  //60度方位
					{
						if(link[ map[r][c-1] ][ map[r+2][c] ])
							break;
						if(r-1>=0 && link[ map[r-1][c-1] ][ map[r+1][c] ])
							break;
						if(r+3<=n && link[ map[r+1][c-1] ][ map[r+3][c] ])
							break;
						if(c-2>=0)
						{
							if(link[ map[r][c-2] ][ map[r+1][c] ])
								break;
							if(link[ map[r+1][c-2] ][ map[r+2][c] ])
								break;
							if(link[ map[r+2][c-2] ][ map[r+1][c] ])
								break;
						}
						if(c+1<=n)
						{
							if(link[ map[r][c-1] ][ map[r+1][c+1] ])
								break;
							if(link[ map[r+1][c-1] ][ map[r][c+1] ])
								break;
							if(link[ map[r+1][c-1] ][ map[r+2][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 3:  //120度方位
					{
						if(link[ map[r][c+1] ][ map[r+2][c] ])
							break;
						if(r-1>=0 && link[ map[r-1][c+1] ][ map[r+1][c] ])
							break;
						if(r+3<=n && link[ map[r+1][c+1] ][ map[r+3][c] ])
							break;
						if(c-1>=0)
						{
							if(link[ map[r][c-1] ][ map[r+1][c+1] ])
								break;
							if(link[ map[r+1][c-1] ][ map[r][c+1] ])
								break;
							if(link[ map[r+2][c-1] ][ map[r+1][c+1] ])
								break;
						}
						if(c+2<=n)
						{
							if(link[ map[r+1][c] ][ map[r][c+2] ])
								break;
							if(link[ map[r+2][c] ][ map[r+1][c+2] ])
								break;
							if(link[ map[r+1][c] ][ map[r+2][c+2] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 4:  //150度方位
					{
						if(link[ map[r][c+2] ][ map[r+1][c] ])
							break;
						if(c-1>=0 && link[ map[r+1][c-1] ][ map[r][c+1] ])
							break;
						if(c+3<=n && link[ map[r+1][c+1] ][ map[r][c+3] ])
							break;
						if(r-1>=0)
						{
							if(link[ map[r-1][c] ][ map[r+1][c+1] ])
								break;
							if(link[ map[r-1][c+1] ][ map[r+1][c] ])
								break;
							if(link[ map[r-1][c+2] ][ map[r+1][c+1] ])
								break;
						}
						if(r+2<=n)
						{
							if(link[ map[r][c+1] ][ map[r+2][c] ])
								break;
							if(link[ map[r][c+1] ][ map[r+2][c+2] ])
								break;
							if(link[ map[r][c+2] ][ map[r+2][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 5:  //210度方位
					{
						if(link[ map[r-1][c] ][ map[r][c+2] ])
							break;
						if(c-1>=0 && link[ map[r-1][c-1] ][ map[r][c+1] ])
							break;
						if(c+3<=n && link[ map[r-1][c+1] ][ map[r][c+3] ])
							break;
						if(r-2>=0)
						{
							if(link[ map[r-2][c] ][ map[r][c+1] ])
								break;
							if(link[ map[r-2][c+1] ][ map[r][c+2] ])
								break;
							if(link[ map[r-2][c+2] ][ map[r][c+1] ])
								break;
						}
						if(r+1<=n)
						{
							if(link[ map[r][c] ][ map[r-1][c+1] ])
								break;
							if(link[ map[r+1][c+1] ][ map[r-1][c] ])
								break;
							if(link[ map[r+1][c+2] ][ map[r-1][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 6:  //240度方位
					{
						if(link[ map[r-2][c] ][ map[r][c+1] ])
							break;
						if(r-3>=0 && link[ map[r-3][c] ][ map[r-1][c+1] ])
							break;
						if(r+1<=n && link[ map[r-1][c] ][ map[r+1][c+1] ])
							break;
						if(c-1>=0)
						{
							if(link[ map[r-2][c-1] ][ map[r-1][c+1] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r][c+1] ])
								break;
							if(link[ map[r][c-1] ][ map[r-1][c+1] ])
								break;
						}
						if(c+2<=n)
						{
							if(link[ map[r-1][c] ][ map[r-2][c+2] ])
								break;
							if(link[ map[r-2][c] ][ map[r-1][c+2] ])
								break;
							if(link[ map[r-1][c] ][ map[r][c+2] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 7:  //300度方位
					{
						if(link[ map[r-2][c] ][ map[r][c-1] ])
							break;
						if(r-3>=0 && link[ map[r-3][c] ][ map[r-1][c-1] ])
							break;
						if(r+1<=n && link[ map[r-1][c] ][ map[r+1][c-1] ])
							break;
						
						if(c-2>=0)
						{
							if(link[ map[r-2][c-2] ][ map[r-1][c] ])
								break;
							if(link[ map[r-1][c-2] ][ map[r-2][c] ])
								break;
							if(link[ map[r][c-2] ][ map[r-1][c] ])
								break;
						}
						if(c+1<=n)
						{
							if(link[ map[r-1][c-1] ][ map[r-2][c+1] ])
								break;
							if(link[ map[r][c-1] ][ map[r-1][c+1] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r][c+1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
					case 8:  //330度方位
					{
						if(link[ map[r][c-2] ][ map[r-1][c] ])
							break;
						if(c-3>=0 && link[ map[r][c-3] ][ map[r-1][c-1] ])
							break;
						if(c+1<=n && link[ map[r][c-1] ][ map[r-1][c+1] ])
							break;
						if(r-2>=0)
						{
							if(link[ map[r-2][c-2] ][ map[r][c-1] ])
								break;
							if(link[ map[r-2][c-1] ][ map[r][c-2] ])
								break;
							if(link[ map[r-2][c] ][ map[r][c-1] ])
								break;
						}
						if(r+1<=n)
						{
							if(link[ map[r-1][c-1] ][ map[r+1][c-2] ])
								break;
							if(link[ map[r-1][c-1] ][ map[r+1][c] ])
								break;
							if(link[ map[r-1][c] ][ map[r+1][c-1] ])
								break;
						}

						int a=map[peg[i].r][peg[i].c];
						int b=map[r][c];
						peg[a].connet[peg[a].pc++]=b;
						peg[b].connet[peg[b].pc++]=a;
						link[a][b]=link[b][a]=true;
						break;
					}
				}
			}
		}
	}
	return;
}

/*BFS,检查先手(黑棋)是否把终域连接在一起(赢家)*/
bool CheckWin(PEG* peg,bool flag)
{
	int NUM;
	if(!flag)  //通过舍弃最后一步棋，检查最后一步棋是否为决定赢棋的一步
		NUM=map[lastx][lasty];

	for(int k=0;k<=n;k++)
	{
		int p=map[0][k];
		if(p && p!=NUM && peg[p].color==1)
		{
			int queue[num];
			bool vist[num]={false};
			int head=0;
			int tail=0;
			queue[tail++]=p;
			vist[p]=true;

			while(head<tail)
			{
				int s=queue[head++];
				if(peg[s].r==n)
					return true;

				for(int i=0;i<peg[s].pc;i++)
				{
					int x=peg[s].connet[i];
					if(!vist[x])
					{
						vist[x]=true;
						if(!flag && x==NUM)
							continue;
						queue[tail++]=x;
					}
				}
			}
		}
	}
	return false;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

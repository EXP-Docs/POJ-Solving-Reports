## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3009] [[Curling 2.0](http://poj.org/problem?id=3009)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: DFS]

------

## 问题描述

哈哈，玩过“**GBA口袋怪兽**”的同学看到这题都应该非常容易理解了，“游戏也不过是这样写出来的” 哈!


题意不难懂，我大致翻译一下：

就是要求把一个冰壶从起点“2”用最少的步数移动到终点“3”

其中0为移动区域，1为石头区域，冰壶一旦想着某个方向运动就不会停止，也不会改变方向（想想冰壶在冰上滑动），除非冰壶撞到石头1 或者 到达终点 3


**注意的是**：

冰壶撞到石头后，冰壶会停在石头前面，此时（静止状态）才允许改变冰壶的运动方向，而该块石头会破裂，石头所在的区域由1变为0. 也就是说，冰壶撞到石头后，并不会取代石头的位置。

终点是一个摩擦力很大的区域，冰壶若到达终点3，就会停止在终点的位置不再移动。


## 解题思路

其实与其说这是深搜题，我觉得更像模拟题。。。

要先明确：

- **0为滑动区域**
- **1为石头区域**
- **2为起点，也是可滑动区域**
- **3为终点，不可滑动区域**

以此为前提，得到以下原则：

- 起点为“2”，也是一个可滑动的区域，所以标记起点位置之后，可以把起点当做0
- 注意区分冰壶是运动的还是静止的，若是静止的话，旁边1格有石头是不能走的。
- 输出冰壶从2到3的最短路，如果最短路的步数大于10（不包括10），视作无法走到终点（**其实这是用来剪枝的**）
- 滑动过程中冰壶不允许出界


基于上面的原则，不难发现：

- （1）所谓的“**走一步**”，就是**指冰壶从一个静止状态到下一个静止状态**，就是说冰壶在运动时经过的“格数”不视作“步数”，也就是说冰壶每次移动的距离都是不定的。
- （2）还有就是由于石头会因为冰壶的碰撞而消失，因此冰壶每“走一步”，场地的环境就会改变一次。
- （3）基于（2），可以发现本题虽然是要找 “最短路”，但是BFS几乎不可能，因为每“走一步”，场地的状态就要改变一次；而如果该步不满足要求，又要求把场地的状态还原到前一步，这只有DFS能做到。
- （4）基于（3），DFS不是BFS，不能简单地用它来找最短路，必须要把所有可能的路一一找出来，再逐一比较它们的步数才能确定最短。但题目值允许1000MS，此时就面临一个超时的问题。所以题目才同时给出“步数超过10则视为失败”的条件，这是用来**剪枝**的


------------


有了上面的分析，就能最终确定本题的解法了，**有2种方法**：

- **DFS+Vector+剪枝**
- **DFS+回溯+剪枝**

 
但是由于POJ对STL的“兼容性”很差，我用STL就没见过不TLE的题。。。这题也一样，所以不推荐，其实Vector是很好用的，利用它的特性可以在DFS返回上一步时，自动还原场地状态，而回溯法则需要手动还原场地状态（其实也就8行代码）


**DFS用于寻找路径，回溯（或Vector）用于还原棋盘状态，剪枝用于优化**


另外注意的时，如果把冰壶定义为“动静”两种状态，那么搜索时就可以以“格”为单位，+1搜索，详细可以看我的程序，我感觉这样比较简单。我感觉每步都用for找移动的格数会非常麻烦。


## AC 源码

### 解题方法一：DFS+回溯+剪枝

```c
/*DFS+回溯+剪枝*/

//Memory Time 
//188K   329MS 

#include<iostream>
using namespace std;

const int inf=11;

typedef class
{
	public:
		int r,c;     //冰壶当前位置
		bool status; //status冰壶当前状态：运动true ,静止false
}SE;

SE s,e;   //记录冰壶起止点
int w,h;  //场地size
int MinStep;  //最短路
int board[30][30];  //场地

void DFS(int i,int j,bool status,int direction,int step,bool flag)  
{ //direction:冰壶当前运动方向  North:0  West:1  South:2  East:3 
  //flag:是否消除direction方向下一格位置的石头

	if(step>10)   //剪枝，超过10步的走法就不再考虑了
		return;

	if(board[i][j]==3)   //终点
	{
		if(MinStep>step)
			MinStep=step;
		return;
	}

	if(flag)  //消除石头
	{
		switch(direction)
		{
		    case 0: {board[i-1][j]=0; break;}
	    	case 1: {board[i][j-1]=0; break;}
			case 2: {board[i+1][j]=0; break;}
			case 3: {board[i][j+1]=0; break;}
		}
	}
	
	if(!status)  //静止
	{
		if(i-1>=1 && (board[i-1][j]==0 || board[i-1][j]==3))  //North
			DFS(i-1,j,true,0,step+1,false);

		if(j-1>=1 && (board[i][j-1]==0 || board[i][j-1]==3))  //West
			DFS(i,j-1,true,1,step+1,false);

		if(i+1<=h && (board[i+1][j]==0 || board[i+1][j]==3))  //South
			DFS(i+1,j,true,2,step+1,false);

		if(j+1<=w && (board[i][j+1]==0 || board[i][j+1]==3))  //East
			DFS(i,j-1,true,3,step+1,false);
	}
	else if(status)  //运动
	{
		switch(direction)
		{
	        case 0:
				{
					if(i-1<1)  //预判下一步是否越界
						return;
					else
					{
						if(board[i-1][j]==0)          //下一位置为0且不越界，继续运动
							DFS(i-1,j,true,0,step,false);
						else if(board[i-1][j]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,0,step,true);
						else if(board[i-1][j]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i-1,j,false,0,step,false);
					}

					break;
				}
			case 1:
				{
					if(j-1<1)  //预判下一步是否越界
						return;
					else
					{
						if(board[i][j-1]==0)          //下一位置为0且不越界，继续运动
							DFS(i,j-1,true,1,step,false);
						else if(board[i][j-1]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,1,step,true);
						else if(board[i][j-1]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i,j-1,false,1,step,false);
					}

					break;
				}
			case 2:
				{
					if(i+1>h)  //预判下一步是否越界
						return;
					else
					{
						if(board[i+1][j]==0)          //下一位置为0且不越界，继续运动
							DFS(i+1,j,true,2,step,false);
						else if(board[i+1][j]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,2,step,true);
						else if(board[i+1][j]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i+1,j,false,2,step,false);
					}

					break;
				}
			case 3:
				{
					if(j+1>w)  //预判下一步是否越界
						return;
					else
					{
						if(board[i][j+1]==0)          //下一位置为0且不越界，继续运动
							DFS(i,j+1,true,3,step,false);
						else if(board[i][j+1]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(i,j,false,3,step,true);
						else if(board[i][j+1]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(i,j+1,false,3,step,false);
					}

					break;
				}
		}
	}

	if(flag)  //回溯前还原石头，即还原上一步的棋盘状态
	{
		switch(direction)
		{
		    case 0: {board[i-1][j]=1; break;}
	    	case 1: {board[i][j-1]=1; break;}
			case 2: {board[i+1][j]=1; break;}
			case 3: {board[i][j+1]=1; break;}
		}
	}

	return;
}

int main(void)
{
	while(cin>>w>>h)
	{
		if(!w && !h)
			break;

		/*Structure the Board*/

		MinStep=inf;
		
		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++)
			{
				cin>>board[i][j];

				if(board[i][j]==2)
				{
					s.r=i;
					s.c=j;
				    s.status=false;
					board[i][j]=0;  //记录起点位置后，把它作为0处理
				}
				if(board[i][j]==3)  //终点是特别位置，冰壶经过或到达该格都会停止
				{
					e.r=i;
					e.c=j;
				}
			}

		/*Search the min path*/

		DFS(s.r , s.c , s.status , 0 , 0 , false);

		if(MinStep<=10)
			cout<<MinStep<<endl;   //DFS里面虽然剪枝了，但是可能把全部走法都剪了，因此还是要判断
		else
			cout<<-1<<endl;

	}
	return 0;
}
```

### 解题方法二：~~DFS+Vector+剪枝~~ （TLE）

```c
/*DFS+Vector+剪枝*/

//TLE
//万恶的POJ好像和STL不兼容，剪枝还是超时
//vector的优势无法发挥啊。。。

#include<iostream>
#include<vector>
using namespace std;

const int inf=11;

typedef class
{
	public:
		int r,c;     //冰壶当前位置
		bool status; //status冰壶当前状态：运动true ,静止false
}SE;

SE s,e;   //记录冰壶起止点
int w,h;  //场地size
int MinStep;  //最短路

void DFS(vector<vector<int> >board,int i,int j,bool status,int direction,int step,bool flag)  
{ //direction:冰壶当前运动方向  North:0  West:1  South:2  East:3 
  //flag:是否消除direction方向下一格位置的石头

	if(step>10)   //剪枝，超过10步的走法就不再考虑了
		return;

	if(board[i][j]==3)   //终点
	{
		if(MinStep>step)
			MinStep=step;
		return;
	}

	if(flag)  //消除石头
	{
		switch(direction)
		{
		    case 0: {board[i-1][j]=0; break;}     //board用vector表示的目的就是为了在当前步删除某位置的石头时
	    	case 1: {board[i][j-1]=0; break;}     //前一步并不会删除该位置的石头
			case 2: {board[i+1][j]=0; break;}
			case 3: {board[i][j+1]=0; break;}
		}
	}
	
	if(!status)  //静止
	{
		if(i-1>=1 && (board[i-1][j]==0 || board[i-1][j]==3))  //North
			DFS(board,i-1,j,true,0,step+1,false);

		if(j-1>=1 && (board[i][j-1]==0 || board[i][j-1]==3))  //West
			DFS(board,i,j-1,true,1,step+1,false);

		if(i+1<=h && (board[i+1][j]==0 || board[i+1][j]==3))  //South
			DFS(board,i+1,j,true,2,step+1,false);

		if(j+1<=w && (board[i][j+1]==0 || board[i][j+1]==3))  //East
			DFS(board,i,j-1,true,3,step+1,false);
	}
	else if(status)  //运动
	{
		switch(direction)
		{
	        case 0:
				{
					if(i-1<1)  //预判下一步是否越界
						return;
					else
					{
						if(board[i-1][j]==0)          //下一位置为0且不越界，继续运动
							DFS(board,i-1,j,true,0,step,false);
						else if(board[i-1][j]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(board,i,j,false,0,step,true);
						else if(board[i-1][j]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(board,i-1,j,false,0,step,false);
					}

					break;
				}
			case 1:
				{
					if(j-1<1)  //预判下一步是否越界
						return;
					else
					{
						if(board[i][j-1]==0)          //下一位置为0且不越界，继续运动
							DFS(board,i,j-1,true,1,step,false);
						else if(board[i][j-1]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(board,i,j,false,1,step,true);
						else if(board[i][j-1]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(board,i,j-1,false,1,step,false);
					}

					break;
				}
			case 2:
				{
					if(i+1>h)  //预判下一步是否越界
						return;
					else
					{
						if(board[i+1][j]==0)          //下一位置为0且不越界，继续运动
							DFS(board,i+1,j,true,2,step,false);
						else if(board[i+1][j]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(board,i,j,false,2,step,true);
						else if(board[i+1][j]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(board,i+1,j,false,2,step,false);
					}

					break;
				}
			case 3:
				{
					if(j+1>w)  //预判下一步是否越界
						return;
					else
					{
						if(board[i][j+1]==0)          //下一位置为0且不越界，继续运动
							DFS(board,i,j+1,true,3,step,false);
						else if(board[i][j+1]==1)          //下一位置为1且不越界，停止运动，并消除下一位置的石头
							DFS(board,i,j,false,3,step,true);
						else if(board[i][j+1]==3)          //下一位置为3且不越界，运动到位置3后停止运动，游戏结束
							DFS(board,i,j+1,false,3,step,false);
					}

					break;
				}
		}
	}

	return;
}

int main(void)
{
	while(cin>>w>>h)
	{
		if(!w && !h)
			break;

		/*Structure the Board*/

		MinStep=inf;
		vector<vector<int> >board(h+1,vector<int>(w+1));

		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++)
			{
				cin>>board[i][j];

				if(board[i][j]==2)
				{
					s.r=i;
					s.c=j;
				    s.status=false;
					board[i][j]=0;  //记录起点位置后，把它作为0处理
				}
				if(board[i][j]==3)  //终点是特别位置，冰壶经过或到达该格都会停止
				{
					e.r=i;
					e.c=j;
				}
			}

		/*Search the min path*/

		DFS(board , s.r , s.c , s.status , 0 , 0 , false);

		if(MinStep<=10)
			cout<<MinStep<<endl;   //DFS里面虽然剪枝了，但是可能把全部走法都剪了，因此还是要判断
		else
			cout<<-1<<endl;

		/*Relax*/

	//	board.swap(vector<vector<int> >());      //POJ好像禁用swap()
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

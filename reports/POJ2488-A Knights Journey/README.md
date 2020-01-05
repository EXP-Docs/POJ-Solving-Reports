## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [2488] [[A Knight's Journey](http://poj.org/problem?id=2488)]

> [Time: 1000MS] [Memory: 65536K] [难度: 初级] [分类: DFS]

------

## 问题描述

给出一个国际棋盘的大小，判断马能否不重复的走过所有格，并记录下其中按字典序排列的第一种路径。

经典的“骑士游历”问题，**DFS**水题一道


## 解题思路


难度不大，但要**注意**的地方有3点：

- 国际象棋的棋盘，行为数字p；列为字母q
- 网上有同学说 这道题最后一组数据后是有空行的会PE...，我测试过，不会的，能AC
- 题目要求以"lexicographically"方式输出，也就是字典序...要以字典序输出路径，那么搜索的方向（我的程序是 `path()` 函数）就要以特殊的顺序排列了...这样只要每次从 `dfs(A,1)` 开始搜索，第一个成功遍历的路径一定是以字典序排列...

**下图是搜索的次序，马的位置为当前位置，序号格为测试下一步的位置的测试先后顺序**

**按这个顺序测试，那么第一次成功周游的顺序就是字典序**

![](/reports/POJ2488-A%20Knights%20Journey/img/01.png)

## AC 源码


```c
//Memory Time 
//240K   32MS 

#include<iostream>
using namespace std;

typedef class
{
	public:
		int row;
		char col;
}location;

int p,q;  //chess size = p*q
          //数字是行p，字母是列q
bool chess['Z'+1][27];

int x,y;  //返回值
void path(int i,int j,int num)  //ij为骑士当前在棋盘的位置 
{                               //num为骑士即将要跳到的位置序号
	switch(num)
	{
     	case 1: {x=i-1; y=j-2; break;}     //注意这个尝试跳的顺序不能错   
		case 2: {x=i+1; y=j-2; break;}     //因为题目要求是字典序lexicographically输出
		case 3: {x=i-2; y=j-1; break;}     //这个顺序错了，必定WA
		case 4: {x=i+2; y=j-1; break;}
		case 5: {x=i-2; y=j+1; break;}
		case 6: {x=i+2; y=j+1; break;}
		case 7: {x=i-1; y=j+2; break;}
		case 8: {x=i+1; y=j+2; break;}
	}
	return;
}

bool DFS(location* way,int i,int j,int step)
{
	chess[i][j]=true;
	way[step].row=i;
	way[step].col=j;
	if(step==way[0].row)
		return true;

	for(int k=1;k<=8;k++)   //骑士从当前位置尝试跳到其他位置
	{
		path(i,j,k);
		int ii=x,jj=y;
		if(!chess[ii][jj] && ii>=1 && ii<=p && jj>='A' && jj<='A'+q-1)
			if(DFS(way,ii,jj,step+1))
				return true;
	}
	
	chess[i][j]=false;  //能执行到这步，说明前面跳的8步都不符合要求
	return false;       //即当前位置是错误位置，擦除记录返回上一步
}

int main(void)
{
	int test;
	cin>>test;
	int t=1;
	while(t<=test)
	{
		/*Initial*/

		memset(chess,false,sizeof(chess));

		cin>>p>>q;
		if(p==1 && q==1)      //范围缩窄，不要也能AC
		{
			cout<<"Scenario #"<<t++<<':'<<endl;
			cout<<"A1"<<endl<<endl;
			continue;
		}
		if(p*q>26 || p>=9 || q>=9 || p<=2 || q<=2)        //范围缩窄，不要也能AC
		{
			cout<<"Scenario #"<<t++<<':'<<endl;
			cout<<"impossible"<<endl<<endl;
			continue;
		}
		
		location* way=new location[p*q+1];   //记录走过的位置坐标
		way[0].row=p*q;   //记录总步数(棋盘总格子数)

		/*DFS*/

		bool flag=false;
		for(int j='A';j<='A'+q-1;j++)
		{
			for(int i=1;i<=p;i++)
				if(DFS(way,i,j,1))
				{
					cout<<"Scenario #"<<t++<<':'<<endl;
					
					for(int k=1;k<=way[0].row;k++)
						cout<<way[k].col<<way[k].row;
					cout<<endl<<endl;
					flag=true;
					break;
				}
				if(flag)
					break;
		}

		if(!flag)
		{
			cout<<"Scenario #"<<t++<<':'<<endl;
			cout<<"impossible"<<endl<<endl;
		}
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

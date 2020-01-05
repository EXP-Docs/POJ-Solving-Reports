## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [3373] [[Changing Digits](http://poj.org/problem?id=3373)]

> [Time: 3000MS] [Memory: 65536K] [难度: 中级] [分类: 记忆化搜索]

------

## 问题描述

给出2个整数n（n<10^100）和k（k<10000），求满足以下条件的整数m

- 1、m与n位数相同
- 2、m能被k整除
- 3、满足以上两点时，m和n在相同位置的地方，数字不同的个数最少
- 4、满足以上三点时，m值最小


## 解题思路

这题解法很多，有人用**DP**，有人用**记忆化搜索**，有人**搜索+强剪枝**。

POJ分类把这题归入“记忆化搜索”，但是我不推荐，原因在于直接写出记忆化搜索算法去解题不容易，**不先用DP做出来，记忆化搜索很难实现**。

我用的是**DFS+强剪枝**。

我做这题的时候，基本无任何思路，本来想参考一下网上前辈的做法，但基本全部都是乱七八糟东拼西凑胡说八道，我下面根据我自己的思路说一下清晰的解题过程，这个思路是借鉴了一下别人的做法，但是绝对清晰。


------


下面进入正题：


**1、问题的有解性：**

设 `n%k=n_MODk`，由抽屉原理可知，在 `[0,k-1]` 这k个顺序自然数中，必有一个数与 `n_MODk` 是同余类。而依题意知 `k<=n`，那么说明这题必有解。

但是这个只能证明DFS是可以寻找到解的，但是不能对解题带来任何帮助。

我不知道是哪个那么缺德，在网上散播谣言说“由于k最多只有5位，根据抽屉原理我们最多只要改变n最后5位数字就能找到答案”。

这是绝对错误的。因为这种做法无法满足条件4。

由于此，可能有同学做这题时，为了省时间，只搜索n的最后 `len(k)` 位，但总得不到结果却不知为何。这种做法错在：当把n低位数字中的1个改小后能够使得 `n_MODk==0`，但若把n高位数字中的1个改小后同样能够使得 `n_MODk==0`，那么为了满足条件4，必然是取后者，抽屉原理的“只要改变n最后5位数字”却不能满足这个条件。

正确的说法应该是“**最多改变n中的5位数字就能得到解**”，但实际解题时没必要应用**抽屉原理**，由于DFS搜索到的第一个解必为最优，因此AllowNum从1个到 `len(n)` 个逐个枚举即可，这样可以避免讨论 `len(n)` 是否大于5。


------

**2、寻解的有序性：**

首先必须注意，这题的条件具有层次性，条件1优先于条件2，条件2优先于条件3，条件3优先于条件4,。而由于数据量很大，为了节省搜索时间，我们必须保证DFS搜索到的第一个答案就是最优，因此这就无形之中**规定了DFS的搜索方向**。


------


**3、高精度处理：**

n的位数最多为101位，以往求n_MODk的方法都是利用**同余模公式**，从高位开始向低位逐位求模，但是本题为了后续DFS需要，用了一个稍微改变的方式求 `n_MODk`。

先把n倒序存放。

定义数组 `mod[101][10]`，`mod[i][j]=((10^i)*j)%k`，先求出：

```
0   1    2    3    4    5    6    7    8    9   （%k）

0   10   20   30   40   50   60   70   80   90  （%k）

0   100  200  300  400  500  600  700  800  900 （%k）

.....
```

通过**递推式** `mod[i][j]=(mod[i-1][j]*10)%k;` 就能避免n次方的运算，节省时间。

由此 `mod[][]` 就能组合出任意 `len(n)` 位内的整数对k求模后的值。那么利用同余模公式就能求得 `n_MODk`。

------


**4、DFS搜索方法：**

```c
bool DFS(int pos, int RestNum, int m_MODk);
```

传参有3个：`pos`，`RestNum`，`m_MODk`

- `Pos`：当前搜索区间为 `[0,pos]`
- `RestNum`：在区间 `[0,pos]` 中剩余 允许改变的数字的个数，个数从1个到 `len(n)`个枚举，保证搜索到解时，n与m在相同位置处不同数字的个数是最少的（条件3）。
- `m_MODk`：当前数字串m对k求模的值，初始化为 `n_MODk`。


**入口处理**：

```c
for(int AllowNum=1;AllowNum<=len;AllowNum++) {
       if(DFS(len-1,AllowNum,n_MODk)) {
		    break;
	   }
}
```

每次入口都有pos=len-1，是为了保证搜索区间最大。

- （1）搜索时先搜索比n小的数字，此时为了搜索到的解m是最小的，应该从区间 `[0,pos]` 的第pos位开始向第0位搜索，因为在相同RestNum情况下，把高位数字变小所得到的m值更小。
- （2）当（1）无解时，搜索比n大的数字，此时为了搜索到的解m是最小的，应该从区间 `[0,pos]` 的第0位开始向第pos位搜索，因为在相同RestNum情况下，把低位数字变大所得到的m值更小。


**出口处理**：

- `m_MODk==0` 返回true
- `RestNum==0` 返回 false


------


**5、关于第三个参数值 `m_MODk` 的传递：**

由于数字串m随着搜索的深度时刻变化，若每次变化后，再按求 `n_MODk` 的方法重新求m_MODk是相当浪费时间的。此时就要利用同余模公式和mod数组。

- 搜索比n小的数字时所用到的同余模公式为： `(a-b)%k=(a%k - b%k)%k`
- 搜索比n大的数字时所用到的同余模公式为： `(a+b)%k=(a%k + b%k)%k`


（1）搜索比n小的数字时，当把m的第i位数字 `m[i]` 改为j时，我们已经有 `((10^i)*m[i])%k` 的值存放在数组 `mod[i][m[i]]` 中，又有 `((10^i)*j)%k` 的值存放在数组 `mod[i][j]` 中，那么把m值改小前后的变化值为（ `mod[i][m[i]]- mod[i][j]` ），然后我们又知道m改变前的模k值为 `m_MODk` 。那么只需把m改变前的 `m_MODk` 减去变化值（ `mod[i][m[i]]- mod[i][j]` ），再对k取模，就是新的 `m_MODk` 值，我们令其等于res。

而为了避免 `m_MODk < (mod[i][m[i]]- mod[i][j])` 而出现负数，我们应该增加一个 `+k` 修正处理，那么具体公式如下：

`res=(m_MODk-(mod[i][m[i]]-mod[i][j])+k)%k;`

以数字 5234，`k=25` 为例，在本算法中数组m实际存放为数字的倒序4321，首位为第0位的“4”，同样 `mod[][]` 存放的是倒序数据。

数据存放： `m[]=4325`, `k=27`

已知 `m_MODk=5234%27=22`，现在要把m的第3位的“5”修改为更小的“1”，已有 `m[3]=5`，设 `j=1`，即令 `m[3]=j`，显然改变后实际的变化值为 `5000-1000=4000`

我们现在要求的是m改变后的 `1234%27` 的值，而 `1234%25=(5234%27 – 4000%27)%27`。由于 `5234%27=m_MODk=22` 已知，那么只需求 `4000%27`。

而 `4000%27=（5000%27-1000%27）%27`，显然 `5000%27` 和 `1000%27` 已经保存在 `mod[][]` 中。 `5000%27=mod[3][ m[3] ]` ，`1000%27=mod[3][ j ]`，说到这里应该都了解了。


（2）搜索比n大的数字时，道理差不多，只不过变化值相减的方向要改变。而且由于是 `m_MODK+变化值` ，即不会出现负数，因此无需 `+k` 修正，具体公式如下：

`res=(m_MODk+(mod[i][j]-mod[i][m[i]]))%k;`

------

**6、关于剪枝：**

定义二维数组 `int**  flag`

令 `flag[pos][m_MODk]=RestNum`

当搜索m的位置区间为 `[0,pos]`，且当前数字串m对k取模值为 `m_MODk` 时，

若剩下允许的修改数字的个数只允许修改RestNum个，

则无论如何修改区间 `[0,pos]` 内的数字也无法使得 `m_MODk==0` ，

那么对于同样的pos和 `m_MODk`, 小于RestNum的个数则更加不可能了



## AC 源码


```c
//Memory Time 
//21444K 47MS

#include<iostream>
#include<string>
using namespace std;

class solve
{
	public:
		solve(char* sn,int tk)
		{
			len=strlen(sn);
			k=tk;
			n_MODk=0;

			InitialFlag(len,k);
			PlayTable_Mod();
			Calculation_n_MODk(sn);

			for(int AllowNum=1;AllowNum<=len;AllowNum++)  //枚举允许修改的数字个数
				if(DFS(len-1,AllowNum,n_MODk)) //要保证搜索区间最大
					break;
		}
		~solve()
		{
			for(int i=len-1;i>=0;i--)
				cout<<m[i];
			cout<<endl;

			delete[] flag;
		}
		void InitialFlag(int len,int k);
		void PlayTable_Mod(void);   //打表mod[][]，利用同余模公式
		void Calculation_n_MODk(char* sn);  //计算n%k
		bool DFS(int pos,int RestNum,int m_MODk);

	protected:
		int len;
		int n[101],m[101];
		int k;
		int n_MODk;  //n%k
		int mod[101][10];  //mod[i][j]=((10^i)*j)%k
		int** flag;  //flag[pos][m_MODk]=RestNum
};        /* 
		     当搜索m的位置区间为[0,pos]，且当前数字串m对k取模值为m_MODk时，
			 若剩下允许的修改数字的个数只允许修改RestNum个，
			 则无论如何修改区间[0,pos]内的数字也无法使得m_MODk==0，
			 那么对于同样的pos和m_MODk, 小于RestNum的个数则更加不可能了,这用于剪枝
          */

void solve::InitialFlag(int len,int k)
{
	flag=new int*[len+1];
	for(int i=0;i<=len;i++)
	{
		flag[i]=new int[k];
		memset(flag[i],false,sizeof(int)*k);
	}
	return;
}

void solve::PlayTable_Mod(void)
{
	for(int j=0;j<=9;j++)
		mod[0][j]=j%k;

	for(int i=1;i<len;i++)
		for(int j=0;j<=9;j++)
			mod[i][j]=(mod[i-1][j]*10)%k;
	return;
}

void solve::Calculation_n_MODk(char* sn)
{
	for(int i=0;i<len;i++)
	{
		n[i]=m[i]=sn[len-i-1]-'0';  //倒序n，并转换为数字串
		n_MODk=(n_MODk+mod[i][ n[i] ])%k;  //n%k
	}

	return;
}

bool solve::DFS(int pos,int RestNum,int m_MODk)
{
	if(m_MODk==0)
		return true;

	if(RestNum==0 || pos<0)
		return false;

	if(RestNum <= flag[pos][m_MODk])  //剪枝
		return false;

	int i,j;

	for(i=pos;i>=0;i--)  //枚举比n小的数m，且m要尽可能小，则从高位开始
		for(j=0;j<n[i];j++)
		{
			if(i==len-1 && j==0)  //m最高位不为0
				continue;

			int res=(m_MODk-(mod[i][m[i]]-mod[i][j])+k)%k;
			int tmp=m[i];
			m[i]=j;
            //i-1即缩减搜索区间
			if(DFS(i-1,RestNum-1,res))
				return true;
			
			m[i]=tmp;
		}

	for(i=0;i<=pos;i++)  //枚举比n大的数m，但m要尽可能小，则从低位开始
		for(j=n[i]+1;j<=9;j++)
		{
			if(i==len-1 && j==0)  //m最高位不为0
				continue;

			int res=(m_MODk+(mod[i][j]-mod[i][m[i]]))%k;  //同余模公式
			int tmp=m[i];
			m[i]=j;
			//i-1即缩减搜索区间
			if(DFS(i-1,RestNum-1,res))
				return true;

			m[i]=tmp;
		}

	flag[pos][m_MODk]=RestNum;  //在区间[0,pos]内只允许修改RestNum个数字无法使得m_MODk==0
	return false;
}

int main(void)
{
	char sn[101];
	int tk;

	while(cin>>sn>>tk)
		solve poj3373(sn,tk);

	return 0;
}
```

------

## 版权声明

　[![Copyright (C) EXP,2016](https://img.shields.io/badge/Copyright%20(C)-EXP%202016-blue.svg)](http://exp-blog.com)　[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
  

- Site: [http://exp-blog.com](http://exp-blog.com) 
- Mail: <a href="mailto:289065406@qq.com?subject=[EXP's Github]%20Your%20Question%20（请写下您的疑问）&amp;body=What%20can%20I%20help%20you?%20（需要我提供什么帮助吗？）">289065406@qq.com</a>


------

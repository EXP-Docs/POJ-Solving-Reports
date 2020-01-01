## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1804] [[Brainman](http://poj.org/problem?id=1804)]

> [Time: 1000MS] [Memory: 30000K] [难度: 初级] [分类: 排序]

------

## 问题描述

和 [POJ2299](/reports/POJ2299-Ultra-QuickSort) 一摸一样，区别在于数据规模缩小了而已


## 解题思路

重申一次要点：

【一个乱序序列的 逆序数】 = 【在只允许相邻两个元素交换的条件下,得到有序序列的交换次数】


**这题有两种解法**：

- ① 若想通过借助**归并排序**求逆序数：时间复杂度O(nlogn)
<br/>　可以参看 [POJ2299](/reports/POJ2299-Ultra-QuickSort) 的思路，几乎一模一样的程序，不过由于规模的缩小，全部变量用int即可
- ② 也可以**直接求逆序数**，无需借助归并排序：时间复杂度O(n^2)
<br/>　把 `S[i]` 和 `s[i+1~n]` 的元素逐个比较，如果 `s[i] > s[k] (k∈[i+1,n])` 则逆序数 `t++`


## AC 源码

### 解题方法一：归并排序

```c
/*借助Mergesort求逆序数O(nlogn)*/

//Memory Time 
//228K   172MS 

#include<iostream>
using namespace std;

const int inf=1000001;
int t;  //数字序列s[]的逆序数

void compute_t(int* s,int top,int mid,int end)
{
	int len1=mid-top+1;
	int len2=end-mid;

	int* left=new int[len1+2];
	int* right=new int[len2+2];

	int i,j;
	for(i=1;i<=len1;i++)
		left[i]=s[top+i-1];
	left[len1+1]=inf;

	for(j=1;j<=len2;j++)
		right[j]=s[mid+j];
	right[len2+1]=inf;

	i=j=1;
	for(int k=top;k<=end;k++)
		if(left[i]<=right[j])
			s[k]=left[i++];
		else
		{
			s[k]=right[j++];
			t+=len1-i+1;
		}

	delete left;
	delete right;

	return;
}

void mergesort(int* s,int top,int end)
{
	if(top<end)
	{
		int mid=(top+end)/2;
		mergesort(s,top,mid);
		mergesort(s,mid+1,end);
		compute_t(s,top,mid,end);
	}
	return;
}
int main(void)
{
	int test;
	cin>>test;
	for(int p=1;p<=test;p++)
	{
		int n;  //数字序列s[]长度
		cin>>n;

		int* s=new int[n+1];

		for(int i=1;i<=n;i++)
			cin>>s[i];

		t=0;
		mergesort(s,1,n);

		cout<<"Scenario #"<<p<<':'<<endl<<t<<endl<<endl;

		delete s;
	}
	return 0;
}
```

### 解题方法二：直接求逆序数

```c
/*直接求逆序数O(n^2)*/

//Memory Time 
//220K  188MS

#include <iostream>    
using namespace std;

int main(int i,int j)
{
	int test;
	cin>>test;
	for(int p=1;p<=test;p++)
	{
		int n;
		cin>>n;

		int* s=new int[n+1];
		for(i=1;i<=n;i++)
			cin>>s[i];

		int t=0;  //s[]的逆序数
		for(i=1;i<=n-1;i++)   //把S[i]和s[i+1~n]的元素逐个比较
			for(j=i+1;j<=n;j++)
				if(s[i]>s[j])  //如果s[i] > s[j] (j∈[i+1,n]) 
					t++;   //则逆序数t++

		cout<<"Scenario #"<<p<<':'<<endl<<t<<endl<<endl;

		delete s;
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

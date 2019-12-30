## [[POJ](http://poj.org/)] [[INDEX](https://github.com/lyy289065406/POJ-Solving-Reports)] [1001] [[Exponentiation](http://poj.org/problem?id=1001)]

> [Time: 1000MS] [Memory: 10000K] [难度: 初级] [分类: 高精度算法]

------

## 问题描述

无。


## 解题思路

浮点**大数**求幂，水题一道，把“大数乘浮点数”按指数循环就OK了，注意结果的整数部分若为0，则不保留整数部分。小数部分若为0，则不保留小数部分和小数点。


## AC 源码


```c
//Memory Time 
//1232K  0MS 

#include<iostream>
#include<string>
using namespace std;

const int size=1000;  //大数位数

void mult(char* A,char* B,char* ans)
{
	int i,j,k;

	int fract;   //总小数个数
	int dot=-1;  //小数点位置
	for(k=0;A[k]!='\0';k++)
		if(A[k]=='.')
			dot=k;
	int lena=k;
	if(dot==-1)
		fract=0;
	else
		fract=lena-dot-1;

	dot=-1;
	for(k=0;B[k]!='\0';k++)
		if(B[k]=='.')
			dot=k;
	int lenb=k;
	if(dot==-1)
		fract+=0;
	else
		fract+=(lenb-dot-1);  //总小数个数

	int a[size+1]={0};
	int b[size+1]={0};
	int pa=0,pb=0;

	/*倒序*/

	for(i=lena-1;i>=0;i--)
	{
		if(A[i]=='.')
			continue;
		a[pa++]=A[i]-'0';
	}
	for(j=lenb-1;j>=0;j--)
	{
		if(B[j]=='.')     //暂时删除小数点
			continue;
		b[pb++]=B[j]-'0';
	}

	int c[2*size+1]={0};
	int lenc;
	for(pb=0;pb<lenb;pb++)
	{
		int w=0;  //低位到高位的进位
		for(pa=0;pa<=lena;pa++)  // = 为了处理最后的进位
		{
			int temp=a[pa]*b[pb]+w;
			w=temp/10;
			temp=(c[pa+pb]+=temp%10);
			c[lenc=pa+pb]=temp%10;
			w+=temp/10;
		}
	}

	/*倒序，得到没有小数点的ans*/

	for(pa=0,pb=lenc;pb>=0;pb--)
		ans[pa++]=c[pb]+'0';
	ans[pa]='\0';
	lena=pa;

	 /*插入小数点*/

	bool flag=true; //标记是否需要删除小数末尾的0
	if(fract==0)   //小数位数为0，无需插入小数点
		flag=false;
	else if(fract<lena) //小数位数小于ans长度，在ans内部插入小数点
	{
		ans[lena+1]='\0';
		for(i=0,pa=lena;pa>0;pa--,i++)
		{
			if(i==fract)
			{
				ans[pa]='.';
				break;
			}
			else
				ans[pa]=ans[pa-1];
		}
				
	}
	else //小数位数大于等于ans长度，在ans前面恰当位置插入小数点
	{
		char temp[size+1];
		strcpy(temp,ans);
		ans[0]='0';
		ans[1]='.';
		for(int i=0;i<fract-lena;i++)  //补充0
			ans[i+2]='0';
		for(j=i,pa=0;pa<lena;pa++)
			ans[j++]=temp[pa];
		ans[j]='\0';
	}

	/*删除ans小数末尾的0*/

	if(flag)
	{
		lena=strlen(ans);
		pa=lena-1;
		while(ans[pa]=='0')
			ans[pa--]='\0';
		if(ans[pa]=='.')   //小数全为0
			ans[pa--]='\0';
	}

	/*删除ans整数开头的0，但至少保留1个0*/

	pa=0;
	while(ans[pa]=='0')  //寻找ans开头第一个不为0的位置
		pa++;

	if(ans[pa]=='\0')  //没有小数
	{
		ans[0]='0';
		ans[1]='\0';
	}
	else  //有小数
	{
		for(i=0;ans[pa]!='\0';i++,pa++)
			ans[i]=ans[pa];
		ans[i]='\0';
	}
	return;
}

char a[size+1];
char ans[size*size+1];

int main(void)
{
	int b;
	while(cin>>a>>b)
	{
		memset(ans,'\0',sizeof(ans));
		ans[0]='1';
		ans[3]='\0';

		for(int i=1;i<=b;i++)
			mult(a,ans,ans);

		cout<<ans<<endl;
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

#if 0
//冒泡排序
//原理：比较相邻的两个数，如果前者比后者大则进行交换
#include<stdio.h>
#include<stdlib.h>

void bubble(int * arr,int sz);

int main()
{
	int arr[] = {5,4,3,2,1};      //排序后应该为1,2,3,4,5,6,7,8,10,23
	int sz = sizeof(arr)/sizeof(arr[0]);
	bubble(arr,sz);
	return 0;
}

void bubble(int * arr,int sz)
{
	int i,j;
	for(i=0;i<sz-1;i++)
	{
		for(j=0;j<sz-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int tem = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tem;
			}
		}
	}
}

#endif
#if 0
#include<stdio.h>
#include<stdlib.h>

void quick(int *arr,int left,int right);
void swap(int *i,int *j);

int main()
{
	int i = 0;
	int arr[] = {4,3,2,5,6,7,8,23,12,13,16};
	int sz = sizeof(arr)/sizeof(arr[0]);
	quick(arr,0,sz-1);
	printf("排序后：");
	for(i = 0;i<sz;i++)
	{
		printf("%d\n",arr[i]);		
	}
	return 0;
}

void quick(int *arr,int left,int right)
{
	int key = arr[right];
	int i = left;
	int j = right;
	if(left >= right)
	{
		return;
	}
while(i<j)
{
	while(i < j && arr[i] <= key)       //此处再次判断i<j是为了防止在接下来判断arr[i] <= key时访问数组越界
	{
		++i;
	}
	swap(&arr[i],&arr[j]);
	while(i < j && arr[j] >= key)
	{
		--j;
	}
	swap(&arr[j],&arr[i]);
}
swap(&arr[i],&key);
	quick(arr,left,i-1);
	quick(arr,i+1,right);
}


void swap(int* i,int* j)
{
	int temp = *i;
	*i = *j;
	*j = temp;
}
#endif
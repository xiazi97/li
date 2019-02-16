#include<stdio.h>

void HeapInit(int *arr,int sz)
{
	int parent = 0;
	int maxchild;
	int left;
	int right;
	int temp;
	while(1){
	left = parent*2 + 1;
	right = parent*2 + 2;
	if(right > sz)
	{
		return;
	}
	maxchild = left;
	if(arr[right] > arr[left])
	{
		maxchild = right;
	}
	if(arr[parent] > arr[maxchild])
	{
		return;
	}
	temp = arr[parent];
	arr[parent] = arr[maxchild];
	arr[maxchild] = temp;
	parent = maxchild;
}
}

int main()
{
	int arr[] = {4,5,2,6,8,1,10,3};
	int sz = sizeof(arr)/sizeof(arr[0]);
	HeapInit(arr,sz);
	return 0;
}
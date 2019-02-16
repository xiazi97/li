#if 0 
#include<stdio.h>

void selectionsort(int *arr,int sz)
{
	int i,j;
	for(i=0;i<sz;i++)
	{
		for(j=i+1;j<=sz-1;j++)
		{
			if(arr[i] > arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main()
{
	int arr[] = {2,4,7,5,8,10,9,1};
	int sz = sizeof(arr)/sizeof(arr[0]);
	selectionsort(arr,sz);
	return 0;
}
#endif
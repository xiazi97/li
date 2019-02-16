#if 0
#include<stdio.h>

void insertsort(int *arr,int sz)
{
	int i,j;
	for(i=0;i<sz-1;i++)
	{
		for(j=i+1;j>0;j--)
		{
			if(arr[j] < arr[j-1])
			{
				int temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
			}
		}
	}
}

int main()
{
	int arr[] = {5,3,2,7,6,10};
	int sz = sizeof(arr)/sizeof(arr[0]);
	insertsort(arr,sz);
   	return 0;
}
#endif

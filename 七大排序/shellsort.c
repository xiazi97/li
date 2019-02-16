#if 0
#include<stdio.h>

void shellsort(int *arr,int sz)
{
	int gap = sz;
	while(gap > 0){
	int i,j,k;
	gap = gap/2;
	for(i=0;i<gap;i++)
	{
		for(j=i;j<=sz;j+=gap)
		{
			for(k=j-gap;k>0,k-gap>0;k-=gap)
			{
				if(arr[k] > arr[k-gap])
				{
					 int tmp = arr[k];
					 arr[k] = arr[k-gap];
					 arr[k-gap] = tmp;
				}
				break;
			}
		}
	}
	}
}

int main()
{
	int arr[] = {2,4,7,5,8,10,9,1};
	int sz = sizeof(arr)/sizeof(arr[0]);
	shellsort(arr,sz);
	return 0;
}
#endif
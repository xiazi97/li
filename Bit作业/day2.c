//1. �����������α�����ֵ��������ֵ�����ݽ��н����� 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void Swap1(int* a,int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//2. ����������ʱ���������������������ݣ������⣩ 
void Swap2(int a,int b)
{
	a = a + b;
	b = a - b;
	a = a - b;
	printf("%d %d\n",a,b);
}

void Swap3(int a ,int b)
{
	a = a * b;
	b = a /b;
	a = a /b;
	printf("%d %d\n",a,b);
}

void Swap4(int a,int b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	printf("%d %d\n",a,b);
}
//3.��10 �����������ֵ�� 
int MaxTen(int* array,int sz)
{
	int i = 0;
	int max = 0;
	for(i=0;i<sz;i++)
	{
		if(array[max] < array[i])
			max = i;
	}
	return array[max];
}
//4.�����������Ӵ�С����� 

//ð������
void Printf(int *array,int sz)
{
	int i = 0,j = 0;
	int cur = 0;
	for(i=0;i<sz;i++)
	{
		for(j=0;j<sz-i;j++)
		{
			if(array[j] < array[j+1])
			{
				cur = array[j];
				array[j] = array[j+1];
				array[j+1] = cur;
			}
		}
	}
}

//5.�������������Լ����
int divisor1(int a ,int b)
{
	if(a > b)
		return divisor1(a-b,b);
	else if(a < b)
		return divisor1 (a,b-a);
	else
		return a;
}

//շת�����
int divisor2(int a ,int b)
{
	int c = 0;
	while(b)
	{
		c=a%b;
		a=b;
		b=c;
	}
	return a;
}

int main()
{
	/*int  a = 1;
	int  b = 2;
	Swap4(a,b);*/
	/*int array[] = {-1,-2,-3,-9,-5,-4,-7,-6,-12,-8};
	int sz = sizeof(array)/sizeof(int);
	printf("%d\n",MaxTen(array,sz));*/
	//printf("%d\n",divisor2(10,5));
	int array[] = {10,6,9};
	int i = 0;
	int sz = sizeof(array)/sizeof(int);
	Printf(array,sz);
	for(i=0;i<sz;i++)
	{
	printf("%d\n",array[i]);
	}
	system("pause");
	return 0;
}
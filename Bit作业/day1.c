//1. 打印100~200 之间的素数 
//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//
//void IsPrime1()
//{
//	int i = 100;
//	for(i=101;i<200;i++)
//	{
//		int j = 2;
//		for(j=2;j<i;j++)
//		{
//			if(i%j == 0)
//				break;
//		}
//		if(j == i)
//			printf("%d ",i);
//	}
//}
//
//void IsPrime2()
//{
//	int i = 100;
//	for(i=101;i<200;i++)
//	{
//		int j = 2;
//		for(j=2;j<200/2;j++)
//		{
//			if(i%j == 0)
//				break;
//		}
//		if(j >= (i/2))
//			printf("%d ",i);
//	}
//}
//
//void IsPrime3()
//{
//	int i = 100;
//	for(i=101;i<200;i+=2)
//	{
//		int j = 2;
//		for(j=2;j<sqrt(1.0*i);j++)
//		{
//			if(i%j == 0)
//				break;
//		}
//		if(j >= sqrt(1.0*i))
//			printf("%d ",i);
//	}
//}
//
////2. 输出乘法口诀表 
//void mul()
//{
//	int i = 0;
//	for(i=1;i<=9;i++)
//	{
//		int j = 0;
//		for(j=1;j<=i;j++)
//		{
//			int k = i*j;
//			printf( "%d*%d = %2d ",j,i,k);
//		}
//		printf("\n");
//	}
//}
//
//
////3. 判断1000年---2000年之间的闰年
//void IsLeapYear()
//{
//	int year;
//	for (year = 1000; year <= 2000; year++)
//	{
//		 if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0 )
//		{
//			printf("%d ", year);
//		}
//	}
//}
//
//int main()
//{
//	//IsPrime1();
//	//IsPrime2();
//	//IsPrime3();
//	mul();
//	//IsLeapYear();
//	system("pause");
//	return 0;
//}
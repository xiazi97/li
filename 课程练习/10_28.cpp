#include<stdlib.h>
#include<iostream>
using namespace std;

#if  0
class Time
{
public:
	Time(int hours,int minute,int second)
		:_hours(hours)
		,_minute(minute)
		,_second(second)
	{
	}

private:
	int _hours;
	int _minute;
	int _second;
};

class Date 
{
public:
	Date(int year = 1900, int month = 01, int day =0)          //初始化列表
		: _year(year) //this->_year = year   为什么不可以？  初始化列表就是为了做初始化工作，对象还不存在
					  //只有当初始化列表执行完毕之后，给变量分配了空间此时才可以找到，不然不知道this指针访问多大空间的大小（int？double？char？）
		,_month(month)
		,_day(day)
		,_t(11,8,30)                   //此时初始化需要调用Time类的构造函数，而Time中既没有实现构造函数,参数也没有缺省值，所以必须在此时对其进行初始化
	{}

	Date( const Date& d)
		:_year(d._year)
		,_month(d._month)
		,_day(d._day)
		,_t(d._t)
	{}
	
private:
	int _year;
	int _month;
	int _day;
	Time _t;               //此时若不添加友元，编译时会报错
};
#endif

#if 0
class Date 
{
public:
	explicit Date(int year)      //explicit修饰构造函数，会禁止单参构造函数类型转化的作用，构造不了临时对象
		:_year(year)
	{}

	//Date(int year = 1900, int month = 01, int day =0)            //单参时候不知道调用哪一个
	//	: _year(year) 
	//	,_month(month)
	//	,_day(day)
	//	{}

	Date( const Date& d)
		:_year(d._year)
		,_month(d._month)
		,_day(d._day)
	{}
	
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d2(2017);
	
	// 用一个整形变量给日期类型对象赋值    
	// 实际编译器背后会用2018构造一个无名对象，最后用无名对象给d1对象进行赋值
	d2 = 2018;
	system("pause");
	return 0;
}
#endif

class Date 
{
public:
	Date(int year = 1900, int month = 01, int day =0)          
		: _year(year) 
		,_month(month)
		,_day(day)
	{}
	/*ostream operator<<(ostream& _cout)   
	{
		_cout << _year << "-" << _month << "-" << _day ;   
		return _cout;
	}*/
private:
	int _year;
	int _month;
	int _day;
};

//ostream operator<<(ostream& _cout,const Date& d)   //为了支持连续输出
//{
//	_cout << d._year << "-" << d._month << "-" << d._day ;   //此时为私有的，不能访问
//	return _cout;
//}

int main()
{
	Date d;
	return 0;
}
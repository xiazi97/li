#define CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<iostream>
using namespace std;

#if 0
//友元函数
class Time
{
	friend void TestFunc();
public:
	Time(int hour = 0,int minute = 0,int second = 0)
		:_hours(hour)
		,_minute(minute)
		,_second(second)
	{}
private:
	int _hours;
	int _minute;
	int _second;
};

class Date
{
	friend void TestFunc();    //友元函数可以在类定义的任何地方声明，不受类访问限定符限制
public:
	Date(int year = 1900 ,int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{}
private:
	int _year;
	int _month;
	int _day;
};

void TestFunc()                //一个函数可以是多个类的友元函数
{
	Date d;
	d._year = 2018;

	Time t;
	t._hours = 17;
}
#endif


#if 0
//友元类
class Time
{
	friend class Date;           //Date访问Time对象的私有成员变量，所以应在Time中声明Date是Time的友元类
public:
	Time(int hour = 0,int minute = 0,int second = 0)
		:_hours(hour)
		,_minute(minute)
		,_second(second)
	{}
private:
	int _hours;
	int _minute;
	int _second;
};

class Date
{    
public:
	Date(int year = 1900 ,int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{}
	 
	void PrintDate()
	{
		cout<< _year << "-" <<_month<<"-"<<_day<<":"<<_t._hours <<":" <<_t._minute<<":"<<_t._second<<endl;
	}

private:
	int _year;
	int _month;
	int _day;
	Time _t;
};
#endif

#if 0
//static
class Date
{
public:
	Date(int year = 1900 ,int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		++_count;
	}

	Date(const Date& d)
	{
		++_count;
	}

	~Date()
	{
		--_count;
	}

	static int GetCount()
	{
		//_day = 1; 编译器处理时实际为：this->_day，而静态成员函数没有隐藏的this指针，不能访问类的非静态成员变量 
		//TestFunc();  //静态成员函数不可以调用非静态成员函数
		return _count;
	}

	void TestFunc()
	{
		GetCount();  //非静态成员函数可以调用类的静态成员函数
	}

private:
	int _year;
	int _month;
	int _day;
	static int _count;
};

int Date::_count = 0;   //定义时不添加static关键字 

int main()
{
	cout  << Date::GetCount() << endl;
	Date d1;
	Date d2;
	cout  << Date::GetCount() << endl;
	return 0;
}
#endif

#if 0
int main()
{
	int* p = new int[10];
	_CrtDumpMemoryLeaks();      //显示当前的内存泄露
	system("pause");
	return 0;
}
#endif
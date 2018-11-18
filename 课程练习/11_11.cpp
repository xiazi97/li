#define CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include<iostream>
using namespace std;

#if 0
//��Ԫ����
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
	friend void TestFunc();    //��Ԫ�����������ඨ����κεط�����������������޶�������
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

void TestFunc()                //һ�����������Ƕ�������Ԫ����
{
	Date d;
	d._year = 2018;

	Time t;
	t._hours = 17;
}
#endif


#if 0
//��Ԫ��
class Time
{
	friend class Date;           //Date����Time�����˽�г�Ա����������Ӧ��Time������Date��Time����Ԫ��
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
		//_day = 1; ����������ʱʵ��Ϊ��this->_day������̬��Ա����û�����ص�thisָ�룬���ܷ�����ķǾ�̬��Ա���� 
		//TestFunc();  //��̬��Ա���������Ե��÷Ǿ�̬��Ա����
		return _count;
	}

	void TestFunc()
	{
		GetCount();  //�Ǿ�̬��Ա�������Ե�����ľ�̬��Ա����
	}

private:
	int _year;
	int _month;
	int _day;
	static int _count;
};

int Date::_count = 0;   //����ʱ�����static�ؼ��� 

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
	_CrtDumpMemoryLeaks();      //��ʾ��ǰ���ڴ�й¶
	system("pause");
	return 0;
}
#endif
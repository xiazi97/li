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
	Date(int year = 1900, int month = 01, int day =0)          //��ʼ���б�
		: _year(year) //this->_year = year   Ϊʲô�����ԣ�  ��ʼ���б����Ϊ������ʼ�����������󻹲�����
					  //ֻ�е���ʼ���б�ִ�����֮�󣬸����������˿ռ��ʱ�ſ����ҵ�����Ȼ��֪��thisָ����ʶ��ռ�Ĵ�С��int��double��char����
		,_month(month)
		,_day(day)
		,_t(11,8,30)                   //��ʱ��ʼ����Ҫ����Time��Ĺ��캯������Time�м�û��ʵ�ֹ��캯��,����Ҳû��ȱʡֵ�����Ա����ڴ�ʱ������г�ʼ��
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
	Time _t;               //��ʱ���������Ԫ������ʱ�ᱨ��
};
#endif

#if 0
class Date 
{
public:
	explicit Date(int year)      //explicit���ι��캯�������ֹ���ι��캯������ת�������ã����첻����ʱ����
		:_year(year)
	{}

	//Date(int year = 1900, int month = 01, int day =0)            //����ʱ��֪��������һ��
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
	
	// ��һ�����α������������Ͷ���ֵ    
	// ʵ�ʱ������������2018����һ������������������������d1������и�ֵ
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

//ostream operator<<(ostream& _cout,const Date& d)   //Ϊ��֧���������
//{
//	_cout << d._year << "-" << d._month << "-" << d._day ;   //��ʱΪ˽�еģ����ܷ���
//	return _cout;
//}

int main()
{
	Date d;
	return 0;
}
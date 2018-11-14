#include<thread>
#include<mutex>
#include<iostream>
using namespace std;

#if 0 
//饿汉模式             缺点：如果对象比较大，可能在启动时创建对象就浪费了很长时间
class Singleton
{
public:
	Singleton& GetInstrance()
	{
		return _p;
	}
private:
	Singleton()
	{}
private:
	//Singleton(const Singleton& s);
	Singleton(const Singleton& s) = delete;
private:
	static Singleton _p;
};

Singleton Singleton::_p;
#endif
/*单线程时可以
//懒汉模式
class Singleton
{
public:
	static Singleton* GetInstrance()
	{
		if(_p == nullptr)
		{
			_p = new Singleton();
			cout<<"Create New!"<<endl;
		}
		return _p;
	}

private:
	Singleton()
	{}

	Singleton(const Singleton& t);
private:
	static Singleton* _p;
};

Singleton* Singleton::_p = nullptr;

int main()
{
	Singleton::GetInstrance();
	return 0;
}
*/

class Singleton
{
public:
	static Singleton* GetInstance()
	{
		//_mutex.lock();  若加在这里则所有线程都被阻塞
		if(_p == nullptr)
		{
			_mutex.lock();
			if(_p == nullptr)
			{
				_p = new Singleton();
				cout<<"Create New!"<<endl;
			}
		_mutex.unlock();
		}
		
		return _p;
	}

	/*对于单例来说肯定要调用此函数，而在调用时 1.可能会忘记调用   2.无法保证其他线程已经用完了
	static void Release()
	{
		if(_p == nullptr)
		{
			_mutex.lock();
			if(_p == nullptr)
			{
				delete _p;
				_p = nullptr;
			}
		_mutex.unlock();
		}
	}*/

	class GC
	{
	public:
		~GC()
		{
			if(_p == nullptr)
			{
			_mutex.lock();
			if(_p == nullptr)
			{
				delete _p;
				_p = nullptr;
			}
			_mutex.unlock();
			}
		}
	};

private:
	Singleton()
	{}

	Singleton(const Singleton& t);
private:
	static Singleton* volatile _p;
	static mutex _mutex;
	static GC _gc;
};

Singleton* volatile Singleton::_p = nullptr;
mutex Singleton::_mutex;
Singleton::GC _gc;

void func(int a)
{
	Singleton::GetInstance();
}

int main() 
{    
	thread t1(func, 10);    
	thread t2(func, 10);
 
    t1.join();    
	t2.join();
 
    cout << Singleton::GetInstance() << endl;    
	cout << Singleton::GetInstance() << endl;
	return 0;
}
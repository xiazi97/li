#include<iostream>
using namespace std;
#if 0
class Test
{
public:
	Test()
	{
		cout<< "Test()" << this << endl;
		_data = 0;
	}

	~Test()
	{
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};




int main()
{
	Test* pt = new Test[10];
	delete[] pt;
	//delete pt ;  此时程序会崩溃，原因：  1.内存泄漏   
	//2.delete掉第一个对象完成后会需要释放空间，但是由于我们提供了析构函数，此时空间首地址现在并不在第一个对象处，而是要向后4个字节，所以会产生错误，引起程序崩溃
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test()
	{
		cout<< "Test()" << this << endl;
		_data = 0;
	}

	void* operator new(size_t size)   //如果在类里定义了，那么默认使用的则是类中自己定义的
	{
		return malloc(size);
	}

	~Test()
	{
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};

void* operator new(size_t size,char* funcName,int lineNo)    //如果用户自定义时，第一个参数必须要给一个字节数，而且返回类型必须要为void*，也可以添加别的参数
{
	cout<<funcName<<":"<<lineNo<<endl;
	return malloc(size);
}

//#define new new(__FUNCDNAME__,__LINE__)

int main()
{
	Test* pt = new Test; 
//	Test* pt = new Test;		//在调用自定义new函数时，若使用new Test(),相当于只是给此函数传了一个字节数，并没有传别的参数，所以并不能打印出来该语句,需要传入参数
	delete pt;
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data)
	{
		cout<< "Test()" << this << endl;
		_data = data;
	}

	~Test()
	{
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};

int main()
{//不但可以处理自定义类型，还可以处理内置类型
	int array[10];
	new(array+3) int(3);
	//定位new表达式
	Test* pt = (Test*)malloc(sizeof(Test));
	new(pt) Test(10);
	/*
	Test* pt1 = new Test(10);是需要进行申请空间并返回的
	而定位new表达式此时已经有空间，所以直接返回该段空间即可
		void* operator new(size_t size,void* p)
		{
			return p;
		}
		call Test();
	*/

	//delete pt;
	pt->~Test();
	free(pt);
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data)
	{
		cout<< "Test()" << this << endl;
		_data = data;
	}

	~Test()
	{
		delete this;    //此时this等价于pt，再次调用delete会循环调用析构函数，从而导致无限递归，所以不要在析构函数中delete掉this
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};

int main()
{
	Test* pt = new Test(10);
	delete pt;
	return 0;
}
#endif


#if 0
//设计一个类，该类只能在堆上创建对象
class Data
{
public:
	static Data* CreateObject(int data)
	{
		return new Data(data);
	}
private:
	Data(int data)
	{
		cout<<"Data():"<<this<<endl;
	}
	Data(const Data& t);
private:
	int _data;
};

int main()
{
	Data* T = Data::CreateObject(10);
	delete T;
	//Data(*T);拷贝构造也被禁掉了
	return 0;
}
#endif

#if 0
class Data
{
public:
	static Data Create()   //缺点一：如果编译器没有优化可能会调用拷贝构造函数
	{
		return Data();
	}

	Data(const Data& t)
	{
		cout<< "Data(const Data& t):"<<this	<<endl;
	}

private:
	Data();
};

class Test
{
public:
	Test()
	{
		Data::Create();    
	}
};


Data s; 
//缺点二：此时s在数据段，在进入主函数之前需要将s构造好，即已经调用了Test函数，只要调用函数就必定要使用栈的空间，所以实例的对象Data::Create();也是在栈上
#endif

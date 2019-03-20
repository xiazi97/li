#include<iostream>
using namespace std;

#if 0
#if 0 
//auto_ptr
//采用资源管理权的转移来解决浅拷贝问题
//C98
template<class T>
class AutoPtr
{
private:
	T* _ptr;
public:
	AutoPtr(T* ptr)
		:_ptr(ptr)
	{}

	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = nullptr;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& sp)
	{
		if(this != sp)
		{
			if(_ptr)
				delete _ptr;
			_ptr = sp._ptr;
			sp._ptr = nullptr;
		}
	}

	~AutoPtr()
	{
		if(_ptr)
			delete _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T& operator->()
	{
		return _ptr;
	}

	T& Get()
	{
		return _ptr;	
	}

};

void Test()
{
	AutoPtr<int> ap1(new int);
	AutoPtr<int> ap2(ap1);
	/*
	但是这样的做法不能像原生态指针一样进行
	int* pa1;
	int* pa2 = pa1;
	
	*pa1 = 10;
	*pa2 = 20;

	在当前做法下理论上执行期间会报错
	*/
}

int main()
{
	Test();
	return 0;
}
#endif

//版本2：资源释放权力的转移
template<class T>
class Autoptr
{
public:
	Autoptr(T* ptr=nullptr)
		:_ptr(ptr)
		,_owner(false)
	{
		if(_ptr)
			_owner = true;
	}

	Autoptr(const Autoptr<T>& ap)
		:_ptr(ap._ptr)
		,_owner(ap._owner)
	{
		ap._owner = false;
	}

	Autoptr<T>& operator=(const Autoptr<T>& sp)
	{
		if(this !=&sp)
		{
			Test();
			_ptr = sp._ptr;
			_owner = sp._owner;
			sp._owner = false;
		}

		return this;
	}

	~Autoptr()
	{
		Test();
	}

	T& operator*()
	{
		return *_ptr;
	}

	T& operator->()
	{
		return _ptr;
	}

	T& Get()
	{
		return _ptr;	
	}

private:
	void Test()
	{
		if(_ptr && _owner)
		{
			delete _ptr;
			_owner = false;
		}
	}

private:
	T* _ptr;
	mutable bool _owner;
};

void Test()
{
	Autoptr<int> ap1(new int);
	Autoptr<int> ap2(ap1);

	
	*ap1 = 10;
	*ap2 = 20;
}

int main()
{
	Test();
	return 0;
}
#endif


#if 0
//unique_ptr
//资源独占，防止被拷贝（只能被一个对象进行管理）
template<calss T>
class Uniqueptr
{
public:
	Uniqueptr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~Uniqueptr()
	{
		if(_ptr)
			delete _ptr;
	}

	T* operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	//C98格式
	Uniqueptr(const Uniqueptr<T>& );
	Uniqueptr<T> operator=(const Uniqueptr& );


	//C11格式
	Uniqueptr(const Uniqueptr<T>& ) = delete;
	Uniqueptr<T> operator=(const Uniqueptr& ) = delete;
private:
	T* _ptr;
};
#endif

//定制删除器
template<class T>
class DFDef
{
public:
	void operator()(T*& p)
	{
		if(p)
		{
			delete p;
			p = nullptr;
		}
	}
};

template<class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if(p)
		{
			free(p);
			p = nullptr;
		}
	}
};


template<class T>
class FClose
{
public:
	void operator()(FILE* p)
	{
		if(p)
		{
			fclose(p);
			p = nullptr;
		}
	}
};


//采用引用计数的方式
//为了线程安全，上锁，但是可能会造成死锁（锁内调用的其他代码如果抛异常则会造成死锁），守卫锁，进入时创建对象，函数退出时自动销毁
#include<mutex>
template<class T,class DF = DFDef>
class Sharedptr
{
public:
	Sharedptr(T* ptr = nullptr)
		:_ptr(ptr)
		,_pCount(nullptr)
	{
		if(_ptr)
		{
			_pCount = new int(1);
			_pm =new mutex;
		}
			
	}

	Sharedptr(const Sharedptr<T>& sp)
		:_ptr(sp._ptr)
		,_pCount(sp._pCount)
		,_pm(sp._pm)
	{
		if(_ptr)
			AddRefCount();//若不判断*_pCount是否为空（sp没有管理资源），可能会因为空指针解引用而出现问题
	}

	Sharedptr<T>& operator=(const Sharedptr<T>& sp)
	{
		if(this != sp)
		{
			if(_ptr && 0 == SubRefCount())
			{
				Release();
			}
			_ptr = sp._ptr;
			_pCount = sp._pCount;
			/*if(*_pCount == 1)
			{
				delete _ptr;
				delete _pCount;
				
			}*/
			if(_ptr)
				AddRefCount();
		}
		return this;
	}

	~Sharedptr()
	{
		if(_ptr && SubRefCount())
		{
			Release();
			
		}
	}

	T* operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	void Release()
	{
		DF() (_ptr);
		//delete _ptr;
		delete _pCount;
		delete _pm;
	}

	int UseCount()
	{
		assert(_pCount);
		return *_pCount;
	}

	void AddRefCount()
	{
		_pm->lock();
		++(*_pCount);
		_pm->unlock();
	}

	int SubRefCount()
	{
		_pm->lock();
		--(*_pCount);
		_pm->unlock();

		return *_pCount;
	}

private:
	T* _ptr;
	int* _pCount;
	mutex* _pm;
};



int main()
{
	Sharedptr<int> sp1(new int);
	Sharedptr<int,Free<int>> sp2((int*)malloc(sizeof(int)));
	Sharedptr<FILE,FClose> sp3(fopen("1.txt","w"));

	return 0;
}

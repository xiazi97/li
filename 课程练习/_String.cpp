#include<assert.h>
#include<iostream>
using namespace std;


#if 0
  浅拷贝问题的String类
class String
{
public:
	String(const char* str = "")    //创建空的字符串
	{
		//assert(str);         //断言检测是否为空
		if(nullptr == str)
			str = "";           //如果为空那么就当作空字符串
		
		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
		/*
			if(nullptr == str)
			{
				//_str = new char   //分配一个字节的空间,但在下边析构时需要与delete匹配起来使用，为了方便，将其设为以下形式
				_str = new[1] char;
				*_str = "\0"
			}
			else
			{
				_str = new char[strlen(str) + 1];
				strcpy(_str,str);
			}
		*/
	} 

	//类似系统生成的默认拷贝构造函数的方式
	//值的拷贝方式-----内存的拷贝
	//后果：多个对象共用同一份资源，在销毁时同一份资源被释放多次而引起程序的崩溃
	String(const String& s)
		:_str(s._str)   //当前对象的指针和s里的字符串共用同一段空间
	{}

	//类似系统生成的默认的赋值运算符重载的方式
	//问题：1.内存泄露
	//		2.与拷贝构造函数类似
	String& operator=(const String& s)   
	{ 
		if(this != &s)
		{
			_str = s._str;
			return *this;
		}
	}

	~String()
	{
		if(_str)  //判断是否有空间，有的话将其释放
		{
			delete[] _str;
			_str = nullptr;
		}
	}

private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	String s2(s1);    //用s1拷贝构造s2，因为没有自己给出拷贝构造函数，系统会默认使用类生成的拷贝构造函数进行值的拷贝（浅拷贝）,销毁期间会对一段资源销毁两次产生程序而崩溃
	String s2 = s1;   //此时会看到s2本身有一个地址空间，但是在赋值时完全将s1中的东西拷贝，使得s2本来的空间找不到了，产生内存泄漏
}
#endif


#if 0
使用深拷贝进行处理
	传统方式
class String
{
public:
	String(const char* str = "")    //创建空的字符串
	{
		//assert(str);         //断言检测是否为空
		if(nullptr == str)
			str = "";           //如果为空那么就当作空字符串
		
		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
		/*
			if(nullptr == str)
			{
				//_str = new char   //分配一个字节的空间,但在下边析构时需要与delete匹配起来使用，为了方便，将其设为以下形式
				_str = new[1] char;
				*_str = "\0"
			}
			else
			{
				_str = new char[strlen(str) + 1];
				strcpy(_str,str);
			}
		*/
	} 

	String(const String& s)
		:_str(new char[strlen(s._str) + 1])   //先分配一段空间
	{
		strcpy(_str,s._str);
	}

	String& operator=(const String& s)
	{
		if(this != &s)
		{
			/*
			释放旧空间，开辟新空间，再进行字符串拷贝
			delete[] _str;			//因为先释放了原来空间，如果开辟新空间失败了，那么会造成影响
			_str = new char[strlen(s._str) + 1];
			strcpy(_str,s._str);
			*/ 
			char* pStr = new char[strlen(s._str) + 1];
			strcpy(_str,s._str);
			delete[] _str;     //释放掉旧空间
			_str = pStr;
		}
		return *this;
	}

	~String()
	{
		if(_str)  //判断是否有空间
		{
			delete[] _str;
			_str = nullptr;
		}
	}

private:
	char* _str;
};


void Test()
{
	String s1("hello");
	String s2(s1);
}

int main()
{
	Test();
	return 0;
}
#endif

#if 0
现代版写法，代码较简洁
class String
{
public:
	String(const char* str = "")    //创建空的字符串
	{
		if(nullptr == str)
			str = "";           //如果为空那么就当作空字符串
		
		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
	} 

	String(const String& s)//注意！本编译器下此时_str没有进行初始化，放的是一个随机值，所以在释放strTemp时出错，所以需要给一个初始值
		:_str(nullptr)
	{
		String strTemp(s._str);
		swap(_str,strTemp._str);  
	}

	/*
	String& operator=(const String& s)
	{
		if(this != &s)
		{
			String strTemp(s);
			swap(_str,strTemp._str);        
		}
		return *this;   //当前对象用的是临时对象的空间，出了作用域销毁临时对象，实际是将当前对象的地址空间释放了
	}
	*/

	String& operator=(String s)
	{
		swap(_str,s._str);
		return *this;
	}

	~String()
	{
		if(_str)  //判断是否有空间
		{
			delete[] _str;
			_str = nullptr;
		}
	}

private:
	char* _str;
};

void Test()
{
	String s1("hello");
	String s2(s1);
	String s3;
	s3 = s2;   //此时实际是临时对象给s3赋值的
}

int main()
{
	Test();
	return 0;
}
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if(nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
		_count = 1;
	}

	String(String& s)
		:_str(s._str)
		,_count(++s._count)
	{}

	~String()
	{
		if(0 == --_count && _str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}

private:
	char* _str;
	int _count;  //每个对象中均有一份，一个对象修改了其他对象不知道
};
#endif

/*
static也不可以
class String
{
public:
	String(const char* str = "")
	{
		if(nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
		_count = 1;
	}

	String(String& s)
		:_str(s._str)
	{
		++_count;
	}

	~String()
	{
		if(0 == --_count && _str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}

private:
	char* _str;
	static int _count;         //所有对象共享的，但资源有可能会有多分，每调用一次构造就将_count置为1了，不能针对多份资源，如 String s3;
};

int String::_count = 0;

void Test()
{
	String s1("hello");
	String s2(s1);
	String s3; //此时会出现问题，到这里时_count重新被置为1，导致只能将s3释放而无法释放s1和s2
}

int main()
{
	Test();
	return 0;
}*/

//写时拷贝（COW copy on write）:浅拷贝+引用计数+在向对象写内容时，是否需要给当前对象独立空间
class String
{
public:
	String(const char* str = "")
		:_pCount(new int(1))
	{
		if(nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
	}

	String(String& s)
		:_str(s._str)
		,_pCount(s._pCount)
	{
		++*(_pCount);
	}

	String& operator=(const String& s)
	{
		if(this != &s)
		{
			if(0 == --(*_pCount) && _str) //检测拷贝以后自己的资源需不需要释放
			{
				delete[] _str;
				_str = nullptr;

				delete _pCount;
				_pCount = nullptr;
			}
			
			//与被拷贝的资源共享资源
			_str = s._str;
			_pCount = s._pCount;

			//新资源计数+1
			++(*_pCount);
		}
		return *this;
	}

	char& operator[](size_t index)   //返回引用是因为有可能返回后作为左值
	{
		if(*_pCount > 1)
		{
			String str(_str);
			this->Swap(str);
		}
		return _str[index];
	}

	const char& operator[](size_t index)const
	{
		return _str[index];
	}

	~String()
	{
		if(0 == --(*_pCount) && _str)
		{
			delete[] _str;
			_str = nullptr;

			delete _pCount;
			_pCount = nullptr;
		}
	}

	void Swap(String& s)
	{
		swap(_str,s._str);
		swap(_pCount,s._pCount);
	}
private:
	char* _str;
	int* _pCount;         
};

void Test()
{
	String s1("hello");
	
	String s2(s1);

	String s3; 
	//s3 = s1;
	s1 = s3;
	s1[0] = 'H';    //此时一改变会全改变，s1,s2,s3共用一份资源
}

int main()
{
	return 0;
}

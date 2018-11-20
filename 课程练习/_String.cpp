#include<assert.h>
#include<string>
#include<iostream>
using namespace std;


#if 0
//浅拷贝问题
class String
{
public:
	String(const char* str = "")   //如果没有传就给一个空的缺省值
	{
		if(nullptr == str)
		{
			assert(str);
			str="";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
	}

	//	if(nullptr == str)
	//	{
	//		//_str = new char;
	//		_str = new char[1];
	//		*_str = '\0';
	//	}
	//	else
	//	{
	//		_str = new char[strlen(str)+1];
	//		strcpy(_str,str);
	//	}
	

	//多个对象使用同一份资源，导致在销毁资源时同一份资源被释放多次
	String(const String& s)
		:_str(s._str)
	{}


	//1.内存泄漏     2.与拷贝构造函数类似
	String& operator=(const String& s)
	{}

	~String()
	{
		if(_str)   //判断有没有空间
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;        //动态空间，保存字符串
};


void Test()
{
	String s1("hello");
	String s2(s1);            //如果是调用默认的拷贝构造函数，那么析构完s2后析构s1时会造成崩溃
}
#endif

#if 0
//为了避免使用同一份空间，可以事先给对象一个空间
class String
{
public:
	String(const char* str = "")   //如果没有传就给一个空的缺省值
	{
		if(nullptr == str)
		{
			assert(str);
			str="";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
	}

	String(const String& s)
		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str,s._str);
	}

	String& operator=(const String& s)
	{
		if(this != &s)
		{
			/*delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str,s._str);*/

			char* pStr = new char[strlen(s._str) + 1];
			strcpy(pStr,s._str);
			delete[] _str;
			_str = pStr;
		}
	}

	~String()
	{
		if(_str)  
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;        
};
#endif

#if 0
class String
{
public:
	String(const char* str = "")   //如果没有传就给一个空的缺省值
	{
		if(nullptr == str)
		{
			assert(str);
			str="";
		}

		_str = new char[strlen(str) + 1];
		strcpy(_str,str);
	}

	//String(const String& s)
	//	:_str(nullptr)    //以便交换时不会发生错误
 //	{
	//	String strTemp(s._str);
	//	swap(_str,strTemp._str);
	//}

	String& operator=(const String& s)
	{
		if(this != &s)
		{
			String strTemp(s._str);
			swap(_str,strTemp._str);  //把当前对象的空间与临时对象的空间交换，出函数时释放临时对象实际时释放当前对象空间
		}
	 return *this;
	}

	String& operator=(String s)     //传值拷贝一个临时对象
  	{
		swap(_str,s._str);
		return *this;
	}

	~String()
	{
		if(_str)  
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
	String s2 = s1;    //此时赋值其实是 strTemp 给 s2 传的值，即为s2指向的其实是临时对象的地址空间，所以不用传引用
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


#if 0
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
	Test();
	return 0;
}
#endif
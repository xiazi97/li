#include<assert.h>
#include<string>
#include<iostream>
using namespace std;


#if 0
//ǳ��������
class String
{
public:
	String(const char* str = "")   //���û�д��͸�һ���յ�ȱʡֵ
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
	

	//�������ʹ��ͬһ����Դ��������������Դʱͬһ����Դ���ͷŶ��
	String(const String& s)
		:_str(s._str)
	{}


	//1.�ڴ�й©     2.�뿽�����캯������
	String& operator=(const String& s)
	{}

	~String()
	{
		if(_str)   //�ж���û�пռ�
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;        //��̬�ռ䣬�����ַ���
};


void Test()
{
	String s1("hello");
	String s2(s1);            //����ǵ���Ĭ�ϵĿ������캯������ô������s2������s1ʱ����ɱ���
}
#endif

#if 0
//Ϊ�˱���ʹ��ͬһ�ݿռ䣬�������ȸ�����һ���ռ�
class String
{
public:
	String(const char* str = "")   //���û�д��͸�һ���յ�ȱʡֵ
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
	String(const char* str = "")   //���û�д��͸�һ���յ�ȱʡֵ
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
	//	:_str(nullptr)    //�Ա㽻��ʱ���ᷢ������
 //	{
	//	String strTemp(s._str);
	//	swap(_str,strTemp._str);
	//}

	String& operator=(const String& s)
	{
		if(this != &s)
		{
			String strTemp(s._str);
			swap(_str,strTemp._str);  //�ѵ�ǰ����Ŀռ�����ʱ����Ŀռ佻����������ʱ�ͷ���ʱ����ʵ��ʱ�ͷŵ�ǰ����ռ�
		}
	 return *this;
	}

	String& operator=(String s)     //��ֵ����һ����ʱ����
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
	String s2 = s1;    //��ʱ��ֵ��ʵ�� strTemp �� s2 ����ֵ����Ϊs2ָ�����ʵ����ʱ����ĵ�ַ�ռ䣬���Բ��ô�����
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
	int _count;  //ÿ�������о���һ�ݣ�һ�������޸�����������֪��
};
#endif

/*
staticҲ������
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
	static int _count;         //���ж�����ģ�����Դ�п��ܻ��ж�֣�ÿ����һ�ι���ͽ�_count��Ϊ1�ˣ�������Զ����Դ���� String s3;
};

int String::_count = 0;

void Test()
{
	String s1("hello");
	String s2(s1);
	String s3; //��ʱ��������⣬������ʱ_count���±���Ϊ1������ֻ�ܽ�s3�ͷŶ��޷��ͷ�s1��s2
}

int main()
{
	Test();
	return 0;
}*/


#if 0
//дʱ������COW copy on write��:ǳ����+���ü���+�������д����ʱ���Ƿ���Ҫ����ǰ��������ռ�
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
			if(0 == --(*_pCount) && _str) //��⿽���Ժ��Լ�����Դ�費��Ҫ�ͷ�
			{
				delete[] _str;
				_str = nullptr;

				delete _pCount;
				_pCount = nullptr;
			}
			
			//�뱻��������Դ������Դ
			_str = s._str;
			_pCount = s._pCount;

			//����Դ����+1
			++(*_pCount);
		}
		return *this;
	}

	char& operator[](size_t index)   //������������Ϊ�п��ܷ��غ���Ϊ��ֵ
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
	s1[0] = 'H';    //��ʱһ�ı��ȫ�ı䣬s1,s2,s3����һ����Դ
}

int main()
{
	Test();
	return 0;
}
#endif
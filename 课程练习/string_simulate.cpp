#include<iostream>
using namespace std;

	class String
	{
	public:
		typedef char* Iterator;
	public:
		String(const char* str)
		{
			if (nullptr == str)
				str = "";
			_size = strlen(str);
			_str = new char[_size + 1];
			_capacity = _size;
			strcpy(_str,str);
		}
		
		String(const char* str,size_t size)
		{
		}

		String(const String& s)
			:_str(new char[s._capacity + 1])
			,_capacity(s._capacity)
			,_size(s._size)
		{
			strcpy(_str,s._str);
		}

		String& operator=(const String& s)
		{
			if(this != &s)
			{
				char* pStr = new char[s._capacity + 1];
				strcpy(pStr,s._str);
				delete[] _str;
				_str = pStr;
				_capacity = s._capacity;
				_size = s._size;
			}
		}

		~String()
		{
			if(_str)
			{
				delete[] _str;
				_str = nullptr;
				_capacity = 0;
				_size = 0;
			}
		}

		Iterator Begin()
		{
			return _str;
		}
		
		Iterator End()
		{
			return _str + _size;
		}

		Iterator RBegin()
		{
			return End();
		}

		Iterator REnd()
		{
			return Begin();
		}
		void PushBack(char c)
		{
			Reserve(_size+1);  //ÅÐ¶Ï¹»²»¹»·Å
			_str[_size++] = c;
			_str[_size] = '\0';
		}
		
		void Append(const char* str)
		{
			int len = strlen(str);
			if(len > (_capacity-_size))
			{
				Reserve(2 * _capacity + len);
			}

			strcat(_str,str);
			_size += len;
		}

		char& operator[](size_t index)
		{
			return _str[index];
		}

		const char& operator[](size_t index)const
		{
			return _str[index];
		}

		void Resize(size_t newSize,char c);
		void Resere(size_t newCapacity);
		int Size()const
		{
			return _size;
		}

		bool Empty()const
		{
			return (0 == _size);
		}

		void Clear()
		{
			_size = 0;
		}

		int find(char c)
		{
			for(size_t i=0;i<_size;++i)
			{
				if(c == _str[i])
					return i;
			}
			return -1;
		}

		int rfind(char c)
		{
			for(int i=_size-1;i>=0;--i)
			{
				if(c == _str[i])
					return i;
			}
			return -1;
		}

		int find(char c,size_t pos = 0)
		{
			for(size_t i=pos;i<_size;++i)
			{
				if(c == _str[i])
					return i;
			}
			return -1;
		}

		int rfind(char c,size_t pos)
		{
			for(int i=_size-1-pos;i>=0;--i)
			{
				if(c == _str[i])
					return i;
			}
			return -1;
		}

		const char* C_Str()const
		{
			return _str;
		}

		void Swap(String& s)
		{
			swap(_str,s._str);
			swap(_size,s._size);
			swap(_capacity,s._capacity);
		}

		void Reserve(size_t newCapacity)
		{
			if(newCapacity > _capacity)
			{
				char* pStr = new char[newCapacity + 1];
				strcpy(pStr,_str);
				delete[] _str;
				_str = pStr;
				_capacity = newCapacity;
			}
		} 

		String Strsub(size_t pos,size_t size)
		{
			int len = strlen(_str + pos);
			if(size > len)
				size = len;
			return String(_str+pos,size);
		}

	private:
		char* _str;
		size_t _capacity;
		size_t _size;
	};
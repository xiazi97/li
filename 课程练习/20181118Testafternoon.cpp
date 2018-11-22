#include<iostream>
using namespace std;
#include <vector>
#include <string>

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}

private:
	int _year;
	int _month;
	int _day;
};



template<class T>
void PrintVector(const vector<T>& v)
{
	for (auto e : v)
		cout << e << " ";

	/*
	for(auto e = v.begin(); e != v.end(); ++it)
	   cout<< *e << " ";
	*/
	cout << endl;
}

void TestVector()
{
	std::vector<int> v1;
	std::vector<int> v2(10, 5);
	std::vector<int> v3(10);  // int() 内置类型，缺省值：0
	std::vector<Date> v4(10); // Date()自定义类型：调用T()缺省的构造函数
	
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	vector<int> v5(array, array+sizeof(array)/sizeof(array[0]));

	string str("hello");
	vector<char> v6(str.begin(), str.end());
	vector<char> v7(v6);

	PrintVector(v2);
	PrintVector(v3);
	PrintVector(v4);
	PrintVector(v5);
	PrintVector(v6);
	PrintVector(v7);
}

int main()
{
	TestVector();
	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}

private:
	int _year;
	int _month;
	int _day;
};

void TestVector()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	vector<int> v1(array, array + 5);
	cout << typeid(vector<int>::iterator).name() << endl;

	vector<int>::iterator it1 = v1.begin();
	*it1 = 10;

	// 列表的初始化
	const vector<int> v2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	cout << typeid(const vector<int>::iterator).name() << endl;

	const vector<int>::const_iterator it2 = v2.cbegin();
	//*it2 = 10;
}

int main()
{
	Date d1(2018, 11, 18);
	Date d2{ 2018, 11, 18 };
	TestVector();
	return 0;
}
#endif

#if 0
#include <algorithm>

int main()
{
	vector<int> v{ 2, 1, 8, 4, 0, 9, 3, 6, 7, 5 };
	sort(v.begin(), v.end());
	return 0;
}
#endif


#if 0
int main()
{
	vector<int> v{ 1, 2, 3, 4 };
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(6);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(20, 5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(10);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(15);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(100);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
	return 0;
}
#endif

#if 0
int main()
{
	size_t sz;
	std::vector<int> foo;
	//foo.reserve(100);
	sz = foo.capacity();
	std::cout << "making foo grow:\n";

	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	return 0;
}
#endif

#if 0
// 迭代器失效
// 1. 什么是迭代器失效？
// 2. vector什么情况下会发生迭代器失效？怎么解决？
//     >> push_back, insert, resize, reserve, assign
//     >> 删除 
int main()
{
	vector<int> v{ 1, 2, 3, 4 };
	vector<int>::iterator it = v.begin();
	*it *= 2;

	for (int i = 0; i < 5; ++i)
		v.push_back(i);

	it = v.begin();  //it迭代器失效
	*it *= 2;

	it = v.begin() + 8;
	cout << *it << endl;

	it = v.begin() + 2;
	it = v.erase(it);
	cout << *it << endl;

	/*
	v.pop_back();
	cout << *it << endl;
	*/

	return 0;
}
#endif

#if 0
int main()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	auto it = v.begin();

	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
		{
			++it;
		}
	}

	return 0;
}
#endif


namespace bit
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef T* reverse_iterator;
	public:
		vector()
			: _start(nullptr)
			, _last(nullptr)
			, _endOfStorage(nullptr)
		{}

		vector(size_t n, const T& data = T())
			: _start(new T[n])
			, _last(_start + n)
			, _endOfStorage(_last)
		{
			for (size_t i = 0; i < n; ++i)
				_start[i] = data;

			// 有问题
			//memset(_start, data, sizeof(T)*n);
		}

		// [first, last)代表一段连续的空间
		vector(T* first, T* last)
		{
			size_t size = last - first;
			_start = new T[size];

			for (size_t i = 0; i < size; ++i)
				_start[i] = first[i];

			/*
			memcpy(_start, first, size*sizeof(T));
			*/

			_last = _start + size;
			_endOfStorage = _last;
		}

		vector(const vector<T>& v);

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _last = _endOfStorage = nullptr;
			}
		}

		// 注意：深浅拷贝的问题
		vector<T>& operator=(const vector<T> v);

		/////////////////////////////////////////////////////
		// itearor
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _last;
		}

		reverse_iterator rbegin()
		{
			return end();
		}

		reverse_iterator rend()
		{
			return rbegin();
		}

		//////////////////////////////////////////////
		// capacity
		size_t size()const
		{
			return _last - _start;
		}

		size_t capacity()const
		{
			return _endOfStorage - _start;
		}

		bool empty()const
		{
			return _start == _last;
		}

		void resize(size_t newSize, const T& data = T())
		{
			size_t oldSize = size();
			if (newSize <= oldSize)
				_last = _start + newSize;
			else
			{
				size_t cap = capacity();
				if (newSize <= cap)
				{
					for (size_t i = oldSize; i < newSize; ++i)
						*_last++ = data;
				}
				else
				{
					T* pTemp = new T[newSize];

					for (size_t i = 0; i < oldSize; ++i)
						pTemp[i] = _start[i];

					for (size_t i = oldSize; i < newSize; ++i)
						pTemp[i] = data;

					delete[] _start;
					_start = pTemp;
					_last = _start + newSize;
					_endOfStorage = _last;
				}
			}
		}

		void reserve(size_t newcapacity)
		{
			size_t oldcapacity = capacity();
			if (newcapacity > oldcapacity)
			{
				T* pTemp = new T[newcapacity];
				size_t count = size();
				for (size_t i = 0; i < count; ++i)
					pTemp[i] = _start[i];

				delete[] _start;
				_start = pTemp;
				_last = _start + count;
				_endOfStorage = _start + newcapacity;
			}
		}
		///////////////////////////////////////////
		// acess
		T& operator[](size_t index)
		{
			return _start[index];
		}

		const T& operator[](size_t index)const
		{
			return _start[index];
		}

		T& front()
		{
			return *_start;
		}

		const T& front()const
		{
			return *_start;
		}

		T& back()
		{
			return *(_last-1);
		}

		const T& back()const
		{
			return *(_last-1);
		}

		/////////////////////////////////////////
		//

		void push_back(const T& data)
		{
			if (size() == capacity())
				reserve(capacity() * 2 + 3);

			*_last++ = data;
		}

		void pop_back()
		{
			--_last;
		}

		// 将data插在pos的位置
		// 返回新插入元素的位置
		iterator insert(iterator pos, const T& data);
		
		// 删除pos位置的元素
		// 返回pos下一个元素所在的位置(搬移后)
		iterator erase(iterator pos);
		void clear()
		{
			_last = _start;
		}

		void swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_last, v._last);
			swap(_endOfStorage, v._endOfStorage);
		}

	private:
		iterator _start;
		iterator _last;   // _size
		iterator _endOfStorage;  // _capacity
	};
}


void TestBitVector1()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	bit::vector<int> v1(array, array+sizeof(array)/sizeof(array[0]));
	cout << v1.size() << endl;
	cout << v1.capacity() << endl;

	bit::vector<int> v2(10, 5);
	for (auto e : v2)
		cout << e << " ";
	cout << endl;

	//bit::vector<int> v3{ 1, 2, 3, 4, 5, 6 };  ?
}

void TestBitVector2()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	bit::vector<int> v1(array, array + sizeof(array) / sizeof(array[0]));

	for (auto it = v1.begin(); it != v1.end(); ++it)
		cout << *it << " ";

	cout << endl;
}

void TestBitVector3()
{
	bit::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	cout << v.size() << endl;
	cout << v.capacity() << endl;
	cout << v[0] << endl;
	cout << v.front() << endl;
	cout << v.back() << endl;

	v.pop_back();
	v.pop_back();
	cout << v.size() << endl;
	cout << v.capacity() << endl;
	cout << v[0] << endl;
	cout << v.front() << endl;
	cout << v.back() << endl;

	v.clear();
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

void TestBitVector4()
{
	bit::vector<int> v(5, 6);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.push_back(6);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(10, 8);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(20, 5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(10);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

int main()
{
	//TestBitVector1();
	//TestBitVector2();
	//TestBitVector3();
	TestBitVector4();
	return 0;
}
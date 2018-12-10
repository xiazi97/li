#pragma once
#include<assert.h>
#include<iostream>
using namespace std;

#if 0
//不是一个真正的函数，是一个（万能）模板
template<class T>     //模板参数列表 可以使用template<typename T> ，不可以使用struct 
T _Add(T left,T right)       //函数模板
{
	return left + right;
}

template<class T>
void PrintfArray(T array,int size)  //数组会自己转换类型
{
	cout<<typeid(array).name() <<endl;
	int i = 0;
	for(i=0;i<size;i++)
	{
		cout<< array[i] << " ";
		cout<<endl;
	}

}

int main()
{
	int array[] = {1,2,3,4,};
	char str[] = "hello";
	PrintfArray(array,sizeof(array)/sizeof(int));
	PrintfArray(str,strlen(str));
	//隐式实例化---不会进行隐式的类型转化，需要用户自己来强制转
	cout<< _Add(1,2) <<endl;   //根据实参类型来进行类型推演生成处理具体类型的函数
	cout<< _Add(1,(int)2.0) <<endl;  //但是面对参数为不同类型时无法判断如何输出，需要对参数进行处理，如强转类型

	//显式实例化
	_Add<int>(1,2.2);
	_Add<>(1,2);    //隐式实例化
	return 0;
}
#endif

#if 0
template<class T>
class Seqlist
{
public:
	Seqlist(int capacity = 10)
		:_Data(new T[capacity])
		,_capacity(capacity)
		,_size(0)
	{}

	//拷贝构造：Seqlist(const Seqlist<T>& s);
	//赋值运算符重载：Seqlist<T>& operator = (const Seqlist<T>& s)

	void PushBack(const T& data)
	{
		_CheckCapacity();
		_Data[_size++] = data;
	}

	void PopBack()
	{
		if(_size != 0)
			--_size;
	}

	//访问任意位置
	T& operator[](size_t index)               //可能会修改s[i]中的元素
	{
		assert(index < _size);
		return _Data[index];
	}

	//因为const类型的对象不能调用普通函数，这里是const对象访问
	const T& operator[](size_t index) const
	{
		assert(index < _size);
		return _Data[index];
	}

	//访问第一个元素
	T& Front()
	{
		return _Data[0];
	}

	const T& Front()const
	{
		return _Data[0];
	}

	//访问最后一个元素
	T& Back()
	{
		return _Data[_size-1];
	}

	const T& Back()const
	{
		return _Data[_size-1];
	}

	size_t Size() const
	{
		return _size;
	}

	size_t Capacity() const
	{
		return _capacity;
	}

	void Clear()
	{
		_size = 0;
	}

	~Seqlist();
private:
	void _CheckCapacity()
	{
		if(_size == _capacity)
		{
			size_t newCapacity = (_capacity<<1);
			//申请空间
			T* Temp = new T[newCapacity];
			//拷贝元素
			memcpy(Temp,_Data,_size*sizeof(T));
			//释放旧空间
			delete[] _Data;
			//替换新空间
			_Data = Temp;
			_capacity = newCapacity;
		}
	}
private:
	T* _Data;
	size_t _capacity;
	size_t _size;
};

template<class T>
Seqlist<T>::~Seqlist()
{
	if(_Data)
	{
		delete[] _Data;
		_Data = nullptr;
		_capacity = 0;
		_size = 0;
	}
}

void TestSeqlist()
{
	Seqlist<int> s1;   
	Seqlist<double> s2;
	Seqlist<char> s3;

	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1[0] = 6;
	cout<< s1.Size()<<endl;
	cout<< s1.Front()<<endl;
	cout<< s1.Back()<<endl;
	s1.Clear();
	cout<<s1.Size()<<endl;
}

#include<string>
void Test()
{
	Seqlist<string> s;
	s.PushBack("0000");
	s.PushBack("1111");
	s.PushBack("2222");
	s.PushBack("3333");
	s.PushBack("4444");
	s.PushBack("5555");
	s.PushBack("6666");
	s.PushBack("7777");
	s.PushBack("8888");
	s.PushBack("9999");
}
int main()
{
	//TestSeqlist();
	Test();
	return 0;
}
#endif

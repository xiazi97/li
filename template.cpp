#pragma once
#include<assert.h>
#include<iostream>
using namespace std;

#if 0
//����һ�������ĺ���
template<class T>     //ģ������б� ����ʹ��template<typename T> ��������ʹ��struct 
T _Add(T left,T right)       //����ģ��
{
	return left + right;
}

template<class T>
void PrintfArray(T array,int size)  //������Լ�ת������
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
	//��ʽʵ����---���������ʽ������ת������Ҫ�û��Լ���ǿת/
	cout<< _Add(1,2) <<endl;   //����ʵ�����������������������ɴ���������͵ĺ���
	cout<< _Add(1,(int)2.0) <<endl;  //������Բ���Ϊ��ͬ����ʱ�޷��ж�����������Ҫ�Բ������д�����ǿת����

	//��ʽʵ����
	_Add<int>(1,2.2);
	_Add<>(1,2);    //��ʽʵ����
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

	//�������죺Seqlist(const Seqlist<T>& s);
	//��ֵ��������أ�Seqlist<T>& operator = (const Seqlist<T>& s)

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

	//��������λ��
	T& operator[](size_t index)               //���ܻ��޸�s[i]�е�Ԫ��
	{
		assert(index < _size);
		return _Data[index];
	}

	//��Ϊconst���͵Ķ����ܵ�����ͨ������������const�������
	const T& operator[](size_t index) const
	{
		assert(index < _size);
		return _Data[index];
	}

	//���ʵ�һ��Ԫ��
	T& Front()
	{
		return _Data[0];
	}

	const T& Front()const
	{
		return _Data[0];
	}

	//�������һ��Ԫ��
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
			//����ռ�
			T* Temp = new T[newCapacity];
			//����Ԫ��
			memcpy(Temp,_Data,_size*sizeof(T));
			//�ͷžɿռ�
			delete[] _Data;
			//�滻�¿ռ�
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
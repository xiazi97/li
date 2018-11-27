#include<iostream>
using namespace std;
template<class T>
class Vector
{
public:
	Vector()
		:_start(nullptr)
		,_last(nullptr)
		,_endOfStorage(nullptr)
	{}

	Vector(T* first,T* end)
	{
		size_t size = end - first;
		_start = new T[size];
		for(i=0;i<size;++i)
		{
			_start[i] = first[i];
			//������memcpy(_start, first, size*sizeof(T));���и�ֵ�������ǳ��������
			
		}
		_last = _start + size;
		_endOfStorage = _last;
	}

	Vector(size_t n,const T& val = T())
		:_start = new T[n]
		,_last = _start + n; 
		,_endOfStorage = _last;
	{
		for(size_t i=0;i<n;++i)
			_start[i] = val;
		//memset(_start ,val ,sizeof(T)*n)������
	}

	Vector(const Vector<T>& v)
		:_start(nullptr)
		,_last(nullptr)
		,endOfStorage(nullptr)
	{
		
	}
private:
	iterator _start;
	iterator _last;   //size
	iterator _endOfStorage;   //capacity
};

int main()
{

	return 0;
}
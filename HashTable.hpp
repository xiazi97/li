#include "Common.h"
#include<iostream>
#include<vector>
using namespace std;

template<class ValueType>
struct  HashNode
{
	HashNode(const ValueType& data)
		:_pNext(nullptr)
		,_data(data)
	{}

	HashNode<ValueType>* _pNext;
	ValueType _data;
};

template<class ValueType,class KOFV,class KTOINT>
class HashTable;

template<class ValueType,class KOFV,class KTOINT>
struct HashTableIterator
{
	typedef HashNode<ValueType> Node;
	typedef Node* PNode;
	typedef HashTableIterator<ValueType,KOFV,KTOINT> Self;
	typedef HashTable<ValueType,KOFV,KTOINT> HashTable;
private:
	PNode _pNode;
	HashTable* _pHT;

public:
	HashTableIterator(HashTable* pHT, PNode pNode = nullptr)
		:_pHT(pHT)
		,_pNode(pNode)
	{}

	HashTableIterator(const Self& s)
		:_pHT(s._pHT)
		,_pNode(s._pNode)
	{}

	ValueType& operator*()
	{
		return _pNode->_data;
	}

	ValueType* operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		Next();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Next();
		return temp;
	}

	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode && _pHT == s._pHT;
	}

	bool operator!=(const Self& s)const
	{
		return !(*this == s);
	}	

private:
	void Next()
	{
		if(_pNode->_pNext)
		{
			_pNode = _pNode->_pNext;
		}
		else
		{
			//找下一个非空桶
			size_t bucketNo = _pHT->HashFunc(_pNode->_data)+1; 
			for(;bucketNo < _pHT->_table.capacity();++bucketNo)
			{
				_pNode = _pHT->_table[bucketNo];
				if(_pNode)
					return;
			}
			_pNode = nullptr;
		}
	}
};

template<class ValueType,class KOFV,class KTOINT>
class HashTable
{
	friend HashTableIterator<ValueType,KOFV,KTOINT>;
	typedef HashNode<ValueType> Node;
	typedef Node* PNode;
	typedef HashTable<ValueType,KOFV,KTOINT> Self;
public:
	typedef HashTableIterator<ValueType,KOFV,KTOINT> Iterator;

private:
	vector<PNode> _table;
	size_t _size;

public:
	HashTable(size_t capacity=10)
		:_table(capacity)
		,_size(0)
	{}

	Iterator Begin()
	{
		for(size_t bucketNo = 0;bucketNo < _table.capacity();++bucketNo)
		{
			if(_table[bucketNo])
				return Iterator(this,_table[bucketNo]);
		}
		return End();
	}

	Iterator End()
	{
		return Iterator(this,nullptr);
	}

	pair<Iterator,bool> InsertUnique(const ValueType& data)
	{
		CheckCapacity();

		//1.计算哈希桶号
		size_t bucketNo = HashFunc(data);
		//2.检测该元素是否存在
		PNode pCur = _table[bucketNo];
		while(pCur)
		{
			if(KOFV()(data) == KOFV()(pCur->_data))
				return make_pair(Iterator(this,pCur),false);

			pCur = pCur->_pNext;
		}

		pCur = new Node(data);
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		return make_pair(Iterator(this,pCur),true);
	}

	size_t EraseUnique(const ValueType& data)
	{
		//1.找当前元素所在的桶号
		size_t bucketNo = HashFunc(data);
		PNode pCur = _table[bucketNo];
		PNode pPre = nullptr;
		while(pCur)
		{
			if(KOFV()(data) == KOFV()(pCur->_data))
			{
				//删除
				if(pPre == nullptr)  //删除的是头节点
				{
					_table[bucketNo] = pCur->_pNext;
				}
				else
				{
					pPre->_pNext = pCur->_pNext;
				}
				delete pCur;
				--_size;
				return 1;
			}
			else
			{
				pPre = pCur;
				pCur = pCur->_pNext;
			}
		}
		return 0;
	}

	Iterator InsertEqual(const ValueType& data)
	{
		CheckCapacity();
		size_t bucketNo = HashFunc(data);
		//2.找插入的位置
		PNode pCur = _table[bucketNo];
		while(pCur)
		{
			if(KOFV()(data) == KOFV()(pCur->_data))
				break;
			pCur = pCur->_pNext;
		}

		PNode pNewNode = new Node(data);
		if(nullptr == pCur)
		{
			pNewNode->_pNext = _table[bucketNo];
			_table[bucketNo] = pNewNode;
		}
		else
		{
			pNewNode->_pNext = pCur->_pNext;
			pCur->_pNext = pNewNode; 
		}
		++_size;
		return Iterator(this,pNewNode);
	}

	size_t EraseEqual(const ValueType& data)
	{
		size_t bucketNo = HashFunc(data);
		PNode pCur = _table[bucketNo];
		PNode pPre = nullptr;
		size_t oldSize = _size;
		while(pCur)
		{
			if(KOFV()(data) == KOFV()(pCur->_data))
			{
				//删除节点
				if(pPre == nullptr)
				{
					_table[bucketNo] = pCur->_pNext;
					delete pCur;
					pCur = _table[bucketNo];
				}
				else
				{
					pPre->_pNext = pCur->_pNext;
					delete pCur;
					pCur = pPre->_pNext;
				}
				--_size;
			}
			else
			{
				pPre = pCur;
				pCur = pCur->_pNext;
			}
			
		}
		return oldSize - _size;
	}

	bool Empty() const
	{
		return  0 == _size;
	}

	size_t Size()const
	{
		return _size;
	}

	Iterator Find(const ValueType& data)
	{
		size_t bucketNo = HashFunc(data);
		PNode pCur = _table[bucketNo];
		while(pCur)
		{
			if(KOFV()(data) == KOFV()(pCur->_data))
				return Iterator(this,pCur);

			pCur = pCur->_pNext;
		}
		return End();
	}

	size_t Count(const ValueType& data)
	{
		size_t bucketNo = HashFunc(data);
		PNode pCur = _table[bucketNo];
		size_t count = 0;
		while(pCur)
		{
			if(KOFV()(data) == KOFV()(pCur->_data))
				++count;

			pCur = pCur->_pNext;
		}
		return count;
	}

	void Clear()
	{
		for(int i=0;i<_table.capacity();++i)
		{
			PNode pCur = _table[i];
			while(pCur)
			{
				_table[i] = pCur->_pNext;
				delete pCur;
				pCur = _table[i];
			}
		}
		_size = 0;
	}

	void Swap(Self& ht)
	{
		_table.swap(ht._table);
		swap(_size,ht._size);
	}

	size_t BucketCount()const
	{
		return _table.capacity();
	}

	size_t BucketSize(size_t n)const
	{
		PNode pCur = _table[n];
		size_t count = 0;
		while(pCur)
		{
			++count;
			pCur = pCur->_pNext;
		}
		return count;
	}

	void PrintfHashTable()
	{
		for(size_t i=0;i<_table.capacity();++i)
		{
			PNode pCur = _table[i];
			cout << "_table[" << i <<"]:";
			while(pCur)
			{
				cout << pCur->_data <<"-->";
				pCur = pCur->_pNext;
			}
			cout <<"NULL"<< endl;
		}
		cout <<endl;
	}
private:
	size_t HashFunc(const ValueType& data)
	{
		//return KOFV()(data) % _table.capacity();       //在这里不知道data的数据类型，所以不能简单的当作Int去取模，需要进行以下类型转换
		return KTOINT()(KOFV()(data)) % _table.capacity(); 
	}

	void CheckCapacity()
	{
		if(_size == _table.capacity())
		{
			Self newHT(GetNextPrime(_size));
			/*相当于将节点翻倍
			for(size_t i=0;i<_table.capacity();++i)
			{
				PNode pCur = _table[i];
				while (pCur)
				{
					newHT.InsertEqual(pCur->_data);  //实际上是用数据去构造了一个新的节点
					pCur = pCur->_pNext;
				}
			}*/
			for(size_t i=0;i<_table.capacity();++i)
			{
				PNode pCur = _table[i];
				while (pCur)
				{
					_table[i] = pCur->_pNext;
					//将pCur节点插入到新哈希桶中
					size_t bucketNo = newHT.HashFunc(pCur->_data);
					PNode pPos = newHT._table[bucketNo];
					while (pPos)
					{
						if(KOFV()(pCur->_data) == KOFV()(pPos->_data))
							break;

						pPos = pPos->_pNext;
					}
					if(nullptr == pPos)
					{
						pCur->_pNext = newHT._table[bucketNo];
						newHT._table[bucketNo] = pCur;
					}
					else
					{
						pCur->_pNext = pPos->_pNext;
						pPos->_pNext = pCur;
					}
					pCur = _table[i];		
				}
			}

			this->Swap(newHT);
		}
	}
};

struct KeyOfValue
{
	int operator()(int data)
	{
		return data;
	}
};

void TestHashTable1()
{
	int array[] = {1,2,3,4,5,5,5,7,6,9};
	HashTable<int,KeyOfValue,KTOINTDEF<int>> ht;
	for(auto e : array)
		ht.InsertUnique(e);

	ht.PrintfHashTable();

	cout << ht.Size() <<endl;

	auto it = ht.Begin();
	while(it != ht.End())
	{
		cout << *it << " ";
			++it;
	}
	cout << ht.BucketCount() <<endl;
	cout <<ht.BucketSize(5) <<endl;
	ht.EraseUnique(5);
	ht.PrintfHashTable();
	it = ht.Begin();
	while(it != ht.End())
	{
		cout << *it << " ";
			++it;
	}
}

void TestHashTable2()
{
	int array[] = {1,2,3,4,5,5,5,7,6,9};
	HashTable<int,KeyOfValue,KTOINTDEF<int>> ht;
	for(auto e : array)
		ht.InsertEqual(e);

	ht.PrintfHashTable();

	cout << ht.Size() <<endl;

	auto it = ht.Begin();
	while(it != ht.End())
	{
		cout << *it << " ";
			++it;
	}
	cout << ht.BucketCount() <<endl;
	cout <<ht.BucketSize(5) <<endl;
	ht.InsertEqual(23);
	ht.EraseEqual(5);
	ht.PrintfHashTable();
	it = ht.Begin();
	while(it != ht.End())
	{
		cout << *it << " ";
			++it;
	}
}
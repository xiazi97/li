#include<iostream>
using namespace std;

namespace simulate_L
{
	template<class T>
	struct ListNode
	{
		ListNode(const T& data = T())    //给一个缺省值
			:_pPre(nullptr)
			,_pNext(nullptr)
			,_data(data)
		{}

		ListNode<T>* _pPre;
		ListNode<T>* _pNext;
		T _data;
	};

	//迭代器：将指针封装
	template<class T,class Ref,class Ptr>
	class ListIterator
	{
		typedef ListNode<T> Node;
		typedef Node* PNode;
		typedef ListIterator<T,Ref,Ptr> self;
	public:
		ListIterator(PNode pNode = nullptr)
			:_pNode(pNode)
		{}

		ListIterator(const self& li)
			:_pNode(li._pNode)
		{}

		Ref operator*()
		{
			return _pNode->_data;
		}

		Ptr operator->()
		{
			return *(operator*());
		}

		self& operator++()
		{
			_pNode = _pNode->_pNext;
			return *this;
		}

		self operator++(int)
		{
			Sele temp(*this);
			_pNode = _pNode->_pNext;
			return temp;
		}

		self& operator--()
		{
			_pNode = _pNode->_pPre;
			return *this;
		}

		self operator--(int)
		{
			Sele temp(*this);
			_pNode = _pNode->_pPre;
			return temp;
		}

		bool operator!=(const self& li)
		{
			return _pNode != li._pNode;
		}

		bool operator==(const self& li)
		{
			return _pNode ==li._pNode;
		}
		PNode _pNode;
	};

	template<class T>
	class list
	{
		typedef ListNode<T>  Node;
		typedef Node* PNode;
	public:
		typedef ListIterator<T,T&,T*> iterator;

	public:
		list()   //空链表
		{
			CreateHead();
		}

		list(size_t n,const T& data = T())   //n个值为data的元素
		{
			CreateHead();
			for(size_t i=0;i<n;++i)
			push_back(data);
		}

		list(T* first,T* last)      //根据区间构造
		{
			CreateHead();
			while (first != last)
				push_back(*first++);
		}

		list(const list<T>& l);   //拷贝构造
		list& operator=(const list<T>& l);  //赋值运算符重载

		~list()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}

		size_t size()const
		{
			size_t count = 0;
			PNode pCur = _pHead->_pNext;
			while(pCur != _pHead)
			{
				count++;
				pCur = pCur->_pNext;
			}
			return count;
		}

		void resize(size_t newSize,const T& data = T())
		{
			size_t oldSize = size();
			if(oldSize < newSize)
			{
				for(size_t i = oldSize;i<newSize;++i)
				push_back(data);
			}
			else
			{
				for(size_t i = newSize;i<oldSize;++i)
					pop_back();
			}
		}

		bool empty()const
		{
			return _pHead->_pNext = _pHead;
		}

		void clear()
		{
			PNode pCur = _pHead->_pNext;
			while(pCur != _pHead)
			{
				_pHead->_pNext = pCur->_pNext;
				delete pCur;
				pCur = _pHead->_pNext;
			}

			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}

		void push_back(const T& data)
		{
			PNode pNewNode = new Node(data);
			//链接新节点，不破坏原链表结构
			pNewNode->_pPre = _pHead->_pPre;
			pNewNode->_pNext = _pHead;
			//更新原链表结构
			pNewNode->_pPre->_pNext = pNewNode;
			_pHead->_pPre = pNewNode;
		}

		void pop_back()
		{
			PNode pDelNode = _pHead->_pPre;
			if(pDelNode != _pHead)
			{
				pDelNode->_pPre->_pNext = _pHead;
				_pHead->_pPre = pDelNode->_pPre;
				delete pDelNode;
			}
		}

		void push_front(const T& data)
		{
			PNode pNewNode = new Node(data);
			pNewNode->_pNext = _pHead->_pNext;
			pNewNode->_pPre = _pHead;
			pNewNode->_pNext->_pPre = pNewNode;
			_pHead->_pNext = pNewNode;
		}

		void pop_front()
		{
			PNode pDelNode = _pHead->_pNext;
			if(pDelNode != _pHead)
			{
				pDelNode->_pNext->_pPre = _pHead;
				_pHead->_pNext = pDelNode->_pNext;
				delete pDelNode;
			}
		}
		
		iterator insert(iterator pos,const T& data)
		{
			PNode pNewNode = new Node(data);

			pNewNode->_pNext = pos._pNode;
			pNewNode->_pPre = pos._pNode->_pPre;
			pNewNode->_pPre->_pNext = pNewNode;
			pNewNode->_pNext->_pPre = pNewNode;

			return iterator(pNewNode);
		}

		iterator erase(iterator pos)
		{
			if(pos._pNode == _pHead)
				return pos;
			PNode pRet = pos._pNode->_pNext;
			pos._pNode->_pPre->_pNext = pos._pNode->_pNext;
			pos._pNode->_pNext->_pPre = pos._pNode->_pPre;
			delete pos._pNode;

			return iterator(pRet);
		}

		iterator begin()
		{
			return iterator(_pHead->_pNext);
		}

		iterator end()
		{
			return iterator(_pHead);
		}

		T& front()
		{
			return _pHead->_pNext->_data;
		}

		const T& front()const
		{
			return _pHead->_pNext->_data;
		}

		T& back()
		{
			return _pHead->_pPre->_data;
		}

		const T& back()const
		{
			return _pHead->_pPre->_data;
		}

	public:
		void CreateHead()
		{
			_pHead = new Node;
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}
	private:
		PNode _pHead;
	};
}

#include<vector>

void PrintList(simulate_L::list<int>& l)
{
	for(auto& e : l)
		cout<< e<< " ";
	cout<<endl;

	//simulate_L::list<int>::iterator it = l.begin();
	auto it = l.begin();
	while(it != l.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

void Test1()
{
	simulate_L::list<int> l1;
	simulate_L::list<int> l2(10,5);
	PrintList(l2);
	//vector<int> v 目前匹配不到
	//simulate_L::list<int> l3(v.begin(),v.end());

	int array[] = {1,2,3,4,5,6,7,8,9,0};
	simulate_L::list<int> l3(array,array+sizeof(array)/sizeof(array[0]));
	PrintList(l3);
}

void Test2()
{
	int array[] = {1,2,3,4};
	simulate_L::list<int> l(array,array+sizeof(array)/sizeof(array[0]));
	PrintList(l);

	l.push_back(5);
	l.pop_back();
	PrintList(l);
	cout<<l.size()<<endl;

	l.push_front(0);
	l.pop_front();

	l.resize(10,8);
	cout<<l.size()<<endl;
	PrintList(l);

	l.resize(2);
	cout<<l.size()<<endl;
	PrintList(l);

	l.clear();
	cout<<l.size()<<endl;
}

int main()	
{
	//Test1();
	Test2();
	return 0;
}
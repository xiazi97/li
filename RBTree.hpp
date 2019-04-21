#pragma once
#include<iostream>
using namespace std;

enum Color{RED,BLACK};

template<class V>
struct RBTreeNode
{
	RBTreeNode(const V& data = V(),const Color color = RED)
		:_pLeft(nullptr)
		,_pRight(nullptr)
		,_pParent(nullptr)
		,_data(data)
		,_color(color)
	{}

	RBTreeNode<V>* _pLeft;
	RBTreeNode<V>* _pRight;
	RBTreeNode<V>* _pParent;
	V _data;
	Color _color;
};

template<class V>
class RBTree
{
	typedef RBTreeNode<V> Node;
	typedef Node* PNode;

private:
	PNode _pHead;
public:
	RBTree()
	{
		_pHead = new Node;       //ͷ�ڵ�
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
		_pHead->_pParent = nullptr;
	}

	~RBTree()
	{
		_Destroy(GetRoot());
	}

	bool Insert(const V& data)
	{
		PNode& pRoot = GetRoot();
		if(nullptr == pRoot)
		{
			pRoot = new Node(data,BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			//���ն��������������ʲ����½ڵ�
			PNode pCur = pRoot;
			PNode pParent = nullptr;
			while(pCur)
			{
				pParent = pCur;
				if(data < pCur->_data)
					pCur = pCur->_pLeft;
				else if(data > pCur->_data)
					pCur = pCur->_pRight;
				else
					return false;
			}

			//�����½ڵ�
			pCur = new Node(data);
			if(data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;

			//���½ڵ����ɫ
			while(pParent != _pHead && pParent->_color == RED)  ///��֤pParentһ�����ڣ���һ����Ϊ���ڵ�
			{
				PNode grandFather = pParent->_pParent;
				if(pParent == grandFather->_pLeft)
				{
					PNode uncle = grandFather->_pRight;
					//uncle������Ϊ��
					if(uncle && uncle->_color == RED)   //���һ
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						//�����
						if(pCur == pParent->_pRight)
						{
							RotateL(pParent);
							swap(pCur,pParent);
						}
						//�����
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else  //�������
				{
					PNode uncle = grandFather->_pLeft;
					if(uncle && uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						if(pCur == pParent->_pLeft)
						{
							RotateR(pParent);
							swap(pCur,pParent);
						}

						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateL(grandFather);
					}
				}
			}
		}

		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	void Inorder()
	{
		_Inorder(GetRoot());
	}

	bool IsRBTree()
	{
		PNode pRoot = GetRoot();
		if(nullptr == pRoot)
			return true;

		if(RED == pRoot->_color)
		{
			cout << "Υ������2�����ڵ����ɫΪ��ɫ"<< endl;
			return false;
		}

		size_t blackCount = 0;
		PNode pCur = pRoot;
		while(pCur)
		{
			if(BLACK == pCur->_color)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		size_t pathBlack = 0;
		return _IsRBTree(pRoot,blackCount,pathBlack);
	}

private:
	PNode& GetRoot()
	{
		return _pHead->_pParent;
	}

	bool _IsRBTree(PNode pRoot,size_t blackCount,size_t pathBlack)
	{
		if(nullptr == pRoot)
			return true;

		if(BLACK == pRoot->_color)
			pathBlack++;

		PNode pParent = pRoot->_pParent;
		if(pParent && pRoot->_color == RED && pParent->_color == RED)
		{
			cout << "Υ������3��������һ��ĺ�ɫ�ڵ�" <<endl;
			return false;
		}
		if(pRoot->_pLeft == nullptr && pRoot->_pRight == nullptr)
		{
			if(blackCount != pathBlack)
			{
				cout << "Υ������4��·���к�ɫ�ڵ�ĸ�������ͬ"<<endl;
				return false;
			}
		}
		return _IsRBTree(pRoot->_pLeft,blackCount,pathBlack) && _IsRBTree(pRoot->_pRight,blackCount,pathBlack);
	}

	PNode LeftMost()
	{
		PNode pRoot = GetRoot();
		if(pRoot == nullptr)
			return _pHead;

		PNode pCur = pRoot;
		while(pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}

	PNode RightMost()
	{
		PNode pRoot = GetRoot();
		if(pRoot == nullptr)
			return _pHead;

		PNode pCur = pRoot;
		while(pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}

	void RotateL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if(pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		PNode pPParent =  pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;

		PNode& pRoot = GetRoot();
		if(pRoot == pParent)
		{
			pRoot = pSubR;
		}
		else
		{
			if(pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}

	void RotateR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if(pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		PNode& pRoot = GetRoot();
		if(pParent == pRoot)
			pRoot = pSubL;
		else
		{
			if(pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}

	void _Inorder(PNode pRoot)
	{
		if(pRoot)
		{
			_Inorder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_Inorder(pRoot->_pRight);
		}
	}

	void _Destroy(PNode& pRoot)
	{
		if(pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
};


void TestRBTree()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	RBTree<int> t;
	for(auto e : a)
		t.Insert(e);

	t.Inorder();

	if(t.IsRBTree())
	{
		cout << "Yes" <<endl;
	}
	else
	{
		cout << "NO" <<endl;
	}
}
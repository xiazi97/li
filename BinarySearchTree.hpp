#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct BSTNode{
	T _data;
	BSTNode<T>* _pLeft;
	BSTNode<T>* _pRight;

	BSTNode(const T& data)
		:_data(data)
		,_pLeft(nullptr)
		,_pRight(nullptr)
	{}
};

template<class T>
class BSTree{
	typedef BSTNode<T> Node;
	typedef Node* PNode;
private:
	PNode _pRoot;

public:
	public:
	BSTree()
		: _pRoot(nullptr)
	{}

	~BSTree()
	{
		_Destroy(_pRoot);
	}

	bool Insert(const T& data)
	{
		if(nullptr == _pRoot){
			_pRoot = new Node(data);
			return true;
		}
		//�ǿ������ҵ�Ӧ�����λ��
		PNode pParent = nullptr;
		PNode pCur = _pRoot;  //��¼һ��pCur��˫��λ��
		while(pCur){
			pParent = pCur;
			if(data < pCur->_data)
				pCur = pCur->_pLeft;
			else if(data > pCur->_data)
				pCur = pCur->_pRight;
			else
				return true;
		}
		//����ڵ�
		pCur = new Node(data);
		if(data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		return true;
	}

	bool Erase(const T& data)
	{
		//�Ҵ�ɾ���ڵ��λ��
		PNode pCur = _pRoot;
		PNode pParent = nullptr;
		while(pCur)
		{
			//pParent = pCur;    ���ܷ����������ʱ���ҵ���ɾ���ڵ㣬���ǲ��ܼ�¼��˫�׵�λ��
			if(data == pCur->_data)
				break;
			else if(data < pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}
		if(nullptr == pCur)			//û���ҵ�
			return false;

		//�����ɾ���ڵ㣺
		//1.Ҷ�ӽڵ�||ֻ���Һ��ӣ�������Ϊ�ա��� pParnet->right = pCur->right;��Ϊ˫�׵��Һ��ӣ� ���� pParent->left = pCur->right��Ϊ˫�׵����ӣ�;(��ɾ���ڵ�Ϊ�Ǹ��ڵ�)  Ϊ���ڵ������pRootȻ��ֱ��ɾ���ڵ㼴��
		//2.ֻ������
		//3.���Һ��Ӿ�����
		if(nullptr == pCur->_pLeft)   //���1
		{
			if(_pRoot == pCur)
				_pRoot = pCur->_pRight;
			else
			{
				if(pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pRight;
				else
					pParent->_pRight = pCur->_pRight;
			}
		}

		else if(nullptr == pCur->_pRight)  //���2
		{
			if(pCur == _pRoot)
				_pRoot = pCur->_pLeft;
			else
			{
				if(pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pLeft;
				else
					pParent->_pRight = pCur->_pLeft;
			}
		}
		else
		{
			//���Һ��Ӿ�����---����ֱ��ɾ������һ������ڵ�
			//���������������ң������������Ҳ�ڵ�
			//Ҳ���������������ң��������������ڵ�
			PNode pFirstOfIn = pCur->_pRight;
			PNode pParent = pCur;
			while(pFirstOfIn->_pLeft)
			{
				pParent = pFirstOfIn;
				pFirstOfIn = pFirstOfIn->_pLeft;
			}//�ҵ��������������ڵ�,����ڵ㣬һ��û�����ӣ��������Һ���

			pCur->_data = pFirstOfIn->_data;
			//ɾ������ڵ�
			if(pFirstOfIn == pParent->_pLeft)
				pParent->_pLeft = pFirstOfIn->_pRight;
			else
				pParent->_pRight = pFirstOfIn->_pRight;
			pCur = pFirstOfIn;
		}
		delete pCur;
		return true;
	}

	void Inorder()
	{
		_InOrder(_pRoot);
	}

	PNode Find(const T& data)
	{
		PNode pCur = _pRoot;
		while (pCur)
		{
			if(data < pCur->_data)
				pCur = pCur->_pLeft;
			else if(data > pCur->_data)
				pCur = pCur->_pRight;
			else
				return pCur;
		}
		return nullptr;
	}

private:
	void _InOrder(PNode _pRoot)  //�������
	{
		if (_pRoot)
			{
				_InOrder(_pRoot->_pLeft);
				cout << _pRoot->_data << " ";
				_InOrder(_pRoot->_pRight);
			}
	}

	void _Destroy(PNode& pRoot)
	{
		if (pRoot)  //��������
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
		
	}
};


void TestBSTree()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	BSTree<int> t;
	for(auto e : a)
		t.Insert(e);

	t.Inorder();

	BSTNode<int>* pNode = t.Find(0);
	if(pNode)
		cout << "Yes"<<endl;
	else
		cout << "No"<<endl;

	t.Erase(6);
	t.Inorder();
	cout <<endl;
	t.Erase(8);
	t.Inorder();
	cout <<endl;
	t.Erase(5);
	t.Inorder();
}
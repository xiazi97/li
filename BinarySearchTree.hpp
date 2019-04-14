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
		//非空则先找到应插入的位置
		PNode pParent = nullptr;
		PNode pCur = _pRoot;  //记录一下pCur的双亲位置
		while(pCur){
			pParent = pCur;
			if(data < pCur->_data)
				pCur = pCur->_pLeft;
			else if(data > pCur->_data)
				pCur = pCur->_pRight;
			else
				return true;
		}
		//插入节点
		pCur = new Node(data);
		if(data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		return true;
	}

	bool Erase(const T& data)
	{
		//找待删除节点的位置
		PNode pCur = _pRoot;
		PNode pParent = nullptr;
		while(pCur)
		{
			//pParent = pCur;    不能放在这里，这里时能找到待删除节点，但是不能记录下双亲的位置
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
		if(nullptr == pCur)			//没有找到
			return false;

		//分情况删除节点：
		//1.叶子节点||只有右孩子，则左孩子为空—— pParnet->right = pCur->right;（为双亲的右孩子） 或者 pParent->left = pCur->right（为双亲的左孩子）;(待删除节点为非根节点)  为根节点则更新pRoot然后直接删除节点即可
		//2.只有左孩子
		//3.左右孩子均存在
		if(nullptr == pCur->_pLeft)   //情况1
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

		else if(nullptr == pCur->_pRight)  //情况2
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
			//左右孩子均存在---不能直接删除，找一个替代节点
			//可以在左子树中找：左子树中最右侧节点
			//也可以在右子树中找：右子树中最左侧节点
			PNode pFirstOfIn = pCur->_pRight;
			PNode pParent = pCur;
			while(pFirstOfIn->_pLeft)
			{
				pParent = pFirstOfIn;
				pFirstOfIn = pFirstOfIn->_pLeft;
			}//找到右子树的最左侧节点,替代节点，一定没有左孩子，可能有右孩子

			pCur->_data = pFirstOfIn->_data;
			//删除替代节点
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
	void _InOrder(PNode _pRoot)  //中序遍历
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
		if (pRoot)  //后序销毁
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
#include <iostream>
using namespace std;

template<class T>
struct AVLTreeNode{
	AVLTreeNode(const T& data)
		:_pLeft(nullptr)
		,_pRight(nullptr)
		,_pParent(nullptr)
		,_data(data)
		,_bf(0) //平衡因子
	{}

	AVLTreeNode<T>* _pLeft;
	AVLTreeNode<T>* _pRight;
	AVLTreeNode<T>* _pParent;
	T _data;
	int _bf;   //平衡因子
};


template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
	typedef Node* PNode;

private:
	PNode _pRoot;

public:
	AVLTree()
		:_pRoot(nullptr)
	{}

	~AVLTree()
	{
		_Destroy(_pRoot);
	}

	bool Insert(const T& data)
	{
		if(nullptr == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}
	
		//寻找要插入节点位置
		PNode pCur = _pRoot;
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
		
		//插入数据
		pCur = new Node(data);
		if(data < pParent->_data)
			pParent->_pLeft = pCur;
		else if(data > pParent->_data)
			pParent->_pRight = pCur;

		pCur->_pParent = pParent;

		//插入之前，pParent:-1/0/1
		//更新平衡因子
		while(pParent)
		{
			if(pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			if(0==pParent->_bf)//高度未发生改变
				break;
			else if(-1 == pParent->_bf || 1 == pParent->_bf)//高度增加了
			{
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{
				//pParent的平衡因子为2或者-2，违反了AVL树的平衡性，需要进行旋转处理
				//新节点插入在
				if(2 == pParent->_bf)
				{
					if(1 == pCur->_bf)
						RotateL(pParent);
					else
						RotateRL(pParent);
				}
				else
				{
					if(-1 == pCur->_bf)
						RotateR(pParent);
					else
						RotateLR(pParent);
				}
				break;
			}
		}	
		return true;
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

		if(nullptr == pPParent)
			_pRoot = pSubL;
		else
		{
			if(pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}

		pParent->_bf = pSubL->_bf = 0;
	}

	void RotateL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if(pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		PNode pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;

		if(nullptr == pPParent)
			_pRoot = pSubR;
		else
		{
			if(pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}

		pParent->_bf = pSubR->_bf = 0;
	}

	void RotateRL(PNode pParent)
	{
		PNode pSubR = pParent->_pRight;
		PNode pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;

		RotateR(pParent->_pRight);
		RotateL(pParent);

		if(1 == bf)
			pParent->_bf = -1;
		else if(-1 == bf)
			pSubR->_bf = 1;
	}

	void RotateLR(PNode pParent)
	{
		PNode pSubL = pParent->_pLeft;
		PNode pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;

		RotateL(pParent->_pLeft);
		RotateR(pParent);

		//更新平衡因子
		if(1 == bf)
		{
			pSubL->_bf = -1;
		}
		else if(-1 == bf)
		{
			pParent->_bf = 1;
		}
	}

	void Inorder()
	{
		_Inorder(_pRoot);
	}

	bool IsAVLTree()
	{
		return _IsAVLTree(_pRoot);
	}


private:
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

	void _Inorder(PNode pRoot)
	{
		if(pRoot)
		{
			_Inorder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_Inorder(pRoot->_pRight);
		}
	}

	int _Height(PNode pRoot)
	{
		if(nullptr == pRoot)
			return 0;
		int leftHeight = _Height(pRoot->_pLeft);
		int rightHeight = _Height(pRoot->_pRight);

		return leftHeight>rightHeight ? leftHeight+1 : rightHeight+1;
	}

	bool _IsAVLTree(PNode pRoot)
	{
		if(nullptr == pRoot)
			return true;
		int leftHeight = _Height(pRoot->_pLeft);
		int rightHeight = _Height(pRoot->_pRight);

		if(abs(pRoot->_bf)>1 || rightHeight - leftHeight != pRoot->_bf)
			return false;
		return _IsAVLTree(pRoot->_pLeft) && _IsAVLTree(pRoot->_pRight);
	}
	
};



void TestAVLTree()
{
	int a[] = {4,2,6,1,3,5,15,7,16,14};//{5,3,4,1,7,8,2,6,0,9};
	AVLTree<int> t;
	for(auto e : a)
		t.Insert(e);

	t.Inorder();

	if(t.IsAVLTree())
		cout << "Yes"<<endl;
	else
		cout << "NO" <<endl;
}

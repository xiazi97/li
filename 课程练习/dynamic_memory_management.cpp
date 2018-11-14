#include<iostream>
using namespace std;
#if 0
class Test
{
public:
	Test()
	{
		cout<< "Test()" << this << endl;
		_data = 0;
	}

	~Test()
	{
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};




int main()
{
	Test* pt = new Test[10];
	delete[] pt;
	//delete pt ;  ��ʱ����������ԭ��  1.�ڴ�й©   
	//2.delete����һ��������ɺ����Ҫ�ͷſռ䣬�������������ṩ��������������ʱ�ռ��׵�ַ���ڲ����ڵ�һ�����󴦣�����Ҫ���4���ֽڣ����Ի������������������
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test()
	{
		cout<< "Test()" << this << endl;
		_data = 0;
	}

	void* operator new(size_t size)   //��������ﶨ���ˣ���ôĬ��ʹ�õ����������Լ������
	{
		return malloc(size);
	}

	~Test()
	{
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};

void* operator new(size_t size,char* funcName,int lineNo)    //����û��Զ���ʱ����һ����������Ҫ��һ���ֽ��������ҷ������ͱ���ҪΪvoid*��Ҳ������ӱ�Ĳ���
{
	cout<<funcName<<":"<<lineNo<<endl;
	return malloc(size);
}

//#define new new(__FUNCDNAME__,__LINE__)

int main()
{
	Test* pt = new Test; 
//	Test* pt = new Test;		//�ڵ����Զ���new����ʱ����ʹ��new Test(),�൱��ֻ�Ǹ��˺�������һ���ֽ�������û�д���Ĳ��������Բ����ܴ�ӡ���������,��Ҫ�������
	delete pt;
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data)
	{
		cout<< "Test()" << this << endl;
		_data = data;
	}

	~Test()
	{
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};

int main()
{//�������Դ����Զ������ͣ������Դ�����������
	int array[10];
	new(array+3) int(3);
	//��λnew���ʽ
	Test* pt = (Test*)malloc(sizeof(Test));
	new(pt) Test(10);
	/*
	Test* pt1 = new Test(10);����Ҫ��������ռ䲢���ص�
	����λnew���ʽ��ʱ�Ѿ��пռ䣬����ֱ�ӷ��ظöοռ伴��
		void* operator new(size_t size,void* p)
		{
			return p;
		}
		call Test();
	*/

	//delete pt;
	pt->~Test();
	free(pt);
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data)
	{
		cout<< "Test()" << this << endl;
		_data = data;
	}

	~Test()
	{
		delete this;    //��ʱthis�ȼ���pt���ٴε���delete��ѭ�����������������Ӷ��������޵ݹ飬���Բ�Ҫ������������delete��this
		cout<< "~Test()" << this << endl;
	}
private:
	int _data;
};

int main()
{
	Test* pt = new Test(10);
	delete pt;
	return 0;
}
#endif


#if 0
//���һ���࣬����ֻ���ڶ��ϴ�������
class Data
{
public:
	static Data* CreateObject(int data)
	{
		return new Data(data);
	}
private:
	Data(int data)
	{
		cout<<"Data():"<<this<<endl;
	}
	Data(const Data& t);
private:
	int _data;
};

int main()
{
	Data* T = Data::CreateObject(10);
	delete T;
	//Data(*T);��������Ҳ��������
	return 0;
}
#endif

#if 0
class Data
{
public:
	static Data Create()   //ȱ��һ�����������û���Ż����ܻ���ÿ������캯��
	{
		return Data();
	}

	Data(const Data& t)
	{
		cout<< "Data(const Data& t):"<<this	<<endl;
	}

private:
	Data();
};

class Test
{
public:
	Test()
	{
		Data::Create();    
	}
};


Data s; 
//ȱ�������ʱs�����ݶΣ��ڽ���������֮ǰ��Ҫ��s����ã����Ѿ�������Test������ֻҪ���ú����ͱض�Ҫʹ��ջ�Ŀռ䣬����ʵ���Ķ���Data::Create();Ҳ����ջ��
#endif

#if 0

#include<stdio.h>
#include<windows.h>
#include<assert.h>

typedef int DataType;

typedef struct ListNode
{
	DataType data;
	struct ListNode *next;
}ListNode;

void ListInit(ListNode** ppFirst)
{
	assert(ppFirst != NULL);
	*ppFirst = NULL;
}

void ListDestroy(ListNode** ppFirst)
{
	*ppFirst = NULL;
}

ListNode* CreatNode(DataType data)
{
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void ListPushFront(ListNode** ppFirst,DataType data)
{
	ListNode* newNode = CreatNode(data);
	assert(ppFirst!=NULL);
	newNode->next = *ppFirst;
	*ppFirst = newNode;
}

void ListPushBack(ListNode** ppFirst,DataType data)
{
	ListNode* newNode = CreatNode(data);
	ListNode* cur = *ppFirst;
	if(*ppFirst == NULL)
	{
		*ppFirst = newNode;
		return;
	}
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = newNode;
}

void ListPopFront(ListNode** ppFirst)
{
	ListNode *del = *ppFirst;
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	*ppFirst = del->next;
	free(del);
}

void ListPopBack(ListNode** ppFirst)
{
	ListNode* cur = *ppFirst;
	ListNode* del;
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	if((*ppFirst)->next ==NULL)
	{
		free(*ppFirst);
		*ppFirst = NULL;
		return;
	}
	while(cur->next->next != NULL)
	{
		cur = cur->next;
	}
	del = cur->next;
	cur->next = NULL;
	free(del);
}

ListNode* ListFind(ListNode* first,DataType data)
{
	ListNode* cur = first;
	for(cur;cur != NULL;cur=cur->next)
	{
		if(data == cur->data)
		{
			return cur;
		}
	}
	return NULL;
}

void ListInsert(ListNode** ppFirst,ListNode* pos,DataType data)
{
	ListNode* cur = *ppFirst;
	ListNode* newNode = CreatNode(data);
	if(*ppFirst == pos)
	{
		ListPushFront(ppFirst,data);
		return;
	}
	while(cur->next!=pos)
	{
		cur=cur->next;
	}
	newNode->next = cur->next;
	cur->next = newNode;
}

void ListDele(ListNode** ppFirst,ListNode* pos)
{
	ListNode* cur = *ppFirst;
	if(*ppFirst == pos){
		ListPopFront(ppFirst);
	return;
	}
	while(cur->next != pos)
	{
		cur = cur->next;
	}
	cur->next = pos->next;
	free(pos);
}

void ListPrintf(ListNode* first)
{
	ListNode* cur = first;
	for(cur;cur!=NULL;cur=cur->next)
	{
		printf("%d->",cur->data);
	}
	printf("NULL\n");
}
	/*void Test()
	{
		ListNode* first;
		ListInit(&first);
		ListPushBack(&first,1);
		ListPushBack(&first,2);
		ListPushBack(&first,3);

		ListPopFront(&first);
		ListPopBack(&first);
		ListPopBack(&first);
	}*/


//��β��ͷ��ӡ������
void PrintReverse(ListNode* first)
{
	ListNode* end = NULL;
	while (end != first)
	{
		ListNode* cur = first;
		while(cur->next !=end)
		{
		cur = cur->next;
		}
		printf("%d",cur->data);
		end = cur;
	}
}
/*�ݹ���*/
void PrintReverse1(ListNode* first)
{
	//ֻ��һ�����
	if(first->next == NULL)
	{
		printf("%d",first->data);
	}else
	{
		PrintReverse1(first->next);//����first��������нڵ�ȫ����ӡ
		printf("%d",first->data);
	}
}

	void PrintReverse2(ListNode* first)
	{
		if(first == NULL)
		{
			return;
		}
		PrintReverse2( first->next);
		printf("%d",first->data);
	}

	void TestPrintfReverse()
	{
		ListNode* first = NULL;
		ListPushBack(&first,1);
		ListPushBack(&first,2);
		ListPushBack(&first,3);
		ListPushBack(&first,4);
		
		PrintReverse2(first);
	}
	
//ɾ��һ����ͷ����ķ�β�ڵ㣨���ܱ�������
	void RemoveNFirst(ListNode* pos)
	{
		ListNode* newNode = pos->next;
		pos->data = pos->next->data;
		pos->next = pos->next->next;
		free(newNode);
	}

//����һ���ڵ㣨���ܱ�������
	void InsertNFirst(ListNode* pos,DataType data)
	{
		ListNode* del = CreatNode(data);
		del->data = pos->data;
		del->next = pos->next;
		pos->next = del;
		pos->data = data;
	}

	
	
//��������

	ListNode* RerverseList1(ListNode* first)
	{
		ListNode* del = first;
		ListNode* node ;
		ListNode* result;
		while(del !=NULL)
		{
			node = del;
			del = del->next;
			node->next = result;
			result = node;
		}
		return result;
	}


	ListNode* RerverseList2(ListNode* first)
	{
		ListNode* p1,*p2,*p3;

		p1 = NULL;
		p2 = first;
		p3 = first->next;

		while(p2 != NULL)
		{
			p2->next = p1;         //ʹ���׽��ָ��ΪNULL
			p1 = p2;               //p1ָ��ԭ�����׽��
			p2 = p3;               //p2ָ��ԭ���ĵڶ����ڵ�
			if(p3 != NULL)
			{
				p3 = p3->next;
			}
		}
		return p1;
	}


//Լɪ��
ListNode *Joseph(ListNode* first,int k)
{
	ListNode* tail = first;
	ListNode* cur =first;
	while(tail->next !=NULL)
	{
		tail = tail->next;
	}
	tail->next = first;
	while(cur->next !=cur)
	{
		ListNode* del = NULL;
		int i =0;
		for(i=0;i<k;i++)
		{
			del = cur;
			cur = cur->next;
		}
		del->next = cur->next;
		free(cur);
		cur = del->next;
	}
	cur->next = NULL;
	return cur;
}


void TestJoseph()
{
	ListNode* first = NULL;
	ListNode* del = NULL;
	int i =0 ;
	for(i=0;i<=5;i++)
	{
		ListPushBack(&first,i);
	}
	del = Joseph(first,2);
	printf("%d\n",del->data);
}
void InsertNF()
{
	ListNode* first = NULL;
	ListPushBack(&first,1);
	ListPushBack(&first,2);
	ListPushBack(&first,3);
	ListPushBack(&first,4);
	InsertNFirst(first,6);
	ListPrintf(first);
}

//�ϲ��������������ϲ�����Ȼ����
ListNode* Admix(ListNode* list1,ListNode* list2)
{
	ListNode* cur1 = list1;
	ListNode* cur2 = list2;
	ListNode* result = NULL;       //�������
	ListNode* tail = NULL;         //������������һ����㣬����β��
	ListNode* next;                //������������е���һ�����

	while(cur1 != NULL && cur2 !=NULL)
	{
		if(cur1->data <= cur2->data)   //��ʱӦȡcur1�еĽ��
		{
			if(result != NULL)           //�������Ϊ����ֱ�������һ�������������
			{
				//����cur1����һ����㣬ʹ��ѭ������
				next = cur1->next;
				tail->next = cur1;
				cur1->next = NULL;
				//�����µ����һ�����
				tail = cur1;
				cur1 = next;
			}else
			{
				next = cur1->next;     //����cur1����һ�����
				result = cur1;
				cur1->next = NULL;
				//�����µ����һ�����
				tail = cur1;
				cur1 = next;
			}
		}else
		{
			//Ӧȡ����2�Ľ��
			if(result != NULL)
			{
				next = cur2->next;
				tail->next = cur2;
				cur2->next = NULL;
				tail  = cur2;
				cur2 = next;
			}
			else
			{
				next = cur2->next;
				result = cur2;
				cur2->next = NULL;
				tail =  cur2;
				cur2 = next;
			}
		}
	}
	if(cur1 == NULL)
	{
		tail->next = cur2;
	}
	if(cur2 == NULL)
	{
		tail->next = cur1;
	}
	return result;
}


//��������������������ͬ������
void PrintfIntersection(ListNode* list1,ListNode* list2)
{
	ListNode* cur1 = list1;
	ListNode* cur2 = list2;
	while (cur1 != NULL && cur2 != NULL)
	{
		if(cur1->data < cur2->data)
		{
			cur1 = cur1->next;
		}else if(cur1->data > cur2->data)
		{
			cur2 = cur2->next;
		}
		else{
			printf("%d",cur1->data);
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
	}
}

//�ж����������Ƿ��ཻ�����ཻ���󽻵�
void PrintfIntersectionDup(ListNode* list1,ListNode* list2)
{
	ListNode* cur1 = list1;
	ListNode* cur2 = list2;
	DataType data;

	while(cur1 != NULL && cur2 !=NULL)
	{
		if(cur1->data <cur2->data){
			cur1 = cur1->next;
		}else if(cur1->data > cur2->data){
			cur2 = cur2->next;
		}
		else{
			printf("%d",cur1->data);
			data = cur1->data;
			while(cur1 != NULL && cur1->data ==data)
			{
				cur1 = cur1->next;
			}
			while(cur2 != NULL && cur2->data ==data)
			{
				cur2 = cur2->next;
			}
		}
	}
} 
#endif
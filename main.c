#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<windows.h>
typedef int StackDateType;
#define MAX_SIZE 100
typedef struct Stack{
	StackDateType array[MAX_SIZE];
	int top;        //��ʾ��ǰ����
}Stack;

//��ʼ��/����
//����ֻ�ܴ�ջ�����У�/ɾ��ֻ��ɾ��ջ����/�飨ֻ�ܲ鿴ջ��Ԫ�أ�
//��->˳����β��
//ɾ->˳����βɾ

void StackInit(Stack* pStack)
{
	pStack->top = 0;
}

void StackDestroy(Stack* pStack)
{
	pStack->top = 0;
}

void StackPush(Stack* pStack,StackDateType data)
{
	assert(pStack->top < MAX_SIZE);
	pStack->array[pStack->top] = data;
	pStack->top++;
}

void StackPop(Stack* pStack)
{
	assert(pStack->top > 0);
	pStack->top--;
}

StackDateType StackTop(const Stack* pStack)
{
	assert(pStack->top > 0);
	return pStack->array[pStack->top-1];  //����ջ��Ԫ��
}

int StackSize(const Stack* pStack)
{
	return pStack->top;
}

int StackFull(const Stack* pStack)
{
	return pStack->top >= MAX_SIZE;
}

int StackEmpty(const Stack* pStack)
{
	return pStack->top <= 0;
}

void BracketMatch(const char* sequence,int size)
{
	Stack stack;
	char ch;
	char leftBracket;
	int i =0;
	StackInit(&stack);
	for(i = 0;i<size;i++)
	{
		ch = sequence[i];
		switch(ch)
		{
		case'(':
		case'{':
		case'[':
			StackPush(&stack,(StackDateType)ch);
			break;
		case')':
		case'}':
		case']':
			if(StackEmpty(&stack))
			{
				printf("�����Ŷ�\n");    //��ʱջΪ�գ�Ȼ��ջ�⻹������һ�������ţ�����Ϊ�����Ŷ�
				StackDestroy(&stack);
				return;
			}
			leftBracket = (char)StackTop(&stack);
			StackPop(&stack);
			if(leftBracket=='(' && ch !=')')
			{
				printf("��ƥ��\n");
				return;
			}
			if(leftBracket=='{' && ch !='}')
			{
				printf("��ƥ��\n");
				return;
			}
			if(leftBracket=='[' && ch !=']')
			{
				printf("��ƥ��\n");
				return;
			}
		default:
			break;
			}
		}
		if(!StackEmpty(&stack))
		{
			printf("�����Ŷ�\n");
			return;
		}
		printf("����ƥ��\n");
	}
int main()
{
	int i = 0;
		const char* seqs[] ={
			"(())abc{[(])}",
			"(()))abc{[]}",
			"(()()abc{[]}",
			"(())abc{[]()}"
		};
		for(i=0;i<4;i++)
		{
			BracketMatch(seqs[i],strlen(seqs[i]));
		}
		system("pause");
		return 0;
}
	
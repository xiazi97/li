#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<windows.h>
typedef int StackDateType;
#define MAX_SIZE 100
typedef struct Stack{
	StackDateType array[MAX_SIZE];
	int top;        //表示当前个数
}Stack;

//初始化/销毁
//增（只能从栈顶进行）/删（只能删除栈顶）/查（只能查看栈顶元素）
//增->顺序表的尾插
//删->顺序表的尾删

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
	return pStack->array[pStack->top-1];  //返回栈顶元素
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
				printf("右括号多\n");    //此时栈为空，然而栈外还有至少一个右括号，所以为右括号多
				StackDestroy(&stack);
				return;
			}
			leftBracket = (char)StackTop(&stack);
			StackPop(&stack);
			if(leftBracket=='(' && ch !=')')
			{
				printf("不匹配\n");
				return;
			}
			if(leftBracket=='{' && ch !='}')
			{
				printf("不匹配\n");
				return;
			}
			if(leftBracket=='[' && ch !=']')
			{
				printf("不匹配\n");
				return;
			}
		default:
			break;
			}
		}
		if(!StackEmpty(&stack))
		{
			printf("左括号多\n");
			return;
		}
		printf("正常匹配\n");
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
	
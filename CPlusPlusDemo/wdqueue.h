#pragma once
#include "myinclude.h"
#include "wdstack.h"

#pragma region 队列的顺序存储
#define MaxSize 50
//队列的顺序存储类型
typedef struct
{
	int data[MaxSize];
	int front, rear;	//front指向队头元素，rear指向队尾元素的下一个位置
}SqQueue;

#pragma region 顺序队列之普通队列的基本操作
void InitQueue(SqQueue& Q)
{
	Q.front = Q.rear = 0;
}

bool QueueEmpty(SqQueue Q)
{
	if (Q.rear == 0 && Q.front == Q.rear)
		return true;
	return false;
}

//队满，可能出现假溢出现象
bool QueueOverflow(SqQueue Q)
{
	if (Q.rear == MaxSize)
		return true;
	return false;
}

bool EnQueue(SqQueue& Q, int x)
{
	if (Q.rear == MaxSize)	//队满，可能出现假溢出现象
		return false;
	Q.data[Q.rear++] = x;
	return true;
}

bool DeQueue(SqQueue& Q, int& x)
{
	if (Q.rear == 0 && Q.front == Q.rear)	//队空
		return false;
	x = Q.data[Q.front++];
	return true;
}

bool GetHead(SqQueue Q, int& x)
{
	if (Q.rear == 0 && Q.front == Q.rear)	//队空
		return false;
	x = Q.data[Q.front];
	return true;
}
#pragma endregion

#pragma region 顺序队列之循环队列的基本操作
void InitCQueue(SqQueue& CQ)
{
	CQ.front = CQ.rear = 0;
}

bool CQueueEmpty(SqQueue CQ)
{
	if (CQ.front == CQ.rear)
		return true;
	return false;
}

bool CQueueOverflow(SqQueue CQ)
{
	if ((CQ.rear + 1) % MaxSize == CQ.front)
		return true;
	return false;
}

bool EnCQueue(SqQueue& CQ, int x)
{
	if ((CQ.rear + 1) % MaxSize == CQ.front)	//队满
		return false;
	CQ.data[CQ.rear] = x;
	CQ.rear = (CQ.rear + 1) % MaxSize;
	return true;
}

bool DeCQueue(SqQueue& CQ, int& x)
{
	if (CQ.front == CQ.rear)	//队空
		return false;
	x = CQ.data[CQ.front];
	CQ.front = (CQ.front + 1) % MaxSize;
	return true;
}
#pragma endregion
#pragma endregion

#pragma region 队列的链式存储
//链队
typedef struct
{
	LNode* front, * rear;	//头指针指向队头结点，尾指针指向队尾结点
}LinkQueue;

#pragma region 链队之普通队列的基本操作
void InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (LNode*)malloc(sizeof(LNode));	  //建立头结点
	Q.front->next = nullptr;
}

bool QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return true;
	return false;
}

//假定内存无限大，则永远不可能出现内存满
bool QueueOverflow(LinkQueue Q)
{
	return false;
}

void EnQueue(LinkQueue& Q, int x)
{
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = x;
	s->next = nullptr;
	Q.rear->next = s;
	Q.rear = s;
}

bool DeQueue(LinkQueue& Q, int& x)
{
	if (Q.front == Q.rear)	//空队
		return false;
	LNode* p = Q.front->next;
	x = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return true;
}

void DestroyQueue(LinkQueue& Q)
{
	int x;
	while (!QueueEmpty(Q))
		DeQueue(Q, x);
}

void PrintQueue(LinkQueue Q)
{
	LNode* p = Q.front->next;
	while (p != nullptr)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
#pragma endregion

#pragma region 链队之循环队列的基本操作
void InitCQueue(LinkQueue& CQ)
{
	CQ.front = CQ.rear = (LNode*)malloc(sizeof(LNode));	//建立头结点,front指向队头结点,rear指向队尾结点的下一个位置
	CQ.rear->next = CQ.front;
}

bool CQueueEmpty(LinkQueue CQ)
{
	if (CQ.front == CQ.rear)
		return true;
	return false;
}

bool CQueueOverflow(LinkQueue CQ)
{
	if (CQ.rear->next == CQ.front)
		return true;
	return false;
}

void EnCQueue(LinkQueue& CQ, int x)
{
	if (CQueueOverflow(CQ))
	{
		//在rear后插入一个新的空闲结点
		auto s = (LNode*)malloc(sizeof(LNode));
		s->next = CQ.rear->next;
		CQ.rear->next = s;
	}
	CQ.rear->data = x;
	CQ.rear = CQ.rear->next;
}

bool DeCQueue(LinkQueue& CQ, int& x)
{
	if (CQueueEmpty(CQ))
		return false;
	x = CQ.front->data;
	CQ.front = CQ.front->next;
	return true;
}
#pragma endregion

#pragma endregion

#pragma region 3.2 综合题
#pragma region 1 循环队列中元素全部利用，设置标志域tag，并以tag的值为0或1来区分front=rear时队列状态是空还是满
typedef struct
{
	int data[MaxSize];
	int front, rear;	//front指向队头元素，rear指向队尾元素的下一个位置
	int tag;
}SqQueueWithTag;

void InitCQueue(SqQueueWithTag& CQ)
{
	CQ.front = CQ.rear = 0;
}

bool EnCQueue(SqQueueWithTag& CQ, int x)
{
	if (CQ.tag == 1 && CQ.front == CQ.rear)	//队满
		return false;
	CQ.data[CQ.rear] = x;
	CQ.rear = (CQ.rear + 1) % MaxSize;
	return true;
}

bool DeCQueue(SqQueueWithTag& CQ, int& x)
{
	if (CQ.tag == 0 && CQ.front == CQ.rear)	//队空
		return false;
	x = CQ.data[CQ.front];
	CQ.front = (CQ.front + 1) % MaxSize;
	return true;
}
#pragma endregion

//2 使用空栈S将队列Q中的元素逆置
//时间O(n),空间O(1),n为队列长度
void QueueReverse(SqQueue& Q)
{
	if (Q.front == Q.rear)	//队空
		return;
	SqStack S;
	InitStack(S);
	while (!QueueEmpty(Q))
	{
		int x;
		DeQueue(Q, x);
		Push(S, x);
	}
	while (!StackEmpty(S))
	{
		int x;
		Pop(S, x);
		EnQueue(Q, x);
	}
}

#pragma region 3 利用两个栈来模拟一个队列
typedef struct
{
	SqStack S1, S2;	//S1用于保存元素，S2用于调整元素顺序
}QueueUsing2Stacks;

bool EnQueue(QueueUsing2Stacks& Q, int x)
{
	if (StackOverflow(Q.S1))
		return false;
	Push(Q.S1, x);
	return true;
}

bool DeQueue(QueueUsing2Stacks& Q, int& x)
{
	if (StackEmpty(Q.S1))
		return false;
	while (!StackEmpty(Q.S1))
	{
		int data;
		Pop(Q.S1, data);
		Push(Q.S2, data);
	}
	Pop(Q.S2, x);
	while (!StackEmpty(Q.S2))
	{
		int data;
		Pop(Q.S2, data);
		Push(Q.S1, data);
	}
	return true;
}

bool QueueEmpty(QueueUsing2Stacks Q)
{
	if (StackEmpty(Q.S1))
		return true;
	return false;
}
#pragma endregion

//4 参考链队之循环队列的基本操作
#pragma endregion

#pragma region 3.3 综合题
//1 括号匹配
//时间O(n),空间O(1),n为算术表达式长度
bool BracketMatching(string expression)
{
	if (expression == "")
		return true;
	LinkStack stack;
	InitStack(stack);
	int i = 0;
	char c = expression[i];
	while (c != '\0')
	{
		c = expression[i++];
		if (c == '(' || c == '[' || c == '{')
		{
			Push(stack, c);
		}
		else if (c == ')' || c == ']' || c == '}')
		{
			int topC;
			int matchC = (c == ')' ? '(' : c == ']' ? '[' : '{');
			if (!Pop(stack, topC) || topC != matchC)
				return false;
		}
	}
	bool match = StackEmpty(stack);
	DestroyStack(stack);
	return match;
}

//2 利用火车调度栈将所有软座车厢调整到硬座车厢之前
//时间O(n),空间O(1),n为队列长度
void Adjust(char* train)
{
	LinkStack stack;
	InitStack(stack);
	char* p = train, * q = train;
	int x;	//0表示S，1表示H
	while (*p)
	{
		if (*p == 'H')
		{
			Push(stack, 1);
		}
		else
		{
			*(q++) = *p;
		}
		p++;
	}
	while (!StackEmpty(stack))
	{
		Pop(stack, x);
		*(q++) = 'H';
	}
	DestroyStack(stack);
}

//3 利用一个栈实现递归函数的非递归计算
//时间O(n),空间为O(1),n为入参n
int P(int x, int n)
{
	SqStack stack;
	InitStack(stack);
	int temp;	//函数中定义局部变量，如果不初始化，则值为未定义
	for (int i = 0; i <= n; i++)
	{

		if (i == 0)
			temp = 1;
		else if (i == 1)
			temp = 2 * x;
		else
		{
			int p1 = 0, p2 = 0;
			Pop(stack, p1);
			Pop(stack, p2);
			temp = 2 * x * p1 - 2 * (i - 1) * p2;
			Push(stack, p1);
		}
		Push(stack, temp);
	}
	GetTop(stack, temp);
	return temp;
}

//4 轮渡管理
//vehicles中1表示客车，0表示货车
void FerryManagement(int vehicles[], int length)
{
	SqQueue trucks, cars, ferryQ;
	InitQueue(trucks);
	InitQueue(cars);
	InitQueue(ferryQ);

}
#pragma endregion
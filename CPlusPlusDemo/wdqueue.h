#pragma once
#include "myinclude.h"
#include "wdstack.h"

#pragma region ���е�˳��洢
#define MaxSize 50
//���е�˳��洢����
typedef struct
{
	int data[MaxSize];
	int front, rear;	//frontָ���ͷԪ�أ�rearָ���βԪ�ص���һ��λ��
}SqQueue;

#pragma region ˳�����֮��ͨ���еĻ�������
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

//���������ܳ��ּ��������
bool QueueOverflow(SqQueue Q)
{
	if (Q.rear == MaxSize)
		return true;
	return false;
}

bool EnQueue(SqQueue& Q, int x)
{
	if (Q.rear == MaxSize)	//���������ܳ��ּ��������
		return false;
	Q.data[Q.rear++] = x;
	return true;
}

bool DeQueue(SqQueue& Q, int& x)
{
	if (Q.rear == 0 && Q.front == Q.rear)	//�ӿ�
		return false;
	x = Q.data[Q.front++];
	return true;
}

bool GetHead(SqQueue Q, int& x)
{
	if (Q.rear == 0 && Q.front == Q.rear)	//�ӿ�
		return false;
	x = Q.data[Q.front];
	return true;
}
#pragma endregion

#pragma region ˳�����֮ѭ�����еĻ�������
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
	if ((CQ.rear + 1) % MaxSize == CQ.front)	//����
		return false;
	CQ.data[CQ.rear] = x;
	CQ.rear = (CQ.rear + 1) % MaxSize;
	return true;
}

bool DeCQueue(SqQueue& CQ, int& x)
{
	if (CQ.front == CQ.rear)	//�ӿ�
		return false;
	x = CQ.data[CQ.front];
	CQ.front = (CQ.front + 1) % MaxSize;
	return true;
}
#pragma endregion
#pragma endregion

#pragma region ���е���ʽ�洢
//����
typedef struct
{
	LNode* front, * rear;	//ͷָ��ָ���ͷ��㣬βָ��ָ���β���
}LinkQueue;

#pragma region ����֮��ͨ���еĻ�������
void InitQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (LNode*)malloc(sizeof(LNode));	  //����ͷ���
	Q.front->next = nullptr;
}

bool QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return true;
	return false;
}

//�ٶ��ڴ����޴�����Զ�����ܳ����ڴ���
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
	if (Q.front == Q.rear)	//�ն�
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

#pragma region ����֮ѭ�����еĻ�������
void InitCQueue(LinkQueue& CQ)
{
	CQ.front = CQ.rear = (LNode*)malloc(sizeof(LNode));	//����ͷ���,frontָ���ͷ���,rearָ���β������һ��λ��
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
		//��rear�����һ���µĿ��н��
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

#pragma region 3.2 �ۺ���
#pragma region 1 ѭ��������Ԫ��ȫ�����ã����ñ�־��tag������tag��ֵΪ0��1������front=rearʱ����״̬�ǿջ�����
typedef struct
{
	int data[MaxSize];
	int front, rear;	//frontָ���ͷԪ�أ�rearָ���βԪ�ص���һ��λ��
	int tag;
}SqQueueWithTag;

void InitCQueue(SqQueueWithTag& CQ)
{
	CQ.front = CQ.rear = 0;
}

bool EnCQueue(SqQueueWithTag& CQ, int x)
{
	if (CQ.tag == 1 && CQ.front == CQ.rear)	//����
		return false;
	CQ.data[CQ.rear] = x;
	CQ.rear = (CQ.rear + 1) % MaxSize;
	return true;
}

bool DeCQueue(SqQueueWithTag& CQ, int& x)
{
	if (CQ.tag == 0 && CQ.front == CQ.rear)	//�ӿ�
		return false;
	x = CQ.data[CQ.front];
	CQ.front = (CQ.front + 1) % MaxSize;
	return true;
}
#pragma endregion

//2 ʹ�ÿ�ջS������Q�е�Ԫ������
//ʱ��O(n),�ռ�O(1),nΪ���г���
void QueueReverse(SqQueue& Q)
{
	if (Q.front == Q.rear)	//�ӿ�
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

#pragma region 3 ��������ջ��ģ��һ������
typedef struct
{
	SqStack S1, S2;	//S1���ڱ���Ԫ�أ�S2���ڵ���Ԫ��˳��
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

//4 �ο�����֮ѭ�����еĻ�������
#pragma endregion

#pragma region 3.3 �ۺ���
//1 ����ƥ��
//ʱ��O(n),�ռ�O(1),nΪ��������ʽ����
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

//2 ���û𳵵���ջ�������������������Ӳ������֮ǰ
//ʱ��O(n),�ռ�O(1),nΪ���г���
void Adjust(char* train)
{
	LinkStack stack;
	InitStack(stack);
	char* p = train, * q = train;
	int x;	//0��ʾS��1��ʾH
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

//3 ����һ��ջʵ�ֵݹ麯���ķǵݹ����
//ʱ��O(n),�ռ�ΪO(1),nΪ���n
int P(int x, int n)
{
	SqStack stack;
	InitStack(stack);
	int temp;	//�����ж���ֲ��������������ʼ������ֵΪδ����
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

//4 �ֶɹ���
//vehicles��1��ʾ�ͳ���0��ʾ����
void FerryManagement(int vehicles[], int length)
{
	SqQueue trucks, cars, ferryQ;
	InitQueue(trucks);
	InitQueue(cars);
	InitQueue(ferryQ);

}
#pragma endregion
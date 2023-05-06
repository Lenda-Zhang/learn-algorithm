#pragma once
#include "myinclude.h"

#pragma region ˳��ջ�������Ͷ��弰��������
#define MaxSize 50	//����ջ��Ԫ�ص�������
//˳��ջ
typedef struct {
	int data[MaxSize];	//���ջ��Ԫ��
	int top;	//ջ��ָ��
}SqStack;

void InitStack(SqStack& S)
{
	S.top = -1;
}

bool StackEmpty(SqStack S)
{
	if (S.top == -1)
		return true;
	else
		return false;
}

bool StackOverflow(SqStack S)
{
	if (S.top == MaxSize - 1)
		return true;
	return false;
}

bool Push(SqStack& S, int x)
{
	if (S.top == MaxSize - 1)	//ջ��
		return false;
	S.data[++S.top] = x;
	return true;
}

bool Pop(SqStack& S, int& x)
{
	if (S.top == -1)
		return false;
	x = S.data[S.top--];
	return true;
}

bool GetTop(SqStack S, int& x)
{
	if (S.top == -1)
		return false;
	x = S.data[S.top];
	return true;
}

void DestroyStack(SqStack& S)
{
	S.top = -1;
}
#pragma endregion

#pragma region ��ջ�������Ͷ��弰��������
//��ջ,nodeСд��Ϊ�˸�����ṹ��������
//����涨��ջû��ͷ��㣬Lheadָ��ջ�����
//ջ�׽������β
typedef struct Linknode
{
	int data;
	struct Linknode* next;
}Linknode, * LinkStack;

void InitStack(LinkStack& Lhead)
{
	Lhead = nullptr;
}

bool StackEmpty(LinkStack Lhead)
{
	if (Lhead == nullptr)
		return true;
	else
		return false;
}

bool Push(LinkStack& Lhead, int x)
{
	//û��ջ���������
	Linknode* n = (Linknode*)malloc(sizeof(Linknode));
	n->data = x;
	n->next = Lhead;
	Lhead = n;
	return true;
}

bool Pop(LinkStack& Lhead, int& x)
{
	if (Lhead == nullptr)
		return false;
	x = Lhead->data;
	Linknode* s = Lhead;
	Lhead = Lhead->next;
	free(s);
	return true;
}

bool GetTop(LinkStack Lhead, int& x)
{
	if (Lhead == nullptr)
		return false;
	x = Lhead->data;
	return true;
}

void DestroyStack(LinkStack& Lhead)
{
	Linknode* n = Lhead;
	while (n != nullptr)
	{
		Linknode* s = n;
		n = n->next;
		free(s);
	}
}
#pragma endregion

#pragma region 3.1 �ۺ���
//3 2)�ж������Ĳ��������Ƿ�Ϸ�
//ʱ��ΪO(n),�ռ�ΪO(1),nΪ���еĳ���
bool IsLegal(char seq[], int length)
{
	int stLen = 0;	//ջ��Ԫ�ظ���
	for (int i = 0; i < length; i++)
	{
		if (seq[i] == 'I')
			stLen++;
		else if (seq[i] == 'O')
		{
			if (stLen <= 0)
				return false;
			stLen--;
		}
	}
	return stLen == 0;
}

typedef struct CharLinkNode {
	char data;
	struct CharLinkNode* next;
}CharLinkNode, * CharLinkStack;

bool Push(CharLinkStack& Lhead, char c)
{
	//û��ջ���������
	CharLinkNode* n = (CharLinkNode*)malloc(sizeof(CharLinkNode));
	n->data = c;
	n->next = Lhead;
	Lhead = n;
	return true;
}

bool Pop(CharLinkStack& Lhead, char& c)
{
	if (Lhead == nullptr)
		return false;
	c = Lhead->data;
	CharLinkNode* s = Lhead;
	Lhead = Lhead->next;
	free(s);
	return true;
}

//4 �ж������ȫ��n���ַ��Ƿ����ĶԳ�
//ʱ��ΪO(n),�ռ�ΪO(1)
bool IsCentralSymmetry(CharLinkNode* L)
{
	if (L == nullptr || L->next == nullptr)	//�ձ��ֻ��һ��Ԫ��
		return true;
	int n = 0;
	CharLinkNode* p = L;
	while (p != nullptr)
	{
		n++;
		p = p->next;
	}
	int half = n / 2;
	p = L;
	CharLinkStack stack;
	while (half > 0)
	{
		Push(stack, p->data);
		p = p->next;
		half--;
	}
	if (n % 2 == 1)
		p = p->next;
	char c;
	while (p != nullptr)
	{
		Pop(stack, c);
		if (p->data != c)
			return false;
		p = p->next;
	}
	return true;
}

#pragma region 5 ����˳��ջ�Ľ�ջ��ջ�㷨
//s1��ջ,��ʼtop1=-1
bool S1Push(int data[], int top1, int top2, int x)
{
	if (top2 - top1 == 1)
		return false;
	data[++top1] = x;
	return true;
}

//s1��ջ
bool S1Pop(int data[], int top1, int& x)
{
	if (top1 == -1)
		return false;
	x = data[top1--];
	return true;
}

//s2��ջ,��ʼtop2=MaxSize
bool S2Push(int data[], int top1, int top2, int x)
{
	if (top2 - top1 == 1)
		return false;
	data[--top2] = x;
	return true;
}

//s2��ջ
bool S2Pop(int data[], int top2, int& x)
{
	if (top2 == MaxSize)
		return false;
	x = data[top2++];
	return true;
}
#pragma endregion
#pragma endregion
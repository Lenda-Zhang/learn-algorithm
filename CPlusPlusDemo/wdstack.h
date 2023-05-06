#pragma once
#include "myinclude.h"

#pragma region 顺序栈数据类型定义及基本操作
#define MaxSize 50	//定义栈中元素的最大个数
//顺序栈
typedef struct {
	int data[MaxSize];	//存放栈中元素
	int top;	//栈顶指针
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
	if (S.top == MaxSize - 1)	//栈满
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

#pragma region 链栈数据类型定义及基本操作
//链栈,node小写是为了跟链表结构定义区分
//这里规定链栈没有头结点，Lhead指向栈顶结点
//栈底结点在链尾
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
	//没有栈满上溢情况
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

#pragma region 3.1 综合题
//3 2)判定所给的操作序列是否合法
//时间为O(n),空间为O(1),n为序列的长度
bool IsLegal(char seq[], int length)
{
	int stLen = 0;	//栈中元素个数
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
	//没有栈满上溢情况
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

//4 判断链表的全部n个字符是否中心对称
//时间为O(n),空间为O(1)
bool IsCentralSymmetry(CharLinkNode* L)
{
	if (L == nullptr || L->next == nullptr)	//空表或只有一个元素
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

#pragma region 5 共享顺序栈的进栈出栈算法
//s1进栈,初始top1=-1
bool S1Push(int data[], int top1, int top2, int x)
{
	if (top2 - top1 == 1)
		return false;
	data[++top1] = x;
	return true;
}

//s1出栈
bool S1Pop(int data[], int top1, int& x)
{
	if (top1 == -1)
		return false;
	x = data[top1--];
	return true;
}

//s2进栈,初始top2=MaxSize
bool S2Push(int data[], int top1, int top2, int x)
{
	if (top2 - top1 == 1)
		return false;
	data[--top2] = x;
	return true;
}

//s2出栈
bool S2Pop(int data[], int top2, int& x)
{
	if (top2 == MaxSize)
		return false;
	x = data[top2++];
	return true;
}
#pragma endregion
#pragma endregion
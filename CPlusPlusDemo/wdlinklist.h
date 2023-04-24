#pragma warning(disable:4996)	//屏蔽error C4996: 'scanf': This function or variable may be unsafe
#pragma once
#include "myinclude.h"

//单链表
typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, * LinkList;

//双链表
typedef struct DNode {
	int data;
	struct DNode* prior, * next;
} DNode, * DLinkList;

#define MaxSize 50
//静态链表
typedef struct
{
	int data;
	int next;
} SLinkList[MaxSize];

//单链表的基本操作
//头插法逆向建立单链表
//每个结点插入时间为O(1)，设单链表表长为n，则总时间为O(n)
LinkList HeadInsert(LinkList& L)
{
	LNode* s;
	int x;
	L = (LinkList)malloc(sizeof(LNode));	//创建头结点
	L->next = nullptr;
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = L->next;
		L->next = s;
		scanf("%d", &x);
	}
	return L;
}

//尾插法正向建立单链表
//每个结点插入时间为O(1)，设单链表表长为n，则总时间为O(n)
LinkList TailInsert(LinkList& L)
{
	int x;
	L = (LinkList)malloc(sizeof(LNode));
	LNode* s, * r = L;	//r为尾指针
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = nullptr;	//尾结点指针置空，漏写则遍历结点时找不到结束标志nullptr
	return L;
}

//按序号查找结点，查找第i个结点
//时间为O(n)
LNode* GetItemByIndex(LinkList L, int i)
{
	if (i < 1)
		return nullptr;
	int j = 1;
	LNode* p = L->next;
	while (j < i && p != nullptr)
	{
		p = p->next;
		j++;
	}
	return p;
}

//按值查找结点
//时间为O(n)
LNode* GetItemByVal(LinkList L, int val)
{
	LNode* p = L->next;
	while (p != nullptr)
	{
		if (p->data == val)
			break;
		p = p->next;
	}
	return p;
}

//求表长
//时间为O(n)
int GetLength(LinkList L)
{
	int cnt = 0;
	LNode* p = L->next;
	while (p != nullptr)
	{
		cnt++;
		p = p->next;
	}
	return cnt;
}

//插入结点：将值为x的新结点插入到单链表的第i个位置上
//方法1：找到第(i-1)个结点，再在其后插入新结点
//时间为O(n)
bool InsertBefore(LinkList& L, int i, int val)
{
	if (i<1 || i > GetLength(L) + 1)
		return false;
	LNode* prior = (i - 1) < 1 ? L : GetItemByIndex(L, i - 1);
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	newNode->data = val;
	newNode->next = prior->next;
	prior->next = newNode;
	return true;
}

//方法2：找到第i个结点，再其前插入新结点
//思路：找到第i个结点，在i后插入新结点，再交换i结点和新结点的值
//时间为O(n)
bool InsertAfter(LinkList& L, int i, int val)
{
	if (i<1 || i > GetLength(L))	//不考虑第(n+1)个结点，此时GetItemByIndex()为nullptr，此时交换两结点的值需要额外考虑
		return false;
	LNode* iNode = GetItemByIndex(L, i);
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->next = iNode->next;
	iNode->next = s;
	s->data = iNode->data;
	iNode->data = val;
}

//删除结点，将第i个结点删除
//时间为O(n)
bool Delete(LinkList& L, int i)
{
	if (i<1 || i>GetLength(L))	//检查删除位置的合法性
		return false;
	LNode* p = (i - 1) < 1 ? L : GetItemByIndex(L, i - 1);
	LNode* q = p->next;
	p->next = q->next;
	free(q);
	return true;
}

//打印单链表
//时间为O(n)
void PrintLinkList(LinkList L)
{
	LNode* p = L->next;
	while (p != nullptr)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

DLinkList TailInsert(DLinkList& DL)
{
	DL = (DLinkList)malloc(sizeof(DNode));
	DL->prior = nullptr;
	DNode* s, * r = DL;
	int x;
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (DNode*)malloc(sizeof(DNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = nullptr;
	return DL;
}

//双链表按序号查找结点，查找第i个结点
//时间为O(n)
DNode* GetItemByIndex(DLinkList DL, int i)
{
	if (i < 1)
		return nullptr;
	DNode* d = DL->next;
	int j = 1;
	while (j < i && d != nullptr)
	{
		d = d->next;
		j++;
	}
	return d;
}

//双链表求表长
//时间为O(n)
int GetLength(DLinkList DL)
{
	int cnt = 0;
	DNode* d = DL->next;
	while (d != nullptr)
	{
		cnt++;
		d = d->next;
	}
	return cnt;
}

//双链表插入，将值为x的新结点插入到双链表的第i个位置上
bool InsertDNode(DLinkList& DL, int i, int val)
{
	if (i<1 || i>GetLength(DL) + 1)	//有效位置为1~(n+1)
		return false;
	DNode* prior = (i - 1) < 1 ? DL : GetItemByIndex(DL, i - 1);
	DNode* s = (DNode*)malloc(sizeof(DNode));
	s->data = val;
	s->next = prior->next;	//1
	s->prior = prior;	//3
	if (prior->next)
		prior->next->prior = s;	//2
	prior->next = s;	//4,注：1,2必须在4之前
	return true;
}

//双链表删除
bool DeleteDNode(DLinkList& DL, int i)
{
	if (i<1 || i>GetLength(DL))	//检查删除位置的合法性
		return false;
	DNode* prior = (i - 1) < 1 ? DL : GetItemByIndex(DL, i - 1);
	DNode* p = prior->next;
	prior->next = p->next;	//1
	if (p->next)
		p->next->prior = prior;	//2
	free(p);	//3
	return true;
}

//打印双链表
//时间O(n)
void PrintDLinkList(DLinkList DL)
{
	DNode* p = DL->next;
	while (p != nullptr)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

//带头结点的循环链表判空

//带头结点的循环链表遍历(打印)
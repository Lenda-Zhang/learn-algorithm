#pragma warning(disable:4996)	//����error C4996: 'scanf': This function or variable may be unsafe
#pragma once
#include "myinclude.h"

//������
typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, * LinkList;

//˫����
typedef struct DNode {
	int data;
	struct DNode* prior, * next;
} DNode, * DLinkList;

#define MaxSize 50
//��̬����
typedef struct
{
	int data;
	int next;
} SLinkList[MaxSize];

//������Ļ�������
//ͷ�巨������������
//ÿ��������ʱ��ΪO(1)���赥�����Ϊn������ʱ��ΪO(n)
LinkList HeadInsert(LinkList& L)
{
	LNode* s;
	int x;
	L = (LinkList)malloc(sizeof(LNode));	//����ͷ���
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

//β�巨������������
//ÿ��������ʱ��ΪO(1)���赥�����Ϊn������ʱ��ΪO(n)
LinkList TailInsert(LinkList& L)
{
	int x;
	L = (LinkList)malloc(sizeof(LNode));
	LNode* s, * r = L;	//rΪβָ��
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = nullptr;	//β���ָ���ÿգ�©д��������ʱ�Ҳ���������־nullptr
	return L;
}

//����Ų��ҽ�㣬���ҵ�i�����
//ʱ��ΪO(n)
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

//��ֵ���ҽ��
//ʱ��ΪO(n)
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

//���
//ʱ��ΪO(n)
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

//�����㣺��ֵΪx���½����뵽������ĵ�i��λ����
//����1���ҵ���(i-1)����㣬�����������½��
//ʱ��ΪO(n)
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

//����2���ҵ���i����㣬����ǰ�����½��
//˼·���ҵ���i����㣬��i������½�㣬�ٽ���i�����½���ֵ
//ʱ��ΪO(n)
bool InsertAfter(LinkList& L, int i, int val)
{
	if (i<1 || i > GetLength(L))	//�����ǵ�(n+1)����㣬��ʱGetItemByIndex()Ϊnullptr����ʱ����������ֵ��Ҫ���⿼��
		return false;
	LNode* iNode = GetItemByIndex(L, i);
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->next = iNode->next;
	iNode->next = s;
	s->data = iNode->data;
	iNode->data = val;
}

//ɾ����㣬����i�����ɾ��
//ʱ��ΪO(n)
bool Delete(LinkList& L, int i)
{
	if (i<1 || i>GetLength(L))	//���ɾ��λ�õĺϷ���
		return false;
	LNode* p = (i - 1) < 1 ? L : GetItemByIndex(L, i - 1);
	LNode* q = p->next;
	p->next = q->next;
	free(q);
	return true;
}

//��ӡ������
//ʱ��ΪO(n)
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

//˫������Ų��ҽ�㣬���ҵ�i�����
//ʱ��ΪO(n)
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

//˫�������
//ʱ��ΪO(n)
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

//˫������룬��ֵΪx���½����뵽˫����ĵ�i��λ����
bool InsertDNode(DLinkList& DL, int i, int val)
{
	if (i<1 || i>GetLength(DL) + 1)	//��Чλ��Ϊ1~(n+1)
		return false;
	DNode* prior = (i - 1) < 1 ? DL : GetItemByIndex(DL, i - 1);
	DNode* s = (DNode*)malloc(sizeof(DNode));
	s->data = val;
	s->next = prior->next;	//1
	s->prior = prior;	//3
	if (prior->next)
		prior->next->prior = s;	//2
	prior->next = s;	//4,ע��1,2������4֮ǰ
	return true;
}

//˫����ɾ��
bool DeleteDNode(DLinkList& DL, int i)
{
	if (i<1 || i>GetLength(DL))	//���ɾ��λ�õĺϷ���
		return false;
	DNode* prior = (i - 1) < 1 ? DL : GetItemByIndex(DL, i - 1);
	DNode* p = prior->next;
	prior->next = p->next;	//1
	if (p->next)
		p->next->prior = prior;	//2
	free(p);	//3
	return true;
}

//��ӡ˫����
//ʱ��O(n)
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

//��ͷ����ѭ�������п�

//��ͷ����ѭ���������(��ӡ)
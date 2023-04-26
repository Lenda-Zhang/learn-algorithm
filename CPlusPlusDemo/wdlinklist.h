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

#pragma region ������Ļ�������
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
bool InsertBefore(LinkList L, int i, int val)
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
bool InsertAfter(LinkList L, int i, int val)
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
bool Delete(LinkList L, int i)
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
#pragma endregion

#pragma region ˫����Ļ�������
//β�巨����˫����
//ʱ��O(n)
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
		s->prior = r;
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
//ʱ��O(n)
bool InsertDNode(DLinkList DL, int i, int val)
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
//ʱ��O(n)
bool DeleteDNode(DLinkList DL, int i)
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
#pragma endregion

#pragma region ѭ��������Ļ�������
//β�巨������ѭ��������
//ÿ��������ʱ��ΪO(1)���赥�����Ϊn������ʱ��ΪO(n)
LinkList CLTailInsert(LinkList& CL)
{
	int x;
	CL = (LinkList)malloc(sizeof(LNode));
	LNode* s, * r = CL;	//rΪβָ��
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = CL;	//β���ָ��ָ��ͷָ��
	return CL;
}

//��ͷ����ѭ���������п�
//ʱ��O(1)
bool IsCircularListEmpty(LinkList CL)
{
	if (CL->next == CL)
		return true;
	return false;
}

//��ͷ����ѭ���������ӡ(����)
//ʱ��O(n)
void PrintCircularList(LinkList CL)
{
	if (IsCircularListEmpty(CL))
		return;
	LNode* p = CL->next;
	do
	{
		cout << p->data << " ";
		p = p->next;
	} while (p != CL);
	cout << endl;
}
#pragma endregion

#pragma region ѭ��˫����Ļ�������
//β�巨������ѭ��˫����
//ʱ��O(n)
DLinkList CDLTailInsert(DLinkList& CDL)
{
	CDL = (DLinkList)malloc(sizeof(DNode));
	DNode* s, * r = CDL;	//rΪβָ��
	int x;
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (DNode*)malloc(sizeof(DNode));
		s->data = x;
		s->prior = r;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = CDL;
	CDL->prior = r;
	return CDL;
}

//��ͷ����ѭ��˫�����п�
//ʱ��O(1)
bool IsCDLEmpty(DLinkList CDL)
{
	if (CDL->prior == CDL && CDL->next == CDL)
		return true;
	return false;
}

//��ͷ����ѭ��˫�����ӡ(����)
//ʱ��O(n)
void PrintCDL(DLinkList CDL)
{
	if (IsCDLEmpty(CDL))
		return;
	DNode* p = CDL->next;
	do
	{
		cout << p->data << " ";
		p = p->next;
	} while (p != CDL);
	cout << endl;
}
#pragma endregion

#pragma region 2.3 �ۺ���
//01 ���һ���ݹ��㷨,ɾ������ͷ���ĵ�����L������ֵΪx�Ľ��
//ʱ��O(n),nΪ������ĳ���
void DeleteRecursion(LinkList& L, int x)
{
	if (L == nullptr)
		return;
	if (L->data == x)
	{
		LNode* temp = L;
		L = L->next;
		free(temp);
		DeleteRecursion(L, x);
	}
	else
	{
		DeleteRecursion(L->next, x);
	}
}

//02 ʱ��O(n),nΪ������ĳ���
LinkList DeleteNodeWithValX(LinkList& L, int x)
{
	LNode* prior = L, * p = L->next;
	while (p != nullptr)
	{
		if (p->data == x)
		{
			prior->next = p->next;
			free(p);
		}
		else
		{
			prior = p;
		}
		p = prior->next;
	}
	return L;
}

//03 ��ͷ���ĵ�������β��ͷ�������ÿ������ֵ
//ʱ��O(n),�ռ�O(1)
void OutputInversion(LinkList L)
{
	if (L->next == nullptr)
		return;
	//�ȷ�ת����
	LNode* prior = nullptr, * p = L->next;
	while (p != nullptr)
	{
		LNode* next = p->next;
		p->next = prior;
		prior = p;
		p = next;
	}
	L->next = prior;
	//�����ÿ������ֵ
	PrintLinkList(L);
}

//04 �ڴ�ͷ���ĵ�����L��ɾ��һ����Сֵ���(Ψһ)�ĸ�Ч�㷨
//ʱ��O(n),�ռ�O(1)
bool DeleteMin(LinkList L)
{
	if (L->next == nullptr)
		return false;
	LNode* p = L->next, * prior = L, * min = p, * priorOfMin = prior;
	while (p != nullptr)
	{
		if (p->data < min->data)
		{
			min = p;
			priorOfMin = prior;
		}
		prior = p;
		p = p->next;
	}
	priorOfMin->next = min->next;
	free(min);
	return true;
}

//05 ����ͷ���ĵ�����͵�����
//ʱ��O(n),�ռ�O(1)
void ReverseList(LinkList L)
{
	LNode* prior = nullptr, * p = L->next;
	while (p != nullptr)
	{
		LNode* next = p->next;
		p->next = prior;
		prior = p;
		p = next;
	}
	L->next = prior;
}

//06 ��ͷ���ĵ�����ʹ��Ԫ�ص�������
//ʹ��ֱ�Ӳ��������㷨,ʱ��O(n^2),�ռ�O(1)
void SortIncreasing(LinkList L)
{
	if (L->next == nullptr)
		return;
	LNode* p = L->next->next;
	L->next->next = nullptr;	//�ȹ���ֻ����һ�����ݽ��ĵ�����
	while (p != nullptr)
	{
		LNode* prior = L;
		while (prior->next != nullptr && prior->next->data < p->data)
			prior = prior->next;
		LNode* next = p->next;
		p->next = prior->next;
		prior->next = p;
		p = next;
		//PrintLinkList(L);
	}
}

//07 ��ͷ���ĵ���������ɾ���������н��ڸ���������ֵ֮���Ԫ�أ������ڣ�
//ʱ��O(n),�ռ�O(1)
void DeleteBetweenXAndY(LinkList L, int x, int y)
{
	if (L->next == nullptr)
		return;
	LNode* prior = L, * p = L->next;
	while (p != nullptr)
	{
		if (p->data >= x && p->data <= y)
		{
			LNode* temp = p;
			prior->next = p->next;
			p = prior->next;
			free(temp);
		}
		else
		{
			prior = p;
			p = p->next;
		}
	}
}

//08 �ҳ�����������Ĺ������(����ͷ���)
//ʱ��O(len1+len2),�ռ�O(1),len1,len2�ֱ�Ϊ������L1,L2�ĳ���
LinkList FindCommon(LinkList L1, LinkList L2)
{
	if (L1 == nullptr || L2 == nullptr)
		return nullptr;
	LNode* p1 = L1, * p2 = L2;
	int len1 = GetLength(L1), len2 = GetLength(L2), diff = len2 - len1;
	LNode* longL = diff > 0 ? L2 : L1;
	LNode* shortL = longL == L1 ? L2 : L1;
	while (diff > 0)
	{
		longL = longL->next;
		diff--;
	}
	while (shortL != longL)
	{
		shortL = shortL->next;
		longL = longL->next;
	}
	return shortL;
}

//09 ��ͷ���ĵ�������������������������и���������Ԫ�أ����ͷŽ����ռ�Ĵ洢�ռ�
//��Ҫ�󣺲�����ʹ��������Ϊ�����ռ䣩
//ע�����õ�06��˼�룬��ֱ�Ӳ���������������ͷ��ڴ�ռ�
//ʱ��O(n^2),�ռ�O(1)
void OutputIncreasing(LinkList& L)
{
	if (L->next == nullptr)
		return;
	LNode* p = L->next->next;
	L->next->next = nullptr;	//�ȹ���ֻ����һ�����ݽ��ĵ�����
	while (p != nullptr)
	{
		LNode* prior = L;
		while (prior->next != nullptr && prior->next->data < p->data)
			prior = prior->next;
		LNode* next = p->next;
		p->next = prior->next;
		prior->next = p;
		p = next;
	}
	p = L->next;
	while (p != nullptr)
	{
		cout << p->data << " ";
		LNode* temp = p;
		p = p->next;
		free(temp);
	}
	cout << endl;
	L->next = nullptr;
}

//10 ��һ����ͷ���ĵ�����ֽ��������ͷ����A��B��
//ֻ��ԭ�������Ϊ������Ԫ�صĵ������
//ֻ��ԭ�������Ϊż����Ԫ�صĵ�����
//�ұ������˳�򲻱�
//ʱ��O(n),�ռ�O(1)
LinkList SplitList(LinkList& A)
{
	LinkList B = (LinkList)malloc(sizeof(LNode));
	B->next = nullptr;
	if (A->next == nullptr)
		return B;
	LNode* p = A->next, * aPrior = A, * bPrior = B;
	int cnt = 1;
	while (p != nullptr)
	{
		if (cnt % 2 == 1)
		{
			aPrior->next = p;
			aPrior = p;
		}
		else
		{
			bPrior->next = p;
			bPrior = p;
		}
		p = p->next;
		cnt++;
	}
	aPrior->next = bPrior->next = nullptr;
	return B;
}

//11 L={a1,b1,a2,b2,...,an,bn}�͵ز�ֳ�
//A={a1,a2,...,an}��B={bn,...,b2,b1}
//���õ�10��˼·���������ڣ�1.��B��Ľ�����Ϊͷ�巨��2.��ʹ����š�
//ʱ��O(n),�ռ�O(1)
LinkList SplitList2(LinkList& A)
{
	LinkList B = (LinkList)malloc(sizeof(LNode));
	B->next = nullptr;
	if (A->next == nullptr)
		return B;
	LNode* p = A->next, * prior = A;
	while (p != nullptr)
	{
		prior->next = p;
		prior = p;
		p = p->next;
		if (p != nullptr)
		{
			LNode* next = p->next;
			p->next = B->next;
			B->next = p;
			p = next;
		}
	}
	prior->next = nullptr;
	return B;
}

//12 ��������ĵ�����ȥ���ظ�Ԫ��
//ʱ��O(n),�ռ�O(1)
void RemoveDuplicate(LinkList& L)
{
	if (L->next == nullptr)
		return;
	LNode* prior = L->next, * p = prior->next;
	while (p != nullptr)
	{
		if (p->data == prior->data)
		{
			LNode* n = p;
			prior->next = p->next;
			p = p->next;
			free(n);
		}
		else
		{
			prior = p;
			p = p->next;
		}
	}
}

//13 ��������������ĵ�����鲢��һ���ݼ��ĵ�����
//��Ҫ������ԭ������������Ŀռ��Ź鲢��ĵ�����
//˼·������ͷ�巨��ת˳��
LinkList MergeIntoDecreasing(LinkList& A, LinkList& B)
{
	LNode* p1 = A->next, * p2 = B->next;
	A->next = nullptr;
	while (p1 != nullptr && p2 != nullptr)
	{
		LNode* p = p2->data < p1->data ? p2 : p1;
		LNode* next = p->next;
		p->next = A->next;
		A->next = p;
		if (p == p1)
			p1 = next;
		else
			p2 = next;
	}
	LNode* p = p1 != nullptr ? p1 : p2;
	while (p != nullptr)
	{
		LNode* next = p->next;
		p->next = A->next;
		A->next = p;
		p = next;
	}
	return A;
}
#pragma endregion
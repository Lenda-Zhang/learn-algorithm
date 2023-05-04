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

//��ͷ����ѭ������������һ�����
LNode* GetLast(LinkList CL)
{
	if (IsCircularListEmpty(CL))
		return nullptr;
	LNode* p = CL->next;
	do
	{
		p = p->next;
	} while (p->next != CL);
	return p;
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
	if (L == nullptr)	//�ݹ����
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

//02 �ڴ�ͷ���ĵ�����ɾ������ֵΪx�Ľ�㣬���ͷ���ռ�
//ʱ��O(n),nΪ������ĳ��ȣ��ռ�O(1)
void DeleteNodeWithValX(LinkList& L, int x)
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
}

#pragma region 03 
//��ͷ���ĵ�������β��ͷ�������ÿ������ֵ
//�ⷨ1����ת����������
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

//�ⷨ2�����õݹ�ջ���ص����գ�
//ʱ��O(n),�ռ�O(1)
void OutputInversion2(LinkList L)
{
	if (L->next != nullptr)
	{
		OutputInversion2(L->next);
		cout << L->next->data << " ";
	}
}
#pragma endregion

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
//ע��Ҳ����ͷ�巨��
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
//ʱ��O(max(len1,len2)),�ռ�O(1),len1,len2�ֱ�Ϊ������L1,L2�ĳ���
LinkList FindCommon(LinkList L1, LinkList L2)
{
	if (L1 == nullptr || L2 == nullptr)
		return nullptr;
	LNode* p1 = L1, * p2 = L2;
	int len1 = GetLength(L1), len2 = GetLength(L2), diff = len2 - len1;
	LNode* longL = diff > 0 ? L2 : L1;
	LNode* shortL = longL == L1 ? L2 : L1;
	diff = abs(diff);
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
//����ÿ�α����ҳ���Сֵ��㣬�����ɾ����ʱ��ҲΪO(n^2)
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

//14 A,B��������ͷ���ĵ�����Ԫ�ص�������
//��A��B�еĹ���Ԫ�ز�����ͷ���ĵ�����C��
//Ҫ���ƻ�A,B�Ľ��
//ʱ��O(len1+len2),�ռ�O(1),len1,len2�ֱ�Ϊ������L1,L2�ĳ���
LinkList FindCommon2(LinkList L1, LinkList L2)
{
	LinkList L3 = (LinkList)malloc(sizeof(LNode));
	LNode* p1 = L1->next, * p2 = L2->next;
	while (p1 != nullptr && p2 != nullptr)
	{
		if (p1 == p2)
			break;
		else if (p1->data < p2->data)
		{
			p1 = p1->next;
		}
		else
		{
			p2 = p2->next;
		}
	}
	if (p1 == nullptr || p2 == nullptr)
		L3->next = nullptr;
	else
	{
		L3->next = p1;
	}
	return L3;
}

//15 ��ͷ�������������������󽻼��������һ������
//ʱ��O(len1+len2),�ռ�O(1),len1,len2�ֱ�Ϊ������L1,L2�ĳ���
void FindCommon3(LinkList& L1, LinkList& L2)
{
	LNode* p1 = L1->next, * p2 = L2->next, * p1Prior = L1;
	while (p1 != nullptr && p2 != nullptr)
	{
		if (p1->data == p2->data)
		{
			p1Prior->next = p1;	//L1�н���������
			p1Prior = p1;
			p1 = p1->next;
			LNode* p = p2;	//L2�н���ͷ�
			p2 = p2->next;
			free(p);
		}
		else if (p1->data < p2->data)
		{
			LNode* p = p1;
			p1 = p1->next;
			free(p);
		}
		else
		{
			LNode* p = p2;
			p2 = p2->next;
			free(p);
		}
	}
	while (p1 != nullptr)	//L2�ѱ����꣬L1δ������
	{
		LNode* p = p1;
		p1 = p1->next;
		free(p);
	}
	while (p2 != nullptr)	//L1�ѱ����꣬L2δ������
	{
		LNode* p = p2;
		p2 = p2->next;
		free(p);
	}
	p1Prior->next = nullptr;
	free(L2);
}

//16 ������������A,B�Ѵ��뵥�����ж�B�Ƿ�ΪA������������
//ʱ��O(len1*len2),�ռ�O(1)
bool IsSubsequence(LinkList A, LinkList B)
{
	if (B->next == nullptr)	//�ձ����κ����е�����������
		return true;
	LNode* p1 = A->next, * firstP1 = p1;
	while (p1 != nullptr)
	{
		LNode* p2 = B->next;
		while (p1 != nullptr && p2 != nullptr)
		{
			if (p1->data != p2->data)
			{
				break;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		if (p2 == nullptr)
			return true;
		else
		{
			p1 = firstP1->next;
			firstP1 = p1;
		}
	}
	return false;
}

//17 �жϴ�ͷ����ѭ��˫�����Ƿ�Գ�
//ʱ��O(n),�ռ�O(1)
bool IsCDLSymmetry(DLinkList CDL)
{
	if (CDL->next == CDL && CDL->prior == CDL)
		return false;
	DNode* first = CDL->next, * last = CDL->prior;
	while (first != last)
	{
		if (first->data != last->data)
			return false;
		first = first->next;
		last = last->prior;
	}
	return true;
}

//18 ����ͷ����ѭ��������h1��h2����h2���ӵ�h1֮��
//Ҫ�����Ӻ�������Ա���ѭ��������ʽ
//ʱ��O(len1+len2),�ռ�O(1),len1,len2�ֱ�Ϊ������L1,L2�ĳ���
void Link(LinkList& h1, LinkList& h2)
{
	if (h2->next == h2)	//��h2Ϊ�գ�����������
		return;
	LNode* r1 = h1, * r2 = h2;
	while (r1->next != h1)	//��h1Ϊ����h2��Ϊ�գ���h2���ӵ�h1֮�󣬲���h2β����ָ����ָ��h1
	{
		r1 = r1->next;
	}
	while (r2->next != h2)
	{
		r2 = r2->next;
	}
	r1->next = h2;
	r2->next = h1;
}

//19 ��ͷ����ѭ�������������ҳ���С�Ľ�㣬ɾ����ֱ������Ϊ�գ���ɾ��ͷ���
//ʱ��O(n^2),�ռ�O(1)
void DeleteIncreasing(LinkList& CL)
{
	while (CL->next != CL)
	{
		LNode* minPrior = CL, * minP = CL->next, * prior = minP, * p = minP->next;
		while (p != CL)
		{
			if (p->data < minP->data)
			{
				minP = p;
				minPrior = prior;
			}
			prior = p;
			p = p->next;
		}
		minPrior->next = minP->next;
		free(minP);
		//PrintCircularList(CL);
	}
	free(CL);
}

//��ͷ���Ĵ�����Ƶ�ȵ�˫����
typedef struct FreqDNode {
	int data;
	int freq = 0;
	struct FreqDNode* pre, * next;
}FreqDNode, * FreqDLinkList;

bool IsFreqDLEmpty(FreqDLinkList FDL)
{
	if (FDL->next == nullptr)
		return true;
	return false;
}

//20 ��дLocate(L,x)��ÿ�η���Ƶ�ȼ�1����ʹ�����н�㱣�ְ�Ƶ�ȵݼ����У�
//ͬʱ������ʵĽ��������ͬƵ�ȵĽ��ǰ��
//ʱ��O(n),�ռ�O(1)
FreqDNode* Locate(FreqDLinkList FDL, int x)
{
	if (IsFreqDLEmpty(FDL))
		return nullptr;
	FreqDNode* p = FDL->next;
	while (p != nullptr && p->data == x)
	{
		p = p->next;
	}
	//���ҵ�ֵΪx�Ľ�㣬������������ժ��
	//����ͷ��ʼɨ�裬���뵽Ƶ����ͬ�Ľ��ǰ��
	if (p != nullptr)
	{
		p->freq++;
		if (p->pre == FDL || p->pre->freq > p->freq)
			return p;
		p->pre->next = p->next;	//������������ժ��
		if (p->next != nullptr)
			p->next->pre = p->pre;
		FreqDNode* q = p->pre;
		while (q != FDL && q->freq <= p->freq)	//����ǰ�����
		{
			q = q->pre;
		}
		p->next = q->next;
		if (q->next != nullptr)
			q->next->pre = p;
		p->pre = q;
		q->next = p;
	}
	return p;
}

//21 �жϵ������Ƿ���ڻ�������ͷ��㣩
//˼·������ָ�뷨����ָ��ÿ����һ������ָ��ÿ��������
//ʱ��O(n),�ռ�O(1)
bool DoesLHasARing(LinkList L)
{
	if (L == nullptr || L->next == nullptr)
		return false;
	LNode* slow = L, * fast = slow->next;
	while (slow != nullptr && fast != nullptr)
	{
		if (slow == fast)
			return true;
		slow = slow->next;
		fast = fast->next;
		if (fast != nullptr)
			fast = fast->next;
	}
	return false;
}

//22 ���Ҵ�ͷ���ĵ������е�����k������ֵ
//˼·��ǰ��ָ�뷨��ǰָ����ǰ��k����Ȼ������ָ��һ��ÿ����һ��
//ʱ��O(n),�ռ�O(1)
int GetKthToLast(LinkList L, int k)
{
	LNode* front = L, * rear = front;
	int cnt = 0;
	while (cnt < k && front != nullptr)
	{
		front = front->next;
		++cnt;
	}
	if (front == nullptr)
		return 0;
	while (front != nullptr && rear != nullptr)
	{
		front = front->next;
		rear = rear->next;
	}
	cout << rear->data << endl;
	return 1;
}

//23 ��ͷ���ĵ�������ҹ�����׺����ʼλ��
//ʱ��O(n),�ռ�O(1)
LNode* FindCommon4(LinkList L1, LinkList L2)
{
	if (L1->next == nullptr || L2->next == nullptr)
		return nullptr;
	int len1 = GetLength(L1), len2 = GetLength(L2), diff = len2 - len1;
	LNode* longL = diff > 0 ? L2 : L1;
	LNode* shortL = longL == L1 ? L2 : L1;
	diff = abs(diff);
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

#pragma region 24
//����������������Ͷ���
typedef struct LinkNode
{
	int data;	//abs(data)<=n
	struct LinkNode* link;
}LinkNode;

//(��ͷ���ĵ�����)��������һ�γ��ֵĽ���ɾ���������ֵ��ͬ�Ľ��
//ʱ��O(n),�ռ�O(n)
void DeleteElemWithSameAbs(LinkList L, int n)
{
	int* map = new int[n + 1] {0};
	LNode* p = L->next, * prior = L;
	while (p != nullptr)
	{
		if (map[abs(p->data)] > 0)
		{
			auto temp = p;
			prior->next = p->next;
			p = prior->next;
			free(temp);
		}
		else
		{
			map[abs(p->data)] = 1;
			prior = p;
			p = p->next;
		}
	}
	//The delete operator deallocates memory and calls the destructor for a single object created with new.
	//The delete[] operator deallocates memoryand calls destructors for an array of objects created with new[].
	//Using delete on a pointer returned by new[] or delete[] on a pointer returned by new results in undefined behavior.
	delete[] map;
}
#pragma endregion

//25 a1,a2,...,a(n-1),an->a1,an,a2,a(n-1),...
//ʱ��O(n),�ռ�O(1)
//˼·��1.��ֳ�����������벿������ӵ�(�е�����ȡ��+1)����㿪ʼ��
//2.���ú�벿������
//3.�����ú�����������β���ǰ�벿������
void Reorder(LinkList L)
{
	int len = GetLength(L);
	if (len < 3)
		return;
	int rearFirstNo = 0;
	if (len % 2 == 1)
		rearFirstNo = (len + 1) / 2;
	else
		rearFirstNo = len / 2;
	//��ֳ�����������벿������ӵ�(�е�����ȡ��+1)����㿪ʼ��
	LNode* rearFirst = L->next, * prior = L;
	while (rearFirstNo > 0)
	{
		prior = rearFirst;
		rearFirst = rearFirst->next;
		rearFirstNo--;
	}
	prior->next = nullptr;
	//���ú�벿������
	prior = nullptr;
	while (rearFirst != nullptr)
	{
		LNode* next = rearFirst->next;
		rearFirst->next = prior;
		prior = rearFirst;
		rearFirst = next;
	}
	rearFirst = prior;
	//�����ú�����������β���ǰ�벿������
	prior = L->next;
	while (rearFirst != nullptr)
	{
		LNode* next = rearFirst->next;
		LNode* priorNext = prior->next;
		rearFirst->next = prior->next;
		prior->next = rearFirst;
		prior = priorNext;
		rearFirst = next;
	}
}
#pragma endregion
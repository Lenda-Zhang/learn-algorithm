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

#pragma region 单链表的基本操作
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

//方法2：找到第i个结点，再其前插入新结点
//思路：找到第i个结点，在i后插入新结点，再交换i结点和新结点的值
//时间为O(n)
bool InsertAfter(LinkList L, int i, int val)
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
bool Delete(LinkList L, int i)
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
#pragma endregion

#pragma region 双链表的基本操作
//尾插法建立双链表
//时间O(n)
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
//时间O(n)
bool InsertDNode(DLinkList DL, int i, int val)
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
//时间O(n)
bool DeleteDNode(DLinkList DL, int i)
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
#pragma endregion

#pragma region 循环单链表的基本操作
//尾插法正向建立循环单链表
//每个结点插入时间为O(1)，设单链表表长为n，则总时间为O(n)
LinkList CLTailInsert(LinkList& CL)
{
	int x;
	CL = (LinkList)malloc(sizeof(LNode));
	LNode* s, * r = CL;	//r为尾指针
	scanf("%d", &x);
	while (x != 9999)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = CL;	//尾结点指针指向头指针
	return CL;
}

//带头结点的循环单链表判空
//时间O(1)
bool IsCircularListEmpty(LinkList CL)
{
	if (CL->next == CL)
		return true;
	return false;
}

//带头结点的循环单链表打印(遍历)
//时间O(n)
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

#pragma region 循环双链表的基本操作
//尾插法正向建立循环双链表
//时间O(n)
DLinkList CDLTailInsert(DLinkList& CDL)
{
	CDL = (DLinkList)malloc(sizeof(DNode));
	DNode* s, * r = CDL;	//r为尾指针
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

//带头结点的循环双链表判空
//时间O(1)
bool IsCDLEmpty(DLinkList CDL)
{
	if (CDL->prior == CDL && CDL->next == CDL)
		return true;
	return false;
}

//带头结点的循环双链表打印(遍历)
//时间O(n)
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

#pragma region 2.3 综合题
//01 设计一个递归算法,删除不带头结点的单链表L中所有值为x的结点
//时间O(n),n为单链表的长度
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

//02 时间O(n),n为单链表的长度
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

//03 带头结点的单链表，从尾到头反向输出每个结点的值
//时间O(n),空间O(1)
void OutputInversion(LinkList L)
{
	if (L->next == nullptr)
		return;
	//先反转链表
	LNode* prior = nullptr, * p = L->next;
	while (p != nullptr)
	{
		LNode* next = p->next;
		p->next = prior;
		prior = p;
		p = next;
	}
	L->next = prior;
	//再输出每个结点的值
	PrintLinkList(L);
}

//04 在带头结点的单链表L中删除一个最小值结点(唯一)的高效算法
//时间O(n),空间O(1)
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

//05 将带头结点的单链表就地逆置
//时间O(n),空间O(1)
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

//06 带头结点的单链表，使其元素递增有序
//使用直接插入排序算法,时间O(n^2),空间O(1)
void SortIncreasing(LinkList L)
{
	if (L->next == nullptr)
		return;
	LNode* p = L->next->next;
	L->next->next = nullptr;	//先构成只含有一个数据结点的单链表
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

//07 带头结点的单链表无序，删除表中所有介于给定的两个值之间的元素（若存在）
//时间O(n),空间O(1)
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

//08 找出两个单链表的公共结点(不带头结点)
//时间O(len1+len2),空间O(1),len1,len2分别为单链表L1,L2的长度
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

//09 带头结点的单链表，按递增次序输出单链表中各结点的数据元素，并释放结点所占的存储空间
//（要求：不允许使用数组作为辅助空间）
//注：采用第06题思想，先直接插入排序，再输出并释放内存空间
//时间O(n^2),空间O(1)
void OutputIncreasing(LinkList& L)
{
	if (L->next == nullptr)
		return;
	LNode* p = L->next->next;
	L->next->next = nullptr;	//先构成只含有一个数据结点的单链表
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

//10 把一个带头结点的单链表分解成两个带头结点的A和B：
//只含原表中序号为奇数的元素的单链表和
//只含原表中序号为偶数的元素的单链表
//且保持相对顺序不变
//时间O(n),空间O(1)
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

//11 L={a1,b1,a2,b2,...,an,bn}就地拆分成
//A={a1,a2,...,an}和B={bn,...,b2,b1}
//采用第10题思路，区别在于：1.对B表的建立改为头插法；2.不使用序号。
//时间O(n),空间O(1)
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

//12 递增有序的单链表，去除重复元素
//时间O(n),空间O(1)
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

//13 将两个递增有序的单链表归并成一个递减的单链表，
//并要求利用原来两个单链表的空间存放归并后的单链表
//思路：利用头插法反转顺序
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
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

//带头结点的循环单链表的最后一个结点
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
	if (L == nullptr)	//递归出口
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

//02 在带头结点的单链表，删除所有值为x的结点，并释放其空间
//时间O(n),n为单链表的长度，空间O(1)
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
//带头结点的单链表，从尾到头反向输出每个结点的值
//解法1：反转链表后再输出
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

//解法2：利用递归栈（重点掌握）
//时间O(n),空间O(1)
void OutputInversion2(LinkList L)
{
	if (L->next != nullptr)
	{
		OutputInversion2(L->next);
		cout << L->next->data << " ";
	}
}
#pragma endregion

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
//注：也可用头插法。
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
//时间O(max(len1,len2)),空间O(1),len1,len2分别为单链表L1,L2的长度
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

//09 带头结点的单链表，按递增次序输出单链表中各结点的数据元素，并释放结点所占的存储空间
//（要求：不允许使用数组作为辅助空间）
//注：采用第06题思想，先直接插入排序，再输出并释放内存空间
//或者每次遍历找出最小值结点，输出并删除。时间也为O(n^2)
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

//14 A,B是两个带头结点的单链表，元素递增有序，
//从A和B中的公共元素产生带头结点的单链表C，
//要求不破坏A,B的结点
//时间O(len1+len2),空间O(1),len1,len2分别为单链表L1,L2的长度
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

//15 带头结点的两个递增的链表，求交集并存入第一个链表
//时间O(len1+len2),空间O(1),len1,len2分别为单链表L1,L2的长度
void FindCommon3(LinkList& L1, LinkList& L2)
{
	LNode* p1 = L1->next, * p2 = L2->next, * p1Prior = L1;
	while (p1 != nullptr && p2 != nullptr)
	{
		if (p1->data == p2->data)
		{
			p1Prior->next = p1;	//L1中结点放入结果集
			p1Prior = p1;
			p1 = p1->next;
			LNode* p = p2;	//L2中结点释放
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
	while (p1 != nullptr)	//L2已遍历完，L1未遍历完
	{
		LNode* p = p1;
		p1 = p1->next;
		free(p);
	}
	while (p2 != nullptr)	//L1已遍历完，L2未遍历完
	{
		LNode* p = p2;
		p2 = p2->next;
		free(p);
	}
	p1Prior->next = nullptr;
	free(L2);
}

//16 两个整数序列A,B已存入单链表，判断B是否为A的连续子序列
//时间O(len1*len2),空间O(1)
bool IsSubsequence(LinkList A, LinkList B)
{
	if (B->next == nullptr)	//空表是任何序列的连续子序列
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

//17 判断带头结点的循环双链表是否对称
//时间O(n),空间O(1)
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

//18 不带头结点的循环单链表h1和h2，将h2链接到h1之后，
//要求链接后的链表仍保持循环链表形式
//时间O(len1+len2),空间O(1),len1,len2分别为单链表L1,L2的长度
void Link(LinkList& h1, LinkList& h2)
{
	if (h2->next == h2)	//若h2为空，则无需链接
		return;
	LNode* r1 = h1, * r2 = h2;
	while (r1->next != h1)	//若h1为空且h2不为空，则将h2链接到h1之后，并将h2尾结点的指针域指向h1
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

//19 带头结点的循环单链表，反复找出最小的结点，删除，直到链表为空，再删除头结点
//时间O(n^2),空间O(1)
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

//带头结点的带访问频度的双链表
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

//20 编写Locate(L,x)，每次访问频度加1，并使链表中结点保持按频度递减排列，
//同时最近访问的结点排在相同频度的结点前面
//时间O(n),空间O(1)
FreqDNode* Locate(FreqDLinkList FDL, int x)
{
	if (IsFreqDLEmpty(FDL))
		return nullptr;
	FreqDNode* p = FDL->next;
	while (p != nullptr && p->data == x)
	{
		p = p->next;
	}
	//若找到值为x的结点，则将它从链表上摘下
	//并从头开始扫描，插入到频度相同的结点前面
	if (p != nullptr)
	{
		p->freq++;
		if (p->pre == FDL || p->pre->freq > p->freq)
			return p;
		p->pre->next = p->next;	//将它从链表上摘下
		if (p->next != nullptr)
			p->next->pre = p->pre;
		FreqDNode* q = p->pre;
		while (q != FDL && q->freq <= p->freq)	//查找前驱结点
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

//21 判断单链表是否存在环（不带头结点）
//思路：快慢指针法，慢指针每次走一步，快指针每次走两步
//时间O(n),空间O(1)
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

//22 查找带头结点的单链表中倒数第k个结点的值
//思路：前后指针法，前指针提前走k步，然后两个指针一起每次走一步
//时间O(n),空间O(1)
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

//23 带头结点的单链表查找公共后缀的起始位置
//时间O(n),空间O(1)
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
//单链表结点的数据类型定义
typedef struct LinkNode
{
	int data;	//abs(data)<=n
	struct LinkNode* link;
}LinkNode;

//(带头结点的单链表)仅保留第一次出现的结点而删除其余绝对值相同的结点
//时间O(n),空间O(n)
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
//时间O(n),空间O(1)
//思路：1.拆分成两个链表，后半部分链表从第(中点向上取整+1)个结点开始；
//2.倒置后半部分链表；
//3.将倒置后的链表结点依次插入前半部分链表。
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
	//拆分成两个链表，后半部分链表从第(中点向上取整+1)个结点开始；
	LNode* rearFirst = L->next, * prior = L;
	while (rearFirstNo > 0)
	{
		prior = rearFirst;
		rearFirst = rearFirst->next;
		rearFirstNo--;
	}
	prior->next = nullptr;
	//倒置后半部分链表
	prior = nullptr;
	while (rearFirst != nullptr)
	{
		LNode* next = rearFirst->next;
		rearFirst->next = prior;
		prior = rearFirst;
		rearFirst = next;
	}
	rearFirst = prior;
	//将倒置后的链表结点依次插入前半部分链表
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
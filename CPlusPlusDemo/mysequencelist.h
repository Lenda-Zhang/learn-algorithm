#pragma once
#include "myinclude.h"

#define MaxSize 50	//定义线性表的最大长度
//静态分配
typedef struct {
	int data[MaxSize];	//顺序表的元素
	int length;	//顺序表的当前长度
}MySqList;	//顺序表的类型定义

void InitList(MySqList& L)
{
	L.length = 0;
}

void DestroyList(MySqList& L)
{
	// Q: Do I need to delete the array L.data?
	// A: Variables declared on the stack don't need to be manually deallocated. 
	// The array you declared is actually stored as an auto (automatic storage) variable, 
	// meaning that it is automatically deallocated when it goes out of scope.
	// In C and C++, unless you explicitly tell the compiler otherwise, 
	// your variables are placed in the stack, meaning that they only exist within the scope (that is, the block) in which they're declared. 
	// The way to explicitly tell the compiler to put something on the heap is either with malloc (the C way) or new (the C++ way). Only then do you need to call free (in C) or delete/delete[] (C++).
	L.length = 0;
}

//在顺序表L的第i个位置插入新元素e
bool ListInsert(MySqList& L, int i, int e)
{
	if (i<1 || i>L.length + 1)	// 判断i的范围是否相等
		return false;
	if (L.length >= MaxSize)	// 当前存储位置已满，不能加入
		return false;
	for (int j = L.length; j >= i; j--)
	{
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}

//删除顺序表L中第i个位置的元素
bool ListDelete(MySqList& L, int i, int& e)
{
	if (i<1 || i>L.length)
		return false;
	e = L.data[i - 1];
	for (int j = i; j < L.length; j++)
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return true;
}

//在顺序表L中查找第一个元素值等于e的元素，并返回其位序
int LocateElem(MySqList L, int e)
{
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return 0;	//说明查找失败
}

void PrintList(MySqList L)
{
	for (int i = 0; i < L.length; i++)
	{
		cout << L.data[i] << " ";
	}
	cout << endl;
}

//动态分配
#define InitSize 100
typedef struct {
	int* data;
	int MaxSide, length;
}MySqListDA;

void InitListDA(MySqListDA& L)
{
	//C way
	//L.data = (int*)malloc(sizeof(int) * InitSize);
	//C++ way
	L.data = new int[InitSize];
	L.length = 0;
}

void DestroyListDA(MySqListDA& L)
{
	//C way
	//free(L.data);
	//C++ way
	delete(L.data);
	L.length = 0;
}

/* 2.2 综合题 */
//01 时间O(n),空间O(1)
bool DeleteMin(MySqList& L, int& e)
{
	if (L.length <= 0)
		return false;
	int min = INT_MAX, index = 0;
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] < min)
		{
			min = L.data[i];
			index = i;
		}
	}
	e = min;
	L.data[index] = L.data[L.length - 1];
	L.length--;
	return true;
}

//02 时间O(n),空间O(1)
void Reverse(MySqList& L)
{
	for (int i = 0; i < L.length / 2; i++)
	{
		int temp = L.data[i];
		L.data[i] = L.data[L.length - i - 1];
		L.data[L.length - i - 1] = temp;
	}
}

//03 时间O(n),空间O(1)
void RemoveAllElemsWithValX(MySqList& L, int x)
{
	if (L.length <= 0)
		return;
	int cnt = 0;	//值为x的元素个数
	int firstPos = -1;
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] == x)
		{
			if (cnt == 0)
				firstPos = i;
			++cnt;
		}
	}
	if (cnt > 0)
	{
		for (int i = firstPos + 1, j = firstPos; i < L.length; i++)
		{
			if (L.data[i] != x)
			{
				L.data[j] = L.data[i];
				j++;
			}
		}
		L.length -= cnt;
	}
}

//04 时间O(n),空间O(1)
bool RemoveFromOrderedList(MySqList& L, int s, int t)
{
	if (L.length <= 0 || s >= t)
		return false;
	int cnt = 0, firstPos = -1;
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] >= s && L.data[i] <= t)
		{
			if (cnt == 0)
				firstPos = i;
			cnt++;
		}
	}
	for (int i = firstPos; (i + cnt) < L.length; i++)
	{
		L.data[i] = L.data[i + cnt];
	}
	L.length -= cnt;
	return true;
}

//05 时间O(n),空间O(1)
bool RemoveFromList(MySqList& L, int s, int t)
{
	if (L.length <= 0 || s >= t)
		return false;
	int cnt = 0, firstPos = -1;
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] >= s && L.data[i] <= t)
		{
			if (cnt == 0)
				firstPos = i;
			cnt++;
		}
	}
	if (cnt > 0)
	{
		for (int i = firstPos + 1, j = firstPos; i < L.length; i++)
		{
			if (L.data[i]<s || L.data[i]>t)
			{
				L.data[j] = L.data[i];
				j++;
			}
		}
		L.length -= cnt;
	}
	return true;
}

//06 有序表,时间O(n),空间O(1)
void DeleteDuplicateFromSort(MySqList& L)
{
	if (L.length <= 0)
		return;
	int i = 0;
	for (int j = 1; j < L.length; j++)
	{
		if (L.data[j] != L.data[i])
			L.data[++i] = L.data[j];
	}
	L.length = i + 1;
}

typedef struct LNode {
	int data;
	struct LNode* next;
}LNode, * Linklist;

//06 思考:无序表,使用散列表拉链法,时间O(n),空间O(n)
void DeleteDuplicate(MySqList& L)
{
	int p = L.length, k = 0;
	LNode* H[MaxSize], * S;//H[M]为散列表的数组部分
	for (int i = 0; i < p; i++)
		H[i] = NULL;
	for (int i = 0, j; i < L.length; i++)
	{
		j = L.data[i] % p;//j为元素对应的散列表数组单元
		if (H[j] == NULL)//判断对应位置链表是否为空
		{
			S = (LNode*)malloc(sizeof(LNode));//创建同义词节点
			S->data = L.data[i];
			S->next = NULL;
			H[j] = S;
			L.data[k++] = L.data[i];//将与元素放入新表中
		}
		else//对应位置链表不为空
		{
			S = H[j];
			while (S != NULL)//判断同义词链表中是否有相同元素
			{
				if (S->data == L.data[i])
					break;
				S = S->next;
			}
			if (S == NULL)//没有相同元素
			{
				S = (LNode*)malloc(sizeof(LNode)); // 创建同义词节点
				S->data = L.data[i];
				S->next = H[j];
				H[j] = S;
				L.data[k++] = L.data[i];//将与元素放入新表中
			}
		}
	}
	L.length = k;
}

//07 时间O(a.length+b.length),空间O(1)
bool MergeSortList(MySqList a, MySqList b, MySqList& c)
{
	if (a.length + b.length > MaxSize)
		return false;
	int i = 0, j = 0, k = 0;
	while (i < a.length && j < b.length)
	{
		if (a.data[i] > b.data[j])
			c.data[k++] = b.data[j++];
		else
			c.data[k++] = a.data[i++];
	}
	while (i < a.length)
		c.data[k++] = a.data[i++];
	while (j < b.length)
		c.data[k++] = b.data[j++];
	c.length = k;
	return true;
}

void printArray(int a[], int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

//08 辅助函数:left,right范围:0~arraySize-1
bool MyReverseList(int a[], int left, int right, int arraySize)
{
	if (arraySize <= 0 || left > right || right > arraySize - 1)
		return false;
	for (int i = left, j = right; i < j; i++, j--)
	{
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	return true;
}

//08 时间O(n),空间O(1)
void Exchange(int a[], int m, int n, int arraySize)
{
	printArray(a, arraySize);
	MyReverseList(a, 0, m - 1, arraySize);
	printArray(a, arraySize);
	MyReverseList(a, m, m + n - 1, arraySize);
	printArray(a, arraySize);
	MyReverseList(a, 0, m + n - 1, arraySize);
	printArray(a, arraySize);
}

//09 有序表且要求时间最少,则使用折半查找,时间,空间
void FindOrInsert(int a[], int x, int& arraySize)
{
	int low = 0, high = arraySize - 1, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == x)
			break;
		else if (a[mid] > x)
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (a[mid] == x && mid != (arraySize - 1))
	{
		int temp = a[mid];
		a[mid] = a[mid + 1];
		a[mid + 1] = temp;
	}
	//没找到，则插入线性表
	if (low > high)
	{
		int i;
		for (i = arraySize - 1; i > high; i--)
		{
			a[i + 1] = a[i];
		}
		a[i + 1] = x;
		arraySize++;
	}
}
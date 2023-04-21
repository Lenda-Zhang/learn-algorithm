#pragma once
#include "myinclude.h"

#define MaxSize 50	//�������Ա����󳤶�
//��̬����
typedef struct {
	int data[MaxSize];	//˳����Ԫ��
	int length;	//˳���ĵ�ǰ����
}MySqList;	//˳�������Ͷ���

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

//��˳���L�ĵ�i��λ�ò�����Ԫ��e
bool ListInsert(MySqList& L, int i, int e)
{
	if (i<1 || i>L.length + 1)	// �ж�i�ķ�Χ�Ƿ����
		return false;
	if (L.length >= MaxSize)	// ��ǰ�洢λ�����������ܼ���
		return false;
	for (int j = L.length; j >= i; j--)
	{
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}

//ɾ��˳���L�е�i��λ�õ�Ԫ��
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

//��˳���L�в��ҵ�һ��Ԫ��ֵ����e��Ԫ�أ���������λ��
int LocateElem(MySqList L, int e)
{
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return 0;	//˵������ʧ��
}

void PrintList(MySqList L)
{
	for (int i = 0; i < L.length; i++)
	{
		cout << L.data[i] << " ";
	}
	cout << endl;
}

//��̬����
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

/* 2.2 �ۺ��� */
//01 ʱ��O(n),�ռ�O(1)
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

//02 ʱ��O(n),�ռ�O(1)
void Reverse(MySqList& L)
{
	for (int i = 0; i < L.length / 2; i++)
	{
		int temp = L.data[i];
		L.data[i] = L.data[L.length - i - 1];
		L.data[L.length - i - 1] = temp;
	}
}

//03 ʱ��O(n),�ռ�O(1)
void RemoveAllElemsWithValX(MySqList& L, int x)
{
	if (L.length <= 0)
		return;
	int cnt = 0;	//ֵΪx��Ԫ�ظ���
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

//04 ʱ��O(n),�ռ�O(1)
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

//05 ʱ��O(n),�ռ�O(1)
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

//06 �����,ʱ��O(n),�ռ�O(1)
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

//06 ˼��:�����,ʹ��ɢ�б�������,ʱ��O(n),�ռ�O(n)
void DeleteDuplicate(MySqList& L)
{
	int p = L.length, k = 0;
	LNode* H[MaxSize], * S;//H[M]Ϊɢ�б�����鲿��
	for (int i = 0; i < p; i++)
		H[i] = NULL;
	for (int i = 0, j; i < L.length; i++)
	{
		j = L.data[i] % p;//jΪԪ�ض�Ӧ��ɢ�б����鵥Ԫ
		if (H[j] == NULL)//�ж϶�Ӧλ�������Ƿ�Ϊ��
		{
			S = (LNode*)malloc(sizeof(LNode));//����ͬ��ʽڵ�
			S->data = L.data[i];
			S->next = NULL;
			H[j] = S;
			L.data[k++] = L.data[i];//����Ԫ�ط����±���
		}
		else//��Ӧλ������Ϊ��
		{
			S = H[j];
			while (S != NULL)//�ж�ͬ����������Ƿ�����ͬԪ��
			{
				if (S->data == L.data[i])
					break;
				S = S->next;
			}
			if (S == NULL)//û����ͬԪ��
			{
				S = (LNode*)malloc(sizeof(LNode)); // ����ͬ��ʽڵ�
				S->data = L.data[i];
				S->next = H[j];
				H[j] = S;
				L.data[k++] = L.data[i];//����Ԫ�ط����±���
			}
		}
	}
	L.length = k;
}

//07 ʱ��O(a.length+b.length),�ռ�O(1)
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

//08 ��������:left,right��Χ:0~arraySize-1
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

//08 ʱ��O(n),�ռ�O(1)
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

//09 �������Ҫ��ʱ������,��ʹ���۰����,ʱ��,�ռ�
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
	//û�ҵ�����������Ա�
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
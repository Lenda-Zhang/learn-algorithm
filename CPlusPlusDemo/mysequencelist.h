#pragma once
#include "myinclude.h"
#include "wdlinklist.h"

#pragma region 静态分配
//定义线性表的最大长度
#define MaxSize 50
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
#pragma endregion

#pragma region 动态分配
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
#pragma endregion

#pragma region 2.2 综合题
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
	MyReverseList(a, 0, m - 1, arraySize);
	MyReverseList(a, m, m + n - 1, arraySize);
	MyReverseList(a, 0, m + n - 1, arraySize);
}

//09 有序表且要求时间最少,则使用折半查找,时间O(log2n),空间O(1)
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
	if (a[mid] == x && mid != (arraySize - 1))	//找到则与后继元素互换
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

void Reverse(int a[], int from, int to)
{
	for (int i = 0; i < (to - from + 1) / 2; i++)
	{
		int temp = a[from + i];
		a[from + i] = a[to - i];
		a[to - i] = temp;
	}
	//自做
	/*for (int i = from, j = to; i < j; i++, j--)
	{
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}*/
}

//10 循环左移p个元素,0<p<n,时间空间都尽可能高效
// 时间O(n),空间O(1)
void Converse(int a[], int n, int p)
{
	Reverse(a, 0, p - 1);
	Reverse(a, p, n - 1);
	Reverse(a, 0, n - 1);
}

//11 找出等长升序序列a和b的中位数,长度>=1,时间空间都尽可能高效,时间O(n),空间O(1)
int FindMedian(int a[], int b[], int arraySize)
{
	int i = 0, j = 0, k = 0, median = a[0];	//中位数应为包含a和b所有元素的升序序列中的第arraySize个数，median记录中位数，k记录当前是第几个数
	while (i < arraySize && j < arraySize)
	{
		if (a[i] > b[j])
			median = b[j++];
		else
			median = a[i++];
		k++;
		if (k == arraySize)
			break;
	}
	return median;
}

//12 找出主元素,0<=ai<n,时间空间都尽可能高效,时间O(n),空间O(n)
int FindMajorElement(int a[], int n)
{
	if (n < 1)
		return -1;
	int* const cnts = new int[n] {0};
	for (int i = 0; i < n; i++)
	{
		cnts[a[i]]++;
	}
	int major = cnts[0], maxCnt = 0;
	for (int i = 1; i < n; i++)
	{
		if (cnts[i] > maxCnt)
		{
			major = i;
			maxCnt = cnts[i];
		}
	}
	delete[] cnts;
	if (maxCnt > n / 2)
		return major;
	return -1;
}

//13 找出数组中未出现的最小正整数,在时间上尽可能高效,因此采用空间换时间,时间O(n),空间O(n)
int FindMinPositiveInt(int a[], int n)
{
	int* const b = new int[n] {0};	//依次存储数字1~n是否出现，如：b[0]=1表示数字1出现，b[n-1]表示数字n出现
	for (int i = 0; i < n; i++)
	{
		if (a[i] > 0 && a[i] <= n)
			b[a[i] - 1] = 1;
	}
	int i;
	for (i = 0; i < n; i++)
	{
		if (b[i] == 0)
			break;
	}
	return i + 1;
}

void sortThreeInts(int& a, int& b, int& c)
{
	if (a > c)
		swap(a, c);
	if (a > b)
		swap(a, b);
	if (b > c)
		swap(b, c);
}

//a是否为三个数中的最小值
bool xls_min(int a, int b, int c)
{
	if (a <= b && a <= c) return true;
	return false;
}

//14 计算并输出所有三元组中的最小距离,D=|a-b|+|b-c|+|c-a|,时间空间都尽可能高效,
//时间O(n),空间O(1),n为三个数组长度之和
int GetTripleMinDistance(int A[], int n, int B[], int m, int C[], int p)
{
	int dMin = INT_MAX;
	int i = 0, j = 0, k = 0;
	while (i < n && j < m && k < p && dMin > 0)
	{
		int d = abs(A[i] - B[j]) + abs(B[j] - C[k]) + abs(C[k] - A[i]);
		if (d < dMin)
			dMin = d;
		if (xls_min(A[i], B[j], C[k]))	//更新a
			i++;
		else if (xls_min(B[j], A[i], C[k]))
			j++;
		else
			k++;
	}
	return dMin;
}
#pragma endregion
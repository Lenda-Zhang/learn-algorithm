#pragma once
#include "myinclude.h"

typedef int ElemType;

#pragma region 插入排序
//直接插入排序
//时间O(n^2),空间O(1)
//稳定性：稳定
//适用性：适用于顺序存储和链式存储
void InsertSort(ElemType a[], int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
	{
		if (a[i] < a[i - 1]) {
			a[0] = a[i];	//复制为哨兵，a[0]不存放元素
			for (j = i - 1; a[0] < a[j]; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = a[0];
		}
	}
}

//折半插入排序
//时间O(n^2),空间O(1)
//稳定性：稳定
//适用性：仅适用于顺序存储
void InsertSort2(ElemType a[], int n)
{
	int i, j, low, high, mid;
	for (i = 2; i <= n; i++)
	{
		a[0] = a[i];	//复制为哨兵，a[0]不存放元素
		low = 1;
		high = i - 1;
		while (low <= high)	//优点：比较次数约为O(nlog2(n))，与待排序表的初始状态无关，仅取决于表中元素个数n
		{
			mid = (low + high) / 2;
			if (a[mid] > a[0])
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i - 1; j >= high + 1; --j)
		{
			a[j + 1] = a[j];
		}
		a[high + 1] = a[0];
	}
}

//希尔排序
//时间O(n^2),空间O(1)
//稳定性：不稳定
//适用性：仅适用于顺序存储
void ShellSort(ElemType a[], int n)
{
	//a[0]只是暂存单元，不是哨兵。当j<=0时，插入位置已到
	int dk, i, j;
	for (dk = n / 2; dk >= 1; dk = dk / 2)
		for (i = dk + 1; i <= n; ++i)
			if (a[i] < a[i - dk])
			{
				a[0] = a[i];
				for (j = i - dk; j > 0 && a[j] > a[0]; j -= dk)
					a[j + dk] = a[j];
				a[j + dk] = a[0];
			}
}
#pragma endregion

#pragma region 交换排序
//冒泡排序
//时间O(n^2),空间O(1)
//稳定性：稳定
//适用性：适用于顺序存储和链式存储的线性表，当链式存储时，可以从前向后进行比较查找插入位置
void BubbleSort(ElemType a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		bool flag = false;	//表示本趟冒泡是否发生交换的标志
		for (int j = n - 1; j > i; j--)
		{
			if (a[j - 1] > a[j]) {
				swap(a[j - 1], a[j]);
				flag = true;
			}
		}
		if (!flag)	//若本趟遍历后没有发生交换，说明表已经有序
			return;
	}
}

//一趟划分
int Partition(ElemType a[], int low, int high)
{
	ElemType pivot = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= pivot)
			--high;
		a[low] = a[high];
		while (low < high && a[low] <= pivot)
			++low;
		a[high] = a[low];
	}
	a[low] = pivot;
	return low;
}

//快速排序
//时间：平均与最佳很接近,为O(nlog2(n)),最坏为O(n^2),
//空间O(log2(n))~O(n)
//稳定性：不稳定
//适用性：只适用于顺序存储
void QuickSort(ElemType a[], int low, int high)
{
	if (low < high)
	{
		int pivotpos = Partition(a, low, high);
		QuickSort(a, low, pivotpos - 1);
		QuickSort(a, pivotpos + 1, high);
	}
}
#pragma endregion

#pragma region 选择排序
//简单选择排序

//堆排序
#pragma endregion
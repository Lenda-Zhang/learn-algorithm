#pragma once
#include "myinclude.h"

typedef int ElemType;

#pragma region ��������
//ֱ�Ӳ�������
//ʱ��O(n^2),�ռ�O(1)
//�ȶ��ԣ��ȶ�
//�����ԣ�������˳��洢����ʽ�洢
void InsertSort(ElemType a[], int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
	{
		if (a[i] < a[i - 1]) {
			a[0] = a[i];	//����Ϊ�ڱ���a[0]�����Ԫ��
			for (j = i - 1; a[0] < a[j]; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = a[0];
		}
	}
}

//�۰��������
//ʱ��O(n^2),�ռ�O(1)
//�ȶ��ԣ��ȶ�
//�����ԣ���������˳��洢
void InsertSort2(ElemType a[], int n)
{
	int i, j, low, high, mid;
	for (i = 2; i <= n; i++)
	{
		a[0] = a[i];	//����Ϊ�ڱ���a[0]�����Ԫ��
		low = 1;
		high = i - 1;
		while (low <= high)	//�ŵ㣺�Ƚϴ���ԼΪO(nlog2(n))����������ĳ�ʼ״̬�޹أ���ȡ���ڱ���Ԫ�ظ���n
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

//ϣ������
//ʱ��O(n^2),�ռ�O(1)
//�ȶ��ԣ����ȶ�
//�����ԣ���������˳��洢
void ShellSort(ElemType a[], int n)
{
	//a[0]ֻ���ݴ浥Ԫ�������ڱ�����j<=0ʱ������λ���ѵ�
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
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
//�����ԣ���������˳��洢��������˳��洢�������������
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

#pragma region ��������
//ð������
//ʱ��O(n^2),�ռ�O(1)
//�ȶ��ԣ��ȶ�
//�����ԣ�������˳��洢����ʽ�洢�����Ա�����ʽ�洢ʱ�����Դ�ǰ�����бȽϲ��Ҳ���λ��
void BubbleSort(ElemType a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		bool flag = false;	//��ʾ����ð���Ƿ��������ı�־
		for (int j = n - 1; j > i; j--)
		{
			if (a[j - 1] > a[j]) {
				swap(a[j - 1], a[j]);	//��װ��swap()�������ƶ�Ԫ��3��
				flag = true;
			}
		}
		if (!flag)	//�����˱�����û�з���������˵�����Ѿ�����
			return;
	}
}

//һ�˻���
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

//��������
//ʱ�䣺ƽ������Ѻܽӽ�,ΪO(nlog2(n)),�ΪO(n^2),
//�ռ�O(log2(n))~O(n)
//�ȶ��ԣ����ȶ�
//�����ԣ�ֻ������˳��洢
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

#pragma region ѡ������
//��ѡ������
//ʱ��O(n^2),�ռ�O(1)
//�ȶ��ԣ����ȶ�
//�����ԣ�������˳��洢����ʽ�洢
void SelectSort(ElemType a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;	//��¼��СԪ�ص�λ��
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[min])
				min = j;
		}
		if (min != i)
			swap(a[i], a[min]);
	}
}

//����Ԫ��kΪ�����������е���
void HeapAdjust(ElemType a[], int k, int len)
{
	a[0] = a[k];	//a[0]�ݴ������ĸ����,Ԫ�ش�1��ʼ�洢
	for (int i = 2 * k; i <= len; i *= 2)
	{
		if (i < len && a[i] < a[i + 1])
			i++;	//ȡֵ�ϴ���ӽ������ɸѡ
		if (a[0] >= a[i])
			break;
		else
		{
			a[k] = a[i];	//��a[i]������˫�׽����
			k = i;
		}
	}
	a[k] = a[0];
}

//���������
void BuildMaxHeap(ElemType a[], int len)
{
	for (int i = len / 2; i > 0; i--)	//��(n/2)~1,�������Ϸ���������
	{
		HeapAdjust(a, i, len);
	}
}

//������
//ʱ��O(nlog2(n)),�ռ�O(1)
//�ȶ��ԣ����ȶ�
//�����ԣ���������˳��洢��������˳��洢�������������
void HeapSort(ElemType a[], int len)
{
	BuildMaxHeap(a, len);
	for (int i = len; i > 1; i--)	//�ô���ѽ�����������,���Դ�len��ʼ,ע:�±�0����������,Ԫ�ش�1��ʼ�洢
	{
		swap(a[i], a[1]);
		HeapAdjust(a, 1, i - 1);
	}
}
#pragma endregion

#pragma region �鲢����
int n = 10;
ElemType* b = (ElemType*)malloc((n + 1) * sizeof(ElemType));	//��������B
//��a������a[low...mid]��a[mid+1...high]��������,�����Ǻϲ���һ�������
void Merge(ElemType a[], int low, int mid, int high)
{
	int i, j, k;
	for (k = low; k <= high; k++)
	{
		b[k] = a[k];
	}
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
	{
		if (b[i] <= b[j])
			a[k] = b[i++];
		else
			a[k] = b[j++];
	}
	while (i <= mid)
		a[k++] = b[i++];
	while (j <= high)
		a[k++] = b[j++];
}

//2·�鲢����
//ʱ��O(nlog2(n)),�ռ�O(n)
//�ȶ��ԣ��ȶ�
//�����ԣ�������˳��洢
void MergeSort(ElemType a[], int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);
		Merge(a, low, mid, high);
	}
}
#pragma endregion
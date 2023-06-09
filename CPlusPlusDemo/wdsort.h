#pragma once
#include "myinclude.h"
#include "wdtree.h"

#pragma region ����������(Binary Sort Tree)
//����(�ݹ�)
BSTNode* BST_Search_Recursion(BiTree T, ElemType key)
{
	if (T == nullptr)
		return nullptr;
	if (key == T->data)
		return T;
	else if (key < T->data)
		return BST_Search_Recursion(T->lchild, key);
	else
		return BST_Search_Recursion(T->rchild, key);
}

//����(�ǵݹ�)
BSTNode* BST_Search_Iteration(BiTree T, ElemType key)
{
	while (T && key != T->data)
	{
		if (key < T->data)
			T = T->lchild;
		else
			T = T->rchild;
	}
	return T;
}

//���룬ע������ֵ0��ʾ���д�����ͬ�ؼ��ֵĽ�㣬����ʧ�ܣ�1��ʾ����ɹ�
int BST_Insert(BiTree& T, ElemType key)
{
	if (T == nullptr)
	{
		T = (BSTNode*)malloc(sizeof(BSTNode));
		T->data = key;
		T->lchild = nullptr; 
		T->rchild = nullptr;
		return 1;
	}
	else if (key == T->data)
	{
		return 0;
	}
	else if (key < T->data)
	{
		return BST_Insert(T->lchild, key);
	}
	else
	{
		return BST_Insert(T->rchild, key);
	}
}

//����
void Create_BST(BiTree& T, ElemType str[], int n)
{
	T = nullptr;	//��ʼʱTΪ����
	int i = 0;
	while (i < n)
	{
		BST_Insert(T, str[i]);
	}
}

//ɾ�������޴���
//˼�룺��3��������ǣ�
//1.����ɾ�����z��Ҷ�ڵ㣬��ֱ��ɾ���������ƻ����������������ʡ�
//2.�����zֻ��һ����������������������z��������Ϊz���������������z��λ�á�
//3.�����z��������������������z��ֱ�Ӻ��(��ֱ��ǰ��)���z��Ȼ��Ӷ�����������ɾȥ���ֱ�Ӻ��(��ֱ��ǰ��)��������ת�����˵�һ��ڶ��������


#pragma endregion
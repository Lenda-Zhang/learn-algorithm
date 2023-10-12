#pragma once
#include "myinclude.h"
#include "wdtree.h"

#pragma region 二叉排序树(Binary Sort Tree)
//查找(递归)
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

//查找(非递归)
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

//插入，注：返回值0表示树中存在相同关键字的结点，插入失败；1表示插入成功
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

//构造
void Create_BST(BiTree& T, ElemType str[], int n)
{
	T = nullptr;	//初始时T为空树
	int i = 0;
	while (i < n)
	{
		BST_Insert(T, str[i]);
	}
}

//删除，暂无代码
//思想：分3种情况考虑：
//1.若被删除结点z是叶节点，则直接删除，不会破坏二叉排序树的性质。
//2.若结点z只有一棵左子树或右子树，则让z的子树成为z父结点的子树，替代z的位置。
//3.若结点z有左、右两棵子树，则令z的直接后继(或直接前驱)替代z，然后从二叉排序树中删去这个直接后继(或直接前驱)，这样就转换成了第一或第二种情况。


#pragma endregion
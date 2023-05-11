#pragma once
#include "myinclude.h"

//线索二叉树的存储结构
typedef struct ThreadNode
{
	int data;
	struct ThreadNode* lchild, * rchild, * parent;
	int ltag, rtag;
}ThreadNode, * ThreadTree;

//序列化与反序列化线索二叉树
class WdCodec {
public:
	// Encodes a tree to a single string.
	string serialize(ThreadNode* root) {
		string str;
		if (root == nullptr)
			str += "None,";
		else
		{
			// dfs中preOrder
			str += to_string(root->data) + ",";
			str += serialize(root->lchild);
			str += serialize(root->rchild);
		}
		return str;
	}

	// Decodes your encoded data to tree.
	ThreadNode* deserialize(string data) {
		list<string> dataArray;
		string str;
		for (auto& ch : data)
		{
			if (ch == ',')
			{
				dataArray.push_back(str);
				str.clear();
			}
			else
			{
				str.push_back(ch);
			}
		}
		if (!str.empty())
		{
			dataArray.push_back(str);
			str.clear();
		}
		return rdeserialize(dataArray, nullptr);
	}
private:
	ThreadNode* rdeserialize(list<string>& dataArray, ThreadNode* parent)
	{
		if (dataArray.front() == "None")
		{
			dataArray.erase(dataArray.begin());
			return nullptr;
		}
		ThreadNode* root = (ThreadNode*)malloc(sizeof(ThreadNode));
		root->data = stoi(dataArray.front());
		root->parent = parent;
		root->ltag = 0;
		root->rtag = 0;
		dataArray.erase(dataArray.begin());
		if (!dataArray.empty())
			root->lchild = rdeserialize(dataArray, root);
		if (!dataArray.empty())
			root->rchild = rdeserialize(dataArray, root);
		return root;
	}
};

#pragma region 中序线索二叉树
void InThread(ThreadTree& p, ThreadTree& pre)
{
	if (p != nullptr)
	{
		InThread(p->lchild, pre);
		if (p->lchild == nullptr)
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != nullptr && pre->rchild == nullptr)
		{
			pre->rchild = p;
			pre->rtag = 1;
		}
		pre = p;
		InThread(p->rchild, pre);
	}
}

//中序遍历建立中序线索二叉树
void CreateInThread(ThreadTree T)
{
	ThreadTree pre = nullptr;
	if (T != nullptr)
	{
		InThread(T, pre);
		pre->rchild = nullptr;
		pre->rtag = 1;
	}
}

//找到中序序列中的第一个结点
ThreadNode* LNRFirstnode(ThreadTree T)
{
	ThreadNode* p = T;
	while (p->ltag == 0)
		p = p->lchild;
	return p;
}

//中序线索二叉树中结点p的后继
ThreadNode* LNRNextnode(ThreadNode* p)
{
	if (p->rtag == 0)
		return LNRFirstnode(p->rchild);
	return p->rchild;
}

//找到中序序列中的最后一个结点
ThreadNode* LNRLastnode(ThreadTree T)
{
	ThreadNode* p = T;
	while (p->rtag == 0)
		p = p->rchild;
	return p;
}

//中序线索二叉树中结点p的前驱
ThreadNode* LNRPrevnode(ThreadNode* p)
{
	if (p->ltag == 0)
		return LNRLastnode(p->lchild);
	return p->lchild;
}

void InOrder(ThreadTree T)
{
	for (ThreadNode* p = LNRFirstnode(T); p != nullptr; p = LNRNextnode(p))
		cout << unitbuf << p->data << " " << nounitbuf;
	cout << endl;
}

void InOrderReverse(ThreadTree T)
{
	for (ThreadNode* p = LNRLastnode(T); p != nullptr; p = LNRPrevnode(p))
		cout << unitbuf << p->data << " " << nounitbuf;
	cout << endl;
}
#pragma endregion

#pragma region 先序线索二叉树
void PreThread(ThreadTree& p, ThreadTree& pre)
{
	if (p != nullptr)
	{
		//solve error: 由于结点的lchild存入前驱信息，无法判断合适跳出递归了，所以要先缓存
		ThreadNode* lchild = p->lchild;
		ThreadNode* rchild = p->rchild;
		if (p->lchild == nullptr)
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != nullptr && pre->rchild == nullptr)
		{
			pre->rchild = p;
			pre->rtag = 1;
		}
		pre = p;
		PreThread(lchild, pre);
		PreThread(rchild, pre);
	}
}

//先序遍历建立先序线索二叉树
void CreatePreThread(ThreadTree T)
{
	ThreadTree pre = nullptr;
	if (T != nullptr)
	{
		PreThread(T, pre);
		pre->rchild = nullptr;
		pre->rtag = 1;
	}
}

//找到先序序列中的第一个结点
ThreadNode* NLRFirstnode(ThreadTree T)
{
	return T;
}

//先序线索二叉树中结点p的后继
ThreadNode* NLRNextnode(ThreadNode* p)
{
	if (p->ltag == 0)
		return p->lchild;
	return p->rchild;
}

//找到先序序列中的最后一个结点
ThreadNode* NLRLastnode(ThreadTree T)
{
	ThreadNode* p = T;
	if (p->rtag == 1)
		return p->rchild;
	while (p->rtag == 0)
		p = p->rchild;
	if (p->ltag == 0)
		p = NLRLastnode(p->lchild);
	return p;
}

//先序线索二叉树中结点p的前驱
ThreadNode* NLRPrevnode(ThreadNode* p)
{
	if (p->ltag == 1)	//若p的左孩子为前驱结点
		return p->lchild;
	if (p->parent == nullptr)	//若p为根节点
		return nullptr;
	else if ((p->parent->ltag == 0 && p == p->parent->lchild) || (p->parent->rtag == 0 && p == p->parent->rchild && p->parent->ltag == 1))	//若p为双亲的左孩子或双亲的右孩子且双亲的左孩子为空
		return p->parent;
	else
		return LNRLastnode(p->parent->lchild);	//若p为双亲的右孩子且双亲的左孩子不为空
}

void PreOrder(ThreadTree T)
{
	for (ThreadNode* p = NLRFirstnode(T); p != nullptr; p = NLRNextnode(p))
		cout << unitbuf << p->data << " " << nounitbuf;
	cout << endl;
}

void PreOrderReverse(ThreadTree T)
{
	for (ThreadNode* p = NLRLastnode(T); p != nullptr; p = NLRPrevnode(p))
		cout << unitbuf << p->data << " " << nounitbuf;
	cout << endl;
}
#pragma endregion

#pragma region 后序线索二叉树
void PostThread(ThreadTree& p, ThreadTree& pre)
{
	if (p != nullptr)
	{
		PostThread(p->lchild, pre);
		PostThread(p->rchild, pre);
		if (p->lchild == nullptr)
		{
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != nullptr && pre->rchild == nullptr)
		{
			pre->rchild = p;
			pre->rtag = 1;
		}
		pre = p;
	}
}

//后序遍历建立后序线索二叉树
void CreatePostThread(ThreadTree T)
{
	ThreadTree pre = nullptr;
	if (T != nullptr)
	{
		PostThread(T, pre);
		if (pre->rchild == nullptr)
			pre->rtag = 1;
	}
}

//找到后序序列中的第一个结点
ThreadNode* LRNFirstnode(ThreadTree T)
{
	ThreadNode* p = T;
	while (p->ltag == 0)
		p = p->lchild;
	if (p->rtag == 0)
		return LRNFirstnode(p->rchild);
	else
		return p;
}

//后序线索二叉树中结点p的后继
ThreadNode* LRNNextnode(ThreadNode* p)
{
	if (p->parent == nullptr)
		return nullptr;
	else if ((p->parent->rtag == 0 && p == p->parent->rchild) || (p->parent->ltag == 0 && p == p->parent->lchild && p->parent->rtag == 1))
		return p->parent;
	else
		return LRNFirstnode(p->parent->rchild);
}

void PostOrder(ThreadTree T)
{
	for (ThreadNode* p = LRNFirstnode(T); p != nullptr; p = LRNNextnode(p))
		cout << unitbuf << p->data << " " << nounitbuf;
	cout << endl;
}
#pragma enregion
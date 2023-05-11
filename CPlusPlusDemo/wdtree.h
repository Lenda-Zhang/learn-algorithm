#pragma once
#include "myinclude.h"

//�����������Ĵ洢�ṹ
typedef struct ThreadNode
{
	int data;
	struct ThreadNode* lchild, * rchild, * parent;
	int ltag, rtag;
}ThreadNode, * ThreadTree;

//���л��뷴���л�����������
class WdCodec {
public:
	// Encodes a tree to a single string.
	string serialize(ThreadNode* root) {
		string str;
		if (root == nullptr)
			str += "None,";
		else
		{
			// dfs��preOrder
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

#pragma region ��������������
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

//�������������������������
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

//�ҵ����������еĵ�һ�����
ThreadNode* LNRFirstnode(ThreadTree T)
{
	ThreadNode* p = T;
	while (p->ltag == 0)
		p = p->lchild;
	return p;
}

//���������������н��p�ĺ��
ThreadNode* LNRNextnode(ThreadNode* p)
{
	if (p->rtag == 0)
		return LNRFirstnode(p->rchild);
	return p->rchild;
}

//�ҵ����������е����һ�����
ThreadNode* LNRLastnode(ThreadTree T)
{
	ThreadNode* p = T;
	while (p->rtag == 0)
		p = p->rchild;
	return p;
}

//���������������н��p��ǰ��
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

#pragma region ��������������
void PreThread(ThreadTree& p, ThreadTree& pre)
{
	if (p != nullptr)
	{
		//solve error: ���ڽ���lchild����ǰ����Ϣ���޷��жϺ��������ݹ��ˣ�����Ҫ�Ȼ���
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

//�������������������������
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

//�ҵ����������еĵ�һ�����
ThreadNode* NLRFirstnode(ThreadTree T)
{
	return T;
}

//���������������н��p�ĺ��
ThreadNode* NLRNextnode(ThreadNode* p)
{
	if (p->ltag == 0)
		return p->lchild;
	return p->rchild;
}

//�ҵ����������е����һ�����
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

//���������������н��p��ǰ��
ThreadNode* NLRPrevnode(ThreadNode* p)
{
	if (p->ltag == 1)	//��p������Ϊǰ�����
		return p->lchild;
	if (p->parent == nullptr)	//��pΪ���ڵ�
		return nullptr;
	else if ((p->parent->ltag == 0 && p == p->parent->lchild) || (p->parent->rtag == 0 && p == p->parent->rchild && p->parent->ltag == 1))	//��pΪ˫�׵����ӻ�˫�׵��Һ�����˫�׵�����Ϊ��
		return p->parent;
	else
		return LNRLastnode(p->parent->lchild);	//��pΪ˫�׵��Һ�����˫�׵����Ӳ�Ϊ��
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

#pragma region ��������������
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

//�������������������������
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

//�ҵ����������еĵ�һ�����
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

//���������������н��p�ĺ��
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
#pragma once
#include "myinclude.h"
#include "wdstack.h"

//����������ʽ�洢�ṹ
typedef int ElemType;

typedef struct BiTNode
{
	ElemType data;	//������
	struct BiTNode* lchild, * rchild;	//���Һ���ָ��
}BiTNode, * BiTree;

BiTNode* rdeserialize(list<string>& dataArray, BiTNode* parent)
{
	if (dataArray.front() == "None")
	{
		dataArray.erase(dataArray.begin());
		return nullptr;
	}
	BiTNode* root = (BiTNode*)malloc(sizeof(BiTNode));
	root->data = stoi(dataArray.front());
	dataArray.erase(dataArray.begin());
	if (!dataArray.empty())
		root->lchild = rdeserialize(dataArray, root);
	if (!dataArray.empty())
		root->rchild = rdeserialize(dataArray, root);
	return root;
}

// Encodes a tree to a single string.
string Serialize(BiTNode* root) {
	string str;
	if (root == nullptr)
		str += "None,";
	else
	{
		// dfs��preOrder
		str += to_string(root->data) + ",";
		str += Serialize(root->lchild);
		str += Serialize(root->rchild);
	}
	return str;
}

// Decodes your encoded data to tree.
BiTNode* Deserialize(string data) {
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

//�ҵ����������е����һ�����
ThreadNode* LRNLastnode(ThreadTree T)
{
	return T;
}

//���������������н��p��ǰ��
ThreadNode* LRNPrevnode(ThreadTree T)
{
	ThreadNode* p = T;
	//��pΪҶ�ӽڵ�
	if (p->ltag == 1 && p->rtag == 1)
	{
		return p->lchild;
	}
	else if (p->rtag == 0)	//��p���Һ���
	{
		return p->rchild;
	}
	else	//��pû���Һ��ӣ���������
	{
		return p->lchild;
	}
}

void PostOrder(ThreadTree T)
{
	for (ThreadNode* p = LRNFirstnode(T); p != nullptr; p = LRNNextnode(p))
		cout << unitbuf << p->data << " " << nounitbuf;
	cout << endl;
}

void PostOrderReverse(ThreadTree T)
{
	for (ThreadNode* p = LRNLastnode(T); p != nullptr; p = LRNPrevnode(p))
		cout << unitbuf << p->data << " " << nounitbuf;
	cout << endl;
}
#pragma endregion

#pragma region 5.3 �ۺ���
void PreOrderRecursion(BiTree T)
{
	if (T)
	{
		cout << unitbuf << T->data << " " << nounitbuf;
		PreOrderRecursion(T->lchild);
		PreOrderRecursion(T->rchild);
	}
}

void InOrderRecursion(BiTree T)
{
	if (T)
	{
		InOrderRecursion(T->lchild);
		cout << unitbuf << T->data << " " << nounitbuf;
		InOrderRecursion(T->rchild);
	}
}

//3 ��������������ķǵݹ��㷨
//ʱ��O(n),�ռ�O(n),nΪ�������������
void PostOrderIteration(BiTree T)
{
	stack<BiTNode*> s;
	auto node = T;
	BiTNode* prev = nullptr;
	while (!s.empty() || node)
	{
		while (node)
		{
			s.push(node);
			node = node->lchild;
		}
		node = s.top();
		if (node->rchild == nullptr || prev == node->rchild)
		{
			cout << unitbuf << node->data << " " << nounitbuf;
			prev = node;
			node = nullptr;	//node�ÿգ�ʹ������ջ�н��
			s.pop();
		}
		else
		{
			node = node->rchild;
		}
	}
}

//4 ���������µ��ϣ����ҵ����α����㷨
//˼·����ԭ��BFS�㷨�м�һ��ջ��ԭ���ʴ���ĳ���ջ���룬�����н����ջ���ٳ�ջ
//ʱ��O(n),�ռ�O(n),nΪ�������������
void BFSReverse(BiTree T)
{
	if (T == nullptr)
		return;
	queue<BiTNode*> q;
	q.push(T);
	stack<BiTNode*> s;
	while (!q.empty())
	{
		auto node = q.front();
		s.push(node);
		if (node->lchild != nullptr)
			q.push(node->lchild);
		if (node->rchild != nullptr)
			q.push(node->rchild);
		q.pop();
	}
	while (!s.empty())
	{
		auto node = s.top();
		cout << unitbuf << node->data << " " << nounitbuf;
		s.pop();
	}
}

//5 �ǵݹ��㷨��������߶�
//˼·��ʹ��DFS�к��������ջ��󳤶ȼ�Ϊ�������߶�
//ʱ��O(n),�ռ�O(n),nΪ�������������
int GetHeight(BiTree T)
{
	stack<BiTNode*> s;
	BiTNode* node = T, * prev = nullptr;
	int height = 0;
	while (!s.empty() || node)
	{
		while (node)
		{
			s.push(node);
			node = node->lchild;
		}
		if (s.size() > height)
			height = s.size();
		node = s.top();
		if (node->rchild == nullptr || prev == node->rchild)
		{
			//cout << unitbuf << node->data << " " << nounitbuf;
			prev = node;
			node = nullptr;
			s.pop();
		}
		else
		{
			node = node->rchild;
		}
	}
	return height;
}

//*5 �ο��𰸣��ǵݹ��㷨��������߶�
//˼·��BFS�����ݵ�ǰ����Ƿ�Ϊ��ǰ�����ҽ�㣬�ж�һ���Ƿ������ɣ��Ӷ�ȷ��������
//ʱ��ռ临�ӶȲο�BFS��
//ע�⣺��ĳ���������ÿ�����������������ȣ����ɲ�����������Ƶ�˼�롣
int GetHeight2(BiTree T)
{
	if (!T)
		return 0;
	int level = 0;
	queue<BiTNode*> q;
	q.push(T);
	BiTNode* lastOfTheLevel = q.back();	//��ǰ������ҽ��
	while (!q.empty())
	{
		auto node = q.front();
		if (node->lchild != nullptr)
			q.push(node->lchild);
		if (node->rchild != nullptr)
			q.push(node->rchild);
		q.pop();
		if (node == lastOfTheLevel)
		{
			level++;
			if (!q.empty())
				lastOfTheLevel = q.back();
		}
	}
	return level;
}

//6 �����������ֵ������ͬ�������������������������н����ö������Ķ�������
//ע�⣺ʹ��llen,rlen���±���㣬�����ж��Ƿ��к���
//ʱ��O(n),�ռ�O(1),nΪ�������������
BiTNode* Deserialize(int l1, int h1, int l2, int h2, int preOrder[], int inOrder[])
{
	BiTNode* root = (BiTNode*)malloc(sizeof(BiTNode));
	root->data = preOrder[l1];
	int i;
	for (i = l2; inOrder[i] != preOrder[l1]; i++);
	int llen = i - l2, rlen = h2 - i;
	if (llen)
	{
		root->lchild = Deserialize(l1 + 1, l1 + llen, l2, l2 + llen - 1, preOrder, inOrder);
	}
	else
		root->lchild = nullptr;
	if (rlen)
	{
		root->rchild = Deserialize(h1 - rlen + 1, h1, h2 - rlen + 1, h2, preOrder, inOrder);
	}
	else
		root->rchild = nullptr;
	return root;
}

//7 �б�����������Ƿ�Ϊ��ȫ������
//˼·������BFS�������н��������(�����ս��)��
//�����ս��ʱ���鿴����Ƿ��зǿս�㡣
//���У�������ȫ��������
//ʱ��O(n),ÿ�������ӳ���һ��,�ռ�O(n)
bool IsFBT(BiTree T)
{
	if (!T)
		return false;
	bool isnullptr = false;
	queue<BiTNode*> q;
	q.push(T);
	while (!q.empty())
	{
		auto node = q.front();
		if (node == nullptr)
		{
			isnullptr = true;
			q.pop();
			continue;
		}
		else
		{
			if (isnullptr)
				return false;
			q.push(node->lchild);
			q.push(node->rchild);
			q.pop();
		}
	}
	return true;
}

//8 ���������������˫��֧���ĸ���
//
int NumOfDoubleBranchNode(BiTree T)
{
	if (T == nullptr)
		return 0;
	else if (T->lchild != nullptr && T->rchild != nullptr)
		return NumOfDoubleBranchNode(T->lchild) + NumOfDoubleBranchNode(T->rchild) + 1;
	else
		return NumOfDoubleBranchNode(T->lchild) + NumOfDoubleBranchNode(T->rchild);
}

//9 �������������н�����������
//˼·��DFS���������LRN��
//ʱ��ռ临�Ӷ�ͬ�������(�ݹ�)�㷨��
void SwapLRChild(BiTree T)
{
	if (T)
	{
		SwapLRChild(T->lchild);
		SwapLRChild(T->rchild);
		auto temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
}

int i = 1;	//������ŵ�ȫ�ֱ���
//10 ��������������е�k������ֵ��1<=k<=�������
//ʱ��ռ临�Ӷ�ͬ�������(�ݹ�)
string GetKthOfPreOrder(BiTree T, int k)
{
	if (T == nullptr)
		return "#";	//�����־
	else if (i == k)
	{
		return to_string(T->data);
	}
	else
	{
		i++;
		auto data = GetKthOfPreOrder(T->lchild, k);
		return data == "#" ? GetKthOfPreOrder(T->rchild, k) : data;
	}
}

//�ͷſռ䣺�Ⱥ��Ӻ����ʹ��LRN
void DeleteXTree(BiTree& T)
{
	if (T)
	{
		DeleteXTree(T->lchild);
		T->lchild = nullptr;
		DeleteXTree(T->rchild);
		T->rchild = nullptr;
		free(T);
	}
}

//11 ��������ÿ��ֵΪx�Ľ�㣬ɾ������Ϊ�������������ͷ���Ӧ�Ŀռ�
//�ͷſռ䣺�Ⱥ��Ӻ����ʹ��LRN��ɾ����������Ҫ��˫�׽���Ӧ�ĺ��ӽ���ÿգ�ʹ��BFS
//ʱ��O(n),ÿ��������һ��,�ռ�O(n),û��ֵΪx�Ľ��,���൱�ڲ������
void Search(BiTree& T, int x)
{
	if (!T)
		return;
	if (T->data == x)
	{
		DeleteXTree(T);
		T = nullptr;
		return;
	}
	queue<BiTNode*> q;
	q.push(T);
	while (!q.empty())
	{
		auto node = q.front();
		if (node->lchild)
		{
			if (node->lchild->data == x)
			{
				DeleteXTree(node->lchild);
				node->lchild = nullptr;
			}
			else
			{
				q.push(node->lchild);
			}
		}
		if (node->rchild)
		{
			if (node->rchild->data == x)
			{
				DeleteXTree(node->rchild);
				node->rchild = nullptr;
			}
			else
			{
				q.push(node->rchild);
			}
		}
		q.pop();
	}
}

//12 ��ӡֵΪx�Ľ����������ȣ�����ֵΪx�Ľ�㲻����һ��
//˼·����������ķǵݹ�ʵ��
void PrintXAncestor(BiTree T, int x)
{
	BiTNode* node = T, * prev = nullptr;
	stack<BiTNode*> s;
	while (!s.empty() || node)
	{
		while (node != nullptr)
		{
			s.push(node);
			node = node->lchild;
		}
		node = s.top();
		if (node->rchild == nullptr || node->rchild == prev)
		{
			s.pop();
			if (node->data == x)
			{
				while (!s.empty())
				{
					cout << unitbuf << s.top()->data << " " << nounitbuf;
					s.pop();
				}
				return;
			}
			prev = node;
			node = nullptr;
		}
		else
		{
			node = node->rchild;
		}
	}
}

typedef struct
{
	BiTree t;
	int tag;	//tag=0��ʾ�����ѱ����ʣ�tag=1��ʾ�Һ����ѱ�����
}stackWithTag;

stackWithTag s[MaxSize], s1[MaxSize];	//ջ�����㹻��

//13 �ҳ������������������������������
//ʱ��ռ临�Ӷ�ͬ�������(�ǵݹ�)
BiTree NearestCommonAncestor(BiTree T, BiTNode* p, BiTNode* q)
{
	int top = 0, top1 = 0;
	auto bt = T;
	while (bt != nullptr || top > 0)
	{
		while (bt != nullptr)
		{
			s[++top].t = bt;
			s[top].tag = 0;
			bt = bt->lchild;
		}
		while (top != 0 && s[top].tag == 1)
		{
			//�ٶ�p��q����࣬����pʱ��ջ��Ԫ�ؾ�Ϊp������
			if (s[top].t == p)
			{
				for (int i = 1; i <= top; i++)
					s1[i] = s[i];
				top1 = top;
			}
			if (s[top].t == q)
			{
				for (int i = top; i > 0; i--)
					for (int j = top1; j > 0; j--)
						if (s1[j].t == s[i].t)
							return s[i].t;
			}
			top--;
		}
		if (top != 0)
		{
			s[top].tag = 1;
			bt = s[top].t->rchild;
		}
	}
	return nullptr;
}

//14 ��ǿն������Ŀ��
//BFS
int GetWidth(BiTree T)
{
	if (!T)
		return 0;
	queue<BiTNode*> q;
	q.push(T);
	auto lastOfTheLevel = q.back();
	int width = INT_MIN, num = 0;
	while (!q.empty())
	{
		auto node = q.front();
		if (node->lchild)
			q.push(node->lchild);
		if (node->rchild)
			q.push(node->rchild);
		num++;
		q.pop();
		if (node == lastOfTheLevel)
		{
			if (num > width)
			{
				width = num;
			}
			num = 0;
			if (!q.empty())
				lastOfTheLevel = q.back();
		}
	}
	return width;
}

vector<ElemType> to_vector(string str)
{
	vector<ElemType> v;
	string s;
	for (int i = 0; i < str.size(); i++)
	{
		while (str[i] != ',' && i < str.size())
		{
			s.push_back(str[i++]);
		}
		v.push_back(stoi(s));
		s.clear();
	}
	return v;
}

string GetPostByPre(vector<ElemType> data, int begin, int end)
{
	ElemType root = data[begin];
	int num = (end - begin) / 2;
	if (num > 0)
	{
		string lchild = GetPostByPre(data, begin + 1, begin + num);
		string rchild = GetPostByPre(data, begin + num + 1, end);
		return (!lchild.empty() ? lchild + "," : "") + (!rchild.empty() ? rchild + "," : "") + to_string(root);
	}
	return to_string(root);
}

//15 ������������(���н��ֵ����ͬ),��֪����������,��������С�
//dataΪԪ���Զ��ŷָ������������ַ���
//
string GetPostByPreStr(string data)
{
	vector<ElemType> v = to_vector(data);
	if (v.size() > 0)
		return GetPostByPre(v, 0, v.size() - 1);
	return "";
}

//16 ����������Ҷ�ӽ�㰴�����ҵ�˳������һ��������
//ʱ��ռ临�Ӷ�ͬ�������
//headΪͷ��㣬prevΪǰ�����
BiTNode* LinkListOfLeafNodes(BiTree T, BiTNode* head, BiTNode*& prev)
{
	if (T)
	{
		if (T->lchild == nullptr && T->rchild == nullptr)
		{
			prev->rchild = T;
			prev = T;
		}
		else
		{
			LinkListOfLeafNodes(T->lchild, head, prev);
			LinkListOfLeafNodes(T->rchild, head, prev);
		}
	}
	return head;
}

//17 �ж����ö������Ƿ�����
//
bool IsSimilar(BiTree T1, BiTree T2)
{
	if (T1 == nullptr && T2 == nullptr)
		return true;
	else if (T1 == nullptr || T2 == nullptr)
		return false;
	else
		return IsSimilar(T1->lchild, T2->lchild) && IsSimilar(T1->rchild, T2->rchild);
}

//18 �����������������в���ָ������ں����ǰ���ڵ�
//

#pragma endregion
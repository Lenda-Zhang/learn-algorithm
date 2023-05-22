#pragma once
#include "myinclude.h"
#include "wdstack.h"

//二叉树的链式存储结构
typedef int ElemType;

typedef struct BiTNode
{
	ElemType data;	//数据域
	struct BiTNode* lchild, * rchild;	//左右孩子指针
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
		// dfs中preOrder
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

//找到后序序列中的最后一个结点
ThreadNode* LRNLastnode(ThreadTree T)
{
	return T;
}

//后序线索二叉树中结点p的前驱
ThreadNode* LRNPrevnode(ThreadTree T)
{
	ThreadNode* p = T;
	//若p为叶子节点
	if (p->ltag == 1 && p->rtag == 1)
	{
		return p->lchild;
	}
	else if (p->rtag == 0)	//若p有右孩子
	{
		return p->rchild;
	}
	else	//若p没有右孩子，但有左孩子
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

#pragma region 5.3 综合题
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

//3 后序遍历二叉树的非递归算法
//时间O(n),空间O(n),n为二叉树结点总数
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
			node = nullptr;	//node置空，使得消耗栈中结点
			s.pop();
		}
		else
		{
			node = node->rchild;
		}
	}
}

//4 二叉树从下到上，从右到左层次遍历算法
//思路：在原有BFS算法中加一个栈，原访问代码改成入栈代码，待所有结点入栈后再出栈
//时间O(n),空间O(n),n为二叉树结点总数
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

//5 非递归算法求二叉树高度
//思路：使用DFS中后序遍历，栈最大长度即为二叉树高度
//时间O(n),空间O(n),n为二叉树结点总数
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

//*5 参考答案：非递归算法求二叉树高度
//思路：BFS，根据当前结点是否为当前层最右结点，判断一层是否遍历完成，从而确定层数。
//时间空间复杂度参考BFS。
//注意：求某层结点个数、每层结点个数、树的最大宽度，都可采用与此题类似的思想。
int GetHeight2(BiTree T)
{
	if (!T)
		return 0;
	int level = 0;
	queue<BiTNode*> q;
	q.push(T);
	BiTNode* lastOfTheLevel = q.back();	//当前层的最右结点
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

//6 二叉树各结点值互不相同，根据先序遍历、中序遍历序列建立该二叉树的二叉链表
//注意：使用llen,rlen简化下标计算，可以判断是否有孩子
//时间O(n),空间O(1),n为二叉树结点总数
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

//7 判别给定二叉树是否为完全二叉树
//思路：采用BFS，将所有结点加入队列(包括空结点)。
//遇到空结点时，查看其后是否有非空结点。
//若有，则不是完全二叉树。
//时间O(n),每个结点进队出队一次,空间O(n)
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

//8 计算二叉树中所有双分支结点的个数
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

//9 交换二叉树所有结点的左、右子树
//思路：DFS，这里采用LRN。
//时间空间复杂度同后序遍历(递归)算法。
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

int i = 1;	//遍历序号的全局变量
//10 求先序遍历序列中第k个结点的值，1<=k<=结点总数
//时间空间复杂度同先序遍历(递归)
string GetKthOfPreOrder(BiTree T, int k)
{
	if (T == nullptr)
		return "#";	//特殊标志
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

//释放空间：先孩子后根，使用LRN
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

//11 对于树中每个值为x的结点，删除以它为根的子树，并释放相应的空间
//释放空间：先孩子后根，使用LRN；删除子树，需要将双亲结点对应的孩子结点置空，使用BFS
//时间O(n),每个结点访问一次,空间O(n),没有值为x的结点,则相当于层序遍历
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

//12 打印值为x的结点的所有祖先，假设值为x的结点不多于一个
//思路：后序遍历的非递归实现
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
	int tag;	//tag=0表示左孩子已被访问，tag=1表示右孩子已被访问
}stackWithTag;

stackWithTag s[MaxSize], s1[MaxSize];	//栈容量足够大

//13 找出二叉树中任意两结点的最近公共祖先
//时间空间复杂度同后序遍历(非递归)
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
			//假定p在q的左侧，遇到p时，栈中元素均为p的祖先
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

//14 求非空二叉树的宽度
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

//15 根据满二叉树(所有结点值均不同),已知其先序序列,求后序序列。
//data为元素以逗号分隔的先序序列字符串
//
string GetPostByPreStr(string data)
{
	vector<ElemType> v = to_vector(data);
	if (v.size() > 0)
		return GetPostByPre(v, 0, v.size() - 1);
	return "";
}

//16 将二叉树的叶子结点按从左到右的顺序连成一个单链表
//时间空间复杂度同先序遍历
//head为头结点，prev为前驱结点
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

//17 判断两棵二叉树是否相似
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

//18 在中序线索二叉树中查找指定结点在后序的前驱节点
//

#pragma endregion
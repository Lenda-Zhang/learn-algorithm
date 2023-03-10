#pragma once
#include <queue>
#include <immintrin.h>
using namespace std;

/** @brief 41:
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
class MovingAverage {
private:
	int _size;
	double _sums;
	queue<int> _queue;
public:
	/** Initialize your data structure here. */
	MovingAverage(int size) : _sums(0) {
		_size = size;
	}

	double next(int val) {
		if (_queue.size() == _size)
		{
			_sums -= _queue.front();
			_queue.pop();
		}
		_queue.emplace(val);
		_sums += val;
		return _sums / _queue.size();
	}
};

/** @brief 42:
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
class RecentCounter {
private:
	queue<int> _requests; // �洢����ʱ�䣬����ÿ�ζ� ping �ĵ��ö�ʹ�ñ�֮ǰ����� t ֵ������д�front��back��ֵ����
public:
	RecentCounter() {

	}

	int ping(int t) {
		while (!_requests.empty() && _requests.front() < t - 3000)
			_requests.pop();
		_requests.push(t);
		return _requests.size();
	}
};

/*
 * Definition for a binary tree node.
 */
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/** @brief 43������ȫ��������ӽڵ�
* ����
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
class CBTInserter1 {
private:
	TreeNode* root;
	queue<TreeNode*> candidate;
public:
	CBTInserter1(TreeNode* root) {
		this->root = root;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			auto node = q.front();
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
			if (node->left == nullptr || node->right == nullptr)
				candidate.push(node);
			q.pop();
		}
	}

	int insert(int v) {
		TreeNode* node = new TreeNode(v);
		TreeNode* parent = candidate.front();
		int ret = parent->val;
		if (parent->left == nullptr)
			parent->left = node;
		else
		{
			parent->right = node;
			candidate.pop();
		}
		candidate.push(node);
		return ret;
	}

	TreeNode* get_root() {
		return root;
	}
};

/** @brief 43������ȫ��������ӽڵ�
* �����Ʊ�ʾ
*/
class CBTInserter {
private:
	TreeNode* root;
	int count = 0;
public:
	CBTInserter(TreeNode* root) {
		this->root = root;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			auto node = q.front();
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
			++count;
			q.pop();
		}
	}

	int insert(int v) {
		++count;
		TreeNode* node = new TreeNode(v);
		TreeNode* parent = root;
		int highbit = 31 - _lzcnt_u32(count); // For 32 bits, _lzcnt_u32 equals __builtin_clz.
		for (int i = highbit - 1; i >= 1; --i)
		{
			if (count & (1 << i))
				parent = parent->right;
			else
				parent = parent->left;
		}
		if (count & 1)
			parent->right = node;
		else
			parent->left = node;

		return parent->val;
	}

	TreeNode* get_root() {
		return root;
	}
};

/**
* ʮ����ת������
*/
string toBinary(int n)
{
	string r;
	while (n != 0)
	{
		r += (n % 2 == 0 ? "0" : "1");
		n >>= 1;
	}
	reverse(r.begin(), r.end());
	//reverseString(r);
	return r;

	/*int number = 15;
	bitset<32> bs(number);*/
}

/**
* ��ת�ַ���
*/
void reverseString(string& s)
{
	int n = s.length();
	for (int i = 0; i < n / 2; i++)
	{
		int temp = s[n - i - 1];
		s[n - i - 1] = s[i];
		s[i] = temp;
	}
}

/**
* �������������
*/
void levelOrder(TreeNode* root)
{
	if (root == nullptr)
		return;
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		auto node = q.front();
		if (node->left != nullptr)
			q.push(node->left);
		if (node->right != nullptr)
			q.push(node->right);
		cout << node->val << " ";
		q.pop();
	}
	cout << endl;
}

/**
* �������������
*/
void preOrder(TreeNode* root)
{
	if (root)
	{
		cout << root->val << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

/** @brief 44��������ÿ������ֵ
 * ������������������ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(height)������nΪ�������ڵ������height��ʾ�������ĸ߶ȡ�
 */
class Solution1 {
public:
	void preOrder(vector<int>& res, TreeNode* root, int curHeight)
	{
		if (curHeight == res.size())
			res.push_back(root->val);
		else
			res[curHeight] = max(root->val, res[curHeight]);
		if (root->left)
			preOrder(res, root->left, curHeight + 1);
		if (root->right)
			preOrder(res, root->right, curHeight + 1);
	}

	vector<int> largestValues(TreeNode* root) {
		if (!root)
			return {};
		vector<int> res;
		preOrder(res, root, 0);
		return res;
	}
};

/** @brief 44��������ÿ������ֵ
 * ������ȱ�����ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)���洢�������ڵ�Ŀռ俪����
 */
class Solution2 {
public:
	vector<int> largestValues(TreeNode* root) {
		if (!root)
			return {};
		vector<int> res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			int len = q.size();
			int maxVal = INT_MIN;
			while (len > 0)
			{
				--len;
				auto node = q.front();
				q.pop();
				maxVal = max(maxVal, node->val);
				if (node->left)
					q.push(node->left);
				if (node->right)
					q.push(node->right);
			}
			res.push_back(maxVal);
		}
		return res;
	}
};

/** @brief ��û������45����������ײ�����ߵ�ֵ
* ������ȱ�����ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��
*/
class Solution3 {
public:
	void dfs(TreeNode* root, int height, int& curHeight, int& curVal)
	{
		if (root == nullptr)
			return;
		++height;
		dfs(root->left, height, curHeight, curVal);
		dfs(root->right, height, curHeight, curVal);
		if (height > curHeight)
		{
			curHeight = height;
			curVal = root->val;
		}
	}

	int findBottomLeftValue(TreeNode* root) {
		int curVal, curHeight = 0;
		dfs(root, 0, curHeight, curVal);
		return curVal;
	}
};

/** @brief 45��
* ������ȱ���
* ʱ�临�Ӷ�ΪO(n)
* �ռ临�Ӷ�ΪO(n)�����������Ϊ���������������q��ౣ��n/2(����ȡ��)���ڵ㡣
*/
class Solution4
{
public:
	int findBottomLeftValue(TreeNode* root)
	{
		int ret;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			auto node = q.front();
			q.pop();
			if (node->right)
				q.push(node->right);
			if (node->left)
				q.push(node->left);
			ret = node->val;
		}
		return ret;
	}
};

/** @brief 46:���������Ҳ���ͼ
*/
class Solution5 {
public:
	// ������ȱ���
	// ʱ�临�Ӷ�ΪO(n)��ÿ���ڵ���ӳ���һ�Σ��ռ临�Ӷ�ΪO(n)�����г�����󲻳���n������nΪ�ڵ�����
	vector<int> rightSideViewBFS(TreeNode* root) {
		if (root == nullptr)
			return {};
		queue<pair<TreeNode*, int>> q;
		unordered_map<int, int> rightmostValAtDepth;
		q.push(make_pair(root, 0));
		while (!q.empty())
		{
			auto nodeInfo = q.front();
			q.pop();
			rightmostValAtDepth[nodeInfo.second] = nodeInfo.first->val; //ÿ�������ʵļ�Ϊ�ò����Ҳ�ڵ�
			if (nodeInfo.first->left)
				q.push(make_pair(nodeInfo.first->left, nodeInfo.second + 1));
			if (nodeInfo.first->right)
				q.push(make_pair(nodeInfo.first->right, nodeInfo.second + 1));
		}
		vector<int> res;
		for (int i = 0; i < rightmostValAtDepth.size(); ++i)
			res.push_back(rightmostValAtDepth[i]);
		return res;
	}

	// ������ȱ���
	// ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)�����������߶ȵ����ܽڵ���n
	vector<int> rightSideView(TreeNode* root)
	{
		if (root == nullptr)
			return {};
		unordered_map<int, int> rightmostValAtDepth;
		vector<int> res;
		dfs(root, 0, rightmostValAtDepth);
		for (int i = 0; i < rightmostValAtDepth.size(); i++)
			res.push_back(rightmostValAtDepth[i]);
		return res;
	}

	void dfs(TreeNode* root, int depth, unordered_map<int, int>& rightmostValAtDepth)
	{
		if (root)
		{
			if (rightmostValAtDepth.count(depth) == 0)
				rightmostValAtDepth[depth] = root->val;
			dfs(root->right, depth + 1, rightmostValAtDepth);
			dfs(root->left, depth + 1, rightmostValAtDepth);
		}
	}
};

/** @brief 47:��������֦
*/
class Solution {
public:
	TreeNode* pruneTree(TreeNode* root) {
		if (root == nullptr || isTreeAllVal0(root))
			return nullptr;
		if (isTreeAllVal0(root->left))
		{
			root->left = nullptr;	// ��֦
		}
		else
		{
			pruneTree(root->left);
		}
		if (isTreeAllVal0(root->right))
		{
			root->right = nullptr;
		}
		else
		{
			pruneTree(root->right);
		}
		return root;
	}

	bool isTreeAllVal0(TreeNode* root)
	{
		if (root == nullptr)
			return true;
		if (root && root->val)
			return false;
		return isTreeAllVal0(root->left) && isTreeAllVal0(root->right);
	}
};
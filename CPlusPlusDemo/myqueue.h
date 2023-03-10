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
	queue<int> _requests; // 存储请求时间，由于每次对 ping 的调用都使用比之前更大的 t 值，则队列从front到back数值递增
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

/** @brief 43：往完全二叉树添加节点
* 队列
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

/** @brief 43：往完全二叉树添加节点
* 二进制表示
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
* 十进制转二进制
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
* 反转字符串
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
* 二叉树层序遍历
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
* 二叉树先序遍历
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

/** @brief 44：二叉树每层的最大值
 * 深度优先中先序遍历，时间复杂度为O(n)，空间复杂度为O(height)，其中n为二叉树节点个数，height表示二叉树的高度。
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

/** @brief 44：二叉树每层的最大值
 * 广度优先遍历，时间复杂度为O(n)，空间复杂度为O(n)，存储二叉树节点的空间开销。
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

/** @brief （没看懂）45：二叉树最底层最左边的值
* 深度优先遍历，时间复杂度为O(n)，空间复杂度为O(n)。
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

/** @brief 45：
* 广度优先遍历
* 时间复杂度为O(n)
* 空间复杂度为O(n)。如果二叉树为满二叉树，则队列q最多保存n/2(向上取整)个节点。
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

/** @brief 46:二叉树的右侧视图
*/
class Solution5 {
public:
	// 广度优先遍历
	// 时间复杂度为O(n)，每个节点入队出队一次，空间复杂度为O(n)，队列长度最大不超过n，其中n为节点总数
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
			rightmostValAtDepth[nodeInfo.second] = nodeInfo.first->val; //每层最后访问的即为该层最右侧节点
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

	// 深度优先遍历
	// 时间复杂度为O(n)，空间复杂度为O(n)，最坏情况下树高度等于总节点数n
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

/** @brief 47:二叉树剪枝
*/
class Solution {
public:
	TreeNode* pruneTree(TreeNode* root) {
		if (root == nullptr || isTreeAllVal0(root))
			return nullptr;
		if (isTreeAllVal0(root->left))
		{
			root->left = nullptr;	// 剪枝
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
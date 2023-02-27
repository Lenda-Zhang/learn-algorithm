#pragma once
#include <queue>
using namespace std;

/** 41: 
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

/** 42: 
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

/** 43: 
* 
*/
class CBTInserter {
public:
	CBTInserter(TreeNode* root) {

	}

	int insert(int v) {

	}

	TreeNode* get_root() {

	}
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
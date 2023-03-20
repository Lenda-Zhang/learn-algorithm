#pragma once
#include "myinclude.h"

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




#pragma once
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

/**
* @brief 30�����롢ɾ����������ʶ���O(1)������
*/
class RandomizedSet {
public:
	unordered_map<int, int> indices; // Ԫ�����Ӧλ�õļ���
	vector<int> nums; // �洢Ԫ��
	bool insert(int val) {
		if (indices.count(val))
			return false;
		int index = nums.size();
		nums.emplace_back(val);
		indices[val] = index;
		return true;
	}
	bool remove(int val) {
		if (!indices.count(val))
			return false;
		// ����ɾ��Ԫ����ĩβԪ�ؽ���λ�ã���ɾ��
		int index = indices[val];
		int lastVal = nums.back();
		nums[index] = lastVal;
		indices[lastVal] = index;
		nums.pop_back();
		indices.erase(val);
		return true;
	}
	int getRandom() {
		int randomIndex = rand() % nums.size();
		return nums[randomIndex];
	}
};

struct DLinkedNode {
	int key, value;
	DLinkedNode* prev, * next;
	DLinkedNode() :key(0), value(0), prev(nullptr), next(nullptr) {}
	DLinkedNode(int _key, int _value) :key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

/**
* @brief 31��LRU�������
* Your LRUCache object will be instantiated and called as such:
* LRUCache* obj = new LRUCache(capacity);
* int param_1 = obj->get(key);
* obj->put(key,value);
*/
class LRUCache {
private:
	unordered_map<int, DLinkedNode*> cache;
	DLinkedNode* head, * tail; // dummy head, dummy tail
	int capacity, size;
	// �ѱ��нڵ��ƶ���head��
	void update(DLinkedNode* node)
	{
		// �Ȱѽڵ�ժ����
		node->next->prev = node->prev;
		node->prev->next = node->next;
		// �ٰѽڵ�ŵ�ͷ�ڵ��
		node->next = head->next;
		node->prev = head;
		head->next->prev = node;
		head->next = node;
	}
public:
	LRUCache(int _capacity) : capacity(_capacity), size(0) {
		head = new DLinkedNode(); // ȷ��node->prevʼ�ղ�Ϊnullptr
		tail = new DLinkedNode(); // ȷ��node->nextʼ�ղ�Ϊnullptr
		head->next = tail;
		tail->prev = head;
	}

	int get(int key) {
		if (!cache.count(key))
			return -1;
		DLinkedNode* node = cache[key];
		update(node);
		return node->value;
	}

	void put(int key, int value) {
		if (cache.count(key))
		{
			auto node = cache[key];
			node->value = value;
			update(node);
			return;
		}
		if (size >= capacity)
		{
			DLinkedNode* realTail = tail->prev; // �� 1 <= capacity <= 3000 �� realTail != head
			cache.erase(realTail->key);
			realTail->key = key;
			realTail->value = value;
			update(realTail);
			cache.insert({ key, realTail });
		}
		else
		{
			DLinkedNode* newNode = new DLinkedNode(key, value);
			newNode->next = head->next;
			newNode->prev = head;
			head->next->prev = newNode;
			head->next = newNode;
			cache[key] = newNode;
			++size;
		}
	}
};

/**
* @brief 32����Ч�ı�λ��
*/
bool isAnagram(string s, string t)
{
	if (s == t || s.size() != t.size())
		return false;
	int cnt[26]{ 0 }; // s���ַ����ִ���
	// memset(cnt, 0, sizeof(cnt)); // ��ʼ��ȫ������Ԫ��
	for (auto c : s)
	{
		++cnt[c - 'a'];
	}
	for (auto c : t)
	{
		--cnt[c - 'a'];
		if (cnt[c - 'a'] < 0)
			return false;
	}
	return true;
}

/**
* @brief 33����λ����
* ʱ�临�Ӷ�ΪO(nklogk)���ռ临�Ӷ�ΪO(nk)������nΪstrs��str������kΪ���str���ȡ�
*/
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	unordered_map<string, vector<string>> map;
	for (string& s : strs)
	{
		string key = s;
		sort(key.begin(), key.end());
		map[key].emplace_back(s);
	}
	vector<vector<string>> answer;
	for (auto it = map.begin(); it != map.end(); ++it) {
		answer.emplace_back(it->second);
	}
	return answer;
}

bool compareByOrder(string s, string t, int map[]) {
	if (s == t)
		return true;
	int len = min(s.size(), t.size());
	for (size_t i = 0; i < len; i++)
	{
		if (map[s[i] - 'a'] == map[t[i] - 'a'])
			continue;
		else
			return map[s[i] - 'a'] < map[t[i] - 'a'];
	}
	return s.size() < t.size();
}

/**
* @brief 34�����������Ƿ�����
*/
bool isAlienSorted(vector<string>& words, string order) {
	if (words.size() < 2)
		return true;
	int map[26] = { 0 };
	for (int i = 0; i < order.size(); i++)
		map[order[i] - 'a'] = i;
	for (int i = 1; i < words.size(); i++)
	{
		if (!compareByOrder(words[i - 1], words[i], map))
			return false;
	}
	return true;
}

int getMinutes(string &s)
{
	return ((s[0] - '0') * 10 + s[1] - '0') * 60 + (s[3] - '0') * 10 + s[4] - '0';
}

/**
* @brief 35����Сʱ���
*/
int findMinDifference(vector<string>& timePoints) {
	// �볲ԭ������n��������n+1ֻ���ӣ������и��Ӷ����ڸ����У���������һ������������ֻ���ӡ�
	// ���ݸ볲ԭ��24*60=1440�����������ʱ����ȣ�������Сʱ���Ϊ0.
	if (timePoints.size() > 1440)
		return 0;
	sort(timePoints.begin(), timePoints.end());
	int ans = INT_MAX;
	int t0Minutes = getMinutes(timePoints[0]);
	int preMinutes = t0Minutes;
	for (int i = 1; i < timePoints.size(); i++)
	{
		int temp = getMinutes(timePoints[i]);
		ans = min(ans, temp - preMinutes);
		preMinutes = temp;
	}
	ans = min(ans, t0Minutes + 1440 - preMinutes);
	return ans;
}


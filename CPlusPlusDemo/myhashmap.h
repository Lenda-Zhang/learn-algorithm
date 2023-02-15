#pragma once
#include <unordered_map>
#include <string>
using namespace std;

/**
* @brief 32：有效的变位词
*/
bool isAnagram(string s, string t)
{
	if (s == t || s.size() != t.size())
		return false;
	unordered_map<char, int> sTimes, tTimes; // 字符出现次数
	for (size_t i = 0; i < s.size(); i++)
	{
		++sTimes[s[i]];
		++tTimes[t[i]];
	}
	if (sTimes.size() != tTimes.size())
		return false;
	for (unordered_map<char, int>::iterator it1 = sTimes.begin(); it1 != sTimes.end(); it1++)
	{
		if (it1->second != tTimes[it1->first])
			return false;
	}
	return true;
}

bool isAnagramRefer(string s, string t)
{
	if (s.size() != t.size() || s == t)
		return false;
	vector<int> cnt(26, 0);
	for (char c : s)
		++cnt[c - 'a'];

	for (char c : t)
	{
		--cnt[c - 'a'];
		if (cnt[c - 'a'] < 0)
			return false;
	}
	return true;
}
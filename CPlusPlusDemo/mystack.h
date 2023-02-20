#pragma once
#include <vector>
#include <string>
#include <stack>
using namespace std;

/**
* @brief 36：后缀表达式
* 时间复杂度为O(n)，空间复杂度为O(n)。
*/
int evalRPN(vector<string>& tokens) {
	stack<int> operands;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
			int op2 = operands.top();
			operands.pop();
			int op1 = operands.top();
			operands.pop();
			int result = 0;
			if (tokens[i] == "+")
				result = op1 + op2;
			else if (tokens[i] == "-")
				result = op1 - op2;
			else if (tokens[i] == "*")
				result = op1 * op2;
			else
				result = op1 / op2;
			operands.push(result);
		}
		else
		{
			int op = stoi(tokens[i]);
			operands.push(op);
		}
	}
	return operands.top();
}

int evalRPNBetter(vector<string>& tokens) {
	vector<int> stack;
	for (auto& s : tokens) {
		int temp1, temp2;
		if (s.back() >= '0' && s.back() <= '9') {
			stack.push_back(std::stoi(s));
		}
		else {
			temp2 = stack.back();
			stack.pop_back();
			temp1 = stack.back();
			stack.pop_back();
			if (s[0] == '+') {
				stack.push_back(temp1 + temp2);
			}
			else if (s[0] == '-') {
				stack.push_back(temp1 - temp2);
			}
			else if (s[0] == '*') {
				stack.push_back(temp1 * temp2);
			}
			else {
				stack.push_back(temp1 / temp2);
			}
		}
	}
	return stack[0];
}

/**
* @brief 37：小行星碰撞
* 时间复杂度为O(n)，空间复杂度为O(1)，不包括返回值内存
*/
vector<int> asteroidCollision(vector<int>& asteroids) {
	vector<int> stack;
	for (size_t i = 0; i < asteroids.size(); )
	{
		if (stack.empty())
		{
			stack.emplace_back(asteroids[i]);
			i++;
			continue;
		}
		int a1 = stack.back(), a2 = asteroids[i];
		if (a1 > 0 && a2 < 0)
		{
			if (abs(a1) > abs(a2))
			{
				i++;
			}
			else if (abs(a1) == abs(a2))
			{
				stack.pop_back();
				i++;
			}
			else
			{
				stack.pop_back();
			}
		}
		else
		{
			stack.emplace_back(asteroids[i]);
			i++;
		}
	}
	return stack;
}

/**
* @brief 逻辑整合后代码
* 时间复杂度为O(n)，空间复杂度为O(1)，不包括返回值内存
*/
vector<int> asteroidCollision1(vector<int>& asteroids)
{
	vector<int> stack;
	for (auto aster : asteroids)
	{
		bool alive = true;
		while (alive && aster < 0 && !stack.empty() && stack.back() > 0)
		{
			alive = stack.back() < -aster;
			if (stack.back() <= -aster)
				stack.pop_back();
		}
		if (alive)
			stack.emplace_back(aster);
	}
	return stack;
}

/**
* @brief 38：每日温度，暴力法
* 时间复杂度为O(mn)，空间复杂度为O(m)，其中m为每个温度首次出现下标的缓存
*/
vector<int> dailyTemperaturesForce(vector<int>& temperatures) {
	int n = temperatures.size();
	vector<int> waitingDays(n);
	int next[101]{ 0 }; // 每个温度第一次出现的下标
	for (auto &t : next)
		t = INT_MAX;
	for (int i = n - 1; i >= 0; i--)
	{
		int t = temperatures[i];
		int warmIndex = INT_MAX;
		for (int j = t + 1; j < 101; j++)
		{
			warmIndex = min(warmIndex, next[j]);
		}
		if (warmIndex < INT_MAX)
			waitingDays[i] = warmIndex - i;
		next[t] = i;
	}
	return waitingDays;
}

/**
* @brief 38：每日温度，单调栈
* 时间复杂度为O(n)，其中n是温度列表的长度。正向遍历温度列表一遍，对于温度列表中的每个下标，最多有一次进栈和出栈的操作。空间复杂度为O(n)。
*/
vector<int> dailyTemperatures(vector<int>& temperatures) {
	int n = temperatures.size();
	vector<int> st(n), ans(n);
	for (int i = 0; i < temperatures.size(); i++)
	{
		while (!st.empty() && temperatures[i] > temperatures[st.back()])
		{
			int day = st.back();
			ans[day] = i - day;
			st.pop_back();
		}
		st.emplace_back(i);
	}
	return ans;
}

/**
* @note 38：提交不通过，原因：超出时间限制
*/
vector<int> dailyTemperaturesTimeout(vector<int>& temperatures) {
	vector<int> waitingDays;
	for (size_t i = 0; i < temperatures.size(); i++)
	{
		size_t j = i + 1;
		for (; j < temperatures.size(); j++)
		{
			if (temperatures[j] > temperatures[i])
				break;
		}
		int day = (j < temperatures.size() ? j - i : 0);
		waitingDays.emplace_back(day);
	}
	return waitingDays;
}
#pragma once
#include <vector>
#include <string>
#include <stack>
using namespace std;

/**
* @brief 36����׺���ʽ
* ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��
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
* @brief 37��С������ײ
* ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)������������ֵ�ڴ�
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
* @brief �߼����Ϻ����
* ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)������������ֵ�ڴ�
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
* @brief 38��ÿ���¶ȣ�������
* ʱ�临�Ӷ�ΪO(mn)���ռ临�Ӷ�ΪO(m)������mΪÿ���¶��״γ����±�Ļ���
*/
vector<int> dailyTemperaturesForce(vector<int>& temperatures) {
	int n = temperatures.size();
	vector<int> waitingDays(n);
	int next[101]{ 0 }; // ÿ���¶ȵ�һ�γ��ֵ��±�
	for (auto& t : next)
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
* @brief 38��ÿ���¶ȣ�����ջ
* ʱ�临�Ӷ�ΪO(n)������n���¶��б�ĳ��ȡ���������¶��б�һ�飬�����¶��б��е�ÿ���±꣬�����һ�ν�ջ�ͳ�ջ�Ĳ������ռ临�Ӷ�ΪO(n)��
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
* @note 38���ύ��ͨ����ԭ�򣺳���ʱ������
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

/**
* @brief 39���ύ��ͨ����ԭ�򣺳���ʱ������
* ʱ�临�Ӷ�ΪO(n^2)���ռ临�Ӷ�ΪO(1)��
*/
int largestRectangleAreaTimeout(vector<int>& heights) {
	int n = heights.size();
	int ans = 0;
	for (int mid = 0; mid < n; ++mid) {
		// ö�ٸ�
		int height = heights[mid];
		int left = mid, right = mid;
		// ȷ�����ұ߽�
		while (left - 1 >= 0 && heights[left - 1] >= height) {
			--left;
		}
		while (right + 1 < n && heights[right + 1] >= height) {
			++right;
		}
		// �������
		ans = max(ans, (right - left + 1) * height);
	}
	return ans;
}

/**
* @brief 39��ֱ��ͼ���������
* ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(n)��
*/
int largestRectangleArea(vector<int>& heights) {
	int n = heights.size();
	vector<int> left(n), right(n);
	stack<int> mono_stack;
	for (int i = 0; i < n; ++i)
	{
		while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i])
			mono_stack.pop();
		left[i] = mono_stack.empty() ? -1 : mono_stack.top();
		mono_stack.push(i);
	}
	mono_stack = stack<int>();
	for (int i = n - 1; i >= 0; --i)
	{
		while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i])
			mono_stack.pop();
		right[i] = mono_stack.empty() ? n : mono_stack.top();
		mono_stack.push(i);
	}
	int ans = 0;
	for (int i = 0; i < n; ++i)
	{
		ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
	}
	return ans;
}

/**
* @brief 40�����������ľ���
* ʱ�临�Ӷ�ΪO(m^2*n)���ռ临�Ӷ�ΪO(mn)������mΪ������nΪ������
*/
int maximalRectangle(vector<string>& matrix) {
	// ����
	int m = matrix.size();
	if (m == 0)
		return 0;
	int	n = matrix[0].size();
	vector<vector<int>> left(m, vector<int>(n));
	// �������ȼ���������ÿ��Ԫ�ص�������� 1 ��������ʹ�ö�ά���� left ��¼������ left[i][j] Ϊ����� i �е� j ��Ԫ�ص�������� 1 ��������
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] == '1')
				left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
		}
	}
	// �����
	int ret = 0;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] == '0')
				continue;
			int width = left[i][j];
			int area = width;
			for (int k = i - 1; k >= 0; --k)
			{
				width = min(width, left[k][j]);
				area = max(area, (i - k + 1) * width);
			}
			ret = max(ret, area);
		}
	}
	return ret;
}

/**
* @brief 40�����������ľ���
* ʹ�õ���ջ��ʱ�临�Ӷ�ΪO(mn)���ռ临�Ӷ�ΪO(mn)������mΪ������nΪ������
*/
int maximalRectangleBetter(vector<string>& matrix) {
	// ����
	int m = matrix.size();
	if (m == 0)
		return 0;
	int	n = matrix[0].size();
	vector<vector<int>> left(m, vector<int>(n));
	// �������ȼ���������ÿ��Ԫ�ص�������� 1 ��������ʹ�ö�ά���� left ��¼������ left[i][j] Ϊ����� i �е� j ��Ԫ�ص�������� 1 ��������
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] == '1')
				left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
		}
	}
	// ���õ���ջ�����
	int ret = 0;
	for (int j = 0; j < n; ++j)
	{
		vector<int> up(m), down(m);
		stack<int> stk;
		for (int i = 0; i < m; ++i)
		{
			while (!stk.empty() && left[stk.top()][j] >= left[i][j])
				stk.pop();
			up[i] = stk.empty() ? -1 : stk.top();
			stk.push(i);
		}
		stk = stack<int>();
		for (int i = m - 1; i >= 0; --i)
		{
			while (!stk.empty() && left[stk.top()][j] >= left[i][j])
				stk.pop();
			down[i] = stk.empty() ? m : stk.top();
			stk.push(i);
		}
		int area = 0;
		for (int i = 0; i < m; ++i)
		{
			int height = down[i] - up[i] - 1;
			area = max(area, height * left[i][j]);
		}
		ret = max(ret, area);
	}
	return ret;
}
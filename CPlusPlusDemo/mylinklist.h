#pragma once
#include <stack>

/**
* @brief ��������ڵ�
*/
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int val);
};

ListNode::ListNode(int val) : val(val), next(nullptr) { }

inline int countList(ListNode* head)
{
	int cnt = 0;
	ListNode* node = head;
	while (node != nullptr)
	{
		++cnt;
		node = node->next;
	}
	return cnt;
}

void print(ListNode* head)
{
	ListNode* node = head;
	while (node != nullptr)
	{
		std::cout << node->val << " ";
		node = node->next;
	}
	std::cout << "<end>" << std::endl;
}

/**
* @brief ��β�����һ���ڵ�
*/
ListNode* append(ListNode* head, int val)
{
	ListNode* newNode = new ListNode(val);
	if (head == nullptr)
		return newNode;
	ListNode* node = head;
	while (node->next != nullptr)
	{
		node = node->next;
	}
	node->next = newNode;
	return head;
}

/**
* @brief ʹ���ڱ��ڵ���β�����һ���ڵ�
*/
ListNode* appendWithDummy(ListNode* head, int val)
{
	ListNode* newNode = new ListNode(val);
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* node = dummy;
	while (node->next != nullptr)
	{
		node = node->next;
	}
	node->next = newNode;
	return dummy->next;
}

/**
* @brief ɾ����һ��ֵΪval�Ľڵ�
*/
ListNode* deleteFirst(ListNode* head, int val)
{
	if (head == nullptr)
		return head;
	if (head->val == val)
		return head->next;
	ListNode* node = head;
	while (node->next != nullptr) {
		if (node->next->val == val)
		{
			node->next = node->next->next;
			break;
		}
		node = node->next;
	}
	return head;
}

/**
* @brief ʹ���ڱ��ڵ�ɾ����һ��ֵΪval�Ľڵ�
*/
ListNode* deleteFirstWithDummy(ListNode* head, int val)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* node = dummy;
	while (node->next != nullptr)
	{
		if (node->next->val == val)
		{
			node->next = node->next->next;
			break;
		}
		node = node->next;
	}
	return dummy->next;
}

/**
* @brief 21��ɾ��������k���ڵ㣬1��k��n
*/
ListNode* deleteNthFromEnd(ListNode* head, int n)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* front = dummy, * rear = dummy;
	for (size_t i = 0; i < n; i++)
	{
		front = front->next;
	}
	while (front->next != nullptr)
	{
		front = front->next;
		rear = rear->next;
	}
	ListNode* p = rear->next;
	rear->next = rear->next->next;
	delete(p);
	return dummy->next;
}

/**
* @brief 21��ɾ��������k���ڵ㣬1��k��n
*/
ListNode* deleteNthFromEndInBook(ListNode* head, int n)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* front = head, * rear = dummy;
	for (size_t i = 0; i < n; i++)
	{
		front = front->next;
	}
	while (front != nullptr)
	{
		front = front->next;
		rear = rear->next;
	}
	ListNode* p = rear->next;
	rear->next = rear->next->next;
	delete(p);
	return dummy->next;
}

/**
* @brief 21ħ�ģ�ɾ��������k���ڵ�
*/
ListNode* deleteNthFromEndHard(ListNode* head, int n)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* front = dummy, * rear = dummy;
	for (size_t i = 0; i < n; i++)
	{
		if (front != nullptr)
			front = front->next;
		else
			return head;
	}
	while (front->next != nullptr)
	{
		front = front->next;
		rear = rear->next;
	}
	ListNode* p = rear->next;
	rear->next = rear->next->next;
	delete(p);
	return dummy->next;
}

/**
* @brief ɾ�����нڵ�
*/
ListNode* deleteAll(ListNode* head)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* node = dummy;
	while (node->next != nullptr)
	{
		ListNode* p = node->next;
		node->next = p->next;
		delete(p);
	}
	return nullptr;
}

/**
* @brief �ж������Ƿ����������������нڵ���
*/
bool detectCycle(ListNode* head, int& ringNodeCount)
{
	int count = 0;
	ListNode* fast = head, * slow = head;
	do {
		if (fast == nullptr)
			break;
		fast = fast->next;
		slow = slow->next;
		if (fast == nullptr)
			break;
		fast = fast->next;
		++count;
	} while (fast != slow);
	if (fast == nullptr || slow == nullptr)
		return false;
	ringNodeCount = count;
	return true;
}

/**
* @brief 22�������л�����ڽڵ�
*/
ListNode* getEntryOfRing(ListNode* head)
{
	int ringNodeCnt = 0;
	if (!detectCycle(head, ringNodeCnt))
		return nullptr;
	ListNode* front = head, * rear = head;
	for (size_t i = 0; i < ringNodeCnt; i++)
		front = front->next;
	while (front != rear)
	{
		front = front->next;
		rear = rear->next;
	}
	return front;
}

/**
* @brief 22����֪�����нڵ����Ľⷨ
*/
ListNode* getEntryOfRing2(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return nullptr;
	ListNode* slow = head->next;
	ListNode* fast = slow->next;
	while (fast != nullptr && slow != nullptr)
	{
		if (fast == slow)
		{
			ListNode* inLoop = slow;
			ListNode* p = head;
			while (p != inLoop)
			{
				p = p->next;
				inLoop = inLoop->next;
			}
			return p;
		}
		fast = fast->next;
		slow = slow->next;
		if (fast != nullptr)
			fast = fast->next;
	}
	return nullptr;
}

/**
* @brief 23����������ĵ�һ���غϽڵ�
* @note ʹ��ջ����LIFO��ʱ�临�Ӷ�O(m+n)���ռ临�Ӷ�O(m+n)
*/
ListNode* getIntersectionNode(ListNode* head1, ListNode* head2)
{
	ListNode* node1 = head1, * node2 = head2;
	std::stack<ListNode*> stack1, stack2;
	while (node1 != nullptr)
	{
		stack1.push(node1);
		node1 = node1->next;
	}
	while (node2 != nullptr)
	{
		stack2.push(node2);
		node2 = node2->next;
	}
	ListNode* intersectionNode = nullptr;
	while (!stack1.empty() && !stack2.empty())
	{
		if (stack1.top() == stack2.top())
		{
			intersectionNode = stack1.top();
			stack1.pop();
			stack2.pop();
		}
		else
			return intersectionNode;
	}
	return nullptr;
}

/**
* ����getLast����
*/
ListNode* getLast(ListNode* head);

/**
* @brief 23����������ĵ�һ���غϽڵ�
* @note ��������������һ��������������
*/
ListNode* getIntersectionNode2(ListNode* head1, ListNode* head2)
{
	if (head1 == nullptr || head2 == nullptr)
		return nullptr;
	// ���컷
	ListNode* head = (head2 == nullptr ? head1 : head2);
	ListNode* last = getLast(head);
	last->next = head;
	ListNode* newHead = (head == head2 ? head1 : head2);
	return getEntryOfRing2(newHead);
}

ListNode* getLast(ListNode* head)
{
	if (head == nullptr)
		return nullptr;
	ListNode* preNode = head, * node = head->next;
	while (node != nullptr)
	{
		preNode = node;
		node = node->next;
	}
	return preNode;
}

/**
* @brief 23����������ǰ�ƽϳ������ָ�룬ʹ�����˶��룬���ƶ��ڵ㣬�ҵ���һ����ȵ�ջָ�룬����ջ�ռ�
*/
ListNode* getIntersectionNodeInBook(ListNode* head1, ListNode* head2)
{
	int cnt1 = countList(head1);
	int cnt2 = countList(head2);
	int delta = abs(cnt1 - cnt2);
	ListNode* longer = cnt1 > cnt2 ? head1 : head2;
	ListNode* shorter = cnt1 > cnt2 ? head2 : head1;
	ListNode* node1 = longer;
	for (size_t i = 0; i < delta; i++)
	{
		node1 = node1->next;
	}
	ListNode* node2 = shorter;
	while (node1 != node2)
	{
		node1 = node1->next;
		node2 = node2->next;
	}
	return node1;
}

/**
* @brief 23��16ms������leetcode��û���
*/
ListNode* getIntersectionNodeBetter(ListNode* headA, ListNode* headB)
{
	if (headA == nullptr || headB == nullptr)
	{
		return nullptr;
	}
	ListNode* pA = headA, * pB = headB;
	while (pA != pB)
	{
		pA = pA == nullptr ? headB : pA->next;
		pB = pB == nullptr ? headA : pB->next;
	}
	return pA;
}

/**
* @brief 24����ת����
* @note ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(1)
*/
ListNode* reverseList(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return head;
	ListNode* left = nullptr, * j = head;
	while (j != nullptr)
	{
		ListNode* right = j->next;
		j->next = left;
		left = j;
		j = right;
	}
	return left;
}

/**
* @brief 24��0ms������leetcode
*/
ListNode* reverseListBetter(ListNode* head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}
	ListNode* now = reverseListBetter(head->next);
	head->next->next = head;
	head->next = nullptr;
	return now;
}

void addToList(int val, int& carry, ListNode** head)
{
	int sum = val + carry;
	carry = sum / 10;
	*head = appendWithDummy(*head, sum % 10);
}

/**
* @brief 25������������ɵ������Ǹ�������ӣ������õ��������ʾ
*/
ListNode* addTwoNumbers(ListNode* head1, ListNode* head2)
{
	ListNode* r1 = reverseList(head1);
	ListNode* r2 = reverseList(head2);
	ListNode* sumList = nullptr;
	int carry = 0;
	while (r1 != nullptr && r2 != nullptr)
	{
		addToList(r1->val + r2->val, carry, &sumList);
		r1 = r1->next;
		r2 = r2->next;
	}
	ListNode* rest = r2 == nullptr ? r1 : r2;
	while (rest != nullptr)
	{
		addToList(rest->val, carry, &sumList);
		rest = rest->next;
	}
	if (carry)
	{
		addToList(0, carry, &sumList);
	}
	return reverseList(sumList);
}

ListNode* addReverse(ListNode* head1, ListNode* head2)
{
	ListNode* dummy = new ListNode(0);
	ListNode* sumNode = dummy;
	ListNode* node1 = head1, * node2 = head2;
	int carry = 0;
	while (node1 != nullptr || node2 != nullptr)
	{
		int sum = (node1 == nullptr ? 0 : node1->val) + (node2 == nullptr ? 0 : node2->val) + carry;
		ListNode* newNode = new ListNode(sum % 10);
		sumNode->next = newNode;
		sumNode = sumNode->next;
		carry = sum / 10;
		node1 = node1 == nullptr ? nullptr : node1->next;
		node2 = node2 == nullptr ? nullptr : node2->next;
	}
	if (carry)
	{
		sumNode->next = new ListNode(carry);
	}
	return dummy->next;
}

/**
* @brief 25������leetcode���ڴ�ռ�õ�
*/
ListNode* addTwoNumbersBetter(ListNode* head1, ListNode* head2)
{
	ListNode* r1 = reverseList(head1);
	ListNode* r2 = reverseList(head2);
	ListNode* sumList = addReverse(r1, r2);
	return reverseList(sumList);
}

/**
* @brief 26����������L0->Ln->L1->Ln-1->L2->Ln-2->...
*/
void reorderList(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return;
	//����ָ�뷨������ֳ�����
	ListNode* prev = head, * slow = head->next, * fast = slow->next;
	while (fast != nullptr && slow != nullptr)
	{
		fast = fast->next;
		prev = slow;
		slow = slow->next;
		if (fast != nullptr)
			fast = fast->next;
	}
	prev->next = nullptr;
	slow = reverseList(slow);
	ListNode* left = head, * right = head->next;
	ListNode* node = slow, * rest = slow->next;
	while (node != nullptr)
	{
		node->next = right;
		left->next = node;

		left = right;
		right = right == nullptr ? nullptr : right->next;
		node = rest;
		rest = rest == nullptr ? nullptr : rest->next;
	}
}

/**
* @brief 27����������
*/
bool isPalindrome(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return true;
	ListNode* prev = head, * slow = head->next, * fast = slow->next;
	while (fast != nullptr && slow != nullptr)
	{
		fast = fast->next;
		prev = slow;
		slow = slow->next;
		if (fast != nullptr)
		{
			fast = fast->next;
		}
	}
	prev->next = nullptr;
	ListNode* firstHalf = head, * secondHalf = slow;
	ListNode* secondHalfReverse = reverseList(secondHalf);
	while (firstHalf != nullptr && secondHalfReverse != nullptr) {
		if (firstHalf->val != secondHalfReverse->val)
			return false;
		firstHalf = firstHalf->next;
		secondHalfReverse = secondHalfReverse->next;
	}
	return true;
}

/**
* @brief 28
*/
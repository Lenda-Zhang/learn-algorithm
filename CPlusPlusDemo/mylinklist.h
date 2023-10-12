#pragma once
#include "myinclude.h"

/**
* @brief 单向链表节点
*/
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int val);
};

ListNode::ListNode(int val) : val(val), next(nullptr) { }

/**
* @brief 多级双向链表节点
*/
class Node {
public:
	int val;
	Node* prev;
	Node* next;
	Node* child;
	Node(int val) :val(val), prev(nullptr), next(nullptr), child(nullptr) {}
};

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
* @brief 在尾部添加一个节点
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
* @brief 使用哨兵节点在尾部添加一个节点
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

Node* getLast(Node* head)
{
	if (head == nullptr)
		return nullptr;
	Node* node = head;
	while (node->next != nullptr)
	{
		node = node->next;
	}
	return node;
}

/**
* 未测试
*/
Node* appendWithDummy(Node* head, int val)
{
	Node* newNode = new Node(val);
	if (head == nullptr)
	{
		head = newNode;
		return head;
	}
	Node* last = getLast(head);
	newNode->prev = last;
	last->next = newNode;
	return head;
}

/**
* @brief 删除第一个值为val的节点
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
* @brief 使用哨兵节点删除第一个值为val的节点
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
* @brief 21：删除倒数第k个节点，1≤k≤n
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
* @brief 21：删除倒数第k个节点，1≤k≤n
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
* @brief 21魔改：删除倒数第k个节点
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
* @brief 找到倒数第k个结点
*/
int FindKthFromEnd(ListNode* head, int k)
{
	ListNode* p = head->next, * q = head->next;
	int count = 0;
	while (p != nullptr)
	{
		if (count == k)
			q = q->next;
		else
			count++;
		p = p->next;
	}
	if (count == k)
	{
		cout << q->val << endl;
		return 1;
	}
	return 0;
}

/**
* @brief 删除所有节点
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
* @brief 判断链表是否包含环，并输出环中节点数
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
* @brief 22：链表中环的入口节点
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
* @brief 22：不知道环中节点数的解法
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
* @brief 23：两个链表的第一个重合节点
* @note 使用栈进行LIFO，时间复杂度O(m+n)，空间复杂度O(m+n)
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
* 声明getLast函数
*/
ListNode* getLast(ListNode* head);

/**
* @brief 23：两个链表的第一个重合节点
* @note 将两个链表改造成一个包含环的链表
*/
ListNode* getIntersectionNode2(ListNode* head1, ListNode* head2)
{
	if (head1 == nullptr || head2 == nullptr)
		return nullptr;
	// 构造环
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
* @brief 23：遍历链表，前移较长链表的指针，使链表后端对齐，逐步移动节点，找到第一个相等的栈指针，无需栈空间
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
* @brief 23：16ms，来自leetcode，没理解
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
* @brief 24：反转链表
* @note 时间复杂度O(n)，空间复杂度O(1)
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
* 递归
*/
ListNode* reverseNext(ListNode* current, ListNode* prev)
{
	if (current == nullptr)
		return prev;
	// 自写
	/*ListNode* next = current->next;
	current->next = prev;
	return reverseNext(next, current);*/

	// 推荐：
	// recursion(1,null),recursion(2,1),recursion(3,2),recursion(4,3),recursion(5,4),recursion(null,5),递推结束。
	// 回溯阶段修改节点的指向，即反转。
	ListNode* result = reverseNext(current->next, current);
	current->next = prev;
	return result;
}

/** @brief 24: 
* 时间复杂度为O(n)，每个节点访问一次。
* 空间复杂度为O(n)，递归的深度与链表长度相关。
*/
ListNode* reverseListRecursion(ListNode* head)
{
	return reverseNext(head, nullptr);
}

/**
* @brief 24：0ms，来自leetcode
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
* @brief 25：单向链表组成的两个非负整数相加，和仍用单向链表表示
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
* @brief 25：来自leetcode，内存占用低
*/
ListNode* addTwoNumbersBetter(ListNode* head1, ListNode* head2)
{
	ListNode* r1 = reverseList(head1);
	ListNode* r2 = reverseList(head2);
	ListNode* sumList = addReverse(r1, r2);
	return reverseList(sumList);
}

/**
* @brief 26：重排链表：L0->Ln->L1->Ln-1->L2->Ln-2->...
*/
void reorderList(ListNode* head)
{
	if (head == nullptr || head->next == nullptr)
		return;
	//快慢指针法把链表分成两半
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
* @brief 27：回文链表
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

void print(Node* head)
{
	Node* node = head;
	while (node != nullptr)
	{
		std::cout << node->val << " ";
		node = node->next;
	}
	std::cout << "<end>" << std::endl;
}

//打印循环链表(不带头结点)
void printCircularList(Node* head)
{
	if (head != nullptr)
	{
		Node* node = head;
		do
		{
			std::cout << node->val << " ";
			node = node->next;
		} while (node != head);
	}
	std::cout << "<end>" << std::endl;
}

/**
* @brief 28：展平多级双向链表
*/
Node* flatten(Node* head)
{
	Node* p = head;
	while (p != nullptr)
	{
		Node* pNext = p->next;
		if (p->child != nullptr)
		{
			Node* cHead = flatten(p->child);
			Node* cLast = getLast(cHead);
			cLast->next = p->next;
			cHead->prev = p;
			if (p->next != nullptr)
				p->next->prev = cLast;
			p->next = cHead;
			p->child = nullptr;
		}
		p = pNext;
	}
	return head;
}

/**
* @brief 29：插入一个值，使排序的循环链表仍然有序
*/
Node* insert(Node* head, int insertVal)
{
	Node* newNode = new Node(insertVal);
	if (head == nullptr)
	{
		head = newNode;
		head->next = head;
		return head;
	}
	Node* p = head->next, * min = head, * max = head;
	do
	{
		if (p->val >= max->val) // 找到最后一个值最大的节点
			max = p;
		p = p->next;
	} while (p != head);
	min = max->next; // 最后一个值最大的节点的下一个节点即为第一个值最小的节点
	if (insertVal <= min->val || insertVal >= max->val) // 若插入值比min小或比max大，则插入min和max之间
	{
		newNode->next = min;
		max->next = newNode;
	}
	else
	{
		// 从值最小的节点开始找，找到最后一个比invertVal小的，第一个比insertVal大的节点p，插在两者之间
		p = min;
		Node* lastLessThan = nullptr, * firstMoreThan = nullptr;
		do
		{
			if (p->val <= insertVal) // 找到最后一个比invertVal小的
				lastLessThan = p;
			p = p->next;
		} while (p != min);
		firstMoreThan = lastLessThan->next; // 最后一个比invertVal小的节点的下一个节点即为第一个比insertVal大的节点
		newNode->next = firstMoreThan;
		lastLessThan->next = newNode;
	}
	return head;
}
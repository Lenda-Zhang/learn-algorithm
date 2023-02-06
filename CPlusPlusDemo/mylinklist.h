#pragma once

/**
* @brief ��������ڵ�
*/
class ListNode
{
public:
	int val;
	ListNode* next;
	ListNode(int val);
};

ListNode::ListNode(int val) {
	this->val = val;
	this->next = nullptr;
}

void print(ListNode* head)
{
	ListNode* node = head;
	while (node != nullptr)
	{
		std::cout << node->val << " ";
		node = node->next;
	}
	std::cout<< "<end>" << std::endl;
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
	free(p);
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
	free(p);
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
	free(p);
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
	return dummy->next;
}
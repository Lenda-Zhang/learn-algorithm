// CPlusPlusDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "myinclude.h"
#include "mylinklist.h"
using namespace std;

int main()
{
	//insert
	Node* n1 = new Node(3);
	Node* n2 = new Node(3);
	Node* n3 = new Node(3);
	n1->next = n2;
	n2->next = n3;
	n3->next = n1;

	Node* head = insert(n1, 0);
	printCircularList(head);

	//flatten
	//Node* n1 = new Node(1);
	//Node* n2 = new Node(2);
	//Node* n3 = new Node(3);
	//Node* n4 = new Node(4);
	//Node* n5 = new Node(5);
	//Node* n6 = new Node(6);
	//Node* n7 = new Node(7);
	//Node* n8 = new Node(8);
	//Node* n9 = new Node(9);
	//n1->next = n2;
	//n2->prev = n1;
	//n2->next = n3;
	//n3->prev = n2;
	//n3->next = n4;
	//n4->prev = n3;

	//n5->next = n6;
	//n6->prev = n5;
	//n6->next = n7;
	//n7->prev = n6;

	//n8->next = n9;
	//n9->prev = n8;

	//n2->child = n5;
	//n6->child = n8;

	//Node* head = flatten(n1);
	//print(head);

	//reorderList
	//ListNode* head = nullptr;
	//for (size_t i = 0; i < 5; i++)
	//{
	//	head = appendWithDummy(head, i + 1);
	//}
	//print(head);
	//cout << isPalindrome(head) << endl;
	//head = deleteAll(head);
	//head = appendWithDummy(head, 1);
	//head = appendWithDummy(head, 2);
	//head = appendWithDummy(head, 3);
	////head = appendWithDummy(head, 3);
	//head = appendWithDummy(head, 2);
	//head = appendWithDummy(head, 1);
	//print(head);
	//cout << isPalindrome(head) << endl;

	////addTwoNumbers
	//ListNode* head1 = nullptr, * head2 = nullptr;
	//for (size_t i = 0; i < 3; i++)
	//{
	//	head1 = appendWithDummy(head1, i + 3);
	//}
	//print(head1);
	//for (size_t i = 0; i < 4; i++)
	//{
	//	head2 = appendWithDummy(head2, i + 6);
	//}
	//print(head2);
	//ListNode* sum = addTwoNumbersBetter(head1, head2);
	//cout << "Sum: ";
	//print(sum);
	//head1 = deleteAll(head1);
	//head2 = deleteAll(head2);

	//for (size_t i = 0; i < 3; i++)
	//{
	//	head1 = appendWithDummy(head1, i + 6);
	//}
	//head1 = reverseList(head1);
	//print(head1);
	//for (size_t i = 0; i < 3; i++)
	//{
	//	head2 = appendWithDummy(head2, i + 3);
	//}
	//head2 = reverseList(head2);
	//print(head2);
	//ListNode* sumList = addTwoNumbersBetter(head1, head2);
	//cout << "Sum: ";
	//print(sumList);


	//reverseList
	/*ListNode* head = nullptr;
	for (size_t i = 1; i <= 5; i++)
	{
		head = appendWithDummy(head, i);
	}
	print(head);
	head = reverseListBetter(head);
	print(head);*/

	////getIntersectionNode
	//ListNode* head1 = nullptr, * head2 = nullptr;
	//ListNode* node = getIntersectionNodeBetter(head1, head2);
	//cout << (node == nullptr ? -1 : node->val) << endl;

	//head1 = append(head1, 1);
	//head1 = append(head1, 2);
	//head1 = append(head1, 3);

	//node = getIntersectionNodeBetter(head1, head2);
	//cout << (node == nullptr ? -1 : node->val) << endl;

	//head2 = append(head2, 7);
	//head2 = append(head2, 8);

	//ListNode* node4 = new ListNode(4);
	//ListNode* node5 = new ListNode(5);
	//ListNode* node6 = new ListNode(6);
	//node4->next = node5;
	//node5->next = node6;

	//ListNode* last1 = getLast(head1);
	//last1->next = node4;
	//ListNode* last2 = getLast(head2);
	//last2->next = node4;

	//node = getIntersectionNodeBetter(head1, head2);
	//cout << (node == nullptr ? -1 : node->val) << endl;

	////getEntryOfRing
	//ListNode* head = nullptr;
	//ListNode* entryOfRing = getEntryOfRing2(head);
	//std::cout << (entryOfRing == nullptr ? -1 : entryOfRing->val) << std::endl;

	//head = new ListNode(1);
	//head->next = head;
	//entryOfRing = getEntryOfRing2(head);
	//std::cout << (entryOfRing == nullptr ? -1 : entryOfRing->val) << std::endl;

	//head = new ListNode(1);
	//ListNode* m = new ListNode(2);
	//m->next = head->next;
	//head->next = m;
	//ListNode* p = new ListNode(6);
	//p->next = head->next;
	//head->next = p;
	//p = new ListNode(4);
	//p->next = head->next;
	//head->next = p;
	//ListNode* q = new ListNode(3);
	//q->next = head->next;
	//head->next = q;
	//p = new ListNode(2);
	//p->next = head->next;
	//head->next = p;
	//m->next = q;
	//entryOfRing = getEntryOfRing2(head);
	//std::cout << (entryOfRing == nullptr ? -1 : entryOfRing->val) << std::endl;

	////deleteNthFromEnd and deleteAll
	//ListNode* head = nullptr;
	//for (int i = 1; i <= 10; i++)
	//{
	//	head = appendWithDummy(head, i);
	//}
	//print(head);
	//head = deleteNthFromEndInBook(head, 7);
	//print(head);
	//head = deleteAll(head);
	//print(head);
	//std::cout << "deleteAll nullptr: ";
	//head = deleteAll(head);
	//print(head);

	////Sentinel Demo
	//ListNode* head = nullptr;
	//head = append(head, 1);
	//print(head);

	//head = append(head, 2);
	//print(head);

	//head = deleteFirst(head, 1);
	//print(head);

	//head = deleteFirstWithDummy(head, 2);
	//print(head);

	//head = deleteFirstWithDummy(head, 1000);
	//print(head);

	//head = appendWithDummy(head, 3);
	//print(head);

	//head = appendWithDummy(head, 4);
	//print(head);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

// CPlusPlusDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "myinclude.h"
#include "mylinklist.h"
#include "myhashmap.h"
#include "mystack.h"
#include "myqueue.h"
#include "mytree.h"
#include "mysequencelist.h"
using namespace std;

int main()
{
	int a[] = { -1,0,9 }, b[] = { -25,-10,10,11 }, c[] = { 2,9,17,30,41 };
	cout << GetTripleMinDistance(a, 3, b, 4, c, 5) << endl;

	/*int a = 3, b = 2, c = 1;
	cout << "a=" << a << ",b=" << b << ",c=" << c << endl;
	sortThreeInts(a, b, c);
	cout << "a=" << a << ",b=" << b << ",c=" << c << endl;*/

	/*int a[] = { -5,3,2,3 };
	cout << FindMinPositiveInt(a, 4) << endl;
	int b[] = { 1,2,3 };
	cout << FindMinPositiveInt(b, 3) << endl;*/

	/*int a[] = { 0,5,5,3,5,7,5,5 };
	cout << FindMajorElement(a, 8) << endl;
	int b[] = { 0,5,5,3,5,1,5,7 };
	cout << FindMajorElement(b, 8) << endl;
	int* c = new int[0];
	cout << FindMajorElement(c, 0) << endl;*/

	/*int a[] = { 11,13,15,17,19 };
	int b[] = { 2,4,6,8,20 };
	cout << FindMedian(a, b, 5) << endl;*/

	/*int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	int arraySize = 10;
	printArray(a, arraySize);
	Converse(a, 10, 3);
	printArray(a, arraySize);*/

	//int a[MaxSize] = { 1,2,3,4,5,7,8 };
	//int arraySize = 7;
	//printArray(a, arraySize);
	////FindOrInsert(a, 6, arraySize);
	//FindOrInsert(a, 2, arraySize);
	//printArray(a, arraySize);


	//int left = 1, right = 10;
	//srand(time(0));
	//int m = (rand() % (right - left + 1)) + left;	//生成[left,right]之间的随机数
	//int n = (rand() % (right - left + 1)) + left;
	//cout << "m=" << m << ",n=" << n << endl;
	//int* a = new int[m + n];
	//for (size_t i = 0; i < m; i++)
	//{
	//	a[i] = 101 + i;
	//}
	//for (size_t i = 0; i < n; i++)
	//{
	//	a[m + i] = 1 + i;
	//}
	//Exchange(a, m, n, m + n);
	//cout << endl;

	// MySqList
	/*MySqList L;
	InitList(L);
	ListInsert(L, 1, 11);
	ListInsert(L, 1, 22);
	ListInsert(L, 1, 33);
	PrintList(L);
	cout << "33 pos: " << LocateElem(L, 33) << endl;
	int e;
	ListDelete(L, 1, e);
	cout << e << endl;
	PrintList(L);
	cout << "33 pos: " << LocateElem(L, 33) << endl;
	DestroyList(L);

	MySqListDA LDA;
	InitListDA(LDA);
	DestroyListDA(LDA);*/

	//// Build binary tree
	//TreeNode* descendant2 = new TreeNode(2);
	//TreeNode* descendant3 = new TreeNode(3);
	//TreeNode* descendant4 = new TreeNode(4);
	//TreeNode* descendant5 = new TreeNode(5);
	//TreeNode* descendant6 = new TreeNode(6);
	//TreeNode* root = new TreeNode(1, descendant2, descendant3);
	//descendant2->left = descendant4;
	//descendant2->right = descendant5;
	//descendant3->left = descendant6;

	//// test serialize and deserialize tree.
	//Codec ser, deser;
	//string serStr = ser.serialize(root);
	//cout << serStr << endl;
	//TreeNode* ans = deser.deserialize(serStr);
	//cout << ser.serialize(root) << endl;

	//serStr = "1,2,3,None,None,4,5,";
	//cout << serStr << endl;
	//root = deser.deserialize(serStr);
	//cout << ser.serialize(root) << endl;

	// Traverse
	/*MyBinaryTree tree;
	tree.preOrderTraverseRecursion(root);
	cout << endl;
	tree.preOrderTraverseIteration(root);
	cout << endl;
	tree.inOrderTraverseRecursion(root);
	cout << endl;
	tree.inOrderTraverseIteration(root);
	cout << endl;
	tree.postOrderTraverseRecursion(root);
	cout << endl;
	tree.postOrderTraverseIteration(root);
	cout << endl;
	tree.bfs(root);
	cout << endl; */

	/*string s = "";
	cout << s.empty() << endl;*/

	/*TreeNode* n2 = new TreeNode(2);
	TreeNode* n3 = new TreeNode(3);
	TreeNode* n1 = new TreeNode(1, n2, n3);
	TreeNode* n4 = new TreeNode(4);
	TreeNode* n5 = new TreeNode(5);
	n2->right = n5;
	n3->right = n4;
	Solution5 *s = new Solution5();
	vector<int> res = s->rightSideView(n1);
	for (int i = 0; i < res.size(); i++)
	{
		cout << res[i] << " ";
	}
	cout << endl;*/

	//cout << toBinary(8) << endl;

	/*输入：inputs = ["CBTInserter", "insert", "insert", "get_root"], inputs = [[[1, 2, 3, 4, 5, 6]], [7], [8], []]
		输出：[null, 3, 4, [1, 2, 3, 4, 5, 6, 7, 8]]*/
		/*TreeNode* leftCLC = new TreeNode(4);
		TreeNode* leftCRC = new TreeNode(5);
		TreeNode* rightCLC = new TreeNode(6);
		TreeNode* leftC = new TreeNode(2, leftCLC, leftCRC);
		TreeNode* rightC = new TreeNode(3, rightCLC, nullptr);
		TreeNode* root = new TreeNode(1, leftC, rightC);
		CBTInserter* obj = new CBTInserter(root);
		int param_1 = obj->insert(7);
		param_1 = obj->insert(8);
		TreeNode* param_2 = obj->get_root();
		levelOrder(obj->get_root());
		preOrder(obj->get_root());*/

		/*RecentCounter* recentCounter = new RecentCounter();
		int param_1 = recentCounter->ping(1);
		param_1 = recentCounter->ping(100);
		param_1 = recentCounter->ping(3001);
		param_1 = recentCounter->ping(3002);
		cout << param_1 << endl;*/

		//MovingAverage* obj = new MovingAverage(3);
		//double param_1 = obj->next(1); // 返回 1.0 = 1 / 1
		//cout << param_1 << endl;
		//param_1 = obj->next(10); // 返回 5.5 = (1 + 10) / 2
		//cout << param_1 << endl;
		//param_1 = obj->next(3); // 返回 4.66667 = (1 + 10 + 3) / 3
		//cout << param_1 << endl;
		//param_1 = obj->next(5);; // 返回 6.0 = (10 + 3 + 5) / 3
		//cout << param_1 << endl;

		/*vector<string> matrix{ "10100", "10111", "11111", "10010" };
		cout << maximalRectangleBetter(matrix) << endl;*/

		/*vector<int>	temperatures{ 73, 74, 75, 71, 69, 72, 76, 73 };
		vector<int> result = dailyTemperatures(temperatures);
		for (auto a : result)
		{
			cout << a << " ";
		}
		cout << endl;*/

		/*vector<int> asteroids = { 8, -8 };
		vector<int> result = asteroidCollision(asteroids);
		for (auto a : result)
		{
			cout << a << " ";
		}
		cout << endl;*/

		//stack<int> s;
		//cout << s.top() << endl; // throw exception

		////evalRPN
		//vector<string> tokens = { "4","13","5","/","+" };
		//cout << evalRPN(tokens) << endl;

		////isAlienSorted
		//vector<string> words{ "hello", "leetcode" };
		//string order = "hlabcdefgijkmnopqrstuvwxyz";
		//cout << isAlienSorted(words, order) << endl;

		////isAnagram
		//cout << isAnagram("ab", "bae") << endl;

		////LRUCache
		//LRUCache *lRUCache = new LRUCache(2);
		//lRUCache->put(2, 1); // 缓存是 {2=1}
		//lRUCache->put(2, 2); // 缓存是 {2=2}
		//cout << "key = 2, value = " << lRUCache->get(2) << endl;    // 返回 2
		//lRUCache->put(1, 1); // 缓存是 {1=1, 2=2}
		//lRUCache->put(4, 1); // 该操作会使得关键字 2 作废，缓存是 {4=1, 1=1}
		//cout << "key = 1, value = " << lRUCache->get(2) << endl;    // 返回 -1 (未找到)

		////insert
		//Node* n1 = new Node(3);
		//Node* n2 = new Node(3);
		//Node* n3 = new Node(3);
		//n1->next = n2;
		//n2->next = n3;
		//n3->next = n1;

		//Node* head = insert(n1, 0);
		//printCircularList(head);

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
		for (int i = 1; i <= 5; i++)
		{
			head = appendWithDummy(head, i);
		}
		print(head);
		head = reverseListRecursion(head);
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

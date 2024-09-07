/*
 * Leetcode #107
 *  Write a method that returns the height of a binary tree
 *  Note: DO NOT modify the binary tree.
*/

#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
	int ele;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	TreeNode() : ele{0}, left{nullptr}, right{nullptr}, parent{nullptr} {}
	TreeNode(int x) : ele{x}, left{nullptr}, right{nullptr}, parent{nullptr} {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : ele{x}, left{left}, right{right}, parent{nullptr} {}
};


int treeHeight(TreeNode *p) {
	if(p == nullptr) return 0; 
	return 1 + max(treeHeight(p->left), treeHeight(p->right));
}


// Test
int main() {
	// Test 1
	TreeNode t1(15); // leaf
	TreeNode t2(7); // leaf
	TreeNode t3(9); // leaf
	TreeNode t5(20, &t1, &t2); // internal node
	TreeNode t6(3, &t3, nullptr); // internal node
	TreeNode t7(1, &t5, &t6); // root

	std::cout << treeHeight(&t7) << std::endl; // 3

	// Test 2

	TreeNode n4(4, nullptr, nullptr); // leaf
	TreeNode n3(3, nullptr, &n4); // internal node
	TreeNode n2(2, &n3, nullptr); // internal node
	TreeNode n1(1, nullptr, &n2); // root

	std::cout << treeHeight(&n1) << std::endl; // 4
	
	// Test 3: Single Node Tree
	TreeNode s1(1); // single node
	std::cout << "Test 3: " << treeHeight(&s1) << " (Expected: 1)" << std::endl;

	// Test 4: Empty Tree
	TreeNode *e1 = nullptr;
	std::cout << "Test 4: " << treeHeight(e1) << " (Expected: 0)" << std::endl;

	// Test 5: Tree with Only Left Children
	TreeNode l4(4, nullptr, nullptr); // leaf
	TreeNode l3(3, &l4, nullptr); // internal node
	TreeNode l2(2, &l3, nullptr); // internal node
	TreeNode l1(1, &l2, nullptr); // root
	std::cout << "Test 5: " << treeHeight(&l1) << " (Expected: 4)" << std::endl;
	
	return 0;
}

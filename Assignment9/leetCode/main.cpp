#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = helperFunc(nums, 0, nums.size() - 1);
        return root;
    }
    
    TreeNode* helperFunc(vector<int>& nums, int begin, int end) {
        if(begin > end){
            return nullptr;
        }
        int mid = ((end - begin) / 2) + begin;
        TreeNode* root = new TreeNode(nums[mid]);
        
        root->left = helperFunc(nums, begin, mid - 1);
        root->right = helperFunc(nums, mid + 1, end);
        
        return root;
    }
};


void printInOrder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

void testSortedArrayToBST(vector<int> nums) {
    Solution solution;
    TreeNode* result = solution.sortedArrayToBST(nums);
    printInOrder(result);
    cout << endl;
}

int main() {
    // Edge Case 1: Empty Array
    vector<int> test1 = {};
    cout << "Test 1 (Empty Array): ";
    testSortedArrayToBST(test1);

    // Edge Case 2: Single Element
    vector<int> test2 = {1};
    cout << "Test 2 (Single Element): ";
    testSortedArrayToBST(test2);

    // Edge Case 3: Array with All Identical Elements
    vector<int> test3 = {2, 2, 2, 2, 2};
    cout << "Test 3 (All Identical Elements): ";
    testSortedArrayToBST(test3);

    // Edge Case 4: Array with Negative and Positive Integers
    vector<int> test5 = {-10, -3, 0, 5, 9};
    cout << "Test 4 (Negative and Positive Integers): ";
    testSortedArrayToBST(test5);

    // Edge Case 5: Array with a Mixture of Negative, Zero, and Positive Integers
    vector<int> test6 = {-15, -10, -5, 0, 5, 10, 15};
    cout << "Test 5 (Mixed Integers): ";
    testSortedArrayToBST(test6);

    return 0;
}
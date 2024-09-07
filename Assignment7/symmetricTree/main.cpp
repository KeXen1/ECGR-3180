#include <iostream>

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
    bool isMirror(TreeNode* left, TreeNode* right){
        if(left == nullptr && right == nullptr) return true;
        if((left == nullptr && right != nullptr) || (left != nullptr && right == nullptr)) return false;
        if(left->val != right->val) return false;
        
        return isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }
    
    bool isSymmetric(TreeNode* root) {
        return isMirror(root->left, root->right);
    }
};

int main(){
    Solution solution;

    // Edge Case 1: Single Node Tree
    TreeNode* singleNode = new TreeNode(1);
    std::cout << "Single Node Tree: " << (solution.isSymmetric(singleNode) ? "Symmetric" : "Not Symmetric") << std::endl;

    // Edge Case 2: Deeply Nested Asymmetric Tree
    TreeNode* deepNestedTree = new TreeNode(1);
    deepNestedTree->left = new TreeNode(2);
    deepNestedTree->right = new TreeNode(2);
    deepNestedTree->left->left = new TreeNode(3);
    deepNestedTree->left->right = new TreeNode(4);
    deepNestedTree->right->left = new TreeNode(4);
    deepNestedTree->right->right = new TreeNode(3);
    deepNestedTree->left->left->left = new TreeNode(5);  // Extra node to make it asymmetric

    std::cout << "Deeply Nested Asymmetric Tree: " << (solution.isSymmetric(deepNestedTree) ? "Symmetric" : "Not Symmetric") << std::endl;

    return 0;
}
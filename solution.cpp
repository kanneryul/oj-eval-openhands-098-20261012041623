#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* root;
    int count;
    int result;
    
    // Insert a value into BST
    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }
        
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else if (val > node->val) {
            node->right = insert(node->right, val);
        }
        
        return node;
    }
    
    // Reverse inorder traversal to find kth largest
    void reverseInorder(TreeNode* node, int k) {
        if (node == nullptr || count >= k) {
            return;
        }
        
        // Visit right subtree first (larger values)
        reverseInorder(node->right, k);
        
        // Process current node
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        
        // Visit left subtree (smaller values)
        reverseInorder(node->left, k);
    }
    
public:
    Solution() : root(nullptr), count(0), result(0) {}
    
    // Build BST from level order array
    void buildBST(const vector<int>& values) {
        for (int val : values) {
            root = insert(root, val);
        }
    }
    
    // Find kth largest element
    int findKthLargest(int k) {
        count = 0;
        result = 0;
        reverseInorder(root, k);
        return result;
    }
    
    // Clean up memory
    void cleanup(TreeNode* node) {
        if (node == nullptr) return;
        cleanup(node->left);
        cleanup(node->right);
        delete node;
    }
    
    ~Solution() {
        cleanup(root);
    }
};

int main() {
    vector<int> values(7);
    int k;
    
    // Read 7 BST values
    for (int i = 0; i < 7; i++) {
        cin >> values[i];
    }
    
    // Read k (cnt)
    cin >> k;
    
    Solution sol;
    sol.buildBST(values);
    
    int result = sol.findKthLargest(k);
    cout << result << endl;
    
    return 0;
}
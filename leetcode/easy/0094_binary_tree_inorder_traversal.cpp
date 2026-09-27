/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    void _dfs(TreeNode* v, vector<int>& result) {
        if (v) {
            _dfs(v->left, result);
            result.push_back(v->val);
            _dfs(v->right, result);
        }
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        _dfs(root, result);
        return result;
    }
};

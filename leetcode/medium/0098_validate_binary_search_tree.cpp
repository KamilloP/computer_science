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
    tuple<long long,long long,bool> _dfs(TreeNode* root) {
        if (!root) {return make_tuple(LLONG_MAX, LLONG_MIN, true);}
        if (root->left && root->left->val >= root->val) {return make_tuple(0,0,false);}
        if (root->right && root->right->val <= root->val) {return make_tuple(0,0,false);}
        auto [ll,lr,lb] = _dfs(root->left);
        if (!lb || lr >= (long long)root->val) {return make_tuple(0,0,false);}
        auto [rl, rr, rb] = _dfs(root->right);
        if (!rb || rl <= (long long)root->val) {return make_tuple(0,0,false);}
        return make_tuple(min(ll, (long long)root->val), max(rr, (long long)root->val), true);

    }
public:
    bool isValidBST(TreeNode* root) {
        auto [l,r,b] = _dfs(root);
        return b;
    }
};

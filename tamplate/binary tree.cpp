#include <iostream>
using namespace std;
#include<string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

// 二叉树结构
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// N叉树结构
class Node
{
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

void Reverse(vector<int>& result)
{
    for (int i = 0, j = result.size() - 1; i < j; ++i, --j)
    {
        int temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
}

// 前序递归遍历
void traversal(TreeNode* root, vector<int>& result)
{
    if (root == nullptr) return;
    result.push_back(root->val);
    traversal(root->left, result);
    traversal(root->right, result);
}
vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> result;
    traversal(root, result);
    return result;
}

// 后序递归遍历
void traversal(TreeNode* root, vector<int>& result)
{
    if (root == nullptr) return;
    traversal(root->left, result);
    traversal(root->right, result);
    result.push_back(root->val);
}
vector<int> postorderTraversal(TreeNode* root)
{
    vector<int> result;
    traversal(root, result);
    return result;
}

// 中序递归遍历
void traversal(TreeNode* root, vector<int>& result)
{
    if (root == nullptr) return;
    traversal(root->left, result);
    result.push_back(root->val);
    traversal(root->right, result);
}
vector<int> inorderTraversal(TreeNode* root)
{
    vector<int> result;
    traversal(root, result);
    return result;
}

// 前序迭代遍历（一）
vector<int> preorderTraversal(TreeNode* root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode*> st_TreeNode;
    st_TreeNode.push(root);
    while (st_TreeNode.empty() == false)
    {
        TreeNode* node = st_TreeNode.top();
        st_TreeNode.pop();
        result.push_back(node->val);
        if (node->right != nullptr)
            st_TreeNode.push(node->right);
        if (node->left != nullptr)
            st_TreeNode.push(node->left);
    }
    return result;
}

// 前序迭代遍历（二）
vector<int> preorderTraversal(TreeNode* root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode*> st_TreeNode;
    TreeNode* node = root;
    while (node != nullptr || !st_TreeNode.empty())
    {
        while (node != nullptr)
        {
            st_TreeNode.push(node);
            result.push_back(node->val);
            node = node->left;
        }
        if (!st_TreeNode.empty())
        {
            node = st_TreeNode.top();
            st_TreeNode.pop();
            node = node->right;
        }
    }
    return result;
}

// 后序迭代遍历（一）
vector<int> postorderTraversal(TreeNode* root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode*> st_TreeNode;
    st_TreeNode.push(root);
    while (!st_TreeNode.empty())
    {
        TreeNode* node = st_TreeNode.top();
        st_TreeNode.pop();
        result.push_back(node->val);
        if (node->left != nullptr)
            st_TreeNode.push(node->left);
        if (node->right != nullptr)
            st_TreeNode.push(node->right);
    }
    Reverse(result);
    return result;
}

// 后序迭代遍历（二）
vector<int> postorderTraversal(TreeNode* root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode*> st_TreeNode;
    TreeNode* node = root;
    while (node != nullptr || !st_TreeNode.empty())
    {
        while (node != nullptr)
        {
            st_TreeNode.push(node);
            result.push_back(node->val);
            node = node->right;
        }
        if (!st_TreeNode.empty())
        {
            node = st_TreeNode.top();
            st_TreeNode.pop();
            node = node->left;
        }
    }
    Reverse(result);
    return result;
}

// 中序迭代遍历（二）
vector<int> inorderTraversal(TreeNode* root)
{
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode*> st_TreeNode;
    TreeNode* node = root;
    while (node != nullptr || !st_TreeNode.empty())
    {
        while (node != nullptr)
        {
            st_TreeNode.push(node);
            node = node->left;
        }
        if (!st_TreeNode.empty())
        {
            node = st_TreeNode.top();
            st_TreeNode.pop();
            result.push_back(node->val);
            node = node->right;
        }
    }
    return result;
}

// 层序遍历（BFS）
vector<vector<int>> levelOrder(TreeNode* root)
{
    vector<vector<int>> result;
    if (root == nullptr)
        return result;
    queue<TreeNode*> que_TreeNode;
    que_TreeNode.push(root);
    while (!que_TreeNode.empty())
    {
        int size = que_TreeNode.size();
        vector<int> temp;
        for (int i = 0; i != size; ++i)
        {
            TreeNode* node = que_TreeNode.front();
            que_TreeNode.pop();
            temp.push_back(node->val);
            if (node->left != nullptr)
                que_TreeNode.push(node->left);
            if (node->right != nullptr)
                que_TreeNode.push(node->right);
        }
        result.push_back(temp);
    }
    return result;
}
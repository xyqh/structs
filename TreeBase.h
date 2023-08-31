#include<vector>
#include<stack>
#include<queue>

template<typename T>
struct TreeNode{
    T val;
    int bf = 0; // balance factor, rightHeight - leftHeight
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode():val(), left(nullptr), right(nullptr), parent(nullptr){};
    TreeNode(T _val):val(_val), left(nullptr), right(nullptr), parent(nullptr){};
    TreeNode(T _val, TreeNode* _left, TreeNode* _right):val(_val), left(_left), right(_right), parent(nullptr){};
};

/**
 * 中序遍历
*/
template<typename T>
std::vector<TreeNode<T>*> inorderTraversal(TreeNode<T>* root){
    std::vector<TreeNode<T>*> ans;
    std::stack<TreeNode<T>*> stk;
    stk.push(root);
    while(root->left){
        stk.push(root->left);
        root = root->left;
    }

    while(!stk.empty()){
        TreeNode<T>* node = stk.top();
        ans.push_back(node);
        stk.pop();

        if(node->right){
            stk.push(node->right);
            node = node->right;
            while(node->left){
                stk.push(node->left);
                node = node->left;
            }
        }
    }

    return ans;
}

/**
 * 层序遍历，空指针也加进去，最后一层全是空的时候就不要打印了
*/
template<typename T>
std::vector<std::vector<TreeNode<T>*>> levelTraversal(TreeNode<T>* root){
    if(root == nullptr) return {};

    bool hasPointer = true;
    std::vector<std::vector<TreeNode<T>*>> ans;
    std::queue<TreeNode<T>*> que;
    que.push(root);

    while(!que.empty() && hasPointer){
        hasPointer = false;
        std::vector<TreeNode<T>*> level;
        int levelNum = que.size();
        for(int i = 0; i < levelNum; ++i){
            TreeNode<T>* node = que.front();
            level.push_back(node);
            que.pop();

            if(node){
                que.push(node->left);
                que.push(node->right);
                hasPointer = hasPointer || node->left || node->right;
            }
        }
        ans.push_back(level);
    }

    return ans;
}

/**
 * 计算树的高度/深度
*/
template<typename T>
int getHeight(TreeNode<T> *root){
    if(root == nullptr) return 0;
    return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}
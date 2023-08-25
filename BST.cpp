#include<vector>
#include<stack>
#include<iostream>

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
std::vector<TreeNode<T>*> InorderTraversal(TreeNode<T>* root){
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
 * 中序遍历的后继节点
*/
template<typename T>
TreeNode<T> *findProcessNodeInInorder(TreeNode<T>* root, TreeNode<T>* node){

}

template<typename T>
class BST{
    using TreeNode = TreeNode<T>;
public:
    /**
     * 怎么插入数据？
     * 不断找相应位置直至其子节点为空
    */
    TreeNode *Insert(T val){
        TreeNode* node = dummyNode->left;
        TreeNode *ret = nullptr;
        while(node){
            if(node->val > val){
                if(node->left){
                    node = node->left;
                }else{
                    ret = new TreeNode(val);
                    node->left = ret;
                    setParentNode(ret, node);
                    break;
                }
            }else if(node->val < val){
                if(node->right){
                    node = node->right;
                }else{
                    ret = new TreeNode(val);
                    node->right = ret;
                    setParentNode(ret, node);
                    break;
                }
            }else{
                return nullptr;
            }
        }

        if(dummyNode->left == nullptr){
            ret = new TreeNode(val);
            dummyNode->left = ret;
            setParentNode(ret, dummyNode);
        }
        return ret;
    }

    bool Remove(T val){
        TreeNode* node = dummyNode;
        while(node->left or node->right){
            if(node->left && node->left->val == val){
                TreeNode *deleteNode = node->left;
                TreeNode *successor = getSuccessorNode(deleteNode);
                if(successor == nullptr){
                    // 如果子节点没有后继节点，那后继节点就是父节点，同时也说明没有右子节点
                    node->left = deleteNode->left;
                    setParentNode(node->left, node);
                }else{
                    // 子节点有后继节点，使后继节点继承当前位置
                    successor->left = deleteNode->left;
                    setParentNode(successor->left, successor);
                    // 考虑后继节点有右节点的情况，右节点需要作为被删除节点的右节点的左节点。（被删除节点必有右节点，否则不会有后继节点）
                    // 但是当后继节点为右节点时，由于getSuccessorNode接口已经断掉了联系，所以deleteNode->right已经为nullptr
                    if(deleteNode->right){
                        deleteNode->right->left = successor->right;
                        setParentNode(successor->right, deleteNode->right);
                    }
                    successor->right = deleteNode->right;
                    setParentNode(successor->right, successor);
                    node->left = successor;
                    setParentNode(node->left, node);
                }

                delete deleteNode;
                return true;
            }

            if(node->right && node->right->val == val){
                TreeNode *deleteNode = node->right;
                // 找左节点的最右节点 或者 右节点的最左节点
                TreeNode *successor = getSuccessorNode(deleteNode);
                if(nullptr == successor){
                    // 如果没有后继节点，说明没有左子节点，同时又是父节点的右子节点，直接把该节点的左节点过继到父节点的右节点上
                    node->right = deleteNode->left;
                    setParentNode(node->right, node);
                }else{
                    // 子节点有后继节点，使后继节点继承当前位置
                    // 后继节点必没有左节点，可以直接替换
                    successor->left = deleteNode->left;
                    setParentNode(successor->left, successor);
                    // 考虑后继节点有右节点的情况，右节点需要作为被删除节点的右节点的左节点。（被删除节点必有右节点，否则不会有后继节点）
                    // 但是当后继节点为右节点时，由于getSuccessorNode接口已经断掉了联系，所以deleteNode->right已经为nullptr
                    if(deleteNode->right){
                        deleteNode->right->left = successor->right;
                        setParentNode(successor->right, deleteNode->right);
                    }
                    successor->right = deleteNode->right;
                    setParentNode(successor->right, successor);
                    node->right = successor;
                    setParentNode(node->right, node);
                }

                delete deleteNode;
                return true;
            }

            // 没有任何一个相等，且同时有两个子节点
            if(node->left && node->right){
                if(node->val > val){
                    node = node->left;
                }else{
                    node = node->right;
                }
                continue;
            }

            // 只有一个子节点
            node = node->left == nullptr ? node->right : node->left;
        }

        return false;
    }

    // 找到子节点中的后继节点并中断，若后继节点不为子节点则在外层处理
    TreeNode *getSuccessorNode(TreeNode *node){
        TreeNode *parent = node;
        node = node->right;
        if(node && node->left){
            while(node && node->left){
                parent = node;
                node = node->left;
            }
            parent->left = nullptr;
        }else{
            parent->right = nullptr;
        }

        return node;
    }

    TreeNode* Search(int val){
        TreeNode* node = dummyNode->left;
        while(node){
            if(node->val > val){
                node = node->left;
            }else if(node->val < val){
                node = node->right;
            }else{
                return node;
            }
        }
        return nullptr;
    }

    void setParentNode(TreeNode *node, TreeNode *parent){
        if(node == nullptr) return;
        node->parent = parent;
    }
    /**
     * 以下为辅助测试接口
    */
    std::vector<TreeNode*> getSerialize(){
        return InorderTraversal<T>(dummyNode->left);
    }

    void printSerialize(){
        auto vec = getSerialize();
        for(int i = 0; i < vec.size(); ++i){
            std::cout << vec[i]->val << " ";
        }
        std::cout << std::endl;
    }
protected:
    TreeNode* dummyNode = new TreeNode();
};

// int main(){
//     std::vector<int> nums = {30,50,40,10,60,20};
//     BST<int> bst;
//     for(int num:nums){
//         bst.Insert(num);
//         bst.printSerialize();
//     }

//     std::cout << std::endl;

//     bst.Remove(30);
//     bst.printSerialize();
//     bst.Insert(0);
//     bst.printSerialize();
//     bst.Remove(60);
//     bst.printSerialize();
//     bst.Remove(40);
//     bst.printSerialize();
//     return 0;
// }
#include "TreeBase.h"
#include <iostream>

template<typename T>
class BST{
typedef TreeNode<T> TreeNode;

private:
    // 获取中序遍历数组
    std::vector<TreeNode*> getInorderTraversal();
    // 获取层序遍历数组
    std::vector<std::vector<TreeNode*>> getLevelTraversal();

public:
    // 插入
    TreeNode *Insert(T val){
        TreeNode *node = dummyNode->left;
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

    // 删除，返回被删除节点的后继节点
    TreeNode *Remove(T val){
        TreeNode *node = dummyNode;
        while(node->left or node->right){
            if(node->left && node->left->val == val){
                TreeNode *deleteNode = node->left;
                // 找后继节点
                TreeNode *successor = getSuccessorNode(deleteNode);
                if(successor == nullptr){
                    // 当不存在后继节点时，返回父节点
                    successor = node;
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
                        TreeNode *_node = deleteNode->right;
                        while(_node->left){
                            _node = _node->left;
                        }
                        _node->left = successor->right;
                        setParentNode(successor->right, deleteNode->right);
                    }
                    successor->right = deleteNode->right;
                    setParentNode(successor->right, successor);
                    node->left = successor;
                    setParentNode(node->left, node);
                }

                delete deleteNode;
                return successor;
            }

            if(node->right && node->right->val == val){
                TreeNode *deleteNode = node->right;
                // 找后继节点
                TreeNode *successor = getSuccessorNode(deleteNode);
                if(nullptr == successor){
                    // 当不存在后继节点时，返回父节点
                    successor = node;
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
                        TreeNode *_node = deleteNode->right;
                        while(_node->left){
                            _node = _node->left;
                        }
                        _node->left = successor->right;
                        setParentNode(successor->right, deleteNode->right);
                    }
                    successor->right = deleteNode->right;
                    setParentNode(successor->right, successor);
                    node->right = successor;
                    setParentNode(node->right, node);
                }

                delete deleteNode;
                return successor;
            }

            if(node == dummyNode){
                node = node->left;
                continue;
            }
            if(node->left && node->val > val){
                node = node->left;
                continue;
            }
            if(node->right && node->val < val){
                node = node->right;
                continue;
            }

            break;
        }

        return nullptr;
    }

    // 获取中序后继节点
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

    // 搜索
    TreeNode *Search(int val){
        TreeNode *node = dummyNode->left;
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

    // 设置父节点
    void setParentNode(TreeNode *node, TreeNode *parent){
        if(node == nullptr) return;
        node->parent = parent;
    }

    // 打印中序遍历
    void printInorderTraversal(){
        auto nodes = inorderTraversal<T>(dummyNode->left);
        for(TreeNode *node:nodes){
            std::cout << node->val << " ";
        }
        std::cout << std::endl;
    }

    // 打印层序遍历
    void printLevelTraversal(){
        auto levels = levelTraversal<T>(dummyNode->left);
        std::cout << "LevelTraversal begin:" << std::endl;
        for(std::vector<TreeNode*> level:levels){
            for(TreeNode *node:level){
                if(node){
                    std::cout << node->val << " ";
                }else{
                    std::cout << "nullptr ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "LevelTraversal end" << std::endl << std::endl;
        std::cout << std::endl;
    }

protected:
    TreeNode* dummyNode = new TreeNode();
};

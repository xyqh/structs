#include "BST.h"
#include <iostream>

template<typename T>
class AVL : public BST<T> {
private:
    using TreeNode = TreeNode<T>;

    // 旋转只需要考虑当前节点及其直接子节点
    /**
     * a左旋
     *   b              a
     * c   a   ->     b   d
     *    e d        c e
    */
    TreeNode *RotateL(TreeNode *node){
        if(node == nullptr) return nullptr;

        TreeNode *right = node->right;
        if(right == nullptr || node == this->dummyNode) return node;

        TreeNode *parent = node->parent;
        bool isLeft = false;
        if(parent->left == node){
            isLeft = true;
        }

        node->right = right->left;
        this->setParentNode(node->right, node);
        right->left = node;
        this->setParentNode(right->left, right);
        if(isLeft){
            parent->left = right;
        }else{
            parent->right = right;
        }
        this->setParentNode(right, parent);
        return right;
    }

    /**
     * 右旋
     *    a         b
     *  b   d  -> c   a
     * c e           e d
    */
    TreeNode *RotateR(TreeNode *node){
        if(node == nullptr) return nullptr;

        TreeNode *left = node->left;
        if(left == nullptr || node == this->dummyNode) return node;
        
        TreeNode *parent = node->parent;
        bool isLeft = false;
        if(parent->left == node){
            isLeft = true;
        }

        node->left = left->right;
        this->setParentNode(node->left, node);
        left->right = node;
        this->setParentNode(left->right, left);
        if(isLeft){
            parent->left = left;
        }else{
            parent->right = left;
        }
        this->setParentNode(left, parent);
        return left;
    }

    // 左旋->右旋
    TreeNode *RotateLR(TreeNode *node){
        return RotateR(RotateL(node)->parent);
    }

    // 右旋->左旋
    TreeNode *RotateRL(TreeNode *node){
        return RotateL(RotateR(node)->parent);
    }

    void rebalanceNodeInsert(TreeNode *node){
        if(node == nullptr) return;

        TreeNode *parent = node->parent;

        // 更新bf
        while(parent != this->dummyNode){
            if(parent->right == node){
                ++parent->bf;
            }else{
                --parent->bf;
            }

            if(parent->bf == 1 || parent->bf == -1){
                parent = parent->parent;
                node = node->parent;
            }else if(parent->bf == 0){
                break;
            }else if(parent->bf == 2 || parent->bf == -2){
                TreeNode *newNode = nullptr;
                // 需要旋转保持平衡
                if(parent->bf == 2 && node->bf == 1){
                    // 右右
                    newNode = RotateL(parent);
                }else if(parent->bf == -2 && node->bf == -1){
                    // 左左
                    newNode = RotateR(parent);
                }else if(parent->bf == 2 && node->bf == -1){
                    // 右左
                    newNode = RotateRL(node);
                }else if(parent->bf == -2 && node->bf == 1){
                    // 左右
                    newNode = RotateLR(node);
                }
                // 不想算了，直接全刷一遍吧
                refreshBalanceFactor(newNode);

                break;
            }else{
                break;
            }
        }
    }

    // todo
    bool rebalanceNodeRemove(TreeNode *node){
        if(node == nullptr) return false;
        refreshOneNodeFactor(node);
        if(node->bf == 2){
            // 右边深度大，看右边的情况
            TreeNode *child = node->right;
            refreshOneNodeFactor(child);
            if(child->bf == -1){
                RotateRL(child);
            }else{
                RotateL(node);
            }
            return true;
        }else if(node->bf == -2){
            // 左边深度大，看左边的情况
            TreeNode *child = node->left;
            refreshOneNodeFactor(child);
            if(child->bf == 1){
                RotateLR(child);
            }else{
                RotateR(node);
            }
            return true;
        }else{
            // 不知道哪边不对劲，继续往下找
            if(rebalanceNodeRemove(node->left)){
                return true;
            }
            if(rebalanceNodeRemove(node->right)){
                return true;
            }
            return false;
        }
    }

    void refreshOneNodeFactor(TreeNode *node){
        if(node == nullptr) return;

        int lHeight = getHeight(node->left);
        int rHeight = getHeight(node->right);
        node->bf = rHeight - lHeight;
    }

    void refreshBalanceFactor(TreeNode *node){
        if(node == nullptr) return;
        refreshOneNodeFactor(node);
        refreshBalanceFactor(node->left);
        refreshBalanceFactor(node->right);
    }

public:
    TreeNode *Insert(T val){
        TreeNode *node = BST<T>::Insert(val);
        rebalanceNodeInsert(node);
        return node;
    }

    TreeNode *Remove(T val){
        TreeNode *node = BST<T>::Remove(val);
        // Remove返回了被删除节点原先的后继节点，直接对后继节点做平衡操作，如果没有后继节点，那就是原先的父节点
        rebalanceNodeRemove(node);
        return node;
    }
};
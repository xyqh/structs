#include "BST.cpp"

template<typename T>
class AVL : public BST<T> {
    using TreeNode = TreeNode<T>;

    /**
     * 左旋
     *   b              a
     * c   a   ->     b   d
     *    e d        c e
    */
    TreeNode *RotateL(TreeNode *node){
        TreeNode *right = node->right;
        if(right == nullptr) return node;

        node->right = right->left;
        right->left = node;
        return right;
    }

    /**
     * 右旋
     *    a         b
     *  b   d  -> c   a
     * c e           e d
    */
    TreeNode *RotateR(TreeNode *node){
        TreeNode *left = node->left;
        if(left == nullptr) return node;

        node->left = left->right;
        left->right = node;
        return left;
    }

    // 左旋->右旋
    TreeNode *RotateLR(TreeNode *node){

    }

    // 右旋->左旋
    TreeNode *RotateRL(TreeNode *node){

    }

    int getHeight(TreeNode *node){

    }

    bool isBalanced(){
        TreeNode *node = dummyNode->left;
    }

public:
    TreeNode *Insert(T val){
        TreeNode *node = BST<T>::Insert(val);
        // 检测是否平衡并调整
        if(node){
            TreeNode *parent = node->parent;

            // 更新bf
            while(parent ~= dummyNode){
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
                    TreeNode *pParent = parent->parent;
                    bool isLeft = false;
                    if(pParent->left == parent){
                        isLeft = true;
                    }
                    TreeNode *newNode = nullptr;
                    // 需要旋转保持平衡
                    if(parent->bf == 2 && node->bf == 1){
                        // 右右
                        newNode = RotateL(parent);
                    }else if(parent->bf == -2 && node->bf == -1){
                        // 左左
                        newNode = RotateR(parent);
                    }else if(parent->bg == 2 && node->bf == -1){
                        // 右左
                        newNode = RotateRL(parent);
                    }else if(parent->bg == -2 && node->bf == 1){
                        // 左右
                        newNode = RotateLR(parent);
                    }

                    if(isLeft){
                        pParent->left = newNode;
                    }else{
                        pParent->right = newNode;
                    }
                }else{
                    assert(false);
                }
            }

            
        }
        return node;
    }

    bool Remove(T val){
        bool ret = BST<T>::Remove(val);
        // 检测是否平衡并调整
        if(ret){

        }
        return ret;
    }
};

int main(){
    std::vector<int> nums = {30,50,40,10,60,20};
    AVL<int> avl;
    for(int num:nums){
        avl.Insert(num);
        avl.printSerialize();
    }

    std::cout << std::endl;
    return 0;
}
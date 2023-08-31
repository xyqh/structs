#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

template <typename T>
struct bst_node_t {
    T val;
    bst_node_t* left;
    bst_node_t* right;

    bst_node_t(const T& v)
        : val(v)
        , left(NULL)
        , right(NULL)
    {
    }

    void add(const T& v)
    {
        if (v < val) {
            if (NULL == left) {
                left = new bst_node_t(v);
            } else {
                left->add(v);
            }
        } else if (val < v) {
            if (NULL == right) {
                right = new bst_node_t(v);
            } else {
                right->add(v);
            }
        } else {
            // equal
            return;
        }
    }

    /// @return true表示子节点free了， 需要在父节点将其置空
    bool remove(const T& v)
    {
        if (v == val) {
            if (left == right) {
                // no child
                free(this);
                return true;
            }

            // 有右子， 则取右子的最左子
            if (NULL != right) {
                int leftest_val = right->get_leftest()->val;
                // 删除右子的最左子
                if (remove(leftest_val)) {
                    right = NULL;
                }
                val = leftest_val; // 更新当前值
                return false;
            }

            // 只有左子， 则取左子的最右子
            int rightest_val = left->get_rightest()->val;
            if (remove(rightest_val)) {
                left = NULL;
            }
            val = rightest_val;
            return false;
        }

        if (v < val) {
            if (NULL != left) {
                if (left->remove(v)) {
                    left = NULL;
                }
            }
        } else {
            if (NULL != right) {
                if (right->remove(v)) {
                    right = NULL;
                }
            }
        }
        return false;
    }

    /// @brief 获取最左子节点， 如果没有左子， 则返回自己
    bst_node_t<T>* get_leftest()
    {
        if (NULL != left) {
            return left->get_leftest();
        }
        return this;
    }

    bst_node_t<T>* get_rightest()
    {
        if (NULL != right) {
            return right->get_rightest();
        }
        return this;
    }

    bst_node_t<T>* search(const T& v)
    {
        if (v == val) {
            return this;
        }
        if (v < val) {
            if (NULL == left) {
                return NULL;
            }
            return left->search(v);
        }

        if (NULL == right) {
            return NULL;
        }
        return right->search(v);
    }
};

template <typename T>
struct bst_t {
    bst_node_t<T>* root = NULL;

    bst_node_t<T>* search(const T& v)
    {
        if (NULL != root) {
            return root->search(v);
        }
        return NULL;
    }

    void add(const T& v)
    {
        if (NULL == root) {
            root = new bst_node_t<T>(v);
            return;
        } else {
            root->add(v);
        }
    }

    void remove(const T& v)
    {
        if (NULL == root) {
            return;
        }

        if (root->remove(v)) {
            root = NULL;
        }
    }
};

int main()
{
    std::vector<int> nums = {5,3,7,2,4,6,8,1};
    // for (int i = 0; i < 10; ++i) {
    //     nums.push_back(rand() % 100);
    // }

    bst_t<int> tree;
    for (int i = 0; i < 10; ++i) {
        tree.add(nums[i]);
        // std::cout << " " << nums[i];
    }

    // std::cout << std::endl;
    tree.remove(4);
    // bst_node_t<int>* a = tree.search(78);
    // if (NULL != a) {
    //     std::cout << " a: " << a->val << std::endl;
    // }

    return 0;
}
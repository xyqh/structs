#include <iostream>
#include "BST.h"

int main(){
    // std::vector<int> nums = {5,3,7,2,4,6,8,1};
    // std::vector<int> nums = {3,2,5,1,4,7,6,8};
    std::vector<int> nums = {60,20,10,30,24,22,32,34};
    BST<int> bst;
    for(int num:nums){
        bst.Insert(num);
        // bst.printInorderTraversal();
    }

    bst.printLevelTraversal();

    bst.Remove(20);
    bst.printLevelTraversal();
    return 0;
}
#include <vector>
#include "AVL.h"

int main(){
    // std::vector<int> nums = {5,3,2,1,4,8,6,7};
    std::vector<int> nums = {2,4,3,1,5,6,7,8};
    AVL<int> avl;
    for(int num:nums){
        avl.Insert(num);
        // avl.printLevelTraversal();
    }
    
    avl.printLevelTraversal();
    avl.Remove(5);
    avl.printLevelTraversal();

    return 0;
}
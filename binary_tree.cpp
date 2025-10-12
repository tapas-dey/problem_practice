#include <vector>
#include <memory>
#include <stack>

using namespace std;

//Define the binary tree node
template <typename T> 
struct BSTNode{
    T value;
    unique_ptr<BSTNode<T>> left, right;
};
//Implement inorder traversal without recursion
vector<int> BSTInOrder(const unique_ptr<BSTNode<int>>& root){
    stack<const BSTNode<int>*> s;
    const auto* curr = root.get();
    vector<int> result;
    while(!s.empty() || curr){
        if (curr){
            s.push(curr);
            //Keep going left untill nullptr
            curr = curr->left.get();
        }
        else{
            //we're going up so process the result first
            curr = s.top();
            s.pop();
            result.push_back(curr->value);
            //Take right now
            curr = curr->right.get();
        }
    } 

}

int max_depth_recursion()
{
    
}
int main()
{
    return 0;
}
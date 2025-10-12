
//Print top view of a Binary Tree
//Ref: https://www.geeksforgeeks.org/print-nodes-top-view-binary-tree/

#include<queue>
#include<map>
#include <iostream>

using namespace std;

//Binary Tree definition
struct Node{
    Node* left;
    Node* right;
    int horizontal_dist;
    int data;
};

// function to create a new node
Node* newNode(int key)
{
    Node* node = new Node();
    node->left = node->right = NULL;
    node->data = key;
    return node;
}

void topView(Node* root){
    if (root == nullptr){
        return;
    }
    //Keeps track of the nodes to process
    queue<Node*> q;
    //Keeps track of the horizontal distance as key and node data as value
    map<int, int> dist_map;
    int horizontal_dist = 0;
    q.push(root);
    while(!q.empty()){
        root = q.front();
        horizontal_dist = root->horizontal_dist;
        if (dist_map.count(horizontal_dist) == 0){
            dist_map[horizontal_dist]= root->data;
        }
        if (root->left){
            root->left->horizontal_dist = horizontal_dist - 1;
            q.push(root->left);
        }
        if (root->right){
            root->right->horizontal_dist = horizontal_dist + 1;
            q.push(root->right);
        }
        q.pop();
    }
    //Print the top view of the binary tree
    cout << "The top view of the binary tree is : " << endl;
    for (auto i = dist_map.begin(); i != dist_map.end(); i++) {
        cout << i->second << " ";
    }
}

int main(){
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    topView(root);
    return 0;
}
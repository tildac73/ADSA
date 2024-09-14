#include "avl-tree.h"
#include <iostream>
using namespace std;

Node * AVL_TREE::insert_node(int val){
    if (root == nullptr){
        root = new Node(val);
        return root;
    }else{
        
    }

    Node * temp = root;
    while (temp != nullptr){
        if (val > temp->val){
            if (temp->right != nullptr){
                temp = temp->right;
            } 
            else{
                temp->right = new Node(val); 
                break;
            } 
            
        }else if (val < temp->val){
            if (temp->left != nullptr){
                temp = temp->left;
            } 
            else{
                temp->left = new Node(val); 
                break;
            } 
        }else{
            break;
        }

    }

    return root;

}


Node* AVL_TREE::delete_node(Node* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }

    if (val < root->val) {
        root->left = delete_node(root->left, val);
    } else if (val > root->val) {
        root->right = delete_node(root->right, val);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;  
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;  
        }

        Node* temp = find_min(root->right);
        root->val = temp->val; 
        root->right = delete_node(root->right, temp->val);  
    }

    return root;
}

Node* AVL_TREE::find_min(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}


void AVL_TREE::pre(Node * root){
    if (root == nullptr){
        cout << "EMPTY" << endl;
        return;
    }
    Node * temp = root;
    cout << temp->val << " ";
    pre(temp->left);
    pre(temp->right);
}

void AVL_TREE::post(Node * root){
    if (root == nullptr){
        cout << "EMPTY" << endl;
        return;
    }
    Node * temp = root;
    
    pre(temp->left);
    pre(temp->right);

    cout << temp->val << " ";
}

void AVL_TREE::in(Node * root){
    if (root == nullptr){
        cout << "EMPTY" << endl;
        return;
    }
    Node * temp = root;
    
    pre(temp->left);
    cout << temp->val << " ";
    pre(temp->right);
}
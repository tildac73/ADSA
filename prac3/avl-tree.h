#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

#include "node.h"

class AVL_TREE {
    friend class Node;
    private:
        Node * root;
    public:
        Node * get_root(){
            return root;
        }
        void set_root(Node * root){
            this->root = root;
        }
        AVL_TREE(){root = nullptr;};
        Node * insert_node(int val);
        Node * delete_node(Node* root, int val);
        Node* find_min(Node* root);
        void pre(Node * root);
        void post(Node * root);
        void in(Node * root);
};

#endif
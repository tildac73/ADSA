#ifndef NODE_H
#define NODE_H

class Node {
    private:
        Node* left;
        Node* right;
        int val;
    public:
        Node(int value);
        friend class AVL_TREE;
};

#endif
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Node {
    private:
        int val; 
        Node * left; 
        Node * right; 
        int height; 
    public:
        Node(int k) { 
            val = k; 
            left = nullptr; 
            right = nullptr; 
            height = 1; 
        }
        friend class AVL_TREE;
};


class AVL_TREE {
    friend class Node;
    private:
        Node * root;
    public:
        AVL_TREE(){root = nullptr;};
        Node * get_root(){
            return root;
        }
        void set_root(Node * root){
            this->root = root;
        }
        int height(Node * node) { 
            if (node == nullptr) 
                return 0; 
            return node->height; 
        }
        
        Node * rightRotate(Node * b) { 
            Node * a = b->left; 
            Node * temp = a->right; 
            a->right = b; 
            b->left = temp; 
            b->height = max(height(b->left), height(b->right))+1; 
            a->height = max(height(a->left), height(a->right))+1; 
            return a; 
        }

        Node * leftRotate(Node * a) { 
            Node * b = a->right; 
            Node * temp = b->left; 
            b->left = a; 
            a->right = temp; 
            a->height = max(height(a->left), height(a->right))+1; 
            b->height = max(height(b->left), height(b->right))+1; 
            return b; 
        }
                
        int getBalance(Node * N) { 
            if (N == nullptr) 
                return 0; 
            return height(N->left) - height(N->right); 
        }

        Node * insert_node(Node * root, int val){
            if (root == nullptr){
                root = new Node(val);
                return root;
            }

            if (val < root->val){
                root->left = insert_node(root->left, val);
            } else if (val > root->val){
                root->right = insert_node(root->right, val);
            } else {
                return root; 
            }

            root->height = 1 + max(height(root->left), height(root->right)); 
            int balance = height(root->left) - height(root->right);

            // LL
            if (balance > 1 && val < root->left->val)
                return rightRotate(root);

            // RR
            if (balance < -1 && val > root->right->val)
                return leftRotate(root);

            // LR
            if (balance > 1 && val > root->left->val) {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            // RL
            if (balance < -1 && val < root->right->val) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
            return root; 

        };

        Node * delete_node(Node* root, int val){
            if (root == nullptr) {
                return nullptr;
            }

            if (val < root->val) {
                root->left = delete_node(root->left, val);
            } else if (val > root->val) {
                root->right = delete_node(root->right, val);
            } else {
                Node * temp = nullptr;

                if ((root->left == nullptr) || (root->right == nullptr)){
                    if (root->left == nullptr){
                        temp = root->right;
                    }else {
                        temp = root->left;
                    }

                    if (temp == nullptr) {
                        temp = root;
                        root = nullptr;
                    } else
                        * root = * temp;
                    delete temp;
                } else {
                    temp = root->left;
                    while (temp->right != nullptr){
                        temp = temp->right;
                    }
                    root->val = temp->val;
                    root->left = delete_node(root->left, temp->val); 
                }
            }

            if (root == nullptr){
                return root;
            }

            root->height = 1 + max(height(root->left), height(root->right)); 
            int balance = height(root->left) - height(root->right);

            //LL
            if (balance > 1 && getBalance(root->left) >= 0)
                return rightRotate(root);

            //RR
            if (balance > 1 && getBalance(root->left) < 0) {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            //LR
            if (balance < -1 && getBalance(root->right) <= 0)
                return leftRotate(root);

            //RL
            if (balance < -1 && getBalance(root->right) > 0) {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;
        };


        void pre(Node * root){
            if (root == nullptr){
                return;
            }
            Node * temp = root;
            cout << temp->val << " ";
            pre(temp->left);
            pre(temp->right);
        };
        void post(Node * root){
            if (root == nullptr){
                return;
            }
            Node * temp = root;
            
            post(temp->left);
            post(temp->right);

            cout << temp->val << " ";
        };
        void in(Node * root){
            if (root == nullptr){
                return;
            }
            Node * temp = root;
            
            in(temp->left);
            cout << temp->val << " ";
            in(temp->right);
        };
};





int main() {
    AVL_TREE tree;
    string line, command;

    while (true) {
        getline(cin, line);

        if (line.empty() || line == "exit") {
            break;  
        }

        istringstream iss(line);
        
        while (iss >> command) {
            if (command[0] == 'A') {  
                int value = stoi(command.substr(1));
                tree.insert_node(tree.get_root(), value);
            } else if (command[0] == 'D') {  
                int value = stoi(command.substr(1));
                tree.set_root(tree.delete_node(tree.get_root(), value));
            } else if (command == "PRE") { 
                if (tree.get_root() == nullptr) {
                    cout << "EMPTY";
                } else {
                    tree.pre(tree.get_root());
                }
                cout << endl;  
            } else if (command == "IN") {  
                if (tree.get_root() == nullptr) {
                    cout << "EMPTY";
                } else {
                    tree.in(tree.get_root());
                }
                cout << endl;
            } else if (command == "POST") {  
                if (tree.get_root() == nullptr) {
                    cout << "EMPTY";
                } else {
                    tree.post(tree.get_root());
                }
                cout << endl;
            }
        }
    }

    return 0;
}

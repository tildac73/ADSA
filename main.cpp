// #include "avl-tree.h"
// #include <iostream>

// using namespace std;

// int main(void){
//     bool cont = true;
//     int val;
//     AVL_TREE * tree = new AVL_TREE();
    
//     while (cont){
//         cout << "enter val: " << endl;
//         cin >> val;

//         if (val == 0){
//             cont = false;
//             break;
//         } else if (val == 1){
//             tree->pre(tree->get_root());
//         }
//         tree->insert_node(val);

//     }
// }

#include "avl-tree.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    AVL_TREE tree;
    string line;
    getline(cin, line);
    istringstream iss(line);
    string command;

    while (iss >> command) {
        if (command[0] == 'A') {
            int value = stoi(command.substr(1));
            tree.insert_node(value);
        } else if (command[0] == 'D') {
            int value = stoi(command.substr(1));
            tree.delete_node(tree.get_root(),value);
        } else if (command == "PRE") {
            tree.pre(tree.get_root());
        } else if (command == "IN") {
            tree.in(tree.get_root());
        } else if (command == "POST") {
            tree.post(tree.get_root());
        }
    }
    cout << endl;
    return 0;
}
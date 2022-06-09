#include <iostream>
#include <cstring>
#include <string>


int GLOBAL_SPACE = 5;

using namespace std;

struct TreeNode {
    string value;
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *dad;
};

void instantiateTree(struct TreeNode *&root) {
    root = nullptr;
}

void insert(struct TreeNode *&node, string newString) {
    if (node == nullptr) {
        node = new TreeNode;
        node->value = newString;
        node->leftChild = nullptr;
        node->rightChild = nullptr;
        node->dad = nullptr;
        cout << "newString: " << newString << " inserted!";
    } else {
        if (newString < node->value) {
            insert(node->leftChild, newString);
            node->leftChild->dad = node;
        } else if (newString > node->value) {
            insert(node->rightChild, newString);
            node->rightChild->dad = node;
        } else {
            if (newString == node->value) {
                cout << "this word already exists in the tree!";
            } else {
                insert(node->leftChild, newString);
                node->leftChild->dad = node;
            }
        }
    }
}

void printNode(TreeNode *node) {
    string dad = (node->dad != nullptr) ? node->dad->value : "";
    string leftChild = (node->leftChild != nullptr) ? node->leftChild->value : "";
    string rightChild = (node->rightChild != nullptr) ? node->rightChild->value : "";

    cout << "[dad: " << dad << "][current: " << node->value << "][leftChild: " << leftChild << "][rightChild: " << rightChild << "]";
}

void postOrder(struct TreeNode *node, int space) {
    if (node == nullptr) {
        return;
    } else {
        space += GLOBAL_SPACE;
        postOrder(node->rightChild, space);
        cout << endl;
        for (int i = GLOBAL_SPACE; i < space; i ++) {
            cout << " ";
        }
        printNode(node);
        postOrder(node->leftChild, space);
    }
}


TreeNode* remove(TreeNode *&node, string name ){
    if(node == nullptr){
        return nullptr;
    }else{
        if(node->value == name){
                //removendo nó folha
                if(node->leftChild == nullptr && node->rightChild == nullptr){
                     delete node;
                     //imprimir uma msg aqui!!!
                     return nullptr;
                }else{
                    //remove no com filhos
                }

        }
        else{
                if(name < node->value){
                    node->leftChild = remove(node->leftChild, name);
                }
                else{
                    node->rightChild = remove(node->rightChild, name);
                }
                return node;

        }
    }
}


void menu(struct TreeNode *&root) {
    bool isFinish = false;

    while (!isFinish) {
        int option;

        cout << "\n\noptions:\n";
        cout << "[1] - insert\n";
        cout << "[2] - search\n";
        cout << "[3] - delete\n";
        cout << "[4] - postOrder\n";
        cout << "[5] - exit\n";

        cout << "\nenter with a option:\n";

        cin >> option;

        switch (option) {
            case 1:
                cout << "enter with a new value:\n";
                string newWord;
                cin >> newWord;
                insert(root, newWord);
                break;
            case 2:
                cout << "enter with a new value:\n";
                break;
            case 3:
                cout << "enter with a name to removed:\n";
                string newWord;
                cin >> newWord;
                root = remove(root, newWord);
                break;
            case 4:
                postOrder(root, GLOBAL_SPACE);
                break;
            case 5:
                isFinish = true;
                break;
            default:
                cout << "\nenter a valid option!\n";
        }
    };
}

void insertDatas(struct TreeNode *&node) {
    string datas[5] = {"João", "José", "Maria", "Pedro", "Antonio"};

    for (const string& data : datas) {
        insert(node, data);
    }
}

int main() {
    TreeNode *tree;
    instantiateTree(tree);
    insertDatas(tree);
    menu(tree);
    return 0;
}

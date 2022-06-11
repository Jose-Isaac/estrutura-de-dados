#include <iostream>
#include <string>

int GLOBAL_SPACE = 5;

using namespace std;

struct TreeNode {
    string value;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
    TreeNode *dad = nullptr;
};

void instantiateTree(struct TreeNode *&root) {
    root = nullptr;
}

void insert(struct TreeNode *&node, const string& newString) {
    if (node == nullptr) {
        node =  (TreeNode*)malloc(sizeof(TreeNode));
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

struct TreeNode* minValueNode(struct TreeNode* node)
{
    struct TreeNode* current = node;

    while (current && current->leftChild != nullptr)
        current = current->leftChild;

    return current;
}

TreeNode * deleteNode(struct TreeNode *node, const string& wordToDelete) {
    if (node == nullptr) {
        return node;
    }

    if (wordToDelete < node->value) {
        node->leftChild = deleteNode(node->leftChild, wordToDelete);
    } else if (wordToDelete > node->value) {
        node->rightChild = deleteNode(node->rightChild, wordToDelete);
    } else {
        if (node->leftChild == nullptr && node->rightChild == nullptr){
            return nullptr;
        } else if (node->leftChild == nullptr) {
            struct TreeNode* temp = node->rightChild;
            free(node);
            return temp;
        } else if (node->rightChild == nullptr) {
            struct TreeNode* temp = node->leftChild;
            free(node);
            return temp;
        }

        struct TreeNode* temp = minValueNode(node->rightChild);
        node->value = temp->value;
        node->rightChild = deleteNode(node->rightChild, temp->value);
    }
    return node;
}

void menu(struct TreeNode *root) {
    bool isFinish = false;

    while (!isFinish) {
        int option = 0;

        cout << "\n\noptions:\n";
        cout << "[1] - insert\n";
        cout << "[2] - search\n";
        cout << "[3] - delete\n";
        cout << "[4] - postOrder\n";
        cout << "[5] - exit\n";

        cout << "\nenter with a option:\n";

        cin >> option;

        switch (option) {
            case 1: {
                string newWord;
                cout << "enter with a new value:\n";
                cin >> newWord;
                insert(root, newWord);
                break;
            }
            case 2:
                break;
            case 3: {
                string word;
                cout << "enter with word to delete\n";
                cin >> word;
                deleteNode(root, word);
                break;
            }
            case 4:
                postOrder(root, GLOBAL_SPACE);
                break;
            case 5:
                isFinish = true;
                break;
            default:
                cout << "\nenter a valid option!\n";
                break;
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

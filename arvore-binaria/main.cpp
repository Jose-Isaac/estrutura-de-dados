#include <iostream>
#include <string>
#include <fstream>

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
        cout << "new name: " << newString << " inserted!\n";
    } else {
        if (newString.length() < node->value.length()) {
            insert(node->leftChild, newString);
            node->leftChild->dad = node;
        } else if (newString.length() > node->value.length()) {
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

struct TreeNode* search(struct TreeNode* node, string& name) {
    if (node == nullptr || node->value == name) return node;

    if (name.length() <= node->value.length()) {
        return search(node->leftChild, name);
    }

    return search(node->rightChild, name);

}

struct TreeNode* minValueNode(struct TreeNode* node)
{
    struct TreeNode* current = node;

    while (current && current->leftChild != nullptr)
        current = current->leftChild;

    return current;
}

TreeNode * deleteNode(struct TreeNode *node, const string& nameToDelete) {
    if (node == nullptr) {
        return node;
    }

    if ((nameToDelete.length() <= node->value.length()) && (node->value != nameToDelete)) {
        node->leftChild = deleteNode(node->leftChild, nameToDelete);
    } else if (nameToDelete.length() > node->value.length()) {
        node->rightChild = deleteNode(node->rightChild, nameToDelete);
    } else {
        if (node->leftChild == nullptr && node->rightChild == nullptr){
            free(node);
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

        if (node->value == nameToDelete) {
            struct TreeNode* temp = minValueNode(node->rightChild);
            node->value = temp->value;
            node->rightChild = deleteNode(node->rightChild, temp->value);
        }
    }
    return node;
}

void checkAndDelete(TreeNode *node, string name) {
  TreeNode* result = search(node, name);
  if (result) {
      deleteNode(node, name);
      cout << "this name: " << name << " is deleted!\n";
      postOrder(node, GLOBAL_SPACE);
  } else {
      cout << "this name: " << name << " not found in the tree\n";
  }
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
            case 2: {
                string name;
                cout << "enter with name to search:\n";
                cin >> name;
                checkAndDelete(root, name);
                break;
            }
            case 3: {
                string name;
                cout << "enter with word to delete\n";
                cin >> name;

                TreeNode* result = search(root, name);
                if (result) {
                    deleteNode(root, name);
                    cout << "this name: " << name << " is deleted!";
                    postOrder(root, GLOBAL_SPACE);
                } else {
                    cout << "this name: " << name << " not found in the tree";
                }
                break;
            }
            case 4: {
                postOrder(root, GLOBAL_SPACE);
                break;
            }
            case 5:
                isFinish = true;
                break;
            default:
                cout << "\nenter a valid option!\n";
                break;
        }
    }
}

void loadDataFromFile(char* path, TreeNode*& tree) {
    ifstream names;
    names.open(path);

    if (names.is_open()) {
        cout << "\nfile is open!\nloading datas...\n";

        string name;
        int isToInsert;

        while (!names.eof()) {
            names >> name;
            names >> isToInsert;

            if (isToInsert) {
                insert(tree, name);
            } else {
                checkAndDelete(tree, name);
            }
        }
        names.close();
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "file path not informed!\n";
        return 1;
    }

    cout << "path " << argv[1];

    TreeNode *tree;
    instantiateTree(tree);
    loadDataFromFile(argv[1], tree);
    menu(tree);
    return 0;
}

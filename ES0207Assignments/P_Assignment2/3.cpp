#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

int main() {
    int t;
    cin >> t;
    TreeNode* root = nullptr;

    while (t--) {
        char action;
        int stock;
        cin >> action >> stock;
        if (action == 'B') {
            if (!root) {
                root = new TreeNode();
                root->value = stock;
                root->left = nullptr;
                root->right = nullptr;
            } else {
                TreeNode* newNode = new TreeNode();
                newNode->value = stock;
                newNode->left = nullptr;
                newNode->right = nullptr;

                TreeNode* current = root;
                while (current) {
                    if (stock < current->value) {
                        if (current->left) {
                            current = current->left;
                        } else {
                            current->left = newNode;
                            break;
                        }
                    } else if (stock > current->value) {
                        if (current->right) {
                            current = current->right;
                        } else {
                            current->right = newNode;
                            break;
                        }
                    } else {
                        break; // Duplicate value, do nothing.
                    }
                }
            }
        } else if (action == 'S') {
            if (!root) {
                continue; // Nothing to remove.
            }

            TreeNode* parent = nullptr;
            TreeNode* current = root;
            while (current && current->value != stock) {
                parent = current;
                if (stock < current->value) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            if (!current) {
                continue; // Value not found, do nothing.
            }

            if (!current->left) {
                if (!parent) {
                    root = current->right;
                } else if (current == parent->left) {
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }
                delete current;
            } else if (!current->right) {
                if (!parent) {
                    root = current->left;
                } else if (current == parent->left) {
                    parent->left = current->left;
                } else {
                    parent->right = current->left;
                }
                delete current;
            } else {
                TreeNode* minRight = current->right;
                TreeNode* minRightParent = current;

                while (minRight->left) {
                    minRightParent = minRight;
                    minRight = minRight->left;
                }

                current->value = minRight->value;

                if (minRight == minRightParent->left) {
                    minRightParent->left = minRight->right;
                } else {
                    minRightParent->right = minRight->right;
                }

                delete minRight;
            }
        } else if (action == 'R') {
            bool found = false;
            TreeNode* current = root;
            while (current) {
                if (stock == current->value) {
                    found = true;
                    break;
                } else if (stock < current->value) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            if (found) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
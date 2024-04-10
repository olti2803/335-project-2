/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myAVLtree.cpp
*/

#include "myAVLtree.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <cmath>

class AVLNode {
public:
    int key, height, count;
    AVLNode *left, *right;
    int size; // Size of subtree for accurate median calculations, considering duplicates.

    AVLNode(int k) : key(k), height(1), count(1), left(nullptr), right(nullptr), size(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* N) {
        return N ? N->height : 0;
    }

    int size(AVLNode* N) {
        return N ? N->size : 0;
    }

    AVLNode* updateNode(AVLNode* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
        // Update size considering the count of duplicates.
        node->size = count(node->left) + count(node->right) + node->count;
        return node;
    }

    int count(AVLNode* N) {
        return N ? N->count * N->size : 0; // Adjust count by multiplying count and size for duplicates.
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y = updateNode(y);
        x = updateNode(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x = updateNode(x);
        y = updateNode(y);
        return y;
    }

    int getBalance(AVLNode* N) {
        return N ? height(N->left) - height(N->right) : 0;
    }

    // Modified insert function to handle duplicates properly.
    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            node->count++; // Increase count for duplicates instead of adding a new node.
        }
        return balance(updateNode(node));
    }

    // Recursively delete a node with the given key, considering duplicates.
    AVLNode* deleteNode(AVLNode* root, int key, bool &deleted) {
        if (root == nullptr) return root;
        if (key < root->key) {
            root->left = deleteNode(root->left, key, deleted);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key, deleted);
        } else {
            if (root->count > 1) {
                root->count--; // Decrease count for duplicates before considering node removal.
                deleted = true;
                return updateNode(root);
            }
            if (!root->left || !root->right) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else *root = *temp;
                delete temp;
                deleted = true;
            } else {
                AVLNode* temp = minValueNode(root->right);
                root->key = temp->key;
                root->count = temp->count;
                temp->count = 1; // Reset count for the successor.
                root->right = deleteNode(root->right, temp->key, deleted);
            }
        }
        if (root == nullptr) return root;
        return balance(updateNode(root));
    }
    // Function to balance the AVL tree at a given node.
AVLNode* balance(AVLNode* node) {
    if (!node) return nullptr;

    // Update the node's height and size before checking the balance factor.
    node = updateNode(node);

    int balanceFactor = getBalance(node);

    // Left Heavy
    if (balanceFactor > 1) {
        // Left-Left Case
        if (getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        // Left-Right Case
        else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    // Right Heavy
    else if (balanceFactor < -1) {
        // Right-Right Case
        if (getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        // Right-Left Case
        else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    // Node is already balanced
    return node;
}

// Utility function to find the node with minimum key value in a subtree rooted with a given node.
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    // The minimum value node is the leftmost leaf of the subtree.
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        bool deleted = false;
        root = deleteNode(root, key, deleted);
    }

    int findMedian() {
        if (!root) throw std::runtime_error("Tree is empty");
        int n = (root->size + 1) / 2;
        return findMedianUtil(root, n);
    }

private:
    int findMedianUtil(AVLNode* node, int n) {
        int leftSize = size(node->left);
        if (leftSize + 1 == n) return node->key;
        else if (n <= leftSize) return findMedianUtil(node->left, n);
        else return findMedianUtil(node->right, n - leftSize - 1);
    }
};

void treeMedian(const std::vector<int>* instructions) {
    AVLTree tree;
    std::vector<int> medians;

    for (auto instruction : *instructions) {
        if (instruction == -1) {
            try {
                medians.push_back(tree.findMedian());
                tree.remove(tree.findMedian());
            } catch (const std::runtime_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else {
            tree.insert(instruction);
        }
    }

    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}

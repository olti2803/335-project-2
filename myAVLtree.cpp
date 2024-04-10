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

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Destructor
AVLTree::~AVLTree() {
    clearTree(root);
}

// Helper to clear the tree recursively
void AVLTree::clearTree(AVLNode* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

// Insert a value into the AVL tree
void AVLTree::insert(int value) {
    root = insertHelper(root, value);
}

// Recursive helper for insertion
AVLNode* AVLTree::insertHelper(AVLNode* node, int value) {
    if (node == nullptr) {
        return new AVLNode(value);
    }

    if (value < node->value) {
        node->left = insertHelper(node->left, value);
    } else if (value > node->value) {
        node->right = insertHelper(node->right, value);
    } else {
        node->count++;
        return node;
    }

    updateHeight(node);
    return balanceTree(node, value);
}

// Update the height of a node
void AVLTree::updateHeight(AVLNode* node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

// Get height of a node
int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// Get balance factor of a node
int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotate
AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotate
AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balance the tree after insertion
AVLNode* AVLTree::balanceTree(AVLNode* node, int value) {
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && value < node->left->value) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && value > node->right->value) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Utility function to count nodes in the tree
int AVLTree::countNodes(AVLNode* node) {
    if (!node) return 0;
    return countNodes(node->left) + countNodes(node->right) + node->count;
}

// Deletes a node with a given value and rebalances the tree
AVLNode* AVLTree::deleteNode(AVLNode* node, int value) {
    if (node == nullptr) return node;

    if (value < node->value) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->value) {
        node->right = deleteNode(node->right, value);
    } else {
        if (node->count > 1) {
            node->count--;
            return node;
        }

        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->value);
        }
    }

    if (node == nullptr) return node;

    updateHeight(node);
    return balanceTree(node, value);
}

// Helper to find the node with the minimum value in a tree
AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Function to pop the median value from the AVL tree
int AVLTree::popMedian() {
    int totalNodes = countNodes(root);
    bool leftSubtree = true;
    AVLNode* medianNode = findMedianNodeAndDelete(root, leftSubtree, (totalNodes + 1) / 2);
    int medianValue = medianNode ? medianNode->value : -1; // Placeholder for cases where the tree might be empty
    // Handle deletion of the median node here if needed
    // Note: Depending on how you manage the median node deletion and the tree's balance, you might adjust this part.
    return medianValue;
}

AVLNode* AVLTree::findMedianNodeAndDelete(AVLNode*& node, int k, bool deleteMedian) {
    if (node == nullptr) {
        return nullptr;
    }

    int leftNodes = countNodes(node->left);

    if (leftNodes < k) {
        if (leftNodes + node->count >= k) {
            if (deleteMedian) {
                node->count--;
                if (node->count == 0) {
                    node = deleteNode(node, node->value);
                }
            }
            return node;
        }
        return findMedianNodeAndDelete(node->right, k - leftNodes - node->count, deleteMedian);
    } else {
        return findMedianNodeAndDelete(node->left, k, deleteMedian);
    }
}

void treeMedian(const std::vector<int>* instructions) {
    AVLTree tree;
    std::vector<int> medians;

    for (int instruction : *instructions) {
        if (instruction == -1) {
            int median = tree.popMedian();
            if (median != -1) { // Ensure the tree wasn't empty
                medians.push_back(median);
            }
        } else {
            tree.insert(instruction);
        }
    }

    // Print out the medians
    for (int median : medians) {
        std::cout << median << " ";
    }
}
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
#include <exception>

using namespace std;

// Node constructor
Node::Node(int val) : val(val), height(1), left(nullptr), right(nullptr) {}

// AVLtree constructor
AVLtree::AVLtree() : root(nullptr), node_count(0) {}

// Get the size of the AVL tree
int AVLtree::getSize() {
    return node_count;
}

// Get the maximum value in the AVL tree
int AVLtree::getMax() {
    if (!root) throw std::runtime_error("AVL tree is empty.");
    Node* current = root;
    while (current->right) {
        current = current->right;
    }
    return current->val;
}

// Insert a value into the AVL tree
void AVLtree::insert(int num) {
    root = insertNode(root, num);
    node_count++;
}

// Remove and return the smallest value in the AVL tree
int AVLtree::popMinimum() {
    if (!root) throw std::runtime_error("AVL tree is empty.");
    int minValue = minimumNode(root)->val;
    root = deleteNode(root, minValue);
    node_count--;
    return minValue;
}

// Remove and return the largest value in the AVL tree
int AVLtree::popMaximum() {
    if (!root) throw std::runtime_error("AVL tree is empty.");
    int maxValue = getMax(); // Utilizes getMax() for the value
    root = deleteNode(root, maxValue);
    node_count--;
    return maxValue;
}

// Helper functions defined below...

Node* AVLtree::insertNode(Node* node, int val) {
    if (!node) return new Node(val);

    if (val < node->val) node->left = insertNode(node->left, val);
    else if (val > node->val) node->right = insertNode(node->right, val);
    else return node; // Duplicate values are not inserted

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = balance_factor(node);

    // Rotations
    if (balance > 1 && val < node->left->val) return rightRotate(node);
    if (balance < -1 && val > node->right->val) return leftRotate(node);
    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* AVLtree::deleteNode(Node* node, int val) {
    if (!node) return node;

    // Find the node to be deleted and perform deletion
    if (val < node->val) node->left = deleteNode(node->left, val);
    else if (val > node->val) node->right = deleteNode(node->right, val);
    else {
        // Node with only one child or no child
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else *node = *temp;
            delete temp;
        } else {
            // Node with two children
            Node* temp = minimumNode(node->right);
            node->val = temp->val;
            node->right = deleteNode(node->right, temp->val);
        }
    }

    if (!node) return node;

    // Update height and rebalance
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = balance_factor(node);

    // Rotations
    if (balance > 1 && balance_factor(node->left) >= 0) return rightRotate(node);
    if (balance > 1 && balance_factor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && balance_factor(node->right) <= 0) return leftRotate(node);
    if (balance < -1 && balance_factor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int AVLtree::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVLtree::balance_factor(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLtree::minimumNode(Node* node) {
    Node* current = node;
    while (current && current->left) current = current->left;
    return current;
}

Node* AVLtree::leftRotate(Node* k1) {
    Node* k2 = k1->right;
    Node* T2 = k2->left;

    k2->left = k1;
    k1->right = T2;

    k1->height = 1 + std::max(getHeight(k1->left), getHeight(k1->right));
    k2->height = 1 + std::max(getHeight(k2->left), getHeight(k2->right));

    return k2;
}

Node* AVLtree::rightRotate(Node* k2) {
    Node* k1 = k2->left;
    Node* T2 = k1->right;

    k1->right = k2;
    k2->left = T2;

    k2->height = 1 + std::max(getHeight(k2->left), getHeight(k2->right));
    k1->height = 1 + std::max(getHeight(k1->left), getHeight(k1->right));

    return k1;
}

void treeMedian(const std::vector<int>* instructions) {
    AVLtree tree;
    for (int instruction : *instructions) {
        if (instruction != -1) {
            tree.insert(instruction);
        } else {
            if (tree.getSize() % 2 == 0) {
                std::cout << "Even number of nodes, operation not supported in this demo." << std::endl;
            } else {
                std::cout << "Median: " << tree.popMaximum() << std::endl;
            }
        }
    }
}
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

Node* AVLTree::insert(Node* node, int value) {
    // 1. Perform the normal BST insertion
    if (node == nullptr) {
        node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;  // new node is initially added at leaf
        return node;
    }

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else  // Equal values are allowed in this AVL tree
        return node;

    // 2. Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // 3. Get the balance factor
    int balance = getBalance(node);

    // 4. If node is unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

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

    // return the (unchanged) node pointer
    return node;
}

Node* AVLTree::deleteNode(Node* root, int value) {
    // 1. Perform the normal BST deletion
    if (root == nullptr)
        return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if(value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        // node with only one child or no child
        if((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if(temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        }
        else {
            // node with two children: get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            // copy the inorder successor's data to this node
            root->value = temp->value;

            // delete the inorder successor
            root->right = deleteNode(root->right, temp->value);
        }
    }

    // if the tree had only one node then return
    if (root == nullptr)
        return root;

    // 2. update height of the current node
    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    // 3. get the balance factor
    int balance = getBalance(root);

    // 4. if the node is unbalanced, then there are 4 cases

    // left left case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // left right case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // right right case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // right left case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrder(Node* node, std::vector<int>& values) {
    if (node != nullptr) {
        inOrder(node->left, values);
        values.push_back(node->value);
        inOrder(node->right, values);
    }
}

int AVLTree::getMedian() {
    if (root == nullptr) {
        throw std::out_of_range("Cannot get median from an empty tree");
    }
    std::vector<int> values;
    inOrder(root, values);
    size_t size = values.size();

    if (size % 2 != 0)
        return values[size / 2];
    else
        return (values[(size - 1) / 2] + values[size / 2]) / 2;
}

int AVLTree::popMedian() {
    if (root == nullptr) {
        throw std::out_of_range("Cannot pop median from an empty tree");
    }
    int median = getMedian();
    root = deleteNode(root, median);
    return median;
}

int AVLTree::getHeight(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int AVLTree::getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;

    // loop down to find the leftmost leaf 
    while (current->left != nullptr)
        current = current->left;

    return current;
}

Node* AVLTree::maxValueNode(Node* node) {
    Node* current = node;

    // loop down to find the rightmost leaf
    while (current->right != nullptr)
        current = current->right;

    return current;
}

void AVLTree::insertValue(int value) {
    root = insert(root, value);
}

void treeMedian(const std::vector<int>* instructions) {
    AVLTree tree;
    std::vector<int> medians;

    for (int instruction : *instructions) {
        if (instruction == -1) { 
            medians.push_back(tree.popMedian());
        } else {
            tree.insertValue(instruction);
        }
    }

    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
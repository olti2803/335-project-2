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
    int key, height, size;
    AVLNode *left, *right;

    // Constructor initializing the AVLNode with key, and setting height and size.
    AVLNode(int k) : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    // Function to get height of the tree.
    int height(AVLNode* N) {
        return N ? N->height : 0;
    }

    // Function to get size of the tree.
    int size(AVLNode* N) {
        return N ? N->size : 0;
    }

    // Function to update node's height and size.
    AVLNode* updateNode(AVLNode* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);
        return node;
    }

    // Right rotate utility.
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y = updateNode(y);
        x = updateNode(x);

        return x;
    }

    // Left rotate utility.
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x = updateNode(x);
        y = updateNode(y);

        return y;
    }

    // Function to get balance factor of node N.
    int getBalance(AVLNode* N) {
        return N ? height(N->left) - height(N->right) : 0;
    }

    // Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);

        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;  // Equal keys are not allowed in BST

        node = updateNode(node);

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key) return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key) return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // Utility to find the node with minimum key value found in that tree.
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr) current = current->left;
        return current;
    }

    // Recursive function to delete a node with a given key from subtree with given root. It returns root of the modified subtree.
    AVLNode* deleteNode(AVLNode* root, int key, bool &deleted) {
        if (root == nullptr) return root;

        // If the key to be deleted is smaller than the root's key, then it lies in left subtree
        if (key < root->key) root->left = deleteNode(root->left, key, deleted);

        // If the key to be deleted is greater than the root's key, then it lies in right subtree
        else if (key > root->key) root->right = deleteNode(root->right, key, deleted);

        // if key is same as root's key, then this is the node to be deleted
        else {
            deleted = true; // Mark as deleted
            // node with only one child or no child
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else // One child case
                 *root = *temp; // Copy the contents of the non-empty child
                
                delete temp;
            } else {
                // node with two children: Get the inorder successor (smallest in the right subtree)
                AVLNode* temp = minValueNode(root->right);

                // Copy the inorder successor's content to this node
                root->key = temp->key;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->key, deleted);
            }
        }

        // If the tree had only one node then return it
        if (root == nullptr) return root;

        // STEP 3: UPDATE HEIGHT OF THE CURRENT NODE
        root = updateNode(root);

        // STEP 4: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

public:
    AVLTree() : root(nullptr) {}

    // Function to insert a new key to the tree
    void insert(int key) {
        root = insert(root, key);
    }

    // Function to delete a key from the tree, if present
    void remove(int key) {
        bool deleted = false;
        root = deleteNode(root, key, deleted);
    }

    // Function to find median of the AVL Tree
    int findMedian() {
        if (!root) throw std::runtime_error("Tree is empty");
        int n = size(root);
        bool isEven = n % 2 == 0;
        int median1 = findMedianUtil(root, (n + 1) / 2);
        if (isEven) {
            int median2 = findMedianUtil(root, (n / 2) + 1);
            return (median1 + median2) / 2; // Return the average if even number of nodes
        }
        return median1; // Return median1 if odd number of nodes
    }

private:
    // Utility function to find the median. It returns the kth smallest element
    int findMedianUtil(AVLNode* node, int k) {
        int leftSize = size(node->left);
        if (leftSize + 1 == k) return node->key;
        else if (k <= leftSize) return findMedianUtil(node->left, k);
        else return findMedianUtil(node->right, k - leftSize - 1);
    }
};

// Function to handle instructions for insertion and median popping from the AVL tree.
void treeMedian(const std::vector<int>* instructions) {
    AVLTree tree;
    for (auto instruction : *instructions) {
        if (instruction == -1) { // If instruction is to pop median
            try {
                std::cout << tree.findMedian() << " ";
                tree.remove(tree.findMedian()); // Remove the median after finding it
            } catch (const std::runtime_error& e) {
                std::cerr << "Error: " << e.what() << std::endl; // Catch and report if tree is empty
            }
        } else {
            tree.insert(instruction); // Insert instruction into the tree
        }
    }
    std::cout << std::endl; // Ensures newline at the end of output
}

/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myAVLtree.hpp
*/

#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <cmath>

// Node structure for the AVL tree
struct AVLNode {
    int value;          // The value of the node
    int count;          // Number of duplicates of this value
    int height;         // Height of the node for balancing
    AVLNode* left;      // Pointer to the left child
    AVLNode* right;     // Pointer to the right child

    // Constructor
    AVLNode(int val) : value(val), count(1), height(1), left(nullptr), right(nullptr) {}
};

// AVL tree class
class AVLTree {
public:
    AVLTree();                      // Constructor
    ~AVLTree();                     // Destructor
    void insert(int value);         // Inserts a value into the AVL tree
    int popMedian();                // Pops the median from the AVL tree
    int countNodes(AVLNode* node);  // Count the total nodes in the tree
    

private:
    AVLNode* root;                  // Pointer to the root node of the AVL tree

    // Helper functions
    AVLNode* insertHelper(AVLNode* node, int value);
    AVLNode* deleteNode(AVLNode* node, int value);
    AVLNode* findMedianNodeAndDelete(AVLNode*& node, int k, bool deleteMedian = true);
    AVLNode* minValueNode(AVLNode* node);
    int getBalance(AVLNode* node);
    int getHeight(AVLNode* node);
    void updateHeight(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* balanceTree(AVLNode* node, int value);
    void clearTree(AVLNode* node);
};

#endif // MYAVLTREE_HPP
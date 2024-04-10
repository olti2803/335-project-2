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

// Definition of the AVL tree node
struct AVLNode {
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
    int count; // To accommodate duplicates

    // Constructor to initialize a new node
    AVLNode(int val) : value(val), left(nullptr), right(nullptr), height(1), count(1) {}
};

class AVLTree {
public:
    AVLTree(); // Constructor to initialize an empty AVL tree
    ~AVLTree(); // Destructor to free the AVL tree

    // Function to insert a new value into the AVL tree
    void insert(int value);

    // Function to pop and return the median value from the AVL tree
    int popMedian();

    static void treeMedian(const std::vector<int>& instructions); // Declaration for treeMedian, the main function we are testing for


private:
    AVLNode* root; // Root of the AVL tree

    // Recursive utility function to insert a new value in the AVL tree
    AVLNode* insertRecursive(AVLNode* node, int value);

    // Utility function to delete a node from the AVL tree
    AVLNode* deleteNode(AVLNode* root, int key);

    // Utility functions for performing right and left rotations
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);


    AVLNode* findMedianNode(AVLNode* node); 
    AVLNode* removeNode(AVLNode* node, int value); 
    
    AVLNode* balanceNode(AVLNode* node);
    AVLNode* findSuccessor(AVLNode* node);
    void updateNode(AVLNode* node);


    // Function to get the balance factor of a node
    int getBalance(AVLNode* N);

    // Function to get the height of a node
    int height(AVLNode* N);

    // Helper function to extract the median value and rebalance the tree
    int getMedianValueAndRebalance();

    // Helper function to clear the tree on destruction
    void clearTree(AVLNode* node);

};

#endif // MYAVLTREE_HPP
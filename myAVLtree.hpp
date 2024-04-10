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

// Node structure for AVL tree
struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    Node* insert(Node* node, int value);
    Node* deleteNode(Node* root, int value);
    int getMedian();
    int popMedian();
    int getHeight(Node* N);
    int getBalance(Node* N);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* minValueNode(Node* node);
    Node* maxValueNode(Node* node);

    void insertValue(int value) {
        root = insert(root, value);
    }

private:
    Node* root;
};

void treeMedian(const std::vector<int>* instructions);

#endif // MYAVLTREE_HPP
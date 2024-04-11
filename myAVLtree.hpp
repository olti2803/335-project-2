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
#include <exception>

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(int value);
    void remove(int value);
    bool isEmpty() const;
    int size() const;
    int findMax() const;
    int findMin() const;
    void treeMedian(const std::vector<int>* instructions);

private:
    struct AVLNode {
        int data;
        AVLNode* left;
        AVLNode* right;
        int height;
        int size;  // Total nodes in subtree
        AVLNode(int d, AVLNode* l = nullptr, AVLNode* r = nullptr, int h = 0, int s = 1)
            : data(d), left(l), right(r), height(h), size(s) {}
    };
    AVLNode* root;

    void insert(int value, AVLNode*& t);
    void remove(int value, AVLNode*& t);
    void balance(AVLNode*& t);
    int height(AVLNode* t) const;
    int getSize(AVLNode* t) const;
    void updateHeightAndSize(AVLNode* t);
    AVLNode* findMin(AVLNode* t) const;
    AVLNode* findMax(AVLNode* t) const;
    void clear(AVLNode*& t);
    void rotateWithLeftChild(AVLNode*& k2);
    void rotateWithRightChild(AVLNode*& k1);
    void doubleWithLeftChild(AVLNode*& k3);
    void doubleWithRightChild(AVLNode*& k1);
};

#endif // MYAVLTREE_HPP
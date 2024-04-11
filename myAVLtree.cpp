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

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clear(root);
}


void AVLTree::updateHeightAndSize(AVLNode* t) {
    t->height = 1 + max(height(t->left), height(t->right));
    t->size = 1 + getSize(t->left) + getSize(t->right);
}

AVLTree::AVLNode* AVLTree::findMin(AVLNode* t) const {
    return t->left == nullptr ? t : findMin(t->left);
}

AVLTree::AVLNode* AVLTree::findMax(AVLNode* t) const {
    return t->right == nullptr ? t : findMax(t->right);
}

int AVLTree::findMax() const {
    if (isEmpty()) throw std::runtime_error("Tree is empty");
    return findMax(root)->data;
}

int AVLTree::findMin() const {
    if (isEmpty()) throw std::runtime_error("Tree is empty");
    return findMin(root)->data;
}

void AVLTree::rotateWithLeftChild(AVLNode*& k2) {
    AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    updateHeightAndSize(k2);
    updateHeightAndSize(k1);
    k2 = k1;
}

void AVLTree::rotateWithRightChild(AVLNode*& k1) {
    AVLNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    updateHeightAndSize(k1);
    updateHeightAndSize(k2);
    k1 = k2;
}

void AVLTree::doubleWithLeftChild(AVLNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void AVLTree::doubleWithRightChild(AVLNode*& k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

void AVLTree::clear(AVLNode*& t) {
    if (t != nullptr) {
        clear(t->left);
        clear(t->right);
        delete t;
        t = nullptr;
    }
}

void AVLTree::balance(AVLNode*& t) {
    if (t == nullptr) return;
    if (height(t->left) - height(t->right) > 1) {
        if (height(t->left->left) >= height(t->left->right)) rotateWithLeftChild(t);
        else doubleWithLeftChild(t);
    } else if (height(t->right) - height(t->left) > 1) {
        if (height(t->right->right) >= height(t->right->left)) rotateWithRightChild(t);
        else doubleWithRightChild(t);
    }
    updateHeightAndSize(t);
}

void AVLTree::insert(int value, AVLNode*& t) {
    if (t == nullptr) t = new AVLNode(value);
    else if (value < t->data) insert(value, t->left);
    else if (value > t->data) insert(value, t->right);
    balance(t);
    updateHeightAndSize(t);
}

void AVLTree::remove(int value, AVLNode*& t) {
    if (t == nullptr) return;
    if (value < t->data) remove(value, t->left);
    else if (value > t->data) remove(value, t->right);
    else if (t->left != nullptr && t->right != nullptr) {
        t->data = findMin(t->right)->data;
        remove(t->data, t->right);
    } else {
        AVLNode* oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
    if (t != nullptr) balance(t);
    updateHeightAndSize(t);
}

void AVLTree::treeMedian(const std::vector<int>* instructions) {
    AVLTree small, large; // Trees to hold the lower and higher halves
    std::vector<int> medians; // To store the medians for printing later

    for (int inst : *instructions) {
        if (inst == -1) {
            // Pop median operation
            if (!small.isEmpty()) {
                int median = small.findMax(); // Extract the current median
                medians.push_back(median);
                small.remove(median); // Remove the median from the small tree
            }
            // No median to pop if small is empty (implied large is also empty)
        } else {
            // Insert operation
            if (small.isEmpty() || inst < small.findMax()) {
                small.insert(inst); // Insert into small if it's less than the current median
            } else {
                large.insert(inst); // Otherwise, insert into large
            }

            // Rebalance the trees to ensure their sizes differ by no more than 1
            if (small.size() > large.size() + 1) {
                // If small has 2 more elements than large, move the largest from small to large
                int toMove = small.findMax();
                small.remove(toMove);
                large.insert(toMove);
            } else if (large.size() > small.size()) {
                // If large has more elements, move the smallest from large to small
                int toMove = large.findMin();
                large.remove(toMove);
                small.insert(toMove);
            }
        }
    }

    // After processing all instructions, print out the medians extracted
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myAVLtree.cpp
*/

#include <algorithm>
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "myAVLtree.hpp"


int height(AVLnode *t) { //returns height of node t
    return t == nullptr ? -1 : t->height;
}

void insert(const int &x, AVLnode *&t) { //inserts x into AVL tree t
    if (t == nullptr) {
        t = new AVLnode(x, nullptr, nullptr); //create new node with x
    } else if (x <= t->element) {
        insert(x, t->left);
    } else if (t->element < x) {
        insert(x, t->right);
    }

    balance(t); //balance the tree
}

static const int ALLOWED_IMBALANCE = 1; //allowed imbalance for AVL tree

//Assume t is balanced or within one of being balanced
void balance(AVLnode *&t){ //balance the AVL tree
    if (t == nullptr) {
        return;
    }

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) { //left subtree is taller
        if (height(t->left->left) >= height(t->left->right)) {// left child of left subtree is taller
            rotateWithLeftChild(t);
        } else {
            doubleWithLeftChild(t);
        }
    } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) { //right subtree is taller
        if (height(t->right->right) >= height(t->right->left)) { //right child of right subtree is taller
            rotateWithRightChild(t);
        } else {
            doubleWithRightChild(t);
        }
    }

    t->height = std::max(height(t->left), height(t->right)) + 1;  //update height of t
}

void rotateWithLeftChild(AVLnode *&k2){ //rotate with left child
    AVLnode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

void rotateWithRightChild(AVLnode *&k2){ //rotate with right child
    AVLnode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = std::max(height(k2->right), height(k2->left)) + 1;
    k1->height = std::max(height(k1->right), k2->height) + 1;
    k2 = k1;
}

void doubleWithLeftChild(AVLnode *&k3){ //double rotate with left child
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void doubleWithRightChild(AVLnode *&k3) { //double rotate with right child
    rotateWithLeftChild(k3->right); 
    rotateWithRightChild(k3); 
}

void remove(const int &x, AVLnode *&t){ //remove x from AVL tree t
    if (t == nullptr) {
        return;
    }

    if (x < t->element) { //x is in left subtree
        remove(x, t->left);
    } else if (t->element < x) { //x is in right subtree
        remove(x, t->right); 
    } else if (t->left != nullptr && t->right != nullptr) { //node has two children
        t->element = findMinimum(t->right)->element;
        remove(t->element, t->right);
    } else { //node has one child
        AVLnode *oldNode = t; 
        t = (t->left != nullptr) ? t->left : t->right; 
        delete oldNode;
        oldNode = nullptr;
    }

    balance(t);
}

AVLnode *findMinimum(AVLnode *t){ //find minimum element in AVL tree t
    if (t == nullptr){ //empty tree
        return nullptr;
    }
    if(t->left == nullptr){ //no left child
        return t;
    }
    return findMinimum(t->left); 
}

AVLnode *findMaximum(AVLnode *t){ //find maximum element in AVL tree t
    if (t != nullptr) {
        while(t->right != nullptr) { //keep going right until no right child
            t = t->right;
        }
    }
    return t;
}

void treeMedian(const std::vector<int> *instructions){ //find median of AVL tree
    std::vector<int> medians; //empty vector that will hold median values
    AVLnode *max = nullptr;
    AVLnode *min = nullptr; 
    int countmax = 0;
    int countmin = 0;

    const auto time_begin = std::chrono::steady_clock::now(); //begin timer to measure for report
    for (auto it = instructions->begin(); it != instructions->end(); ++it){
        if (max == nullptr && *it != -1) {
            insert(*it, max);
            countmax += 1; 
        } else if (*it == -1) {
            AVLnode *rightMost = findMaximum(max); //find rightmost node
            medians.push_back(rightMost->element);  //add rightmost node to medians
            remove(rightMost->element, max);
            countmax -= 1; 
            if (countmin > countmax) { //if min is greater than max
                AVLnode *leftMost = findMinimum(min); //find leftmost node
                auto copy = leftMost->element; 
                remove(copy, min);
                insert(copy, max);
                countmin -= 1;
                countmax += 1;
            }
        } else {
            if (*it <= findMaximum(max)->element) { //if element is less than or equal to max
                insert(*it, max);
                countmax += 1;
                if (countmax > countmin + 1) { //if max is greater than min by more than 1
                    AVLnode *rightMost = findMaximum(max);
                    int copyy = rightMost->element;
                    remove(copyy, max);
                    insert(copyy, min); 
                    countmax -= 1;
                    countmin += 1; 
                }
            } else if (*it > findMaximum(max)->element) { //if element is greater than max
                insert(*it, min);
                countmin += 1; 
                if (countmin > countmax){ //if min is greater than max
                    AVLnode *leftMost = findMinimum(min);
                    auto coppyyy = leftMost->element;
                    remove(coppyyy, min);
                    insert(coppyyy, max);
                    countmin -= 1;
                    countmax += 1;
                }
            }
        }
    }

    //TIMING IS COMMENTED OUT

    // const auto time_end = std::chrono::steady_clock::now();
    // int duration_ = std::chrono::duration<double, std::micro>(time_end - time_begin).count();

    // std::cout << "\n\nTime to insert and pop medians for AVLtree: " << duration_ << " microseconds\n" << std::endl;

    // for (auto m: medians){
    //     //std::cout << m << " ";
    // }
}
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
    return t == nullptr ? -1 : t->height; //if t is null, return -1, else return height of t
}

void insert(const int &x, AVLnode *&t) { //inserts x into AVL tree t
    if (t == nullptr) {//empty tree
        t = new AVLnode(x, nullptr, nullptr); //create new node with x
    } else if (x <= t->element) {//x is less than or equal to element of t
        insert(x, t->left);//insert x into left subtree
    } else if (t->element < x) {//x is greater than element of t
        insert(x, t->right);//insert x into right subtree
    }

    balance(t); //balance the tree
}

static const int ALLOWED_IMBALANCE = 1; //allowed imbalance for AVL tree

//Assume t is balanced or within one of being balanced
void balance(AVLnode *&t){ //balance the AVL tree
    if (t == nullptr) { //empty tree
        return;//do nothing
    }

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) { //left subtree is taller
        if (height(t->left->left) >= height(t->left->right)) {// left child of left subtree is taller
            rotateWithLeftChild(t);//rotate with left child
        } else {//right child of left subtree is taller
            doubleWithLeftChild(t);//double rotate with left child
        }
    } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) { //right subtree is taller
        if (height(t->right->right) >= height(t->right->left)) { //right child of right subtree is taller
            rotateWithRightChild(t); //rotate with right child
        } else {//left child of right subtree is taller
            doubleWithRightChild(t);//double rotate with right child
        }
    }

    t->height = std::max(height(t->left), height(t->right)) + 1;  //update height of t
}

void rotateWithLeftChild(AVLnode *&k2){ //rotate with left child
    AVLnode *k1 = k2->left; //k1 is left child of k2
    k2->left = k1->right;//right child of k1 is left child of k2
    k1->right = k2;//k2 is right child of k1
    k2->height = std::max(height(k2->left), height(k2->right)) + 1; //update height of k2
    k1->height = std::max(height(k1->left), k2->height) + 1;//update height of k1
    k2 = k1;//k1 is now k2
}

void rotateWithRightChild(AVLnode *&k2){ //rotate with right child
    AVLnode *k1 = k2->right;//k1 is right child of k2
    k2->right = k1->left;//left child of k1 is right child of k2
    k1->left = k2;//k2 is left child of k1
    k2->height = std::max(height(k2->right), height(k2->left)) + 1;//update height of k2
    k1->height = std::max(height(k1->right), k2->height) + 1;//update height of k1
    k2 = k1;//k1 is now k2
}

void doubleWithLeftChild(AVLnode *&k3){ //double rotate with left child
    rotateWithRightChild(k3->left);//rotate right child of left child
    rotateWithLeftChild(k3);//rotate left child
}

void doubleWithRightChild(AVLnode *&k3) { //double rotate with right child
    rotateWithLeftChild(k3->right); //rotate left child of right child
    rotateWithRightChild(k3); //rotate right child
}

void remove(const int &x, AVLnode *&t){ //remove x from AVL tree t
    if (t == nullptr) {//empty tree
        return;//do nothing
    }

    if (x < t->element) { //x is in left subtree
        remove(x, t->left);//remove x from left subtree
    } else if (t->element < x) { //x is in right subtree
        remove(x, t->right); //remove x from right subtree
    } else if (t->left != nullptr && t->right != nullptr) { //node has two children
        t->element = findMinimum(t->right)->element;//replace node with minimum element in right subtree
        remove(t->element, t->right);//remove minimum element from right subtree
    } else { //node has one child
        AVLnode *oldNode = t; //node to be removed
        t = (t->left != nullptr) ? t->left : t->right; //replace node with child
        delete oldNode;//delete node
        oldNode = nullptr;//delete node
    }

    balance(t);//balance the tree
}

AVLnode *findMinimum(AVLnode *t){ //find minimum element in AVL tree t
    if (t == nullptr){ //empty tree
        return nullptr;//return null
    }
    if(t->left == nullptr){ //no left child
        return t;//return t
    }
    return findMinimum(t->left); //keep going left until no left child
}

AVLnode *findMaximum(AVLnode *t){ //find maximum element in AVL tree t
    if (t != nullptr) { //not empty tree
        while(t->right != nullptr) { //keep going right until no right child
            t = t->right;//go right
        }
    }
    return t;//return t
}

void treeMedian(const std::vector<int> *instructions){ //find median of AVL tree
    std::vector<int> medians; //empty vector that will hold median values
    AVLnode *max = nullptr;//max AVL tree
    AVLnode *min = nullptr; //min AVL tree
    int countmax = 0;//count of max AVL tree
    int countmin = 0;//count of min AVL tree

    const auto time_begin = std::chrono::steady_clock::now(); //begin timer to measure for report
    for (auto it = instructions->begin(); it != instructions->end(); ++it){ //iterate through instructions
        if (max == nullptr && *it != -1) { //if max is empty and element is not -1
            insert(*it, max); //insert element into max
            countmax += 1; //increment count of max
        } else if (*it == -1) { //if element is -1
            AVLnode *rightMost = findMaximum(max); //find rightmost node
            medians.push_back(rightMost->element);  //add rightmost node to medians
            remove(rightMost->element, max); //remove rightmost node from max
            countmax -= 1; //decrement count of max
            if (countmin > countmax) { //if min is greater than max
                AVLnode *leftMost = findMinimum(min); //find leftmost node
                auto copy = leftMost->element; //copy leftmost node
                remove(copy, min); //remove leftmost node from min
                insert(copy, max);//insert leftmost node into max
                countmin -= 1;//decrement count of min
                countmax += 1;//increment count of max
            }
        } else { //element is not -1
            if (*it <= findMaximum(max)->element) { //if element is less than or equal to max
                insert(*it, max);//insert element into max
                countmax += 1;//increment count of max
                if (countmax > countmin + 1) { //if max is greater than min by more than 1
                    AVLnode *rightMost = findMaximum(max);//find rightmost node
                    int copyy = rightMost->element;//copy rightmost node
                    remove(copyy, max);//remove rightmost node from max
                    insert(copyy, min); //insert rightmost node into min
                    countmax -= 1;//decrement count of max
                    countmin += 1; //increment count of min
                }
            } else if (*it > findMaximum(max)->element) { //if element is greater than max
                insert(*it, min); //insert element into min
                countmin += 1; //increment count of min
                if (countmin > countmax){ //if min is greater than max
                    AVLnode *leftMost = findMinimum(min);//find leftmost node
                    auto copyv3 = leftMost->element;//copy leftmost node
                    remove(copyv3, min);//remove leftmost node from min
                    insert(copyv3, max);//insert leftmost node into max
                    countmin -= 1;//decrement count of min
                    countmax += 1;//increment count of max
                }
            }
        }
    }

    //TIMING

    // const auto time_end = std::chrono::steady_clock::now();
    // int duration_ = std::chrono::duration<double, std::micro>(time_end - time_begin).count();

    // std::cout << "\n\nTime to insert and pop medians for AVLtree: " << duration_ << " microseconds\n" << std::endl;

    for (auto m: medians){ //print medians
        std::cout << m << " ";//prints
    }
}
/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myAVLtree.hpp
*/

#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <algorithm>
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

struct AVLnode { //AVL tree node
    int element; //element of node
    AVLnode *right;//right child
    AVLnode *left;//left child
    int height;//height of node

    AVLnode(const int &ele, AVLnode *lt, AVLnode *rt, int h = 0) : //constructor
        element(ele), left(lt), right(rt), height(h) {}

    AVLnode(int &&ele, AVLnode *lt, AVLnode *rt, int h = 0) :  //constructor
        element(std::move(ele)), left(lt), right(rt), height(h) {}
};

int height(AVLnode *t); //returns height of node t
void insert(const int &x, AVLnode *&t); //inserts x into AVL tree t
void balance(AVLnode *&t);//balance the AVL tree
void rotateWithLeftChild(AVLnode *&k2);//rotate with left child
void rotateWithRightChild(AVLnode *&k1);//rotate with right child
void doubleWithLeftChild(AVLnode *&k3);//double with left child
void doubleWithRightChild(AVLnode *&k1);//double with right child
void remove(const int &x, AVLnode *&t);//remove x from AVL tree t
AVLnode *findMaximum(AVLnode *t);//find maximum node in AVL tree t
AVLnode *findMinimum(AVLnode *t);//find minimum node in AVL tree t
void treeMedian(const std::vector<int> *instructions);//find median of AVL tree

#endif // MYAVLTREE_HPP
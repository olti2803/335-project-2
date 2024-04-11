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

struct AVLnode {
    int element;
    AVLnode *right;
    AVLnode *left;
    int height;

    AVLnode(const int &ele, AVLnode *lt, AVLnode *rt, int h = 0) : 
        element(ele), left(lt), right(rt), height(h) {}

    AVLnode(int &&ele, AVLnode *lt, AVLnode *rt, int h = 0) : 
        element(std::move(ele)), left(lt), right(rt), height(h) {}
};

int height(AVLnode *t);
void insert(const int &x, AVLnode *&t);
void balance(AVLnode *&t);
void rotateWithLeftChild(AVLnode *&k2);
void rotateWithRightChild(AVLnode *&k1);
void doubleWithLeftChild(AVLnode *&k3);
void doubleWithRightChild(AVLnode *&k1);
void remove(const int &x, AVLnode *&t);
AVLnode *findMaximum(AVLnode *t);
AVLnode *findMinimum(AVLnode *t);
void treeMedian(const std::vector<int> *instructions);

#endif
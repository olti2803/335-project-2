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

struct Node 
{
    int val, height;
    Node *left, *right;
    Node(int val);  // Constructor declaration
};

class AVLtree {
public:
    AVLtree();  // Constructor
    int getSize();  // Get the number of nodes
    int getMax();  // Get the maximum value
    void insert(int num);  // Insert a value
    int popMinimum();  // Remove and return the smallest value
    int popMaximum();  // Remove and return the largest value
    Node* insertNode(Node* node, int val);  // Helper for insert
    Node* deleteNode(Node* node, int val);  // Delete a node

private:
    Node* root;
    int node_count;
    int getHeight(Node* node);
    int balance_factor(Node* node);
    Node* minimumNode(Node* node);
    Node* leftRotate(Node* k1);
    Node* rightRotate(Node* k2);
};

void treeMedian(const std::vector<int> *instructions);

#endif 

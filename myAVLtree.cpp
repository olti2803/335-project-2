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

void treeMedian(const std::vector<int>* instructions) {
    if (!instructions) {
        std::cerr << "Error: Null pointer passed to treeMedian." << std::endl;
        return;
    }

    AVLTree tree; // Single AVL tree to store all elements
    std::vector<int> medians; // Vector to hold medians

    for (int instruction : *instructions) {
        if (instruction == -1) {
            // Print median
            if (tree.empty()) {
                std::cerr << "Error: No elements to find median." << std::endl;
                continue;
            }
            medians.push_back(tree.findMedian()); // Get median directly from the AVL tree
        } else {
            // Insert instruction value into the AVL tree
            tree.insert(instruction, tree.root);
        }
    }

    // Print medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}

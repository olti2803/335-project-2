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

    AVLTree small_tree, large_tree; // Two AVL trees to store elements less than or equal to median and greater than median

    std::vector<int> medians; // Vector to hold medians

    for (int instruction : *instructions) {
        if (instruction == -1) {
            // Print median
            if (small_tree.empty()) {
                std::cerr << "Error: No elements to find median." << std::endl;
                continue;
            }
            medians.push_back(small_tree.findMax(small_tree.root)->element); // Get median from the small_tree
        } else {
            // Insert instruction value into the appropriate AVL tree
            if (small_tree.empty() || instruction <= small_tree.findMax(small_tree.root)->element) {
                small_tree.insert(instruction, small_tree.root);
            } else {
                large_tree.insert(instruction, large_tree.root);
            }
            
            // Rebalance the trees
            if (small_tree.getSize(small_tree.root) > large_tree.getSize(large_tree.root) + 1) {
                int temp = small_tree.findMax(small_tree.root)->element;
                small_tree.remove(temp, small_tree.root);
                large_tree.insert(temp, large_tree.root);
            } else if (large_tree.getSize(large_tree.root) > small_tree.getSize(small_tree.root)) {
                int temp = large_tree.findMin(large_tree.root)->element;
                large_tree.remove(temp, large_tree.root);
                small_tree.insert(temp, small_tree.root);
            }
        }
    }

    // Print medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}


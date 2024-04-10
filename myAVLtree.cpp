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

void treeMedian(const std::vector<int>* instructions) {
    if (!instructions) {
        std::cerr << "Error: Null pointer passed to treeMedian." << std::endl;
        return;
    }

    AvlTree<int> tree; // Assuming AvlTree is a template class that requires a type

    std::vector<int> medians; // Vector to hold medians

    for (int instruction : *instructions) {
        if (instruction == -1) {
            // Attempt to pop median from the AVL tree
            if (tree.isEmpty()) {
                std::cerr << "Error: No elements to find median." << std::endl;
                continue;
            }
            try {
                int median = tree.popMedian(); // Correctly use popMedian here
                medians.push_back(median);
            } catch (const UnderflowException& e) {
                std::cerr << e.what() << std::endl;
            }
        } else {
            // Insert instruction value into the AVL tree
            tree.insert(instruction); // Insert directly without accessing root
        }
    }

    // Print medians
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}

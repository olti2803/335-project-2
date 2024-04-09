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

// Dummy implementation for AVL Node, just for the stub.
struct AVLNode {
    int key;
    AVLNode *left, *right;
    AVLNode(int value) : key(value), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        // Placeholder: Print action instead of actual insertion
        std::cout << "Inserting " << key << " into AVL Tree (stubbed).\n";
    }

    int popMedian() {
        // Placeholder: Return a fixed value and print action
        std::cout << "Popping median from AVL Tree (stubbed).\n";
        return -1; // Return a dummy median value
    }

    ~AVLTree() {
        // Cleanup resources if any, for now, it's a stub so nothing to clean
    }
};

void treeMedian(const std::vector<int>* instructions) {
    AVLTree tree;
    std::vector<int> medians;

    for (int instruction : *instructions) {
        if (instruction == -1) {
            // Use the stubbed popMedian method
            int median = tree.popMedian();
            if (median != -1) { // In real implementation, check if tree was empty
                medians.push_back(median);
            }
        } else {
            // Use the stubbed insert method
            tree.insert(instruction);
        }
    }

    // Stub: Print medians collected from the stubbed popMedian calls
    for (int median : medians) {
        std::cout << median << " (stubbed) ";
    }
    std::cout << std::endl;
}

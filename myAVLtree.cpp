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

using namespace std;

void treeMedian(const std::vector<int>& instructions) {
    AvlTree<int> tree;
    for (int instruction : instructions) {
        if (instruction == -1) { // Pop median operation
            try {
                std::cout << tree.popMedian() << " ";
            } catch (const UnderflowException& e) {
                std::cout << "Attempted to pop from an empty tree." << std::endl;
            }
        } else { // Insert operation
            tree.insert(instruction);
        }
    }
    std::cout << std::endl; // Ensure the output ends with a new line
}

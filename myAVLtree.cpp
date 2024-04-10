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

void treeMedian(const vector<int>* instructions) {
    AvlTree<int> tree;
    vector<int> medians;

    for (int instruction : *instructions) {
        if (instruction == -1) { // Pop median operation
            try {
                int median = tree.popMedian();
                medians.push_back(median);
            } catch (const UnderflowException& e) {
                cout << "Attempted to pop median from an empty tree." << endl;
            }
        } else { // Insert operation
            tree.insert(instruction);
        }
    }

    // Output all medians at once to minimize I/O operations.
    for (int median : medians) {
        cout << median << " ";
    }
    cout << endl;
}
/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myVector.cpp
*/

#include "myVector.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

// Function to insert an element into a sorted vector in a position that keeps the vector sorted
void insertSorted(std::vector<int> &vec, int value) {
    auto it = std::lower_bound(vec.begin(), vec.end(), value);
    vec.insert(it, value);
}

// Function to pop and print the median from a sorted vector
int popMedian(std::vector<int> &vec) {
    if (vec.empty()) return -1; // Return -1 if the vector is empty (should not happen in correct usage)

    size_t medianIndex = (vec.size() - 1) / 2; // Works for both even and odd sized vectors
    int median = vec[medianIndex];
    vec.erase(vec.begin() + medianIndex); // Remove the median
    return median;
}

void vectorMedian(const std::vector<int>* instructions) {
    std::vector<int> vec; // Vector to store the numbers in sorted order
    std::vector<int> medians; // Vector to store the medians that are popped

    for (int instruction : *instructions) {
        if (instruction == -1) {
            // Pop median operation
            int median = popMedian(vec);
            if (median != -1) { // If the vector was not empty
                medians.push_back(median);
            }
        } else {
            // Insert operation
            insertSorted(vec, instruction);
        }
    }

    // Print out all medians at once to minimize I/O operations
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
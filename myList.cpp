/*
Olti Gjoni
CSCI-335 PROJECT 2
DUE 04/10/24
myList.cpp
*/

#include "myList.hpp"
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <list>
#include <iostream>
#include <iterator> 

// Function to insert an element into a sorted list in a position that keeps the list sorted
void insertSorted(std::list<int> &lst, int value) {
    auto it = lst.begin();
    for (; it != lst.end() && *it < value; ++it);
    lst.insert(it, value);
}

// Function to pop and print the median from a sorted list
int popMedian(std::list<int> &lst) {
    if (lst.empty()) return -1; // Return -1 if the list is empty (should not happen in correct usage)

    size_t steps = (lst.size() - 1) / 2; // Works for both even and odd sized lists
    auto it = lst.begin();
    std::advance(it, steps); // Move iterator to the median's position
    int median = *it;
    lst.erase(it); // Remove the median
    return median;
}

void listMedian(const std::vector<int>* instructions) {
    std::list<int> lst; // List to store the numbers in sorted order
    std::vector<int> medians; // Vector to store the medians that are popped

    for (int instruction : *instructions) {
        if (instruction == -1) {
            // Pop median operation
            int median = popMedian(lst);
            if (median != -1) { // If the list was not empty
                medians.push_back(median);
            }
        } else {
            // Insert operation
            insertSorted(lst, instruction);
        }
    }

    // Print out all medians at once to minimize I/O operations
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
